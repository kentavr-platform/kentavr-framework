/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-uart-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_UART_REGS
#define AVR_UART_REGS
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
template <uint8_t N>
struct USART_traits
{
    static constexpr bool exists = false;
};
//------------------------------------------------------------------------------------------------
#define DEFINE_USART_REGS(N, _RXDATA, _TXDATA, _STATUS, _CTRLA, _CTRLB, _CTRLC, _BAUD) \
template <> \
struct USART_traits <N> { \
    static inline volatile uint8_t& RXDATA = _RXDATA; \
    static inline volatile uint8_t& TXDATA = _TXDATA; \
    static inline volatile uint8_t& STATUS = _STATUS; \
    static inline volatile uint8_t& CTRLA  = _CTRLA; \
    static inline volatile uint8_t& CTRLB  = _CTRLB; \
    static inline volatile uint8_t& CTRLC  = _CTRLC; \
    static inline volatile uint16_t& BAUD  = _BAUD; \
    static constexpr bool exists = true; \
};
//------------------------------------------------------------------------------------------------
#if defined(UDR0)
  DEFINE_USART_REGS(0, UDR0, UDR0, UCSR0A, UCSR0A, UCSR0B, UCSR0C, UBRR0);
  #define RXEN    RXEN0
  #define TXEN    TXEN0
  #define RXCIE   RXCIE0
  #define UDRIE   UDRIE0
  #define TXC     TXC0
  #define UDRE    UDRE0
  #define UCSZ0   UCSZ00
  #define UCSZ1   UCSZ01
  #define UCSZ2   UCSZ02
  #define U2X     U2X0
  #define USBS    USBS0
  #define UPM0    UPM00
  #define UPM1    UPM01
#elif defined(UDR1)
  // some MCUs do not have UART0, but have UART1
  #define RXEN    RXEN1
  #define TXEN    TXEN1
  #define RXCIE   RXCIE1
  #define UDRIE   UDRIE1
  #define TXC     TXC1
  #define UDRE    UDRE1
  #define UCSZ0   UCSZ10
  #define UCSZ1   UCSZ11
  #define UCSZ2   UCSZ12
  #define U2X     U2X1
  #define USBS    USBS1
  #define UPM0    UPM10
  #define UPM1    UPM11
#else
  // make dummy definitions for MCUs without a hardware UART.
  #define RXEN    0
  #define TXEN    0
  #define RXCIE   0
  #define UDRIE   0
  #define TXC     0
  #define UDRE    0
  #define UCSZ0   0
  #define UCSZ1   0
  #define UCSZ2   0
  #define U2X     0
  #define USBS    0
  #define UPM0    0
  #define UPM1    0
#endif
//------------------------------------------------------------------------------------------------
#if defined(UDR1)
  DEFINE_USART_REGS(1, UDR1, UDR1, UCSR1A, UCSR1A, UCSR1B, UCSR1C, UBRR1);
#endif

#if defined(UDR2)
  DEFINE_USART_REGS(2, UDR2, UDR2, UCSR2A, UCSR2A, UCSR2B, UCSR2C, UBRR2);
#endif

#if defined(UDR3)
  DEFINE_USART_REGS(3, UDR3, UDR3, UCSR3A, UCSR3A, UCSR3B, UCSR3C, UBRR3);
#endif
//------------------------------------------------------------------------------------------------
#endif
