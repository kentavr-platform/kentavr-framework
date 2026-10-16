/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-spi.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_SPI_H
#define AVR_SPI_H
//------------------------------------------------------------------------------------------------
#include "avr-spi-common.h"
#include "avr-spi-regs.h"
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t TX_BUF_SIZE>
class SPI
{
public:
    using pins = SPI_pins <N>;
    static constexpr uint32_t min_master_frequency = (F_CPU + 127UL) / 128UL;

    static ResultCode   init_master(uint32_t frequency,
                                    SPI_Clock_Mode clock_mode = SPI_CLOCK_MODE_0,
                                    SPI_Bit_Order bit_order = SPI_MSB_FIRST);
    static ResultCode   init_slave(const SPI_Slave_Config &config);
    static void         disable();
    static bool         is_busy();
    static void         wait();
    static SPI_Mode     get_mode();
    static ResultCode   send(const uint8_t *data, uint16_t count,
                             void (*callback)(ResultCode result) = nullptr);
    static ResultCode   receive(uint8_t *data, uint16_t count,
                                void (*callback)(ResultCode result) = nullptr);
    static ResultCode   duplex(const uint8_t *tx, uint8_t *rx, uint16_t count,
                               void (*callback)(ResultCode result) = nullptr);
private:
    using regs = SPI_traits <N>;
    static inline volatile SPI_Mode mode = SPI_DISABLED;
    static inline volatile bool busy = false;
    static inline uint8_t tx_buf[TX_BUF_SIZE];
    static struct MasterState
    {
        const uint8_t *tx = nullptr;
        uint8_t *rx = nullptr;
        uint16_t count = 0;
        uint16_t index = 0;
        void (*callback)(ResultCode) = nullptr;
        ResultCode result = ERR_UNKNOWN;
    } master;
    static inline SPI_Slave_Config slave;
    static void         configure(SPI_Clock_Mode clock_mode, SPI_Bit_Order bit_order,
                                  bool master, uint8_t prescaler, bool double_speed);
    static ResultCode   transfer(const uint8_t *tx, uint8_t *data, uint16_t size,
                                 void (*callback)(ResultCode));
    static ResultCode   polling_transfer(const uint8_t *tx, uint8_t *rx, uint16_t size);
    static void         _start();
    static void         complete(ResultCode result);
    static void         interrupt();

    template <class>
    friend struct SPI_dispatcher;
};
//------------------------------------------------------------------------------------------------
#if defined(SPI_STC_vect) && !defined(SPI0_INT_vect)
  #define SPI0_INT_vect  SPI_STC_vect
#endif

#ifdef ISR_HANDLERS_MODULE
  #define _SETUP_SPI_ISR(VECT, N) ISR(VECT) { SPI_dispatcher <SPI##N> :: interrupt(); }
#else
  #define _SETUP_SPI_ISR(VECT, N)
#endif

#define _ENABLE_SPI(N, TX_BUF_SIZE)                                                         \
  using SPI##N = SPI <N, TX_BUF_SIZE>;                                                      \
  _SETUP_SPI_ISR(SPI##N##_INT_vect, N)

#if defined(SPI0_SUPPORTED)
  #define ENABLE_SPI0(TX_BUF_SIZE) _ENABLE_SPI(0, TX_BUF_SIZE)
#else
  #define ENABLE_SPI0(TX_BUF_SIZE) PRAGMA(GCC error "SPI0 is not supported by this MCU")
#endif

#if defined(SPI1_SUPPORTED)
  #define ENABLE_SPI1(TX_BUF_SIZE) _ENABLE_SPI(1, TX_BUF_SIZE)
#else
  #define ENABLE_SPI1(TX_BUF_SIZE) PRAGMA(GCC error "SPI1 is not supported by this MCU")
#endif
//------------------------------------------------------------------------------------------------
#include "avr-spi.tpp"
//------------------------------------------------------------------------------------------------
#endif

