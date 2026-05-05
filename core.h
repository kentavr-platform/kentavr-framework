/*------------------------------------------------------------------------------------------------
 * core.h
 *
 *  This file contains core includes and definitions.
 *
//----------------------------------------------------------------------------------------------*/
#ifndef CORE_H
#define CORE_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/interrupt.h>
#include "AVR/avr-macro.h"
#include "AVR/avr-delay.h"
#include "AVR/GPIO/avr-gpio.h"
#include "platform/pins.h"
#include "AVR/UART/avr-uart.h"
#include "LED/led.h"
//------------------------------------------------------------------------------------------------

/// Early init could be useful in some cases
void early_init() __attribute__((naked, used, section(".init0")));

//------------------------------------------------------------------------------------------------

/** Enable and configure UARTs here
    All UART drivers are the same and support all the methods and parameters.
    Warning: buffer sizes must be power of 2 and <= 256 (8-bit optimized mode)

ENABLE_UARTx(
             RX_BUFFER_SIZE,  -- the size of the reception buffer (required)
             TX_BUFFER_SIZE,  -- the size ot the transmission buffer (required)
    Flow controll is not implemented in this design. However you can do it yourself.
    Fill free to uncomment and/or change the following lines.
                                                                                                */
ENABLE_UART0(64, 64);
//ENABLE_UART1(64, 8);

//------------------------------------------------------------------------------------------------



void early_init() __attribute__((naked, used, section(".init0")));
//------------------------------------------------------------------------------------------------
#endif // CORE_H
