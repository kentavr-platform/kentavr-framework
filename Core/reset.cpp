/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: reset.cpp
//----------------------------------------------------------------------------------------------*/
#include <avr/io.h>
#include "reset.h"
#include "Core/macro.h"
//------------------------------------------------------------------------------------------------
// Some bootloaders hands control to the application with a jump 0 rather than a
// hardware reset. In this case they can leave peripheral interrupts enabled
// and prevent normal application run after startup or enable_interrupts().

// These functions clear probably enabled interrupts, that could harm the
// application.
//------------------------------------------------------------------------------------------------
extern "C" void cli_at_startup() __attribute__((naked, used, section(".init0")));
void cli_at_startup()
{
    __asm__ __volatile__("cli" ::: "memory");
}
//------------------------------------------------------------------------------------------------
// Label only: the empty .init1 falls through to the CRT register and stack setup.
extern "C" void init_registers_and_stack() __attribute__((naked, used, section(".init1")));
void init_registers_and_stack() {}
//------------------------------------------------------------------------------------------------
uint8_t avr_reset_source __attribute__((section(".noinit")));
//------------------------------------------------------------------------------------------------
extern "C" void get_reset_source() __attribute__((naked, used, section(".init2")));
void get_reset_source()
{
    avr_reset_source = MCUSR;
    MCUSR = 0;
}
//------------------------------------------------------------------------------------------------
extern "C"  void after_bootloader() __attribute__((naked, used, section(".init3")));
void after_bootloader()
{
#if defined(USB_COM_vect)
    // disable USB
    clr_bit(USBCON, VBUSTE);
    UDIEN = 0;
#endif
    __asm__ __volatile__("nop");
}
//------------------------------------------------------------------------------------------------
extern "C" int reset_entry() asm("main");
int reset_entry()
{
    main(Reset_source(avr_reset_source));
    return 0;
}
//------------------------------------------------------------------------------------------------
