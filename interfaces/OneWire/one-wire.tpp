//------------------------------------------------------------------------------------------------
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
    // wait for the bus to become free
    while(!GPIO <pin> :: read());

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
    ATOMIC_BLOCK
    {
        _pull_down(1);
        udelay(2);
        int8_t tmp = GPIO <pin> :: read();
        udelay(70 - 1);
        return tmp;
    }
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
template <class pin>
__inline uint8_t OneWireBus <pin> :: reset()
{
    ATOMIC_BLOCK
    {
        _pull_down(500);
        udelay(70);
        uint8_t tmp = GPIO <pin> :: read();
        udelay(500 - 70);
        return tmp;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * Returns true while one or more 1-Wire devices
 * are performing temperature conversion.
 *
 * Valid after CONVERT T command.
 *
 * For externally powered devices only.
 */
template <class pin>
__inline bool OneWireBus <pin> :: busy()
{
    return _read_bit() == 0;
}
//------------------------------------------------------------------------------------------------
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
template <class pin>
__inline uint8_t OneWireBus <pin> :: read_byte()
{
    uint8_t tmp = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        tmp >>= 1;
        tmp |= _read_bit() ? 0x80 : 0;
    }
    return tmp;
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline uint16_t OneWireBus <pin> :: read_word()
{
    uint8_t tmp = 0;
    for(uint8_t i = 0; i < 16; i++)
    {
        tmp >>= 1;
        tmp |= _read_bit() ? 0x8000 : 0;
    }
    return tmp;
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline bool OneWireBus <pin> :: find_first(OneWireAddress &addr)
{
    find_reset();
    return find_next(addr);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline bool OneWireBus <pin> :: find_next(OneWireAddress &addr)
{
    return _find(addr, 0xF0);  // ‎CMD ROM SEARCH
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline bool OneWireBus <pin> :: find_alarm(OneWireAddress &addr)
{
    return _find(addr, 0xEC);  // ‎CMD ALARM SEARCH
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void OneWireBus <pin> :: find_reset()
{
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
                selected_bit = (addr.data[rom_byte] & rom_mask) ? 1 : 0;
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
            addr.data[rom_byte] |= rom_mask;
        }
        else
        {
            addr.data[rom_byte] &= ~rom_mask;
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

    if(Dallas_CRC8(addr.data, 7) != addr.crc())
    {
        _last_error = ERR_BAD_CHECKSUM;
        return false;
    }

    _last_error = OK;
    return true;
}
//------------------------------------------------------------------------------------------------
// select device without presense guarantee
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
// select device without presense guarantee
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
template <class pin>
__inline ResultCode OneWireBus <pin> :: last_error()
{
    return _last_error;
}
//------------------------------------------------------------------------------------------------



