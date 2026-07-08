/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: core.h
//----------------------------------------------------------------------------------------------*/
#ifndef CORE_H
#define CORE_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//------------------------------------------------------------------------------------------------
#ifdef F_CPU
  #error ! F_CPU should not be defined directly
#endif
//------------------------------------------------------------------------------------------------
#if defined(CRYSTAL_FREQ)
  #define F_CPU             CRYSTAL_FREQ        // external crystal or ceramic resonator
#elif defined(EXTERNAL_CLOCK)
  #define F_CPU             EXTERNAL_CLOCK      // external clock source
#elif defined(INTERNAL_CLOCK_8MHZ)
  #define F_CPU             8000000UL           // internal RC clock generator
#else
  #error ! Define CRYSTAL_FREQ=, EXTERNAL_CLOCK= or INTERNAL_CLOCK_8MHZ
  #define F_CPU
#endif
//------------------------------------------------------------------------------------------------
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
#include "GPIO/avr-gpio.h"
#include "UART/avr-uart.h"
#include "I2C/avr-i2c.h"
#include "EEPROM/avr-eeprom.h"
#include "serial/serial-bit-out.h"

// interfaces
#include "settings/settings.h"
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
