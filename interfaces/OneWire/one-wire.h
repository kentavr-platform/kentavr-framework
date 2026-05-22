#ifndef ONEWIRE_H
#define ONEWIRE_H
//------------------------------------------------------------------------------------------------
/**
 * @brief 1-Wire device address
 *
 * 64-bit unique identifier
 */
struct OneWireAddress
{
    uint8_t data[8] = {0};
    uint8_t family()    const { return data[0]; }
    uint8_t crc()       const { return data[7]; }
};
//------------------------------------------------------------------------------------------------
/**
 * @brief 1-Wire bus driver
 *
 * Software bit-banged implementation
 *
 * Provides:
 *  - Bus reset / presence detection
 *  - ROM search algorithm (enumeration)
 *  - Device selection (MATCH ROM / SKIP ROM)
 *  - Low-level read / write primitives
 *
 * @tparam pin GPIO pin for bus communication.
 */
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
    void        find_reset(OneWireAddress &addr);
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
// special type-trait
template <class Type> struct is_OneWireBus : false_type {};
template <class pin>  struct is_OneWireBus <OneWireBus<pin>>  : true_type {};
//------------------------------------------------------------------------------------------------
#include "one-wire.tpp"
//------------------------------------------------------------------------------------------------
#endif
