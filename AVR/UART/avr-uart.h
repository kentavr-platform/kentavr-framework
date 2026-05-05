#ifndef AVR_UART_H
#define AVR_UART_H
//------------------------------------------------------------------------------------------------
#include <avr/pgmspace.h>
#include "AVR/avr-macro.h"
#include "avr-uart-regs.h"
//------------------------------------------------------------------------------------------------
enum UART_BAUD_RATE
{
    BAUD_2400,
    BAUD_4800,
    BAUD_9600,
    BAUD_19200,
    BAUD_38400,
    BAUD_57600,
    BAUD_115200
    /*  Note: higher baud rates may require careful system clock selection.
        This list can be extended, but must be maintained with caution. */
};
//------------------------------------------------------------------------------------------------
enum UART_DATA_BITS
{
    DATA_BITS_5,
    DATA_BITS_6,
    DATA_BITS_7,
    DATA_BITS_8
};
//------------------------------------------------------------------------------------------------
enum UART_STOP_BITS
{
    STOP_BITS_1,
    STOP_BITS_2
};
//------------------------------------------------------------------------------------------------
enum UART_PARITY
{
    PARITY_NONE,
    PARITY_EVEN,
    PARITY_ODD
};
//------------------------------------------------------------------------------------------------
struct FlashStringWrapper { const char *str; };
#define _flash(a) (FlashStringWrapper{PSTR(a)})
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
class UART
{
public:
    UART() {};
    static void init(enum UART_BAUD_RATE rate,
                     enum UART_DATA_BITS dbits = DATA_BITS_8,
                     enum UART_PARITY parity = PARITY_NONE,
                     enum UART_STOP_BITS sbits= STOP_BITS_1);
    static void disable();
    static void disable_rx();
    static void disable_tx();
    static void enable();
    static void enable_rx();
    static void enable_tx();
    uint8_t peek();
    uint8_t read(uint8_t *buf, const uint8_t count);
    static void write(const char *str);
    static void write(FlashStringWrapper fs);
    static bool tx_busy();
    static void tx_wait();
    static void rx_interrupt();
    static void tx_interrupt();
private:
    using regs = USART_traits <N>;
    static void flush_rx();
    static void flush_tx();
    static bool write_char(const char chr);
    static uint8_t rx_buf[RX_BUF_SIZE];
    static uint8_t tx_buf[TX_BUF_SIZE];
    static volatile uint8_t rx_head, rx_tail;
    static  uint8_t tx_head, tx_tail;
    static uint8_t rx_errors;
    static uint8_t tx_errors;
    //uint8_t available();
};

//------------------------------------------------------------------------------------------------
#define ENABLE_UART(N, RX_BUF_SIZE, TX_BUF_SIZE) \
using UART##N = UART <N, RX_BUF_SIZE, TX_BUF_SIZE>; \
ISR(USART##N##_RX_vect)     { UART##N :: rx_interrupt(); } \
ISR(USART##N##_UDRE_vect)   { UART##N :: tx_interrupt(); }
#define ENABLE_UART0(RX, TX) ENABLE_UART(0, RX, TX)
#define ENABLE_UART1(RX, TX) ENABLE_UART(1, RX, TX)
//------------------------------------------------------------------------------------------------
#include "avr-uart.tpp"
//------------------------------------------------------------------------------------------------
#endif // AVR_UART_H
