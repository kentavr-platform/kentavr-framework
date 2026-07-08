/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: arduino-mega2560.h
//----------------------------------------------------------------------------------------------*/
#ifndef ARDUINO_MEGA2560_H
#define ARDUINO_MEGA2560_H
//------------------------------------------------------------------------------------------------
// Digital pins
using AP_0   = E0;  // RX0
using AP_1   = E1;  // TX0
using AP_2   = E4;
using AP_3   = E5;
using AP_4   = G5;
using AP_5   = E3;
using AP_6   = H3;
using AP_7   = H4;
using AP_8   = H5;
using AP_9   = H6;
using AP_10  = B4;
using AP_11  = B5;
using AP_12  = B6;
using AP_13  = B7;  // L
using AP_14  = J1;  // TX3
using AP_15  = J0;  // RX3
using AP_16  = H1;  // TX2
using AP_17  = H0;  // RX2
using AP_18  = D3;  // TX1
using AP_19  = D2;  // RX1
using AP_20  = D1;  // SDA
using AP_21  = D0;  // SCL
using AP_22  = A0;
using AP_23  = A1;
using AP_24  = A2;
using AP_25  = A3;
using AP_26  = A4;
using AP_27  = A5;
using AP_28  = A6;
using AP_29  = A7;
using AP_30  = C7;
using AP_31  = C6;
using AP_32  = C5;
using AP_33  = C4;
using AP_34  = C3;
using AP_35  = C2;
using AP_36  = C1;
using AP_37  = C0;
using AP_38  = D7;
using AP_39  = G2;
using AP_40  = G1;
using AP_41  = G0;
using AP_42  = L7;
using AP_43  = L6;
using AP_44  = L5;
using AP_45  = L4;
using AP_46  = L3;
using AP_47  = L2;
using AP_48  = L1;
using AP_49  = L0;
using AP_50  = B3;  // MISO
using AP_51  = B2;  // MOSI
using AP_52  = B1;  // SCK
using AP_53  = B0;  // SS

// Analog pins
using AP_A0  = F0;
using AP_A1  = F1;
using AP_A2  = F2;
using AP_A3  = F3;
using AP_A4  = F4;
using AP_A5  = F5;
using AP_A6  = F6;
using AP_A7  = F7;
using AP_A8  = K0;
using AP_A9  = K1;
using AP_A10 = K2;
using AP_A11 = K3;
using AP_A12 = K4;
using AP_A13 = K5;
using AP_A14 = K6;
using AP_A15 = K7;

// SPI
using AP_MISO = AP_50;
using AP_MOSI = AP_51;
using AP_SCK  = AP_52;
using AP_SS   = AP_53;

// UART
using AP_RX   = AP_0;
using AP_TX   = AP_1;
using AP_RX0  = AP_0;
using AP_TX0  = AP_1;
using AP_RX1  = AP_19;
using AP_TX1  = AP_18;
using AP_RX2  = AP_17;
using AP_TX2  = AP_16;
using AP_RX3  = AP_15;
using AP_TX3  = AP_14;

// I2C
using AP_SDA = AP_20;
using AP_SCL = AP_21;

// LEDs
using AP_L     = AP_13;
using AP_RXLED = NC;  // not present
using AP_TXLED = NC;  // not present
//------------------------------------------------------------------------------------------------
#endif
