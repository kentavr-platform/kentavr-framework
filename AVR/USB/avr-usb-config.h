/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: AVR/USB/avr-usb-config.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_USB_CONFIG_H
#define AVR_USB_CONFIG_H
//------------------------------------------------------------------------------------------------
#include "Core/oscillator.h"
//------------------------------------------------------------------------------------------------
#define ARCH              ARCH_AVR8
#define USB_DEVICE_ONLY   // no other device drivers from LUFA library
#define F_USB             F_CPU
#define INTERRUPT_CONTROL_ENDPOINT    // proceed EP0 in USB_COM_vect ISR
//------------------------------------------------------------------------------------------------
#endif
