/*------------------------------------------------------------------------------------------------
 * AVR/avr-gpio.h
 *
 *  This file contains hardware-specific GPIO implementation.
 *
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_GPIO_H
#define AVR_GPIO_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
enum GPIO_mode
{
    /// Set pin as input and leave opened
    INPUT_OPEN      = 1,
    /// Set pin as input with internal pull-up
    INPUT_PULLUP    = 2,
    /// Set pin as output and set high level
    OUTPUT_HIGH     = 3,
    /// Set pin as output and set low level
    OUTPUT_LOW      = 4,
};
//------------------------------------------------------------------------------------------------
template <
    volatile uint8_t port_addr,
    volatile uint8_t dir_addr,
    volatile uint8_t pin_addr,
    uint8_t bit>
struct pin
{
    static constexpr uint8_t PORT  = port_addr;
    static constexpr uint8_t DDR   = dir_addr;
    static constexpr uint8_t PIN   = pin_addr;
    static constexpr uint8_t BIT   = bit;
};
//------------------------------------------------------------------------------------------------
template <class pin>
struct GPIO
{
public:
    static void     set_mode(enum GPIO_mode);
    static void     write_high();
    static void     write_low();
    static void     toggle();
    static uint8_t  read();
};
//------------------------------------------------------------------------------------------------
#include "avr-gpio.tpp"     // "dirty" class template implementation
//------------------------------------------------------------------------------------------------
#endif
