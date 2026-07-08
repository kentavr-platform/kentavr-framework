/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: led.h
//----------------------------------------------------------------------------------------------*/
/**
 * @file led.h
 * @brief LED drivers.
 *
 * This module contains drivers for:
 * - LED_C       single cathode-driven LED
 * - LED_A       single anode-driven LED
 * - RG_LED_CA   bicolor common anode red-green LED
 * - RG_LED_CC   bicolor common cathode red-green LED
 * - RB_LED_CA   bicolor common anode red-blue LED
 * - RB_LED_CC   bicolor common cathode red-blue LED
 * - GB_LED_CA   bicolor common anode green-blue LED
 * - GB_LED_CC   bicolor common cathode green-blue LED
 * - RGB_LED_CA  tricolor common anode red-green-blue (RGB) LED
 * - RGB_LED_CC  tricolor common cathode red-green-blue (RGB) LED
 */
#ifndef LED_H
#define LED_H
//------------------------------------------------------------------------------------------------
#include "GPIO/avr-gpio.h"
//------------------------------------------------------------------------------------------------
/// Single anode-driven LED
template <class pin>
class LED_A
{
public:
    LED_A()                 { GPIO <pin> :: set_mode(OUTPUT_LOW); }
    __inline void on()      { GPIO <pin> :: write_high(); }
    __inline void off()     { GPIO <pin> :: write_low(); }
    __inline void toggle()  { GPIO <pin> :: toggle(); }
};
//------------------------------------------------------------------------------------------------
/// Single cathode-driven LED
template <class pin>
class LED_C
{
public:
    LED_C()                 { GPIO <pin> :: set_mode(OUTPUT_HIGH); }
    __inline void on()      { GPIO <pin> :: write_low(); }
    __inline void off()     { GPIO <pin> :: write_high(); }
    __inline void toggle()  { GPIO <pin> :: toggle(); }
};
//------------------------------------------------------------------------------------------------
/*
 *      COMMON CATHODE multi-LEDs
 *
 *----------------------------------------------------------------------------------------------*/
/// Common cathode bicolor LED (protected, for inheritance only)
template <class pinA, class pinB>
class BiLED_CC
{
public:
    void off();
protected:
    BiLED_CC();
    void on_A();
    void on_B();
    void on_AB();
};
//------------------------------------------------------------------------------------------------
/// Common cathode red-green bicolor LED
template <class pinA, class pinB>
class RG_LED_CC : public BiLED_CC <pinA, pinB>
{
public:
    __inline void on_red()      { BiLED_CC <pinA, pinB> :: on_A();  }
    __inline void on_green()    { BiLED_CC <pinA, pinB> :: on_B();  }
    __inline void on_yellow()   { BiLED_CC <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common cathode red-blue bicolor LED
template <class pinA, class pinB>
class RB_LED_CC : public BiLED_CC <pinA, pinB>
{
public:
    __inline void on_red()      { BiLED_CC <pinA, pinB> :: on_A();  }
    __inline void on_blue()     { BiLED_CC <pinA, pinB> :: on_B();  }
    __inline void on_magenta()  { BiLED_CC <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common cathode green-blue bicolor LED
template <class pinA, class pinB>
class GB_LED_CC : public BiLED_CC <pinA, pinB>
{
public:
    __inline void on_green()    { BiLED_CC <pinA, pinB> :: on_A();  }
    __inline void on_blue()     { BiLED_CC <pinA, pinB> :: on_B();  }
    __inline void on_cyan()     { BiLED_CC <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common cathode RGB LED
template <class pinR, class pinG, class pinB>
class RGB_LED_CC
{
public:
    RGB_LED_CC();
    void on_red();
    void on_green();
    void on_blue();
    void on_yellow();
    void on_magenta();
    void on_cyan();
    void on_white();
    void off();
};
//------------------------------------------------------------------------------------------------
/*
 *      COMMON ANODE multi-LEDs
 *
 *----------------------------------------------------------------------------------------------*/
/// Common anode bicolor LED (protected, for inheritance only)
template <class pinA, class pinB>
class BiLED_CA
{
public:
    void off();
protected:
    BiLED_CA();
    void on_A();
    void on_B();
    void on_AB();
};
//------------------------------------------------------------------------------------------------
/// Common anode red-green bicolor LED
template <class pinA, class pinB>
class RG_LED_CA : public BiLED_CA <pinA, pinB>
{
public:
    __inline void on_red()      { BiLED_CA <pinA, pinB> :: on_A();  }
    __inline void on_green()    { BiLED_CA <pinA, pinB> :: on_B();  }
    __inline void on_yellow()   { BiLED_CA <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common anode red-blue bicolor LED
template <class pinA, class pinB>
class RB_LED_CA : public BiLED_CA <pinA, pinB>
{
public:
    __inline void on_red()      { BiLED_CA <pinA, pinB> :: on_A();  }
    __inline void on_blue()     { BiLED_CA <pinA, pinB> :: on_B();  }
    __inline void on_magenta()  { BiLED_CA <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common anode green-blue bicolor LED
template <class pinA, class pinB>
class GB_LED_CA : public BiLED_CA <pinA, pinB>
{
public:
    __inline void on_green()    { BiLED_CA <pinA, pinB> :: on_A();  }
    __inline void on_blue()     { BiLED_CA <pinA, pinB> :: on_B();  }
    __inline void on_cyan()     { BiLED_CA <pinA, pinB> :: on_AB(); }
};
//------------------------------------------------------------------------------------------------
/// Common anode RGB LED
template <class pinR, class pinG, class pinB>
class RGB_LED_CA
{
public:
    RGB_LED_CA();
    void on_red();
    void on_green();
    void on_blue();
    void on_yellow();
    void on_magenta();
    void on_cyan();
    void on_white();
    void off();
};
//------------------------------------------------------------------------------------------------
// console namers:
SET_CONSOLE_TEMPLATE_TYPE_NAME(LED_A);
SET_CONSOLE_TEMPLATE_TYPE_NAME(LED_C);

SET_CONSOLE_TEMPLATE_TYPE_NAME(RG_LED_CC);
SET_CONSOLE_TEMPLATE_TYPE_NAME(RB_LED_CC);
SET_CONSOLE_TEMPLATE_TYPE_NAME(GB_LED_CC)
SET_CONSOLE_TEMPLATE_TYPE_NAME(RGB_LED_CC);

SET_CONSOLE_TEMPLATE_TYPE_NAME(RG_LED_CA);
SET_CONSOLE_TEMPLATE_TYPE_NAME(RB_LED_CA);
SET_CONSOLE_TEMPLATE_TYPE_NAME(GB_LED_CA)
SET_CONSOLE_TEMPLATE_TYPE_NAME(RGB_LED_CA);
//------------------------------------------------------------------------------------------------
#include "led.tpp"
//------------------------------------------------------------------------------------------------
#endif // LED_H
