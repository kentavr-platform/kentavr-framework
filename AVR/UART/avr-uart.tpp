/*------------------------------------------------------------------------------------------------
 * avr-uart.tpp
 *
 * ATTENTION! This file is included from avr-uart.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
// static members initialisation
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_buf[RX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_buf[TX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_errors = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_errors = 0;
//------------------------------------------------------------------------------------------------
/// void UART :: init(...)
/// Intialize and enable UART with corresponding parameters
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: init(enum UART_BAUD_RATE rate,
                                                         enum UART_DATA_BITS dbits,
                                                         enum UART_PARITY parity,
                                                         enum UART_STOP_BITS sbits)
{
    // disable everything and set default values
    regs :: CTRLA = 0;
    regs :: CTRLB = 0;
    regs :: CTRLC = 0;
    // baud rate
    switch(rate)
    {
    case BAUD_2400:
        regs :: BAUD = (F_CPU / 8 / 2400 - 1) / 2;
        break;
    case BAUD_4800:
        regs :: BAUD = (F_CPU / 8 / 4800 - 1) / 2;
        break;
    case BAUD_9600:
        regs :: BAUD = (F_CPU / 8 / 9600 - 1) / 2;
        break;
    case BAUD_19200:
        regs :: BAUD = (F_CPU / 8 / 19200 - 1) / 2;
        break;
    case BAUD_38400:
        regs :: BAUD = (F_CPU / 8 / 38400 - 1) / 2;
        break;
    case BAUD_57600:
        set_bit(regs :: CTRLA, U2X);
        regs :: BAUD = (F_CPU / 4 / 57600 - 1) / 2;
        break;
    case BAUD_115200:
        set_bit(regs :: CTRLA, U2X);
        regs :: BAUD = (F_CPU / 4 / 115200 - 1) / 2;
        break;
    }
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
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable_rx()
/// Enables UART receiption
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_rx()
{
    set_bits(regs :: CTRLB, RXEN, RXCIE);
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable_tx()
/// Enables UART transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_tx()
{
    set_bits(regs :: CTRLB, TXEN);
}
//------------------------------------------------------------------------------------------------
/// void UART :: enable()
/// Enables UART receiption and transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable()
{
    set_bits(regs :: CTRLB, TXEN, RXEN, RXCIE);
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable_rx()
/// Disables UART receiption
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_rx()
{
    clr_bits(regs :: CTRLB, RXEN, RXCIE);
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable_tx()
/// Disables UART transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_tx()
{
    clr_bits(regs :: CTRLB, TXEN);
}
//------------------------------------------------------------------------------------------------
/// void UART :: disable()
/// Disables UART receiption and transmission (also sets TX pin in OUTPUT mode and HIGH level)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable()
{
    clr_bits(regs :: CTRLB, TXEN, RXEN, RXCIE);
}
//------------------------------------------------------------------------------------------------
/// void UART :: flush_rx()
/// Cleans up (flushes) receiver buffer
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: flush_rx()
{
    rx_head = 0;
    rx_tail = 0;
    rx_errors = 0;
}
//------------------------------------------------------------------------------------------------
/// void UART :: flush_tx()
/// Cleans up (flushes) transmitter buffer
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: flush_tx()
{
    clr_bit(regs :: CTRLB, UDRIE);
    tx_head = 0;
    tx_tail = 0;
    tx_errors = 0;
}
//------------------------------------------------------------------------------------------------
/// bool UART :: tx_busy()
/// Checks the TX line for an active transission
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline bool UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_busy()
{
    return (tx_head != tx_tail) || !test_bit(regs :: STATUS, TXC);
}
//------------------------------------------------------------------------------------------------
/// bool UART :: tx_wait()
/// BLOCKING method that waits until the current transmission will be completed
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_wait()
{
    while(tx_busy());
}
//------------------------------------------------------------------------------------------------
/// void UART :: rx_interrupt();
/// Receiver interrupt handler (ISR)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_interrupt()
{
    // if(test_bit(_UCSRA,_DOR))  // FIXME
    uint8_t index = (rx_head + 1);
    if(index == RX_BUF_SIZE) index = 0;
    rx_buf[rx_head] = regs :: RXDATA;
    rx_head = index;
}
//------------------------------------------------------------------------------------------------
/// void UART :: tx_interrupt();
/// Transmitter UDRE interrupt handler (ISR)
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_interrupt()
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
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline bool UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_char(const char chr)
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
        uint8_t i = (tx_head + 1) & (TX_BUF_SIZE - 1);     // modulo power-of-two optimization
        if (i == tx_tail)
        {
            // TX buffer overrun detected
            if(tx_errors != 0xFF) tx_errors++;
            // you may add some other signals over here - for example turn on a LED at GPIO pin
            GPIO <B3> :: set_mode(OUTPUT_HIGH);
            return false;
        }
        tx_buf[tx_head] = chr;
        tx_head = i;
        set_bit(regs :: CTRLB, UDRIE);     // enable interrupt
    }
    return true;
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(const char *str)
/// Non-blocking write of a null-terminated string from RAM.
/// Drops the whole string if it does not fit into TX buffer
/// at the moment of checking (best-effort, non-atomic guarantee).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(const char *str)
{
    uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
    if(strlen(str) > free)
    {
        // required string does not fit into buffer
        return;
    }
    while(*str)
    {
        write_char(*str++);
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
    while(*str)
    {
        while(!write_char(*str));
        str++;
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
    uint8_t count = 0;
    while(*str)
    {
        if(!write_char(*str++))
        {
            return count;
        }
        count++;
    }
    return count;
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
    const char *ptr = fs.str;
    uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
    if(strlen(ptr) > free)
    {
        // required string does not fit into buffer
        return;
    }
    char ch;
    while ((ch = pgm_read_byte(ptr++)))
    {
        write_char(ch);
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
    const char *ptr = fs.str;
    char ch;
    while ((ch = pgm_read_byte(ptr++)))
    {
        while(!write_char(ch));
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
    uint8_t count = 0;
    const char *ptr = fs.str;
    char ch;
    while((ch = pgm_read_byte(ptr++)))
    {
        if(!write_char(ch))
        {
            return count;
        }
        count++;
    }
    return count;
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(uint8_t *buf, uint8_t count)
/// Non-blocking write 'count' bytes from a buffer 'buf'.
/// Does nothing if 'count' is greater than available TX buffer size at the moment of
/// checking (best-effort, non-atomic guarantee).
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(uint8_t *buf, uint8_t count)
{
    uint8_t free = (tx_tail - tx_head - 1) & (TX_BUF_SIZE - 1);
    if(count > free)
    {
        return;
    }
    while(count--)
    {
        write_char(*buf++);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write_all(uint8_t *buf, uint8_t count)
/// BLOCKING write 'count' bytes from a buffer 'buf'.
/// In case of lack buffer space this method BLOCKS (does not return) and WAITS until the buffer
/// will become free and all 'count' bytes from will be placed in the TX buffer completely.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_all(uint8_t *buf, uint8_t count)
{
    while(count--)
    {
        while(!write_char(*buf));
        buf++;
    }
}
//------------------------------------------------------------------------------------------------
/// uint8_t UART :: write_any(uint8_t *buf, uint8_t count)
/// Non-blocking write 'count' bytes from a buffer 'buf'.
/// In case of lack buffer space this method writes ONLY available PART of the buffer.
/// Returns the number of bytes, placed in the buffer.
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write_any(uint8_t *buf, uint8_t count)
{
    uint8_t n = 0;
    while(count--)
    {
        if(!write_char(*buf++))
        {
            return n;
        }
    }
    return n;
}
//------------------------------------------------------------------------------------------------

