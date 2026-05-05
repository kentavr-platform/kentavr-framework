template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_buf[RX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_buf[TX_BUF_SIZE];
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
volatile uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: rx_errors = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_head = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_tail = 0;
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
uint8_t UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_errors = 0;
//------------------------------------------------------------------------------------------------z
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
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: flush_tx()
{
    clr_bit(regs :: CTRLB, UDRIE);
    tx_head = 0;
    tx_tail = 0;
    tx_errors = 0;
}
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline bool UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_busy()
{
    return (tx_head != tx_tail) || !test_bit(regs :: STATUS, TXC);
}
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_wait()
{
    while(tx_busy())
    {
        GPIO <A7> :: toggle();
    }
}
//------------------------------------------------------------------------------------------------
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
        // === BUFFER WRITE ===
        uint8_t i = (tx_head + 1) & (TX_BUF_SIZE - 1);     // modulo power-of-two optimization
        if (i == tx_tail)
        {
            // TX buffer overrun
            if(tx_errors != 0xFF) tx_errors++;
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
/// Writes null-terminated string from RAM
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(const char *str)
{
    while(*str)
    {
        write_char(*str++);
    }
}
//------------------------------------------------------------------------------------------------
/// void UART :: write(_flash(const char *str))
/// Writes null-terminated string from flash memory (PROGMEM)
/// Hint: always use _flash() macro for literals to save your RAM
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(FlashStringWrapper fs)
{
    const char *ptr = fs.str;
    char ch;
    while ((ch = pgm_read_byte(ptr++)))
    {
        write_char(ch);
    }
}
//------------------------------------------------------------------------------------------------

