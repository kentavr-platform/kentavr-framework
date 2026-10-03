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
#include "Core/macro.h"
#include "Core/errors.h"
#include "Core/type_traits.h"
#include "Core/units.h"
#include "Core/format.h"
#include "Core/nostream.h"
#include "Core/bcd.h"

// hardware-specific drivers
#include "AVR/avr-macro.h"
#include "AVR/avr-delay.h"
#include "Services/Console/debug.h"
#include "AVR/GPIO/avr-gpio.h"
#include "AVR/Timer/avr-timer.h"
#include "AVR/UART/avr-uart.h"
#include "AVR/I2C/avr-i2c.h"
#include "AVR/EEPROM/avr-eeprom.h"
#include "Interfaces/Serial/serial-bit-out.h"


// interfaces
#include "Services/Settings/settings.h"
#include "Interfaces/OneWire/one-wire.h"

// external drivers
#include "Devices/LED/led.h"
#include "Devices/Servo/servo.h"
#include "Services/Console/console.h"
#include "Devices/Sensors/DS1820/DS18x20.h"
#include "Devices/Sensors/DS1820/DS1820.h"
#include "Devices/Sensors/DS18S20/DS18S20.h"
#include "Devices/Sensors/DS18B20/DS18B20.h"
#include "Devices/RTC/DS3231/DS3231.h"
//------------------------------------------------------------------------------------------------
/// Early init could be useful in some cases
void early_init() __attribute__((naked, used, section(".init0")));
//------------------------------------------------------------------------------------------------
#endif
