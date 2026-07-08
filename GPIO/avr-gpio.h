/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-gpio.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_GPIO_H
#define AVR_GPIO_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include "pins.h"
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
// not connected (dummy) pin
template <>
struct GPIO <NC>
{
    static __inline void set_mode(GPIO_mode) {}
    static __inline void write_high() {}
    static __inline void write_low() {}
    static __inline void toggle() {}
    static __inline uint8_t read() { return 0; }
};
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(GPIO);
//------------------------------------------------------------------------------------------------
#include "core/type_traits/is_connected.h"
#include "avr-gpio.tpp"
//------------------------------------------------------------------------------------------------
#endif
