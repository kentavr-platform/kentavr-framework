/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: arduino-pro-micro.h
//----------------------------------------------------------------------------------------------*/
#ifndef ARDUINO_PRO_MICRO_H
#define ARDUINO_PRO_MICRO_H
//------------------------------------------------------------------------------------------------
// Digital pins
using AP_0   = D2;  // RX
using AP_1   = D3;  // TX
using AP_2   = D1;  // SDA
using AP_3   = D0;  // SCL
using AP_4   = D4;
using AP_5   = C6;
using AP_6   = D7;
using AP_7   = E6;
using AP_8   = B4;
using AP_9   = B5;
using AP_10  = B6;
using AP_11  = NC;  // not present
using AP_12  = NC;  // not present
using AP_13  = NC;  // not present
using AP_14  = B3;  // MISO
using AP_15  = B1;  // SCK
using AP_16  = B2;  // MOSI
using AP_17  = NC;  // not present

// Analog pins
using AP_A0  = F7;
using AP_A1  = F6;
using AP_A2  = F5;
using AP_A3  = F4;

// SPI
using AP_MISO = AP_14;
using AP_SCK  = AP_15;
using AP_MOSI = AP_16;

// UART
using AP_RX  = AP_0;
using AP_TX  = AP_1;

// I2C
using AP_SDA = AP_2;
using AP_SCL = AP_3;

// LEDs
using AP_L     = NC;  // not present
using AP_RXLED = B0;
using AP_TXLED = D5;
//------------------------------------------------------------------------------------------------
#endif
