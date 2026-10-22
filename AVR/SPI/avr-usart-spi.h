/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-usart-spi.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_USART_SPI_H
#define AVR_USART_SPI_H
//------------------------------------------------------------------------------------------------
#include "avr-spi-common.h"
#include "avr-usart-spi-regs.h"
#include "../PowerSave/avr-powersave.h"
//------------------------------------------------------------------------------------------------
/**
 * @brief USART peripheral operating in master SPI mode.
 *
 * This master-only SPI driver uses the selected USART. It is available only
 * on MCUs whose USART supports master SPI mode, and cannot be used at the same time as
 * UART<N>. Chip select is controlled by the device driver through GPIO.
 *
 * A null completion callback selects blocking mode; a non-null callback
 * selects non-blocking mode. Blocking transmit data is read directly from the
 * caller's buffer. Non-blocking transmit data is copied into the driver's
 * fixed-size buffer. RX data is written directly into the caller's buffer,
 * which must remain valid until completion. One operation may be active at a
 * time; there is no transfer queue. receive() sends 0xFF and is not limited by
 * TX_BUF_SIZE. Completion callbacks run from interrupt context and must be
 * short and non-blocking.
 *
 * init_master() does not enable global interrupts. Blocking calls and
 * wait() require enabled interrupts and must not be called from an ISR.
 * disable() cancels an active operation without invoking its callback. Call
 * wait() before disable() when the current transfer must finish normally.
 * Calls while disabled return
 * ERR_BAD_MODE; zero-length operations are rejected.
 * The board configuration selects any nondefault AVR Dx PORTMUX route.
 *
 * @tparam N USART peripheral index, starting at zero.
 * @tparam TX_BUF_SIZE Maximum TX byte count copied for one non-blocking operation.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
class USART_SPI
{
public:
    using pins = USART_SPI_pins <N>;
    static constexpr uint32_t min_master_frequency =
        USART_SPI_traits <N> :: max_divider
            ? (F_CPU - 1UL) / (2UL * USART_SPI_traits <N> :: max_divider) + 1UL
            : 0;

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
    using regs = USART_SPI_traits <N>;
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

    static ResultCode   transfer(const uint8_t *tx, uint8_t *rx, uint16_t size,
                               void (*callback)(ResultCode));
    static void         _start();
    static void         complete(ResultCode result);
    static void         interrupt();

    template <class>
    friend struct SPI_dispatcher;
};
//------------------------------------------------------------------------------------------------
#ifdef ISR_HANDLERS_MODULE
  #define _SETUP_USART_SPI_ISR(VECT, N) ISR(VECT) { SPI_dispatcher <USART_SPI##N> :: interrupt(); }
#else
  #define _SETUP_USART_SPI_ISR(VECT, N)
#endif

#if defined(USART_SPI0_SUPPORTED) && defined(USART0_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_0() _SETUP_USART_SPI_ISR(USART0_TXC_vect, 0)
#elif defined(USART_SPI0_SUPPORTED) && defined(USART0_TX_vect)
  #define _ENABLE_USART_SPI_ISR_0() _SETUP_USART_SPI_ISR(USART0_TX_vect, 0)
#else
  #define _ENABLE_USART_SPI_ISR_0() PRAGMA(GCC error "Using USART0 in SPI mode is not supported by this MCU")
#endif

#if defined(USART_SPI1_SUPPORTED) && defined(USART1_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_1() _SETUP_USART_SPI_ISR(USART1_TXC_vect, 1)
#elif defined(USART_SPI1_SUPPORTED) && defined(USART1_TX_vect)
  #define _ENABLE_USART_SPI_ISR_1() _SETUP_USART_SPI_ISR(USART1_TX_vect, 1)
#else
  #define _ENABLE_USART_SPI_ISR_1() PRAGMA(GCC error "Using USART1 in SPI mode is not supported by this MCU")
#endif

#if defined(USART_SPI2_SUPPORTED) && defined(USART2_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_2() _SETUP_USART_SPI_ISR(USART2_TXC_vect, 2)
#elif defined(USART_SPI2_SUPPORTED) && defined(USART2_TX_vect)
  #define _ENABLE_USART_SPI_ISR_2() _SETUP_USART_SPI_ISR(USART2_TX_vect, 2)
#else
  #define _ENABLE_USART_SPI_ISR_2() PRAGMA(GCC error "Using USART2 in SPI mode is not supported by this MCU")
#endif

#if defined(USART_SPI3_SUPPORTED) && defined(USART3_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_3() _SETUP_USART_SPI_ISR(USART3_TXC_vect, 3)
#elif defined(USART_SPI3_SUPPORTED) && defined(USART3_TX_vect)
  #define _ENABLE_USART_SPI_ISR_3() _SETUP_USART_SPI_ISR(USART3_TX_vect, 3)
#else
  #define _ENABLE_USART_SPI_ISR_3() PRAGMA(GCC error "Using USART3 in SPI mode is not supported by this MCU")
#endif

#if defined(USART_SPI4_SUPPORTED) && defined(USART4_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_4() _SETUP_USART_SPI_ISR(USART4_TXC_vect, 4)
#elif defined(USART_SPI4_SUPPORTED) && defined(USART4_TX_vect)
  #define _ENABLE_USART_SPI_ISR_4() _SETUP_USART_SPI_ISR(USART4_TX_vect, 4)
#else
  #define _ENABLE_USART_SPI_ISR_4() PRAGMA(GCC error "Using USART4 in SPI mode is not supported by this MCU")
#endif

#if defined(USART_SPI5_SUPPORTED) && defined(USART5_TXC_vect)
  #define _ENABLE_USART_SPI_ISR_5() _SETUP_USART_SPI_ISR(USART5_TXC_vect, 5)
#elif defined(USART_SPI5_SUPPORTED) && defined(USART5_TX_vect)
  #define _ENABLE_USART_SPI_ISR_5() _SETUP_USART_SPI_ISR(USART5_TX_vect, 5)
#else
  #define _ENABLE_USART_SPI_ISR_5() PRAGMA(GCC error "Using USART5 in SPI mode is not supported by this MCU")
#endif

#define _ENABLE_USART_SPI(N, TX_BUF_SIZE)          \
  using USART_SPI##N = USART_SPI <N, TX_BUF_SIZE>; \
  _ENABLE_USART_SPI_ISR_##N()

#define ENABLE_USART_SPI0(TX_BUF_SIZE) _ENABLE_USART_SPI(0, TX_BUF_SIZE)
#define ENABLE_USART_SPI1(TX_BUF_SIZE) _ENABLE_USART_SPI(1, TX_BUF_SIZE)
#define ENABLE_USART_SPI2(TX_BUF_SIZE) _ENABLE_USART_SPI(2, TX_BUF_SIZE)
#define ENABLE_USART_SPI3(TX_BUF_SIZE) _ENABLE_USART_SPI(3, TX_BUF_SIZE)
#define ENABLE_USART_SPI4(TX_BUF_SIZE) _ENABLE_USART_SPI(4, TX_BUF_SIZE)
#define ENABLE_USART_SPI5(TX_BUF_SIZE) _ENABLE_USART_SPI(5, TX_BUF_SIZE)
//------------------------------------------------------------------------------------------------
#include "avr-usart-spi.tpp"
#endif // AVR_USART_SPI_H
