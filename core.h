/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: core.h
//----------------------------------------------------------------------------------------------*/
#ifndef CORE_H
#define CORE_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "AVR/avr-mcu.h"
#include <avr/interrupt.h>
//------------------------------------------------------------------------------------------------
// core modules
#include "Core/oscillator.h"
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
#include "Core/reset.h"
#include "Services/Console/debug.h"
#include "AVR/GPIO/avr-gpio.h"
#include "AVR/Timer/avr-timer.h"
#include "AVR/UART/avr-uart.h"
#include "AVR/I2C/avr-i2c.h"
#include "AVR/SPI/avr-spi.h"
#include "AVR/SPI/avr-usart-spi.h"
#include "AVR/USB/avr-usb.h"
#include "AVR/EEPROM/avr-eeprom.h"
#include "AVR/Watchdog/avr-watchdog.h"

// services
#include "Services/Settings/settings.h"

// drivers with config-defined settings
#include "AVR/ADC/avr-adc.h"

// interfaces
#include "Interfaces/OneWire/one-wire.h"
#include "Interfaces/Serial/serial-bit-out.h"
#include "Interfaces/SerialUSB/serial-usb.h"
#include "Interfaces/AVR-ISP/avr-isp.h"

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
#endif
