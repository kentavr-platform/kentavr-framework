/*------------------------------------------------------------------------------------------------
 * one-wire.tpp
 *
 * ATTENTION! This file is included from one-wire.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
uint8_t Dallas_CRC8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;
    for(uint8_t i = 0; i < len; i++)
    {
        uint8_t inbyte = data[i];
        for(uint8_t j = 0; j < 8; j++)
        {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if(mix)
            {
                crc ^= 0x8C;
            }
            inbyte >>= 1;
        }
    }
    return crc;
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void OneWireBus <pin> :: _pull_down(uint16_t delay)
{
    // attach to the bus and release it after delay
    GPIO <pin> :: set_mode(OUTPUT_LOW);
    udelay(delay);
    GPIO <pin> :: set_mode(INPUT_OPEN);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void OneWireBus <pin> :: _write_one()
{
    _pull_down(10);
    udelay(70 - 10);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void OneWireBus <pin> :: _write_zero()
{
    _pull_down(70);
    udelay(2);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline uint8_t OneWireBus <pin> :: _read_bit()
{
    int8_t tmp = 0;
    ATOMIC_BLOCK
    {
        _pull_down(1);
        udelay(2);
        tmp = GPIO <pin> :: read();
        udelay(70 - 1);
    }
    return tmp;
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void OneWireBus <pin> :: _write_bit(uint8_t bit)
{
    ATOMIC_BLOCK
    {
        if(bit)
        {
            _write_one();
        }
        else
        {
            _write_zero();
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Sends reset pulse and checks for device presence.
 *
 * @return 0 if at least one device responded (presence detected),
 *         1 if no devices are present.
 *
 * @note 1-Wire presence pulse is active LOW.
 */
