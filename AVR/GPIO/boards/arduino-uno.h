/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: arduino-uno.h
//----------------------------------------------------------------------------------------------*/
#ifndef ARDUINO_UNO_H
#define ARDUINO_UNO_H
//------------------------------------------------------------------------------------------------
// Digital pins
using AP_0   = D0;  // RX
using AP_1   = D1;  // TX
using AP_2   = D2;
using AP_3   = D3;
using AP_4   = D4;
using AP_5   = D5;
using AP_6   = D6;
using AP_7   = D7;
using AP_8   = B0;
using AP_9   = B1;
using AP_10  = B2;
using AP_11  = B3;  // MOSI
using AP_12  = B4;  // MISO
using AP_13  = B5;  // SCK / L

// Analog pins
using AP_A0  = C0;
using AP_A1  = C1;
using AP_A2  = C2;
using AP_A3  = C3;
using AP_A4  = C4;  // SDA
using AP_A5  = C5;  // SCL

// SPI
using AP_MISO = AP_12;
using AP_SCK  = AP_13;
using AP_MOSI = AP_11;

// UART
using AP_RX  = AP_0;
using AP_TX  = AP_1;

// I2C
using AP_SDA = AP_A4;
using AP_SCL = AP_A5;

// LEDs
using AP_L     = AP_13;
using AP_RXLED = NC;  // not present
using AP_TXLED = NC;  // not present
//------------------------------------------------------------------------------------------------
#endif
