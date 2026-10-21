/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: serial-usb.h
//----------------------------------------------------------------------------------------------*/
#ifndef SERIAL_USB_H
#define SERIAL_USB_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "AVR/avr-macro.h"
//------------------------------------------------------------------------------------------------
enum SerialUSB_mode : uint8_t
{
    RX_only = 0x01,    // Receive from the hardware OUT bank; disable transmission.
    TX_only = 0x02,    // Transmit; discard incoming host packets.
    RX_TX   = 0x03     // Receive and transmit.
};
//------------------------------------------------------------------------------------------------
/**
 * @brief USB CDC-ACM serial interface.
 *
 * Provides byte-stream communication with a USB host over the CDC data
 * endpoints.
 */
class SerialUSB
{
public:
    explicit SerialUSB(enum SerialUSB_mode mode = RX_TX);
    static void init();
    static bool connected();
    static bool DTR();
    static uint8_t available();
    static int peek();
    static int read();
    static uint8_t read(uint8_t *buf, const uint8_t count);
    uint8_t write(char data);
    uint8_t write(const char *str);
    uint8_t write(FlashStringWrapper fs);
    uint8_t write(const uint8_t *buf, uint16_t count);
    uint8_t write_all(const char *str);
    uint8_t write_all(FlashStringWrapper fs);
    uint8_t write_all(const uint8_t *buf, uint16_t count);
    uint8_t tx_wait();
};
//------------------------------------------------------------------------------------------------
__inline FlashStringWrapper console_type_name(const SerialUSB &)
{
    return _flash("SerialUSB");
}
//------------------------------------------------------------------------------------------------
#endif
