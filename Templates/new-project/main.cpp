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
    // static SerialBitOut <B4, 500000> debug;  Console console(debug);
    // static UART0 uart;                       Console console(uart);
    // static SerialUSB usb;                    Console console(usb);
#else
    Console console;    // a black-hole object with no output and zero runtime overhead
#endif
//------------------------------------------------------------------------------------------------
void main(Reset_source reset)
{
    // uart.init(500000);   // the highest baudrate supported for 16 and 20 MHz crystal both
    // usb.init();


    // enable_interrupts();

    // console.log("== RESET ==");


    while(1)
    {
        // main loop

        // watchdog.kick();
        mdelay(100);
    }

}
//------------------------------------------------------------------------------------------------
