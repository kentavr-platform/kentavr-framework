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

    All UART instances share the same driver implementation.

    Warning: buffer sizes must be power of 2 and <= 256 (8-bit optimized mode). Please note,
    that effective ring buffer capacity is one byte less than the configured buffer size
    (BUFFER_SIZE - 1).

    A buffer size of 0 (zero) completely disables RX or TX respectively - no interrupt,
    no buffer, no code.

    Flow control is not implemented in this design. However you can do it yourself.

ENABLE_UARTx(
             RX_BUFFER_SIZE,  -- size of reception buffer (required)
             TX_BUFFER_SIZE,  -- size of transmission buffer (required)

    Feel free to uncomment and modify the following lines.
                                                                                                */
ENABLE_UART0(4, 64);
ENABLE_UART1(8, 2);

//------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------
#endif // CORE_H
