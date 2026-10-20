/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: reset.h
//----------------------------------------------------------------------------------------------*/
#ifndef RESET_H
#define RESET_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include "Core/macro.h"
//------------------------------------------------------------------------------------------------
class Reset_source
{
public:
    explicit constexpr Reset_source(uint8_t flags) : flags(flags) {}

    constexpr bool power_on()  const { return test_bit(flags, PORF); }
    constexpr bool external()  const { return test_bit(flags, EXTRF); }
    constexpr bool brown_out() const { return test_bit(flags, BORF); }

#if defined(WDRF)
    constexpr bool watchdog() const { return test_bit(flags, WDRF); }
#endif

#if defined(JTRF)
    constexpr bool jtag() const { return test_bit(flags, JTRF); }
#endif

#if defined(USBRF)
    constexpr bool usb() const { return test_bit(flags, USBRF); }
#endif

private:
    friend uint8_t console_value(const Reset_source &value) { return value.flags; }
    uint8_t flags;
};
//------------------------------------------------------------------------------------------------
extern void main(Reset_source source) asm("application_main");
//------------------------------------------------------------------------------------------------
#endif
