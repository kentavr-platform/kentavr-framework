#ifndef ONEWIRE_H
#define ONEWIRE_H
//------------------------------------------------------------------------------------------------
struct OneWireAddress
{
    uint8_t data[8];
    uint8_t family()    const { return data[0]; }
    uint8_t crc()       const { return data[7]; }
};
//------------------------------------------------------------------------------------------------
template <class pin>
class OneWireBus
{
public:
    uint8_t     reset();
    bool        busy();
    bool        find_first(struct OneWireAddress &addr);
    bool        find_next(OneWireAddress &addr);
    bool        find_alarm(OneWireAddress &addr);
    void        find_reset();
    bool        select_device(const OneWireAddress &addr);
    bool        start_broadcast();
    uint64_t    read_single_address();
    uint8_t     read_byte();
    uint16_t    read_word();
    void        write_byte(uint8_t data);
    ResultCode  last_error();
private:
    bool        _find(OneWireAddress &addr, uint8_t mode);
    void        _pull_down(uint16_t delay);
    void        _write_one();
    void        _write_zero();
    uint8_t     _read_bit();
    void        _write_bit(uint8_t bit);
    uint8_t     _last_discrepancy = 0;
    bool        _last_device = false;
    ResultCode  _last_error = ERR_UNKNOWN;

};
//------------------------------------------------------------------------------------------------
uint8_t Dallas_CRC8(const uint8_t *data, uint8_t len);
//------------------------------------------------------------------------------------------------
#include "one-wire.tpp"
//------------------------------------------------------------------------------------------------
#endif // ONEWIRE_H

/*
class OneWire
{
public:

    bool search_begin()
    {
        _last_discrepancy = 0;
        _last_device = false;
        return true;
    }

    // rom must point to 8-byte buffer
    bool search_next(uint8_t* rom)
    {
        if(_last_device)
            return false;

        if(reset())
            return false;

        write_byte(0xF0); // SEARCH ROM

        uint8_t bit_index = 1;
        uint8_t rom_byte = 0;
        uint8_t rom_mask = 1;

        uint8_t discrepancy_marker = 0;

        while(bit_index <= 64)
        {
            uint8_t bit0 = read_bit();
            uint8_t bit1 = read_bit();

            // no devices
            if(bit0 && bit1)
                return false;

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
                    selected_bit = (rom[rom_byte] & rom_mask) ? 1 : 0;
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
                    discrepancy_marker = bit_index;
            }

            // store selected bit
            if(selected_bit)
                rom[rom_byte] |= rom_mask;
            else
                rom[rom_byte] &= ~rom_mask;

            write_bit(selected_bit);

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
            _last_device = true;

        return true;
    }

private:

    uint8_t _last_discrepancy = 0;
    bool    _last_device = false;

private:

    bool reset();
    void write_bit(uint8_t bit);
    uint8_t read_bit();
    void write_byte(uint8_t value);
};
*/
