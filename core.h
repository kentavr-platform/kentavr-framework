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

// core utils
#include "core/type_traits.h"
#include "core/errors.h"
#include "core/units.h"

// hardware-specific components drivers
#include "AVR/avr-macro.h"
#include "AVR/avr-delay.h"
#include "AVR/GPIO/avr-gpio.h"
#include "AVR/GPIO/pins.h"
#include "AVR/UART/avr-uart.h"
#include "AVR/Serial/serial-bit-out.h"

// external interfaces
#include "interfaces/OneWire/one-wire.h"

// external components drivers
#include "LED/led.h"
#include "Console/console.h"
#include "sensors/DS18B20/DS18B20.h"
#include "sensors/DS1822/DS1822.h"
#include "sensors/DS1825/DS1825.h"
//------------------------------------------------------------------------------------------------

/// Early init could be useful in some cases
void early_init() __attribute__((naked, used, section(".init0")));

//------------------------------------------------------------------------------------------------
/** Enable and configure hardware UARTs here

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

    Feel free to uncomment and modify the following lines to enable hardware UARTs.
                                                                                                */
// ENABLE_UART0(0, 128);
// ENABLE_UART1(8, 8);

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
#endif // CORE_H
