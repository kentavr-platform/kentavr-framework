/*------------------------------------------------------------------------------------------------
 * Project:
 *
 * Based on KentAVR Framework (https://github.com/kentavr-platform/kentavr-framework)
 *
 * File: main.cpp
//----------------------------------------------------------------------------------------------*/
#include "KentAVR/core.h"
#include "config.h"
//------------------------------------------------------------------------------------------------
#ifdef DEBUG
    // static SerialBitOut <B4, 1000000> debug; Console console(debug);
    // static UART0 uart;                       Console console(uart);
    // static SerialUSB usb;                    Console console(usb);
#else
    Console console;    // a black-hole object with no output and zero runtime overhead
#endif

//------------------------------------------------------------------------------------------------
void early_init()
{
    // Runs immediately after reset, before stack and runtime initialization.
    // Use with extreme caution: only code that does not use the stack is safe here.
    // See the GCC AVR documentation for section(".initX") and naked functions.
    // ...

    // Startup continues with stack and runtime initialization.
}
//------------------------------------------------------------------------------------------------
int main()
{
    // uart.init();
    // usb.init();


    // enable_interrupts();

    // console.log("== RESET ==");


    while(1)
    {
        // main loop
        
    }

    return 0;
}
//------------------------------------------------------------------------------------------------
