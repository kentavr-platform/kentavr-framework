/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins.h
//----------------------------------------------------------------------------------------------*/
#ifndef PINS_H
#define PINS_H
//------------------------------------------------------------------------------------------------
template <
    volatile uint8_t port_addr,
    volatile uint8_t dir_addr,
    volatile uint8_t pin_addr,
    volatile uint8_t tgl_addr,
    uint8_t bit>
struct pin
{
    static constexpr uint8_t PORT  = port_addr;
    static constexpr uint8_t DDR   = dir_addr;
    static constexpr uint8_t PIN   = pin_addr;
    static constexpr uint8_t TGL   = tgl_addr;
    static constexpr uint8_t BIT   = bit;
};
//------------------------------------------------------------------------------------------------
struct NC {};       // Not Connected "pin"
//------------------------------------------------------------------------------------------------
#define DECLARE_PIN(ID, PORT, DDR, PIN, TGL, BIT) struct ID : pin <PORT, DDR, PIN, TGL, BIT> {};
//------------------------------------------------------------------------------------------------
#if defined(__AVR_ATmega8__)
  #include "pins_m8.h"
#elif defined(__AVR_ATmega88__) \
  || defined(__AVR_ATmega88P__) \
  || defined(__AVR_ATmega328__) \
  || defined(__AVR_ATmega328P__)
  #include "pins_m88.h"
#elif defined(__AVR_ATmega1284P__)
  #include "pins_m1284.h"
#elif defined(__AVR_ATmega32u4__)
  #include "pins_m32u4.h"
#elif defined(AVR128DX_FAMILY)
  #include "pins_128dx48.h"
#else
  #error "Unsupported or undefined MCU"
#endif
//------------------------------------------------------------------------------------------------
// Support pin names for popular Arduino boards
#if defined(ARDUINO_AVR_UNO)
  #include "boards/arduino-uno.h"
#elif defined(ARDUINO_AVR_NANO)
  #include "boards/arduino-nano.h"
#elif defined(ARDUINO_AVR_LEONARDO)
  #include "boards/arduino-leonardo.h"
#elif defined(ARDUINO_AVR_MINI)
  #include "boards/arduino-mini.h"
#elif defined(ARDUINO_AVR_MICRO)
  #include "boards/arduino-micro.h"
#elif defined(ARDUINO_AVR_PRO_MINI)
  #include "boards/arduino-pro-mini.h"
#elif defined(ARDUINO_AVR_PRO_MICRO)
  #include "boards/arduino-pro-micro.h"
#elif defined(ARDUINO_AVR_LEONARDO)
  #include "boards/arduino-leonardo.h"
#elif defined(ARDUINO_AVR_MEGA2560)
  #include "boards/arduino-mega2560.h"
#endif
//------------------------------------------------------------------------------------------------
#endif


