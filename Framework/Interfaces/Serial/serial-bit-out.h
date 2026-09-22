/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: serial-bit-out.h
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Bit-banged software UART transmitter (TX only).
 *
 * Implements a fully software UART transmitter using a single GPIO pin.
 * Timing is cycle-accurate and depends on F_CPU and baud rate at compile time.
 *
 * @tparam pin  GPIO pin descriptor (must provide PORT and BIT definitions)
 * @tparam baud Transmission baud rate (compile-time constant)
 *
 * @note This implementation is timing-critical and must not be modified
 *       without re-verifying generated assembly cycle counts.
 *
 * @note Interrupts are disabled during any transmission to guarantee timing.
 */
 //------------------------------------------------------------------------------------------------
#ifndef SERIAL_BITOUT_H
#define SERIAL_BITOUT_H
//------------------------------------------------------------------------------------------------
template <class pin, uint32_t baud>
class SerialBitOut
{
public:
                SerialBitOut();
    void        write(uint8_t data);
    void        write(const char *str);
    void        write_all(const char *str);
    void        write(FlashStringWrapper fs);
    void        tx_wait() {}
private:
    void        _write_char(uint8_t data);
    static constexpr uint8_t _bit_cycles = 8;
    static constexpr uint32_t _bit_delay = (F_CPU + baud / 2) / baud - _bit_cycles;
};
//------------------------------------------------------------------------------------------------
template <class pin, uint32_t baud>
FlashStringWrapper console_type_name(const SerialBitOut <pin, baud> &)
{
    return _flash("SerialBitOut");
}
//------------------------------------------------------------------------------------------------
#include "serial-bit-out.tpp"
//------------------------------------------------------------------------------------------------
#endif // SERIAL_BITOUT_H
