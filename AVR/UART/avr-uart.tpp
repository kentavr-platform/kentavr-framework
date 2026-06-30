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
/**
 * @brief Initialize and enable the UART using an arbitrary baud rate.
 *
 * Configures baud rate, frame format, RX/TX buffers and hardware receiver or
 * transmitter according to the template buffer sizes. Global interrupts are
 * enabled after successful configuration because buffered RX/TX uses ISRs.
 *
 * @param rate Requested baud rate in bits per second.
 * @param dbits Number of data bits in one UART frame.
 * @param parity Parity mode.
 * @param sbits Number of stop bits.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if the requested baud rate cannot be represented
 *         with acceptable error.
 */
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
/**
 * @brief Initialize and enable the UART using a predefined baud rate.
 *
 * Converts the selected UART_BAUD_RATE value to its numeric baud rate and
 * delegates the actual setup to init(uint32_t, UART_DATA_BITS, UART_PARITY,
 * UART_STOP_BITS).
 *
 * @param rate Predefined baud rate selector.
 * @param dbits Number of data bits in one UART frame.
 * @param parity Parity mode.
 * @param sbits Number of stop bits.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if @p rate is not a supported selector or the baud
 *         configuration error is too high.
 */
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
/**
 * @brief Configure UART registers and reset internal driver state.
 *
 * Disables the UART control registers, selects the best baud mode, configures
 * frame format, flushes enabled buffers and then enables RX/TX according to
 * RX_BUF_SIZE and TX_BUF_SIZE.
 *
 * @param rate Requested baud rate in bits per second.
 * @param dbits Number of data bits in one UART frame.
 * @param parity Parity mode.
 * @param sbits Number of stop bits.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if baud error is greater than the accepted limit.
 */
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
/**
 * @brief Select the best baud configuration for normal or double-speed mode.
 *
 * Calculates baud settings for both UART clock modes and returns the one with
 * the lower baud-rate error.
 *
 * @param rate Requested baud rate in bits per second.
 *
 * @return Baud configuration with the lowest error.
 */
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
/**
 * @brief Calculate UART baud register settings for one clock mode.
 *
 * Computes UBRR value, real baud rate and baud error in ppm for either normal
 * speed or double-speed mode. Invalid zero baud rate returns a configuration
 * with UINT32_MAX error.
 *
 * @param rate Requested baud rate in bits per second.
 * @param u2x True to calculate double-speed mode, false for normal mode.
 *
 * @return Calculated baud configuration.
 */
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
/**
 * @brief Enable UART reception.
 *
 * Enables the hardware receiver and RX-complete interrupt when RX buffering is
 * configured. For RX_BUF_SIZE == 0 this method compiles to no code.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_rx()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        set_bits(regs :: CTRLB, RXEN, RXCIE);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable UART transmission.
 *
 * Enables the hardware transmitter when TX buffering is configured. For
 * TX_BUF_SIZE == 0 this method compiles to no code.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable_tx()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        set_bits(regs :: CTRLB, TXEN);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable configured UART directions.
 *
 * Enables RX when RX_BUF_SIZE is non-zero and TX when TX_BUF_SIZE is non-zero.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: enable()
{
    enable_rx();
    enable_tx();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable UART reception.
 *
 * Disables the hardware receiver and RX-complete interrupt when RX buffering is
 * configured. For RX_BUF_SIZE == 0 this method compiles to no code.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_rx()
{
    if constexpr(RX_BUF_SIZE > 0)
    {
        clr_bits(regs :: CTRLB, RXEN, RXCIE);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable UART transmission.
 *
 * Disables the hardware transmitter when TX buffering is configured. For
 * TX_BUF_SIZE == 0 this method compiles to no code.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable_tx()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        clr_bits(regs :: CTRLB, TXEN);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable configured UART directions.
 *
 * Disables RX when RX_BUF_SIZE is non-zero and TX when TX_BUF_SIZE is non-zero.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: disable()
{
    disable_rx();
    disable_tx();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Clear the RX ring buffer and RX error counter.
 *
 * Resets RX head/tail indices and clears the receiver overflow counter. For
 * RX_BUF_SIZE == 0 this method compiles to no code.
 */
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
/**
 * @brief Clear the TX ring buffer and TX error counter.
 *
 * Disables the data-register-empty interrupt, resets TX head/tail indices and
 * clears the transmitter overflow counter. For TX_BUF_SIZE == 0 this method
 * compiles to no code.
 */
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
/**
 * @brief Check whether a transmission is still active.
 *
 * The transmitter is considered busy while the TX ring buffer contains data or
 * the hardware transmit-complete flag is not set.
 *
 * @return true if queued or hardware transmission is active.
 * @return false if TX is disabled at compile time or idle.
 */
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
/**
 * @brief Wait until the current transmission is complete.
 *
 * Blocks while tx_busy() is true. For TX_BUF_SIZE == 0 this method returns
 * immediately.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: tx_wait()
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(tx_busy());
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Handle the UART receive interrupt.
 *
 * Reads the received byte from the hardware data register and appends it to the
 * RX ring buffer. If the buffer is full, the byte is discarded and rx_errors is
 * incremented up to 255.
 *
 * This method is intended to be called only from the UART RX ISR generated by
 * ENABLE_UARTx().
 */
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
/**
 * @brief Handle the UART data-register-empty interrupt.
 *
 * Sends the next queued byte from the TX ring buffer. If the buffer is empty,
 * disables the UDR-empty interrupt until new data is queued.
 *
 * This method is intended to be called only from the UART UDRE ISR generated by
 * ENABLE_UARTx().
 */
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
/**
 * @brief Queue or directly send one byte.
 *
 * If the TX ring buffer is empty and the hardware data register is ready, the
 * byte is written directly to the data register. Otherwise the byte is appended
 * to the TX ring buffer and the UDR-empty interrupt is enabled.
 *
 * @param chr Byte to transmit.
 *
 * @return true if the byte was accepted for transmission.
 * @return false if TX is disabled at compile time or the TX buffer is full.
 */
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
/**
 * @brief Write one byte in non-blocking mode.
 *
 * Attempts to send or queue one byte. If the TX buffer is full, the byte is
 * dropped and tx_errors is incremented by _write_char().
 *
 * @param data Byte to transmit.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: write(uint8_t data)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        _write_char(data);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Write one byte in blocking mode.
 *
 * Repeats until the byte is accepted by _write_char(). For TX_BUF_SIZE == 0
 * this method compiles to no code.
 *
 * @param data Byte to transmit.
 */
