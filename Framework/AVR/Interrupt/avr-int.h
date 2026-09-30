/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-int.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_INT_H
#define AVR_INT_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/interrupt.h>
#include "../GPIO/avr-gpio.h"
//------------------------------------------------------------------------------------------------
/**
 * Compile-time friend proxy which keeps GPIO :: interrupt() private.
 * The inline call is optimized away and adds no runtime dispatch overhead.
 */
template <uint8_t N>
struct INT_dispatcher
{
    static void interrupt()
    {
        GPIO <typename INT_traits <N> :: pin> :: interrupt();
    }
};
//------------------------------------------------------------------------------------------------
#define _ENABLE_INT(N, VECTOR)                                                        \
  static_assert(INT_traits <N> :: exists, "INT" #N " does not exist in this MCU");    \
  template <>                                                                         \
  struct GPIO_INT <INT_traits <N> :: pin>                                             \
  {                                                                                   \
      static constexpr bool enabled = true;                                           \
  };                                                                                  \
  ISR(VECTOR)                                                                         \
  {                                                                                   \
      INT_dispatcher <N> :: interrupt();                                              \
  }
//------------------------------------------------------------------------------------------------
#define ENABLE_INT0 _ENABLE_INT(0, INT0_vect)
#define ENABLE_INT1 _ENABLE_INT(1, INT1_vect)
#define ENABLE_INT2 _ENABLE_INT(2, INT2_vect)
#define ENABLE_INT3 _ENABLE_INT(3, INT3_vect)
#define ENABLE_INT4 _ENABLE_INT(4, INT4_vect)
#define ENABLE_INT5 _ENABLE_INT(5, INT5_vect)
#define ENABLE_INT6 _ENABLE_INT(6, INT6_vect)
#define ENABLE_INT7 _ENABLE_INT(7, INT7_vect)
//------------------------------------------------------------------------------------------------
#endif
