/*------------------------------------------------------------------------------------------------
 * core.h
 *
 *  This file contains core includes and definitions.
 *
//----------------------------------------------------------------------------------------------*/
#ifndef CORE_H
#define CORE_H
//------------------------------------------------------------------------------------------------
#define F_CPU 20000000UL
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/interrupt.h>

// core modules
#include "core/type_traits.h"
#include "core/errors.h"
#include "core/units.h"
#include "core/format.h"
#include "core/nostream.h"
#include "core/bcd.h"

// hardware-specific drivers
#include "AVR/avr-macro.h"
#include "AVR/avr-delay.h"
#include "console/debug.h"
#include "AVR/GPIO/avr-gpio.h"
#include "AVR/GPIO/pins.h"
#include "AVR/UART/avr-uart.h"
#include "AVR/I2C/i2c.h"
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
#include "RTC/DS3231/DS3231.h"
//------------------------------------------------------------------------------------------------
/// Early init could be useful in some cases
void early_init() __attribute__((naked, used, section(".init0")));
//------------------------------------------------------------------------------------------------
#endif
