/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: led.tpp
 *
 * WARNING! This file is included from led.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
/*
 *      COMMON CATHODE BiLEDs
 *
 *----------------------------------------------------------------------------------------------*/
template <class pinA, class pinB>
BiLED_CC <pinA, pinB> :: BiLED_CC()
{
    GPIO <pinA> :: set_mode(OUTPUT_LOW);
    GPIO <pinB> :: set_mode(OUTPUT_LOW);
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CC <pinA, pinB> :: on_A()
{
    GPIO <pinA> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CC <pinA, pinB> :: on_B()
{
    GPIO <pinA> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CC <pinA, pinB> :: on_AB()
{
    GPIO <pinA> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CC <pinA, pinB> :: off()
{
    GPIO <pinA> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
/*
 *      COMMON ANODE BiLEDs
 *
 *----------------------------------------------------------------------------------------------*/
template <class pinA, class pinB>
BiLED_CA <pinA, pinB> :: BiLED_CA()
{
    GPIO <pinA> :: set_mode(OUTPUT_HIGH);
    GPIO <pinB> :: set_mode(OUTPUT_HIGH);
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CA <pinA, pinB> :: on_A()
{
    GPIO <pinA> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CA <pinA, pinB> :: on_B()
{
    GPIO <pinA> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CA <pinA, pinB> :: on_AB()
{
    GPIO <pinA> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinA, class pinB>
__inline void BiLED_CA <pinA, pinB> :: off()
{
    GPIO <pinA> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
/*
 *      COMMON CATHODE (CC) RGB LED
 *
 *----------------------------------------------------------------------------------------------*/
template <class pinR, class pinG, class pinB>
RGB_LED_CC <pinR, pinG, pinB> :: RGB_LED_CC()
{
    GPIO <pinR> :: set_mode(OUTPUT_LOW);
    GPIO <pinG> :: set_mode(OUTPUT_LOW);
    GPIO <pinB> :: set_mode(OUTPUT_LOW);
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_red()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_green()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_blue()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_yellow()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_magenta()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_cyan()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: on_white()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CC <pinR, pinG, pinB> :: off()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
/*
 *      COMMON ANODE (CA) RGB LED
 *
 *----------------------------------------------------------------------------------------------*/
template <class pinR, class pinG, class pinB>
RGB_LED_CA <pinR, pinG, pinB> :: RGB_LED_CA()
{
    GPIO <pinR> :: set_mode(OUTPUT_HIGH);
    GPIO <pinG> :: set_mode(OUTPUT_HIGH);
    GPIO <pinB> :: set_mode(OUTPUT_HIGH);
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_red()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_green()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_blue()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_yellow()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_magenta()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_cyan()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: on_white()
{
    GPIO <pinR> :: write_low();
    GPIO <pinG> :: write_low();
    GPIO <pinB> :: write_low();
}
//------------------------------------------------------------------------------------------------
template <class pinR, class pinG, class pinB>
__inline void RGB_LED_CA <pinR, pinG, pinB> :: off()
{
    GPIO <pinR> :: write_high();
    GPIO <pinG> :: write_high();
    GPIO <pinB> :: write_high();
}
//------------------------------------------------------------------------------------------------

