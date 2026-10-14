/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-spi-common.h
 * Common types and interrupt dispatch shared by SPI and USART_SPI.
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_SPI_COMMON_H
#define AVR_SPI_COMMON_H
#include <stdint.h>
//------------------------------------------------------------------------------------------------
enum SPI_Clock_Mode
{
    SPI_CLOCK_MODE_0,   // CPOL = 0, CPHA = 0
    SPI_CLOCK_MODE_1,   // CPOL = 0, CPHA = 1
    SPI_CLOCK_MODE_2,   // CPOL = 1, CPHA = 0
    SPI_CLOCK_MODE_3    // CPOL = 1, CPHA = 1
};
//------------------------------------------------------------------------------------------------
enum SPI_Bit_Order
{
    SPI_MSB_FIRST,
    SPI_LSB_FIRST
};
//------------------------------------------------------------------------------------------------
enum SPI_Mode
{
    SPI_DISABLED,
    SPI_MASTER,
    SPI_SLAVE
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Process one received byte in SPI slave mode.
 *
 * Called from interrupt context. Store the byte to send on the next transfer
 * through @p next_tx; keep the callback short and non-blocking.
 * @param received Byte received from the external master.
 * @param next_tx Output location for the next byte to transmit.
 */
using SPI_Slave_Callback = void (*)(uint8_t received, uint8_t *next_tx);
//------------------------------------------------------------------------------------------------
/** @brief Configuration for the hardware SPI slave mode. */
struct SPI_Slave_Config
{
    SPI_Clock_Mode      clock_mode  = SPI_CLOCK_MODE_0;  /// < Clock polarity and phase
    SPI_Bit_Order       bit_order   = SPI_MSB_FIRST;     /// < Bit transmission order
    uint8_t             first_tx    = 0xFF;              /// < Byte sent on the first transfer
    SPI_Slave_Callback  callback    = nullptr;           /// < Required byte callback
};
//------------------------------------------------------------------------------------------------
/** @brief Adapter that lets an ISR call a driver's private interrupt method. */
template <class SPI_type>
struct SPI_dispatcher
{
    static void interrupt()
    {
        SPI_type :: interrupt();
    }
};
//------------------------------------------------------------------------------------------------
#endif