template <class pin>
__inline uint8_t OneWireBus <pin> :: reset()
{
    _pull_down(480);
    udelay(70);
    uint8_t tmp = GPIO <pin> :: read();
    udelay(480 - 70 + 5);
    return tmp;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Checks if any device is currently performing conversion.
 *
 * Valid after CONVERT T command.
 *
 * @return true if bus reads LOW (device busy),
 *         false otherwise.
 *
 * @note VFor externally powered devices only.
 */
template <class pin>
__inline bool OneWireBus <pin> :: busy()
{
    return _read_bit() == 0;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes a byte to 1-Wire bus (LSB-first).
 *
 * @param data Byte to transmit.
 */
template <class pin>
__inline void OneWireBus <pin> :: write_byte(uint8_t data)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        if(data & 0x01)
        {
            _write_one();
        }
        else
        {
            _write_zero();
        }
        data >>= 1;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads a single byte from 1-Wire bus (LSB-first).
 *
 * @return Received byte.
 */
template <class pin>
__inline uint8_t OneWireBus <pin> :: read_byte()
{
    uint8_t tmp = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        tmp |= (_read_bit() << i);
    }
    return tmp;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads a 16-bit word from 1-Wire bus.
 *
 * @return Received word (LSB-first).
 */
template <class pin>
__inline uint16_t OneWireBus <pin> :: read_word()
{
    uint16_t tmp = 0;
    for(uint8_t i = 0; i < 16; i++)
    {
        tmp |= (_read_bit() << i);
    }
    return tmp;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Starts ROM search and returns first discovered device.
 *
 * @param addr Output ROM address.
 * @return true if device found, false otherwise.
 */
template <class pin>
__inline bool OneWireBus <pin> :: find_first(OneWireAddress &addr)
{
    find_reset(addr);
    return find_next(addr);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Continues ROM search to find next device.
 *
 * @param addr Output ROM address.
 * @return true if next device found, false if no more devices exist.
 */
template <class pin>
__inline bool OneWireBus <pin> :: find_next(OneWireAddress &addr)
{
    return _find(addr, 0xF0);  // ‎CMD ROM SEARCH
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Searches for devices in alarm state (ALARM SEARCH command).
 *
 * @param addr Output ROM address.
 * @return true if alarm device found.
 */
template <class pin>
__inline bool OneWireBus <pin> :: find_alarm(OneWireAddress &addr)
{
    return _find(addr, 0xEC);  // ‎CMD ALARM SEARCH
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Resets ROM search state machine.
 *
 * Must be called before starting a new enumeration sequence.
 *
 * @param addr ROM address buffer to be cleared before next search starts.
 *
 * @note Application should provide a clear address for next search call.
 */
template <class pin>
__inline void OneWireBus <pin> :: find_reset()
{
    _last_discrepancy = 0;
    _last_device = false;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Resets ROM search state machine and prepairs OneWireAddress for
 * the new search after a previous one.
 *
 * Must be called before starting a new enumeration sequence.
 *
 * @param addr ROM address buffer to be cleared before next search starts.
 */
template <class pin>
__inline void OneWireBus <pin> :: find_reset(OneWireAddress &addr)
{
    addr = {0};
    _last_discrepancy = 0;
    _last_device = false;
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline bool OneWireBus <pin> :: _find(OneWireAddress &addr, uint8_t mode)
{
    if(_last_device)
    {
        // no more devices
        _last_error = ERR_NO_MORE;
        return false;
    }

    if(reset())
    {
        // no devices at all
        _last_error = ERR_NOT_FOUND;
        return false;
    }

    write_byte(mode);

    uint8_t bit_index = 1;
    uint8_t rom_byte = 0;
    uint8_t rom_mask = 1;
    uint8_t discrepancy_marker = 0;
    uint8_t saved_discrepancy = _last_discrepancy;
    bool saved_last_device = _last_device;
    OneWireAddress path = addr;

    while(bit_index <= 64)
    {
        uint8_t bit0 = _read_bit();
        uint8_t bit1 = _read_bit();

        // no devices
        if(bit0 && bit1)
        {
            _last_error = ERR_NOT_FOUND;
            return false;
        }

        uint8_t selected_bit;

        if(bit0 != bit1)
        {
            // only one possible direction
            selected_bit = bit1 ? 0 : 1;
        }
        else
        {
            // discrepancy
            if(bit_index < _last_discrepancy)
            {
                // follow previous path
                selected_bit = (path.data[rom_byte] & rom_mask) ? 1 : 0;
            }
            else if(bit_index == _last_discrepancy)
            {
                // switch direction
                selected_bit = 1;
            }
            else
            {
                // first visit
                selected_bit = 0;
            }

            if(selected_bit == 0)
            {
                discrepancy_marker = bit_index;
            }
        }

        // store selected bit
        if(selected_bit)
        {
            path.data[rom_byte] |= rom_mask;
        }
        else
        {
            path.data[rom_byte] &= ~rom_mask;
        }
        _write_bit(selected_bit);

        bit_index++;

        rom_mask <<= 1;

        if(rom_mask == 0)
        {
            rom_mask = 1;
            rom_byte++;
        }
    }
    _last_discrepancy = discrepancy_marker;
    if(_last_discrepancy == 0)
    {
        _last_device = true;
    }

    if(Dallas_CRC8(path.data, 7) != path.crc())
    {
        _last_discrepancy = saved_discrepancy;
        _last_device = saved_last_device;
        _last_error = ERR_BAD_CHECKSUM;
        return false;
    }
    addr = path;
    _last_error = OK;
    return true;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Selects a specific device by its address.
 *
 * @param addr Target device address.
 *
 * @return true if bus reset succeeded and command was sent.
 *
 * @note Does not verify device presence after selection.
 */
template <class pin>
__inline bool OneWireBus <pin> :: select_device(const OneWireAddress &addr)
{
    if(reset())
    {
        // no devices
        _last_error = ERR_NOT_FOUND;
        return false;
    }
    write_byte(0x55);   // CMD MATCH ROM
    for(uint8_t i = 0; i < 8; i++)
    {
        write_byte(addr.data[i]);
    }
    return true;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Selects all devices on the bus (broadcast mode).
 *
 * The next command will be processed by all the devices
 * (if supported).
 *
 * @return true if bus reset succeeded.
 */
template <class pin>
__inline bool OneWireBus <pin> :: start_broadcast()
{
    if(reset())
    {
        // no devices
        _last_error = ERR_NOT_FOUND;
        return false;
    }
    write_byte(0xCC);   // CMD SKIP ROM
    return true;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Returns last bus operation error code.
 *
 * @return ResultCode of last operation.
 */
template <class pin>
__inline ResultCode OneWireBus <pin> :: last_error()
{
    return _last_error;
}
//------------------------------------------------------------------------------------------------



