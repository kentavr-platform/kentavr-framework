#ifndef AVR_UART_H
#define AVR_UART_H
//------------------------------------------------------------------------------------------------
#include <avr/pgmspace.h>
#include <string.h>
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
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
class UART
{
public:
    UART() {};
    // configuring and control management
    static void     init(enum UART_BAUD_RATE rate,
                         enum UART_DATA_BITS dbits = DATA_BITS_8,
                         enum UART_PARITY parity = PARITY_NONE,
                         enum UART_STOP_BITS sbits= STOP_BITS_1);
    static void     init(uint32_t rate,
                         enum UART_DATA_BITS dbits = DATA_BITS_8,
                         enum UART_PARITY parity = PARITY_NONE,
                         enum UART_STOP_BITS sbits = STOP_BITS_1);
    static void     disable();
    static void     disable_rx();
    static void     disable_tx();
    static void     enable();
    static void     enable_rx();
    static void     enable_tx();
    static void     flush_rx();
    static void     flush_tx();
    static bool     tx_busy();
    static void     tx_wait();
    //              errors management
    static uint8_t  get_rx_errors();
    static uint8_t  get_tx_errors();
    //              readings
    static uint8_t  available();
    static int      peek();
    static int      read();
    static uint8_t  read(uint8_t *buf, const uint8_t count);
    //              write a single byte from RAM
    static void     write    (uint8_t data);
    static void     send     (uint8_t data);
    //              null-terminated string writes from RAM
    static void     write    (const char *str);
    static void     write_all(const char *str);
    static uint8_t  write_any(const char *str);
    //              null-terminated string writes from PROGMEM
    static void     write    (FlashStringWrapper fs);
    static void     write_all(FlashStringWrapper fs);
    static uint8_t  write_any(FlashStringWrapper fs);
    //              bufer writes from RAM
    static void     write    (const uint8_t *buf, uint8_t count);
    static void     write_all(const uint8_t *buf, uint8_t count);
    static uint8_t  write_any(const uint8_t *buf, uint8_t count);
    //              interrupts handlers
    static void     rx_interrupt();
    static void     tx_interrupt();
private:
    //              internal routines
    static void     _init_common(enum UART_DATA_BITS dbits,
                                 enum UART_PARITY parity,
                                 enum UART_STOP_BITS sbits);
    static bool     _write_char(const char chr);
    //              internal data
    static uint8_t  rx_buf[RX_BUF_SIZE];
    static uint8_t  tx_buf[TX_BUF_SIZE];
    static volatile uint8_t  rx_head, rx_tail;
    static volatile uint8_t  tx_head, tx_tail;
    static uint8_t  rx_errors;
    static uint8_t  tx_errors;
    using           regs = USART_traits <N>;

};
//------------------------------------------------------------------------------------------------
// UART interrupt presets
#define _SETUP_UART_RX_ISR(N)             ISR(USART##N##_RX_vect)   { UART##N :: rx_interrupt(); }
#define _SETUP_UART_TX_ISR(N)             ISR(USART##N##_UDRE_vect) { UART##N :: tx_interrupt(); }

#define _ENABLE_UART_RX_ISR(N, BUF_SIZE)     _ENABLE_UART_RX_ISR_##BUF_SIZE(N)
#define _ENABLE_UART_TX_ISR(N, BUF_SIZE)     _ENABLE_UART_TX_ISR_##BUF_SIZE(N)

#define _ENABLE_UART_RX_ISR_0(N)                // zero RX buffer size - do not setup RX interrupt
#define _ENABLE_UART_RX_ISR_2(N)                _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_4(N)                _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_8(N)                _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_16(N)               _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_32(N)               _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_64(N)               _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_128(N)              _SETUP_UART_RX_ISR(N)
#define _ENABLE_UART_RX_ISR_256(N)              _SETUP_UART_RX_ISR(N)

#define _ENABLE_UART_TX_ISR_0(N)                // zero TX buffer size - do not setup TX interrupt
#define _ENABLE_UART_TX_ISR_2(N)                _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_4(N)                _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_8(N)                _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_16(N)               _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_32(N)               _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_64(N)               _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_128(N)              _SETUP_UART_TX_ISR(N)
#define _ENABLE_UART_TX_ISR_256(N)              _SETUP_UART_TX_ISR(N)

// main ENABLE_UART() macro
#define _ENABLE_UART(N, RX_BUF_SIZE, TX_BUF_SIZE) \
using UART##N = UART <N, RX_BUF_SIZE, TX_BUF_SIZE>; \
_ENABLE_UART_RX_ISR(N, RX_BUF_SIZE) \
_ENABLE_UART_TX_ISR(N, TX_BUF_SIZE)

// platform-specific wrappers
#define ENABLE_UART0(RX_BUF_SIZE, TX_BUF_SIZE) _ENABLE_UART(0, RX_BUF_SIZE, TX_BUF_SIZE)
#define ENABLE_UART1(RX_BUF_SIZE, TX_BUF_SIZE) _ENABLE_UART(1, RX_BUF_SIZE, TX_BUF_SIZE)
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline FlashStringWrapper
console_type_name(const UART<N, RX_BUF_SIZE, TX_BUF_SIZE> &)
{
    return _flash("UART");
}
//------------------------------------------------------------------------------------------------
#include "avr-uart.tpp"
//------------------------------------------------------------------------------------------------
#endif // AVR_UART_H
