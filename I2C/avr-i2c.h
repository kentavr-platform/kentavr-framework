/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-i2c.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_I2C_H
#define AVR_I2C_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "AVR/avr-macro.h"
#include "core/errors.h"
#include "avr-i2c-regs.h"
//------------------------------------------------------------------------------------------------
enum I2C_Mode : uint8_t
{
    I2C_DISABLED,
    I2C_MASTER,
    I2C_SLAVE
};
//------------------------------------------------------------------------------------------------
enum I2C_Slave_Action
{
    I2C_SLAVE_START,
    I2C_SLAVE_BROADCAST_START,
    I2C_SLAVE_DATA,
    I2C_SLAVE_END,
    I2C_SLAVE_MORE
};
//------------------------------------------------------------------------------------------------
struct I2C_Slave_Config
{
    uint8_t     address = 0;
    bool        receive_broadcasts = false;
    // callback function pointer, called from ISR, keep it short
    ResultCode  (*receiver_callback)
                (enum I2C_Slave_Action action, uint8_t data) = nullptr;
    // callback function pointer, called from ISR, keep it short
    ResultCode  (*transmitter_callback)
                (enum I2C_Slave_Action action, uint8_t *data) = nullptr ;
};
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
class TWI
{
public:
    static ResultCode       init_master(uint32_t freq);
    static ResultCode       init_slave(const I2C_Slave_Config &config);
    static void             disable();
    static bool             is_busy();
    static void             wait();
    static I2C_Mode         get_mode()  { return mode; }
    static ResultCode       send(uint8_t address, const void *data, uint8_t size,
                                 void (*callback)(ResultCode result) = nullptr);
    static ResultCode       receive(uint8_t address, void *data, uint8_t size,
                                    void (*callback)(ResultCode result) = nullptr);
    static void             interrupt();

private:
    using regs = I2C_traits <N>;
    static void             _reset();
    static void             _start();
    static void             _stop();
    static void             _ack();
    static void             _nack();
    static void             _write_dr(uint8_t data);
    static void             _read_dr();
    static void             _complete(ResultCode result);
    static void             _listen();

    static constexpr uint8_t max_tries = 3;
    static uint8_t          tx_buf[TX_BUF_SIZE];
    static I2C_Mode         mode ;
    static volatile bool    busy;
    static struct MasterState
    {
        uint8_t  address = 0;
        uint8_t  *buf = nullptr;
        uint8_t  size = 0;
        uint8_t  index = 0;
        uint8_t  tries_left = 0;
        ResultCode result = ERR_UNKNOWN;
        void (*callback)(ResultCode result) = nullptr;
    } master;
    static I2C_Slave_Config slave;
};
//------------------------------------------------------------------------------------------------
#define _SETUP_TWI_ISR(VECT, BUS) ISR(VECT) { I2C##BUS :: interrupt(); }

#if defined(TWI_vect)
  #define _ENABLE_TWI_ISR_0() _SETUP_TWI_ISR(TWI_vect, 0)
#elif defined(TWI0_vect)
  #define _ENABLE_TWI_ISR_0() _SETUP_TWI_ISR(TWI0_vect, 0)
#endif

#if defined(TWI1_vect)
  #define _ENABLE_TWI_ISR_1() _SETUP_TWI_ISR(TWI1_vect, 1)
#endif

#define _ENABLE_I2C(N, TX_BUF_SIZE) \
using I2C##N = TWI <N, TX_BUF_SIZE>; \
_ENABLE_TWI_ISR_##N()

// I2C0
#if defined(I2C0_SUPPORTED)
  #define ENABLE_I2C0(TX_BUF_SIZE) _ENABLE_I2C(0, TX_BUF_SIZE)
#else
  #define ENABLE_I2C0(TX_BUF_SIZE) PRAGMA(GCC error "I2C0 is not supported by this MCU")
#endif

// I2C1
#if defined(I2C1_SUPPORTED)
  #define ENABLE_I2C1(TX_BUF_SIZE) _ENABLE_I2C(1, TX_BUF_SIZE)
#else
  #define ENABLE_I2C1(TX_BUF_SIZE) PRAGMA(GCC error "I2C1 is not supported by this MCU")
#endif
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline FlashStringWrapper console_type_name(const TWI <N, TX_BUF_SIZE> &)
{
    return _flash("I2C");
}
//------------------------------------------------------------------------------------------------
#include "avr-i2c.tpp"
//------------------------------------------------------------------------------------------------
#endif



