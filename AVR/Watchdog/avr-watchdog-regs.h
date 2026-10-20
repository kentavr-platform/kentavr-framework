/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-watchdog-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_WATCHDOG_REGS_H
#define AVR_WATCHDOG_REGS_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include "Core/macro.h"
//------------------------------------------------------------------------------------------------
#ifndef NOREG
#define NOREG _SFR_IO8(NONE)
#endif
//------------------------------------------------------------------------------------------------
#if (defined(WDTCSR) || defined(WDTCR))
//------------------------------------------------------------------------------------------------
struct Watchdog_traits
{
    static constexpr bool exists = true;
    static constexpr uint8_t ENABLE = WDE;
    static constexpr uint8_t PRESCALER_MASK = _bits(WDP0, WDP1, WDP2);

#if defined(WDTCSR)
    static inline volatile uint8_t& CONTROL = WDTCSR;
#elif defined(WDTCR)
    static inline volatile uint8_t& CONTROL = WDTCR;
#endif

#if defined(WDCE)
    static constexpr uint8_t CHANGE_ENABLE = WDCE;
#elif defined(WDTOE)
    static constexpr uint8_t CHANGE_ENABLE = WDTOE;
#endif

#if defined(WDP3)
    static constexpr bool has_extended_timeout = true;
    static constexpr uint8_t PRESCALER_HIGH = WDP3;
#else
    static constexpr bool has_extended_timeout = false;
    static constexpr uint8_t PRESCALER_HIGH = 0;
#endif

#if defined(WDIE) && defined(WDIF) && defined(WDT_vect)
    static constexpr bool has_interrupt = true;
    static constexpr uint8_t INTERRUPT = WDIE;
    static constexpr uint8_t INTERRUPT_FLAG = WDIF;
    #define WATCHDOG_HAS_INTERRUPT
#else
    static constexpr bool has_interrupt = false;
    static constexpr uint8_t INTERRUPT = 0;
    static constexpr uint8_t INTERRUPT_FLAG = 0;
#endif
};
//------------------------------------------------------------------------------------------------
#else
struct Watchdog_traits
{
    static constexpr bool exists = false;
    static constexpr bool has_interrupt = false;
    static constexpr bool has_extended_timeout = false;
    static inline volatile uint8_t& CONTROL = NOREG;
    static constexpr uint8_t ENABLE = 0;
    static constexpr uint8_t CHANGE_ENABLE = 0;
    static constexpr uint8_t PRESCALER_MASK = 0;
    static constexpr uint8_t PRESCALER_HIGH = 0;
    static constexpr uint8_t INTERRUPT = 0;
    static constexpr uint8_t INTERRUPT_FLAG = 0;
};
//------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------
#endif
