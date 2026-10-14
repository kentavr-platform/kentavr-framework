/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-isp.tpp
 * Included from avr-isp.h; do not compile separately.
//----------------------------------------------------------------------------------------------*/
/**
 * @class AVR_ISP
 * @brief In-System Programming session over an SPI master interface.
 *
 * The target is held in reset while programming. ISP commands are four-byte
 * transfers; command and response buffers passed to command() must each hold
 * exactly four bytes. Flash addresses exposed by this interface are byte
 * addresses. Page geometry remains the responsibility of the caller.
 * Calls wait for interrupt-driven SPI transfers and require enabled interrupts;
 * do not call them from an ISR. Reserve the SPI bus for the entire session.
 * Target programming times must not exceed the fixed 20 ms write/erase wait
 * used by this driver.
 * Include through core.h so GPIO and the target pin types are available.
 *
 * @tparam SPI SPI peripheral type configured as master.
 * @tparam RST_PIN GPIO pin connected to the target RESET line.
 */
/** Configure the SPI master rate and release the target from reset. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: init(uint32_t frequency)
{
    if(active) return ERR_BUSY;
    ResultCode result = SPI :: init_master(frequency, SPI_CLOCK_MODE_0, SPI_MSB_FIRST);
    if(result != OK) return result;
    GPIO <RST_PIN> :: set_mode(OUTPUT_HIGH);
    initialized = true;
    extended_address = 0;
    return OK;
}
//------------------------------------------------------------------------------------------------
/** Assert target reset and enter programming mode. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: enter_programming_mode()
{
    if(!initialized)
        return ERR_BAD_MODE;

    if(active)
        return OK;

    if(SPI :: is_busy())
        return ERR_BUSY;

    const uint8_t request[4] = {0xAC, 0x53, 0, 0};
    uint8_t response[4];
    ResultCode result = ERR_REJECTED;

    for(uint8_t attempt = 0; attempt < enable_attempts; ++attempt)
    {
        GPIO <RST_PIN> :: write_high();
        mdelay(reset_pulse_ms);
        GPIO <RST_PIN> :: write_low();
        mdelay(reset_wait_ms);
        extended_address = 0;
        result = SPI :: duplex(request, response, 4);
        if(result != OK)
            break;
        if(response[2] == 0x53)
        {
            active = true;
            return OK;
        }
        result = ERR_REJECTED;
    }
    GPIO <RST_PIN> :: write_high();
    return result;
}
//------------------------------------------------------------------------------------------------
/** Release target reset and leave programming mode. */
template <class SPI, class RST_PIN>
void AVR_ISP <SPI, RST_PIN> :: leave_programming_mode()
{
    if(initialized)
        GPIO <RST_PIN> :: write_high();
    active = false;
    extended_address = 0;
}
//------------------------------------------------------------------------------------------------
/** Execute one raw four-byte AVR ISP instruction during programming mode. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: command(const uint8_t request[4], uint8_t response[4])
{
    if(!active)
        return ERR_BAD_MODE;

    if(!request || !response)
        return ERR_BAD_PARAMETER;

    // Save before transfer: callers may use the same buffer for TX and RX.
    const bool extended = (request[0] == 0x4D);
    const uint8_t bank = request[2];
    ResultCode result = SPI :: duplex(request, response, 4);
    if(result == OK && extended)
        extended_address = bank;
    return result;
}
//------------------------------------------------------------------------------------------------
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: instruction(uint8_t a, uint8_t b, uint8_t c,
                                               uint8_t d, uint8_t *value)
{
    const uint8_t request[4] = {a, b, c, d};
    uint8_t response[4];
    ResultCode result = command(request, response);
    if(result == OK && value)
        *value = response[3];
    return result;
}
//------------------------------------------------------------------------------------------------
/** Erase the target chip. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: chip_erase()
{
    ResultCode result = instruction(0xAC, 0x80, 0, 0);
    if(result != OK)
        return result;
    mdelay(programming_wait_ms);

    // Old targets (including ATmega8) require a reset pulse after chip erase command
    active = false;
    return enter_programming_mode();
}
//------------------------------------------------------------------------------------------------
/** Read the complete three-byte device signature. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: read_signature(uint8_t signature[3])
{
    if(!signature)
        return ERR_BAD_PARAMETER;

    for(uint8_t i = 0; i < 3; ++i)
    {
        ResultCode result = instruction(0x30, 0, i, 0, signature + i);
        if(result != OK)
            return result;
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/** Read the low, high, or extended fuse byte. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: read_fuse(AVR_ISP_Fuse fuse, uint8_t &value)
{
    switch(fuse)
    {
    case AVR_ISP_FUSE_LOW:
        return instruction(0x50, 0x00, 0, 0, &value);
    case AVR_ISP_FUSE_HIGH:
        return instruction(0x58, 0x08, 0, 0, &value);
    case AVR_ISP_FUSE_EXTENDED:
        return instruction(0x50, 0x08, 0, 0, &value);
    }
    return ERR_BAD_PARAMETER;
}
//------------------------------------------------------------------------------------------------
/** Write the low, high, or extended fuse byte. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: write_fuse(AVR_ISP_Fuse fuse, uint8_t value)
{
    uint8_t opcode;
    switch(fuse)
    {
    case AVR_ISP_FUSE_LOW:
        opcode = 0xA0;
        break;
    case AVR_ISP_FUSE_HIGH:
        opcode = 0xA8;
        break;
    case AVR_ISP_FUSE_EXTENDED:
        opcode = 0xA4;
        break;
    default:
        return ERR_BAD_PARAMETER;
    }
    ResultCode result = instruction(0xAC, opcode, 0, value);
    if(result == OK)
        mdelay(programming_wait_ms);
    return result;
}
//------------------------------------------------------------------------------------------------
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: select_address(uint32_t address)
{
    const uint8_t bank = uint8_t(address >> 17);
    if(bank == extended_address)
        return OK;
    return instruction(0x4D, 0, bank, 0);
}
//------------------------------------------------------------------------------------------------
/** Read target Flash bytes using a byte address. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: read_flash(uint32_t address, uint8_t *data, uint16_t size)
{
    if(!active) return ERR_BAD_MODE;
    // ISP has a 24-bit word address (including the extended address byte).
    if((size && !data) || address > 0x2000000UL || size > 0x2000000UL - address)
        return ERR_BAD_PARAMETER;
    for(uint16_t i = 0; i < size; ++i, ++address)
    {
        ResultCode result = select_address(address);
        if(result != OK)
            return result;

        result = instruction((address & 1) ? 0x28 : 0x20,
                             uint8_t(address >> 9), uint8_t(address >> 1), 0, data + i);
        if(result != OK)
            return result;
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * Write one complete, page-aligned target Flash page after chip erase.
 * page_size is the target's actual power-of-two page size in bytes.
 */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: write_flash_page(uint32_t address, const uint8_t *data,
                                                      uint16_t page_size)
{
    if(!active)
        return ERR_BAD_MODE;

    if(!data || page_size < 2 || (page_size & (page_size - 1)) ||
       (address & (page_size - 1)) || address >= 0x2000000UL ||
       page_size > 0x2000000UL - address)
        return ERR_BAD_PARAMETER;

    ResultCode result = select_address(address);
    if(result != OK)
        return result;
    for(uint16_t offset = 0; offset < page_size; offset += 2)
    {
        // Load each low byte before the corresponding high byte.
        result = instruction(0x40, uint8_t(offset >> 9), uint8_t(offset >> 1), data[offset]);
        if(result != OK)
            return result;

        result = instruction(0x48, uint8_t(offset >> 9), uint8_t(offset >> 1), data[offset + 1]);
        if(result != OK)
            return result;
    }
    result = instruction(0x4C, uint8_t(address >> 9), uint8_t(address >> 1), 0);
    if(result == OK)
        mdelay(programming_wait_ms);
    return result;
}
//------------------------------------------------------------------------------------------------
/** Read target EEPROM bytes using a byte address. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: read_eeprom(uint16_t address, uint8_t *data,
                                               uint16_t size)
{
    if(!active)
        return ERR_BAD_MODE;

    if((size && !data) || uint32_t(address) + size > 0x10000UL)
        return ERR_BAD_PARAMETER;

    for(uint16_t i = 0; i < size; ++i, ++address)
    {
        ResultCode result = instruction(0xA0, uint8_t(address >> 8), uint8_t(address), 0, data + i);
        if(result != OK)
            return result;
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/** Write target EEPROM bytes using a byte address. */
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: write_eeprom(uint16_t address, const uint8_t *data,
                                                  uint16_t size)
{
    if(!active)
        return ERR_BAD_MODE;

    if((size && !data) || uint32_t(address) + size > 0x10000UL)
        return ERR_BAD_PARAMETER;

    for(uint16_t i = 0; i < size; ++i, ++address)
    {
        ResultCode result = instruction(0xC0, uint8_t(address >> 8), uint8_t(address), data[i]);
        if(result != OK)
            return result;
        mdelay(programming_wait_ms);
    }
    return OK;
}
