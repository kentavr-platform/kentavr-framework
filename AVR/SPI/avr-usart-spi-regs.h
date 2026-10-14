/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-usart-spi-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_USART_SPI_REGS_H
#define AVR_USART_SPI_REGS_H
//------------------------------------------------------------------------------------------------
template <uint8_t N>
struct USART_SPI_traits
{
    static constexpr bool exists = false;
    static constexpr bool tx_interrupt_in_a = false;
    static constexpr uint16_t max_divider = 0;
};
//------------------------------------------------------------------------------------------------
#define DEFINE_USART_SPI_REGS(N, _RX_ENABLE, _TX_ENABLE, _TX_INTERRUPT, \
                              _TX_COMPLETE, _RX_COMPLETE, _MODE0, _MODE1, \
                              _POLARITY) \
template <> \
struct USART_SPI_traits <N> : USART_traits <N> { \
    static constexpr bool exists = true; \
    static constexpr bool tx_interrupt_in_a = false; \
    static constexpr uint16_t max_divider = 4096; \
    static constexpr uint8_t RX_ENABLE = _RX_ENABLE; \
    static constexpr uint8_t TX_ENABLE = _TX_ENABLE; \
    static constexpr uint8_t TX_INTERRUPT = _TX_INTERRUPT; \
    static constexpr uint8_t TX_COMPLETE = _TX_COMPLETE; \
    static constexpr uint8_t RX_COMPLETE = _RX_COMPLETE; \
    static constexpr uint8_t MODE0 = _MODE0; \
    static constexpr uint8_t MODE1 = _MODE1; \
    static constexpr uint8_t PHASE = 1; \
    static constexpr uint8_t ORDER = 2; \
    static constexpr uint8_t POLARITY = _POLARITY; \
    static constexpr uint8_t POWER_BIT = PRUSART##N; \
    USART_SPI_POWER_REGS \
};
//------------------------------------------------------------------------------------------------
#define DEFINE_USART_SPI_DX_REGS(N, _USART, _PORT) \
template <> \
struct USART_SPI_traits <N> { \
    static constexpr bool exists = true; \
    static constexpr bool tx_interrupt_in_a = true; \
    static constexpr uint16_t max_divider = 1023; \
    static inline volatile uint8_t& STATUS = _USART.STATUS; \
    static inline volatile uint8_t& CTRLA = _USART.CTRLA; \
    static inline volatile uint8_t& CTRLB = _USART.CTRLB; \
    static inline volatile uint8_t& CTRLC = _USART.CTRLC; \
    static inline volatile uint8_t& RXDATA = _USART.RXDATAL; \
    static inline volatile uint8_t& TXDATA = _USART.TXDATAL; \
    static inline volatile uint16_t& BAUD = _USART.BAUD; \
    static inline volatile uint8_t& CLOCK_CONTROL = _PORT.PIN2CTRL; \
    static constexpr uint8_t RX_ENABLE = USART_RXEN_bp; \
    static constexpr uint8_t TX_ENABLE = USART_TXEN_bp; \
    static constexpr uint8_t TX_INTERRUPT = USART_TXCIE_bp; \
    static constexpr uint8_t TX_COMPLETE = USART_TXCIF_bp; \
    static constexpr uint8_t RX_COMPLETE = USART_RXCIF_bp; \
    static constexpr uint8_t PHASE = USART_UCPHA_bp; \
    static constexpr uint8_t ORDER = USART_UDORD_bp; \
    static constexpr uint8_t MODE0 = USART_CMODE_0_bp; \
    static constexpr uint8_t MODE1 = USART_CMODE_1_bp; \
    static constexpr uint8_t INVERT = PORT_INVEN_bp; \
};
//------------------------------------------------------------------------------------------------
#if defined(USART_TX_vect) && !defined(USART0_TX_vect)
  #define USART0_TX_vect USART_TX_vect
#endif
//------------------------------------------------------------------------------------------------
#if defined(PRR0)
  #define USART_SPI_POWER0_REG \
    static inline volatile uint8_t& POWER0 = PRR0;
#elif defined(PRR)
  #define USART_SPI_POWER0_REG \
    static inline volatile uint8_t& POWER0 = PRR;
#else
  #define USART_SPI_POWER0_REG
#endif
#if defined(PRR1)
  #define USART_SPI_POWER1_REG \
    static inline volatile uint8_t& POWER1 = PRR1;
#else
  #define USART_SPI_POWER1_REG
#endif
#define USART_SPI_POWER_REGS \
    USART_SPI_POWER0_REG \
    USART_SPI_POWER1_REG
//------------------------------------------------------------------------------------------------
#if defined(UDR0) && defined(UMSEL00) && defined(UMSEL01)
  DEFINE_USART_SPI_REGS(0, RXEN0, TXEN0, TXCIE0, TXC0, RXC0,
                        UMSEL00, UMSEL01, UCPOL0)
  #define USART_SPI0_SUPPORTED
#endif
#if defined(UDR1) && defined(UMSEL10) && defined(UMSEL11)
  DEFINE_USART_SPI_REGS(1, RXEN1, TXEN1, TXCIE1, TXC1, RXC1,
                        UMSEL10, UMSEL11, UCPOL1)
  #define USART_SPI1_SUPPORTED
#endif
#if defined(UDR2) && defined(UMSEL20) && defined(UMSEL21)
  DEFINE_USART_SPI_REGS(2, RXEN2, TXEN2, TXCIE2, TXC2, RXC2,
                        UMSEL20, UMSEL21, UCPOL2)
  #define USART_SPI2_SUPPORTED
#endif
#if defined(UDR3) && defined(UMSEL30) && defined(UMSEL31)
  DEFINE_USART_SPI_REGS(3, RXEN3, TXEN3, TXCIE3, TXC3, RXC3,
                        UMSEL30, UMSEL31, UCPOL3)
  #define USART_SPI3_SUPPORTED
#endif
//------------------------------------------------------------------------------------------------
// AVR_DX_FAMILY branch
#if defined(USART0_TXC_vect) && defined(USART0)
  DEFINE_USART_SPI_DX_REGS(0, USART0, PORTA)
  #define USART_SPI0_SUPPORTED
#endif
#if defined(USART1_TXC_vect) && defined(USART1)
  DEFINE_USART_SPI_DX_REGS(1, USART1, PORTC)
  #define USART_SPI1_SUPPORTED
#endif
#if defined(USART2_TXC_vect) && defined(USART2)
  DEFINE_USART_SPI_DX_REGS(2, USART2, PORTF)
  #define USART_SPI2_SUPPORTED
#endif
#if defined(USART3_TXC_vect) && defined(USART3)
  DEFINE_USART_SPI_DX_REGS(3, USART3, PORTB)
  #define USART_SPI3_SUPPORTED
#endif
//------------------------------------------------------------------------------------------------
#endif // AVR_USART_SPI_REGS_H
