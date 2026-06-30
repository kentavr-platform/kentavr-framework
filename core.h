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

// core modules
#include "core/type_traits.h"
#include "core/errors.h"
#include "core/units.h"
#include "core/nostream.h"

// hardware-specific drivers
#include "AVR/avr-macro.h"
#include "AVR/avr-delay.h"
#include "console/debug.h"
#include "AVR/GPIO/avr-gpio.h"
#include "AVR/GPIO/pins.h"
#include "AVR/UART/avr-uart.h"
#include "AVR/EEPROM/avr-eeprom.h"
#include "AVR/serial/serial-bit-out.h"


// interfaces
#include "core/settings/settings.h"
#include "interfaces/OneWire/one-wire.h"

// external drivers
#include "LED/led.h"
#include "console/console.h"
#include "sensors/DS1820/DS18x20.h"
#include "sensors/DS1820/DS1820.h"
#include "sensors/DS18S20/DS18S20.h"
#include "sensors/DS18B20/DS18B20.h"
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
             )

    Feel free to uncomment and modify the following lines to enable hardware UARTs.
                                                                                                */
// ENABLE_UART0(0, 128);
// ENABLE_UART1(8, 8);

//------------------------------------------------------------------------------------------------

/**
    Enable settings instance and reserves EEPROM space.

    Allocates an EEPROM object occupying exactly Size bytes and creates a
    global settings storage instance using that region.

 ENABLE_SETTINGS(
                 SETTINGS_SIZE  -- EEPROM size reserved for settings storage
                                   (header + data + index)
                )

    Uncomment and modify the following lines to enable
                                                                                                */
ENABLE_SETTINGS(512);

//------------------------------------------------------------------------------------------------
#endif
