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
 * Flash and EEPROM writes use RDY/BSY polling for recognized ISP targets;
 * other programming operations and unrecognized targets use a fixed 20 ms wait.
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
/** Clear cached target information before connecting to a different target. */
template <class SPI, class RST_PIN>
void AVR_ISP <SPI, RST_PIN> :: forget_target()
{
    target_signature = 0;
    target_supports_rdy_bsy = false;
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
    if(result == OK && request[0] == 0x30 && request[1] == 0 && request[2] < 3)
    {
        const uint8_t signature_index = request[2];
        const uint8_t shift = uint8_t(16 - 8 * signature_index);
        const uint32_t data_mask = uint32_t(0xFF) << shift;
        const uint32_t read_mask = uint32_t(1) << (24 + signature_index);
        target_signature = (target_signature & ~data_mask)
                         | (uint32_t(response[3]) << shift)
                         | read_mask;
        if((target_signature & 0x07000000UL) == 0x07000000UL)
        {
            target_supports_rdy_bsy = supports_rdy_bsy();
        }
    }
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
/** Check the known classic megaAVR/tinyAVR signatures with ISP RDY/BSY polling. */
template <class SPI, class RST_PIN>
bool AVR_ISP <SPI, RST_PIN> :: supports_rdy_bsy() const
{
    const uint32_t signature = target_signature & 0x00FFFFFFUL;
    switch(signature)
    {
    case 0x1E9007UL: // ATtiny13
    case 0x1E9108UL: // ATtiny25
    case 0x1E9109UL: // ATtiny26
    case 0x1E910AUL: // ATtiny2313
    case 0x1E910BUL: // ATtiny24
    case 0x1E910CUL: // ATtiny261
    case 0x1E9205UL: // ATmega48
    case 0x1E9206UL: // ATtiny45
    case 0x1E9207UL: // ATtiny44
    case 0x1E9208UL: // ATtiny461
    case 0x1E9209UL: // ATtiny48
    case 0x1E920AUL: // ATmega48P/PA
    case 0x1E9210UL: // ATmega48PB
    case 0x1E920DUL: // ATtiny4313
    case 0x1E920EUL: // ATtiny40
    case 0x1E9215UL: // ATtiny441
    case 0x1E930AUL: // ATmega88
    case 0x1E930BUL: // ATtiny85
    case 0x1E930CUL: // ATtiny84
    case 0x1E930DUL: // ATtiny861
    case 0x1E930FUL: // ATmega88P/PA
    case 0x1E9311UL: // ATtiny88
    case 0x1E9314UL: // ATtiny828
    case 0x1E9315UL: // ATtiny841
    case 0x1E9316UL: // ATmega88PB
    case 0x1E9401UL: // ATmega161
    case 0x1E9402UL: // ATmega163
    case 0x1E9403UL: // ATmega16
    case 0x1E9404UL: // ATmega162
    case 0x1E9405UL: // ATmega169
    case 0x1E9406UL: // ATmega168
    case 0x1E9407UL: // ATmega165P/PA
    case 0x1E940AUL: // ATmega164P
    case 0x1E940BUL: // ATmega168P/PA
    case 0x1E940FUL: // ATmega164A
    case 0x1E9410UL: // ATmega165
    case 0x1E9411UL: // ATmega169A
    case 0x1E9412UL: // ATtiny1634
    case 0x1E9415UL: // ATmega168PB
    case 0x1E9483UL: // AT90PWM316
    case 0x1E9487UL: // ATtiny167
    case 0x1E9488UL: // ATmega16U4
    case 0x1E9489UL: // ATmega16U2
    case 0x1E9502UL: // ATmega32
    case 0x1E9503UL: // ATmega329
    case 0x1E9504UL: // ATmega3290
    case 0x1E9505UL: // ATmega325
    case 0x1E9506UL: // ATmega3250
    case 0x1E9508UL: // ATmega324P
    case 0x1E950BUL: // ATmega329P/PA
    case 0x1E950CUL: // ATmega3290P/PA
    case 0x1E950DUL: // ATmega325P/PA
    case 0x1E950EUL: // ATmega3250P/PA
    case 0x1E950FUL: // ATmega328P
    case 0x1E9511UL: // ATmega324PA
    case 0x1E9514UL: // ATmega328
    case 0x1E9515UL: // ATmega324A
    case 0x1E9516UL: // ATmega328PB
    case 0x1E9517UL: // ATmega324PB
    case 0x1E9581UL: // AT90CAN32
    case 0x1E9584UL: // ATmega32M1
    case 0x1E9587UL: // ATmega32U4
    case 0x1E958AUL: // ATmega32U2
    case 0x1E9602UL: // ATmega64
    case 0x1E9603UL: // ATmega649
    case 0x1E9604UL: // ATmega6490
    case 0x1E9605UL: // ATmega645
    case 0x1E9606UL: // ATmega6450
    case 0x1E9608UL: // ATmega640
    case 0x1E9609UL: // ATmega644
    case 0x1E960AUL: // ATmega644P/PA
    case 0x1E960BUL: // ATmega649P
    case 0x1E960CUL: // ATmega6490P
    case 0x1E960DUL: // ATmega645P
    case 0x1E960EUL: // ATmega6450P
    case 0x1E9682UL: // AT90USB646
    case 0x1E9684UL: // ATmega64M1
    case 0x1E9702UL: // ATmega128
    case 0x1E9703UL: // ATmega1280
    case 0x1E9704UL: // ATmega1281
    case 0x1E9705UL: // ATmega1284P
    case 0x1E9706UL: // ATmega1284
    case 0x1E9781UL: // AT90CAN128
    case 0x1E9782UL: // AT90USB1286
    case 0x1E9801UL: // ATmega2560
    case 0x1E9802UL: // ATmega2561
        return true;
    default:
        return false;
    }
}
//------------------------------------------------------------------------------------------------
template <class SPI, class RST_PIN>
ResultCode AVR_ISP <SPI, RST_PIN> :: wait_for_programming_operation()
{
    if(!target_supports_rdy_bsy)
    {
        mdelay(programming_wait_ms);
        return OK;
    }

    for(uint8_t elapsed = 0; elapsed <= programming_wait_ms; ++elapsed)
    {
        uint8_t status;
        ResultCode result = instruction(0xF0, 0, 0, 0, &status);
        if(result != OK)
            return result;
        if(!(status & 0x01))
            return OK;
        if(elapsed < programming_wait_ms)
            mdelay(1);
    }
    return ERR_UNKNOWN;
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

    // An odd start needs its own high-byte read to reach the next word.
    if(size && (address & 1))
    {
        ResultCode result = select_address(address);
        if(result != OK)
            return result;

        result = instruction(0x28, uint8_t(address >> 9), uint8_t(address >> 1), 0, data);
        if(result != OK)
            return result;
        ++address;
        ++data;
        --size;
    }

    // Read both bytes of each word in one uninterrupted SPI transfer.
    while(size >= 2)
    {
        ResultCode result = select_address(address);
        if(result != OK)
            return result;

        const uint8_t address_high = uint8_t(address >> 9);
        const uint8_t address_low = uint8_t(address >> 1);
        const uint8_t request[8] = {
            0x20, address_high, address_low, 0,
            0x28, address_high, address_low, 0
        };
        uint8_t response[8];
        result = SPI :: duplex(request, response, sizeof(request));
        if(result != OK)
            return result;

        data[0] = response[3];
        data[1] = response[7];
        address += 2;
        data += 2;
        size -= 2;
    }

    if(size)
    {
        ResultCode result = select_address(address);
        if(result != OK)
            return result;

        return instruction(0x20, uint8_t(address >> 9), uint8_t(address >> 1), 0, data);
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
        result = wait_for_programming_operation();
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
        result = wait_for_programming_operation();
        if(result != OK)
            return result;
    }
    return OK;
}
