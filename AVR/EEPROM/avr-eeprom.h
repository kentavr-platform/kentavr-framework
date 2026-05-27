#ifndef AVR_EEPROM_H
#define AVR_EEPROM_H
#include <avr/eeprom.h>
//------------------------------------------------------------------------------------------------
class EEPROM_Storage
{
public:
    using offset_t = uint16_t;

    ResultCode read(offset_t addr, void *data, size_t size)
    {
        eeprom_read_block(data, reinterpret_cast <const void*> (addr), size);
        return OK;
    }

    ResultCode write(offset_t addr, const void *data, size_t size)
    {
        eeprom_update_block(data, reinterpret_cast <void*> (addr), size);
        return OK;
    }

    template <class Type>
    ResultCode read(offset_t addr, Type &value)
    {
        return read(addr, &value, sizeof(Type));
    }

    template <class Type>
    ResultCode write(offset_t addr, const Type &value)
    {
        return write(addr, &value, sizeof(Type));
    }
} EEPROM;
//------------------------------------------------------------------------------------------------
#endif
