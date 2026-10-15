/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: Core/startup.c
//----------------------------------------------------------------------------------------------*/
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
// Some bootloaders hands control to the application with a jump 0 rather than a
// hardware reset. In this case they can leave peripheral interrupts enabled
// and prevent normal application run after startup or enable_interrupts().

// These functions clear probably enabled interrupts, that could harm the
// application.
//------------------------------------------------------------------------------------------------
void cli_at_startup(void) __attribute__((naked, used, section(".init0")));
void cli_at_startup(void)
{
    __asm__ __volatile__("cli" ::: "memory");
}
//------------------------------------------------------------------------------------------------
void after_bootloader(void) __attribute__((naked, used, section(".init3")));
void after_bootloader(void)
{
    // This function is placed in the AVR startup section .init3.
    // .init3 runs after .init2 has initialized the stack pointer and the zero
    // register, but before .init4 copies initialized data and clears .bss.
    // Keep this hook independent of globals and constructors. It is declared
    // naked, so do not add code that needs a stack frame or emits a return.

#if defined(USB_COM_vect)
    USBCON &= ~_BV(VBUSTE);
    UDIEN = 0;
#endif
}
//------------------------------------------------------------------------------------------------