template <uint8_t N, uint16_t RX_BUF_SIZE, uint16_t TX_BUF_SIZE>
__inline void UART <N, RX_BUF_SIZE, TX_BUF_SIZE> :: send(uint8_t data)
{
    if constexpr(TX_BUF_SIZE > 0)
    {
        while(!_write_char(data));
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Write a RAM string in all-or-nothing non-blocking mode.
 *
 * Checks the currently available TX buffer space and writes the string only if
 * the whole null-terminated string fits at that moment. The terminating null
 * byte is not transmitted.
 *
 * @param str Null-terminated RAM string to transmit.
 */
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
/**
 * @brief Write a full RAM string in blocking mode.
 *
 * Writes every byte of the null-terminated string, waiting for TX buffer space
 * whenever needed. The terminating null byte is not transmitted.
 *
 * @param str Null-terminated RAM string to transmit.
 */
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
/**
 * @brief Write as much of a RAM string as currently possible.
 *
 * Transmits bytes from the null-terminated string until the string ends or
 * _write_char() rejects a byte because the TX buffer is full.
 *
 * @param str Null-terminated RAM string to transmit.
 *
 * @return Number of bytes accepted for transmission.
 */
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
/**
 * @brief Write a PROGMEM string in all-or-nothing non-blocking mode.
 *
 * Checks the currently available TX buffer space and writes the string only if
 * the whole null-terminated flash string fits at that moment. The terminating
 * null byte is not transmitted.
 *
 * @param fs Flash string wrapper, typically created by _flash("text").
 */
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
/**
 * @brief Write a full PROGMEM string in blocking mode.
 *
 * Writes every byte of the null-terminated flash string, waiting for TX buffer
 * space whenever needed. The terminating null byte is not transmitted.
 *
 * @param fs Flash string wrapper, typically created by _flash("text").
 */
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
/**
 * @brief Write as much of a PROGMEM string as currently possible.
 *
 * Transmits bytes from the null-terminated flash string until the string ends
 * or _write_char() rejects a byte because the TX buffer is full.
 *
 * @param fs Flash string wrapper, typically created by _flash("text").
 *
 * @return Number of bytes accepted for transmission.
 */
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
/**
 * @brief Write a RAM byte buffer in all-or-nothing non-blocking mode.
 *
 * Checks the currently available TX buffer space and writes the buffer only if
 * all @p count bytes fit at that moment.
 *
 * @param buf Pointer to the first byte to transmit.
 * @param count Number of bytes to transmit.
 */
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
/**
 * @brief Write a full RAM byte buffer in blocking mode.
 *
 * Writes all @p count bytes, waiting for TX buffer space whenever needed.
 *
 * @param buf Pointer to the first byte to transmit.
 * @param count Number of bytes to transmit.
 */
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
/**
 * @brief Write as much of a RAM byte buffer as currently possible.
 *
 * Transmits bytes from @p buf until @p count bytes are accepted or
 * _write_char() rejects a byte because the TX buffer is full.
 *
 * @param buf Pointer to the first byte to transmit.
 * @param count Maximum number of bytes to transmit.
 *
 * @return Number of bytes accepted for transmission.
 */
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
/**
 * @brief Return the RX overflow error counter.
 *
 * The counter is incremented by rx_interrupt() when a received byte cannot be
 * stored because the RX ring buffer is full. The counter saturates at 255 and
 * is reset by flush_rx().
 *
 * @return RX error count, or 0 when RX buffering is disabled.
 */
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
/**
 * @brief Return the TX overflow error counter.
 *
 * The counter is incremented by _write_char() when a byte cannot be queued
 * because the TX ring buffer is full. The counter saturates at 255 and is reset
 * by flush_tx().
 *
 * @return TX error count, or 0 when TX buffering is disabled.
 */
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
/**
 * @brief Return the number of bytes currently available in the RX buffer.
 *
 * @return Number of queued RX bytes, or 0 when RX buffering is disabled.
 */
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
/**
 * @brief Peek the next received byte without removing it from the RX buffer.
 *
 * @return Next byte as an unsigned 8-bit value promoted to int.
 * @return -1 if the RX buffer is empty or RX buffering is disabled.
 */
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
/**
 * @brief Read and remove the next byte from the RX buffer.
 *
 * @return Next byte as an unsigned 8-bit value promoted to int.
 * @return -1 if the RX buffer is empty or RX buffering is disabled.
 */
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
/**
 * @brief Read multiple bytes from the RX buffer.
 *
 * Removes up to @p count bytes from the RX ring buffer and copies them to
 * @p buf. Reading stops early if the RX buffer becomes empty.
 *
 * @param buf Destination buffer.
 * @param count Maximum number of bytes to read.
 *
 * @return Number of bytes copied to @p buf.
 */
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
