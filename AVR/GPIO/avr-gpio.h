/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-gpio.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_GPIO_H
#define AVR_GPIO_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
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
enum INT_mode
{
    INT_LOW_LEVEL,
    INT_ANY_CHANGE,
    INT_FALLING,
    INT_RISING
};
//------------------------------------------------------------------------------------------------
template <class pin>
struct GPIO
{
public:
    static void         set_mode(enum GPIO_mode);
    static GPIO_mode    get_mode();
    static void         write_high();
    static void         write_low();
    static void         toggle();
    static uint8_t      read();
    static inline void  enable_int(INT_mode mode = INT_ANY_CHANGE);
    static inline void  disable_int();
    static inline void  enable_pcint();
    static inline void  claim_pcint();
    static inline void  disable_pcint();
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
    static __inline GPIO_mode get_mode() { return INPUT_OPEN; }
    static __inline uint8_t read() { return 0; }
    static __inline void enable_int(INT_mode) {}
    static __inline void disable_int() {}
    static __inline void enable_pcint() {}
    static __inline void claim_pcint() {}
    static __inline void disable_pcint() {}
};
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(GPIO);
//------------------------------------------------------------------------------------------------
#include "../../Core/type_traits/is_connected.h"
#include "avr-gpio.tpp"
//------------------------------------------------------------------------------------------------
#endif
