/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-uart.tpp
 *
 * WARNING! This file is included from avr-uart.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
// static members initialisation
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_buf[RX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_buf[TX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_errors = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_errors = 0;
//------------------------------------------------------------------------------------------------
/// ResultCode UART :: init(uint32_t rate, ...)
/// Intialize and enable UART with corresponding parameters
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline ResultCode UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: init(uint32_t rate,
                                                               enum UART_DATA_BITS dbits,
                                                               enum UART_PARITY parity,
                                                               enum UART_STOP_BITS sbits)
{
    ResultCode result = _configure(rate, dbits, parity, sbits);
    if(result != OK)
        return result;
    enable_interrupts();
    return OK;
};
//------------------------------------------------------------------------------------------------
/// ResultCode UART :: init(enum UART_BAUD_RATE rate, ...)
/// Intialize and enable UART with corresponding parameters
/// This method is preferred for standart rates and works faster.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline ResultCode UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: init(enum UART_BAUD_RATE rate,
                                                               enum UART_DATA_BITS dbits,
                                                               enum UART_PARITY parity,
                                                               enum UART_STOP_BITS sbits)
{
    switch(rate)
    {
    case BAUD_2400:
        return init(2400, dbits, parity, sbits);
    case BAUD_4800:
        return init(4800, dbits, parity, sbits);
    case BAUD_9600:
        return init(9600, dbits, parity, sbits);
    case BAUD_19200:
        return init(19200, dbits, parity, sbits);
    case BAUD_38400:
        return init(38400, dbits, parity, sbits);
    case BAUD_57600:
        return init(57600, dbits, parity, sbits);
    case BAUD_115200:
        return init(115200, dbits, parity, sbits);
    }
    return ERR_BAD_PARAMETER;
};
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline ResultCode UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: _configure(uint32_t rate,
                                                                     enum UART_DATA_BITS dbits,
                                                                     enum UART_PARITY parity,
                                                                     enum UART_STOP_BITS sbits)
{
    // disable everything and set default values
    regs :: CTRLA = 0;
    regs :: CTRLB = 0;
    regs :: CTRLC = 0;
    constexpr uint32_t max_baud_error_ppm = 20000; // 2%
    BaudConfig baud_cfg = _select_baud(rate);
    if(baud_cfg.error_ppm > max_baud_error_ppm)
    {
        // ATTENTION! Baud rate error is too high!
        return ERR_BAD_PARAMETER;
    }
    if(baud_cfg.u2x)
    {
        set_bit(regs :: CTRLA, U2X);
    }
    regs :: BAUD = baud_cfg.ubrr;
    // data bits
    switch(dbits)
    {
    case DATA_BITS_5:
        break;
    case DATA_BITS_6:
        set_bits(regs :: CTRLC, UCSZ0);
        break;
    case DATA_BITS_7:
        set_bits(regs :: CTRLC, UCSZ1);
        break;
    case DATA_BITS_8:
        set_bits(regs :: CTRLC, UCSZ0, UCSZ1);
        break;
    }
    // stop bits
    switch(sbits)
    {
    case STOP_BITS_1:
        break;
    case STOP_BITS_2:
        set_bits(regs :: CTRLC, USBS);
        break;
    }
    // parity
    switch(parity)
    {
    case PARITY_NONE:
        break;
    case PARITY_EVEN:
        set_bits(regs :: CTRLC, UPM1);
        break;
    case PARITY_ODD:
        set_bits(regs :: CTRLC, UPM0, UPM1);
        break;
    }
    flush_rx();
    flush_tx();
    enable();
    return OK;
}
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline BaudConfig UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: _select_baud(uint32_t rate)
{
    BaudConfig x1 = _calc_baud(rate, false);
    BaudConfig x2 = _calc_baud(rate, true);
    if(x2.error_ppm < x1.error_ppm)
        return x2;
    return x1;
}
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline BaudConfig UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: _calc_baud(uint32_t rate, bool u2x)
{
    constexpr uint32_t UBRR_MAX = (1u << 12) - 1;
    BaudConfig cfg = {0, 0, UINT32_MAX, u2x};
    if(rate == 0)
        return cfg;
    const uint32_t divider = u2x ? 8UL : 16UL;
    const uint64_t denom = uint64_t(rate) * divider;
    uint64_t n = (uint64_t(F_CPU) + denom / 2) / denom;
    if(n < 1)
        n = 1;
    if(n > uint64_t(UBRR_MAX) + 1)
        n = uint64_t(UBRR_MAX) + 1;
    cfg.ubrr = uint16_t(n - 1);
    cfg.real_rate = uint32_t(uint64_t(F_CPU) / (uint64_t(divider) * n));
    const uint32_t diff = (cfg.real_rate > rate) ? cfg.real_rate - rate : rate - cfg.real_rate;
    cfg.error_ppm = uint32_t(uint64_t(diff) * 1000000ULL / rate);
    return cfg;
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable_rx()
/// Enables UART reception
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_rx()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        set_bits(regs :: CTRLB, RXEN, RXCIE);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable_tx()
/// Enables UART transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_tx()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        set_bits(regs :: CTRLB, TXEN);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable()
/// Enables UART reception and transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable()
{
    enable_rx();
    enable_tx();
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable_rx()
/// Disables UART reception
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_rx()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        clr_bits(regs :: CTRLB, RXEN, RXCIE);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable_tx()
/// Disables UART transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_tx()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        clr_bits(regs :: CTRLB, TXEN);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable()
/// Disables UART reception and transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable()
{
    disable_rx();
    disable_tx();
}
//------------------------------------------------------------------------------------------------
/// void UART :: flush_rx()
/// Cleans up (flushes) receiver buffer
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: flush_rx()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        rx_head = 0;
        rx_tail = 0;
        rx_errors = 0;
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: flush_tx()
/// Cleans up (flushes) transmitter buffer
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: flush_tx()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        clr_bit(regs :: CTRLB, UDRIE);
        tx_head = 0;
        tx_tail = 0;
        tx_errors = 0;
    }
}
//------------------------------------------------------------------------------------------------
/// bool UART :: tx_busy()
/// Checks the TX line for an active transmission
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline bool UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_busy()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        return (tx_head != tx_tail) || !test_bit(regs :: STATUS, TXC);
    }
    else
    {
        return false;
    }
}
//------------------------------------------------------------------------------------------------
/// bool UART :: tx_wait()
/// BLOCKING method that waits until the current transmission will be completed
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_wait()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(tx_busy());
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: rx_interrupt();
/// Receiver interrupt handler (ISR)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_interrupt()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        uint8_t data = regs :: RXDATA;
        uint8_t next = (rx_head + 1) & (RX_BUF_SIZE - 1);      // modulo power-of-two optimization
        if(next == rx_tail)
        {
            // RX buffer overrun
            if(rx_errors != 0xFF) rx_errors++;
            // You may add some other signals over here - for example turn on a LED at GPIO pin
            // GPIO <B2> :: set_mode(OUTPUT_HIGH);
            // then do nothing - the received byte will be discarded
            return;
        }
        rx_buf[rx_head] = data;
        rx_head = next;
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: tx_interrupt();
/// Transmitter UDRE interrupt handler (ISR)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_interrupt()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        if(tx_head != tx_tail)
        {
            // prepare to send next byte
            regs :: TXDATA = tx_buf[tx_tail];
            tx_tail = (tx_tail + 1) & (TX_BUF_SIZE - 1);      // modulo power-of-two optimization
        }
        else
        {
            // buffer is empty - so disable interrupt
            clr_bit(regs :: CTRLB, UDRIE);
        }
    }
}
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
bool UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: _write_char(const char chr)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        if(tx_head == tx_tail && test_bit(regs :: STATUS, UDRE))
        {
            // === DIRECT WRITE ===
            // The output buffer is empty - send a single byte directly.
            // At this point the UDRIE interrupt has been disabled
            // either by its handler or by flush_tx().
            set_bit(regs :: STATUS, TXC);
            regs :: TXDATA = chr;
        }
        else
        {
            // === BUFFERED WRITE ===
            uint8_t next = (tx_head + 1) & (TX_BUF_SIZE - 1);     // modulo power-of-two optimization
            if (next == tx_tail)
            {
                // TX buffer overrun detected
                if(tx_errors != 0xFF) tx_errors++;
                // You may add some other signals over here - for example turn on a LED at GPIO pin
                //GPIO <B3> :: set_mode(OUTPUT_HIGH);
                return false;
            }
            tx_buf[tx_head] = chr;
            tx_head = next;
            set_bit(regs :: CTRLB, UDRIE);     // enable interrupt
        }
        return true;
    }
    else
    {
        return false;
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(uint8_t data)
/// Non-blocking write of a single byte from RAM.
/// Does nothing (skips) if there is no free space in TX buffer
/// at the moment of checking (best-effort, non-atomic guarantee).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(uint8_t data)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        _write_char(data);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: send(uint8_t data)
/// BLOCKING write of a single byte from RAM.
/// In case of full TX buffer BLOCKS (does not return) and WAITS until
/// the buffer will become free and all the string will be placed in the buffer completely.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: send(uint8_t data)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(!_write_char(data));
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(const char *str)
/// Non-blocking write of a null-terminated string from RAM.
/// Drops the whole string if it does not fit into TX buffer
/// at the moment of checking (best-effort, non-atomic guarantee).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(const char *str)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
        if(strlen(str) > free)
        {
            // required string does not fit into buffer
            return;
        }
        while(*str)
        {
            _write_char(*str++);
        }
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write_all(const char *str)
/// BLOCKING write of a null-terminated string from RAM.
/// In case of lack buffer space this method BLOCKS (does not return) and WAITS until
/// the buffer will become free and all the string will be placed in the buffer completely.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_all(const char *str)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(*str)
        {
            while(!_write_char(*str));
            str++;
        }
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: write_any(const char *str)
/// Non-blocking write of a null-terminated string from RAM.
/// In case of lack buffer space this method writes ONLY available PART of the string.
/// Returns the number of bytes, placed in the buffer.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_any(const char *str)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        uint8_t count = 0;
        while(*str)
        {
            if(!_write_char(*str++))
            {
                return count;
            }
            count++;
        }
        return count;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(_flash(const char *str))
/// Non-blocking write of a null-terminated string from flash memory (PROGMEM).
/// Drops the whole string if it does not fit into TX buffer
/// at the moment of checking (best-effort, non-atomic guarantee).
/// Hint: always use _flash() macro for literals to save your RAM
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(FlashStringWrapper fs)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        PGM_P ptr = fs.str;
        uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
        if(strlen_P(ptr) > free)
        {
            // required string does not fit into buffer
            return;
        }
        char ch;
        while ((ch = pgm_read_byte(ptr++)))
        {
            _write_char(ch);
        }
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write_all(_flash(const char *str))
/// BLOCKING write of a null-terminated string from flash memory (PROGMEM).
/// In case of lack buffer space this method BLOCKS (does not return) and WAITS until
/// the buffer will become free and all the string will be placed in the buffer completely.
/// Hint: always use _flash() macro for literals to save your RAM
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_all(FlashStringWrapper fs)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        PGM_P ptr = fs.str;
        char ch;
        while ((ch = pgm_read_byte(ptr++)))
        {
            while(!_write_char(ch));
        }
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write_any(_flash(const char *str))
/// Non-blocking write of a null-terminated string from flash memory (PROGMEM).
/// In case of lack buffer space this method writes ONLY available PART of the string.
/// Returns the number of bytes, placed in the buffer.
/// Hint: always use _flash() macro for literals to save your RAM
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_any(FlashStringWrapper fs)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        uint8_t count = 0;
        PGM_P ptr = fs.str;
        char ch;
        while((ch = pgm_read_byte(ptr++)))
        {
            if(!_write_char(ch))
            {
                return count;
            }
            count++;
        }
        return count;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(const uint8_t *buf, uint8_t count)
/// Non-blocking write 'count' bytes from a buffer 'buf'.
/// Does nothing if 'count' is greater than available TX buffer size at the moment of
/// checking (best-effort, non-atomic guarantee).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(const uint8_t *buf, uint8_t count)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
        if(count > free)
        {
            return;
        }
        while(count--)
        {
            _write_char(*buf++);
        }
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write_all(const uint8_t *buf, uint8_t count)
/// BLOCKING write 'count' bytes from a buffer 'buf'.
/// In case of lack buffer space this method BLOCKS (does not return) and WAITS until the buffer
/// will become free and all 'count' bytes from will be placed in the TX buffer completely.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_all(const uint8_t *buf, uint8_t count)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(count--)
        {
            while(!_write_char(*buf));
            buf++;
        }
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: write_any(const uint8_t *buf, uint8_t count)
/// Non-blocking write 'count' bytes from a buffer 'buf'.
/// In case of lack buffer space this method writes ONLY available PART of the buffer.
/// Returns the number of bytes, placed in the buffer.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_any(const uint8_t *buf, uint8_t count)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        uint8_t n = 0;
        while(count--)
        {
            if(!_write_char(*buf++))
            {
                return n;
            }
            n++;
        }
        return n;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: get_rx_errors()
/// Return the number of receiver errors.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: get_rx_errors()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        return rx_errors;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: get_tx_errors()
/// Return the number of transmitter errors.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: get_tx_errors()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        return tx_errors;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: available()
/// Return the number of bytes, available in RX buffer.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: available()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        return (rx_head - rx_tail) & (RX_BUF_SIZE - 1);
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
/// int UART :: peek()
/// Read the next byte from RX buffer without extracting - leave the buffer unchanged.
/// Returns the byte or -1 in case of error (no data - empty buffer).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline int UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: peek()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        if(rx_head != rx_tail)
        {
            return rx_buf[rx_tail];
        }
        else
        {
            // RX buffer is empty
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
//------------------------------------------------------------------------------------------------
/// int UART :: read()
/// Extract the next byte from RX buffer.
/// Returns the byte or -1 in case of error (no data - empty buffer).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline int UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: read()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        if(rx_head != rx_tail)
        {
            uint8_t data = rx_buf[rx_tail];
            rx_tail = (rx_tail + 1) & (RX_BUF_SIZE - 1);     // modulo power-of-two optimization
            return data;
        }
        else
        {
            // RX buffer is empty
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: read(uint8_t *buf, const uint8_t count)
/// Extract next 'count' bytes from RX buffer.
/// Returns the number of bytes read.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: read(uint8_t *buf, const uint8_t count)
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        uint8_t i = 0;
        while(i < count)
        {
            if(rx_head == rx_tail)
            {
                // no data left
                break;
            }
            buf[i++] = rx_buf[rx_tail];
            rx_tail = (rx_tail + 1) & (RX_BUF_SIZE - 1);
        }
        return i;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
