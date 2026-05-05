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
#include "LED/led.h"
#include "AVR/UART/avr-uart.h"

//------------------------------------------------------------------------------------------------
ENABLE_UART0(8, 256);        // Buffer sizes must be power of 2 and <= 256 (8-bit optimized mode)
//ENABLE_UART1(100, 200);

void early_init() __attribute__((naked, used, section(".init0")));
//------------------------------------------------------------------------------------------------
#endif // CORE_H
