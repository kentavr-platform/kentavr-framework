#ifndef AVR_UART_REGS
#define AVR_UART_REGS
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
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
};
template <uint8_t N> struct USART_traits;
#ifdef __AVR_ATmega1284P__
DEFINE_USART_REGS(0, UDR0, UDR0, UCSR0A, UCSR0A, UCSR0B, UCSR0C, UBRR0);
DEFINE_USART_REGS(1, UDR1, UDR1, UCSR1A, UCSR1A, UCSR1B, UCSR1C, UBRR1);
// the following declarations use UART #0 bits because they are the same for UART #0 and UART #1
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
#endif // __AVR_ATmega1284P__
//------------------------------------------------------------------------------------------------
#ifdef AVR128DX_FAMILY

#endif // AVR128DX_FAMILY
//------------------------------------------------------------------------------------------------
#endif // AVR_UART_REGS
