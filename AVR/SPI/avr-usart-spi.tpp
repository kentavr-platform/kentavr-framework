/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-usart-spi.tpp
 * Included from avr-usart-spi.h; do not compile separately.
//----------------------------------------------------------------------------------------------*/
#include <string.h>
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t TX_BUF_SIZE>
typename USART_SPI <N, TX_BUF_SIZE> :: MasterState
USART_SPI <N, TX_BUF_SIZE> :: master {};
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure the USART as an SPI master.
 *
 * This function does not enable global interrupts. They must be enabled by
 * the application for transfers to complete.
 *
 * @param frequency Requested maximum SCK frequency in Hz. The selected rate
 *                   is the fastest supported rate that does not exceed it.
 * @param clock_mode SPI clock polarity and phase.
 * @param bit_order Bit transmission order.
 * @return OK on success, ERR_BUSY if a transfer is active, or
 *         ERR_BAD_PARAMETER if settings are out of range.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: init_master(uint32_t frequency,
                                                            SPI_Clock_Mode clock_mode,
                                                            SPI_Bit_Order bit_order)
{
    if(busy)
        return ERR_BUSY;

    if(frequency == 0 || frequency > F_CPU / 2)
        return ERR_BAD_PARAMETER;

    const uint32_t divider = (F_CPU - 1UL) / (2UL * frequency) + 1UL;
    if(divider > regs :: max_divider)
        return ERR_BAD_PARAMETER;

    switch(N)
    {
        case 0:
            #if defined(__AVR_HAVE_PRR1_PRUSART0)
                clr_bit(regs :: POWER1, regs :: POWER_BIT);
            #elif defined(__AVR_HAVE_PRR0_PRUSART0) || defined(__AVR_HAVE_PRR_PRUSART0)
                clr_bit(regs :: POWER0, regs :: POWER_BIT);
            #endif
            break;
        case 1:
            #if defined(__AVR_HAVE_PRR1_PRUSART1)
                clr_bit(regs :: POWER1, regs :: POWER_BIT);
            #elif defined(__AVR_HAVE_PRR0_PRUSART1) || defined(__AVR_HAVE_PRR_PRUSART1)
                clr_bit(regs :: POWER0, regs :: POWER_BIT);
            #endif
            break;
        case 2:
            #if defined(__AVR_HAVE_PRR1_PRUSART2)
                clr_bit(regs :: POWER1, regs :: POWER_BIT);
            #elif defined(__AVR_HAVE_PRR0_PRUSART2) || defined(__AVR_HAVE_PRR_PRUSART2)
                clr_bit(regs :: POWER0, regs :: POWER_BIT);
            #endif
            break;
        case 3:
            #if defined(__AVR_HAVE_PRR1_PRUSART3)
                clr_bit(regs :: POWER1, regs :: POWER_BIT);
            #elif defined(__AVR_HAVE_PRR0_PRUSART3) || defined(__AVR_HAVE_PRR_PRUSART3)
                clr_bit(regs :: POWER0, regs :: POWER_BIT);
            #endif
            break;
    }

    disable();
    regs :: BAUD = 0;
    uint8_t control = _bits(regs :: MODE0, regs :: MODE1);
    if(bit_order == SPI_LSB_FIRST)
        set_bit(control, regs :: ORDER);
    if(clock_mode & 1)
        set_bit(control, regs :: PHASE);
#if defined(AVR_DX_FAMILY)
    GPIO <typename pins :: SCK> :: set_mode(OUTPUT_LOW);
    if(clock_mode & 2)
        set_bit(regs :: CLOCK_CONTROL, regs :: INVERT);
    else
        clr_bit(regs :: CLOCK_CONTROL, regs :: INVERT);
#else
    if(clock_mode & 2)
    {
        set_bit(control, regs :: POLARITY);
        GPIO <typename pins :: SCK> :: set_mode(OUTPUT_HIGH);
    }
    else
        GPIO <typename pins :: SCK> :: set_mode(OUTPUT_LOW);
#endif

    regs :: CTRLC = control;
    regs :: STATUS = _bit(regs :: TX_COMPLETE);  // W1C
    if constexpr(regs :: tx_interrupt_in_a)
    {
        regs :: BAUD = uint16_t(divider << 6);
        regs :: CTRLB = _bits(regs :: TX_ENABLE, regs :: RX_ENABLE);
        regs :: CTRLA = _bit(regs :: TX_INTERRUPT);
    }
    else
    {
        regs :: CTRLB = _bits(regs :: TX_ENABLE, regs :: RX_ENABLE, regs :: TX_INTERRUPT);
        // Classic USART requires UBRR to be loaded after enabling the transmitter.
        regs :: BAUD = uint16_t(divider - 1);
    }
    mode = SPI_MASTER;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Compatibility method for the SPI driver interface.
 *
 * USART SPI hardware does not support slave mode. Calling this method causes
 * a compile-time error.
 *
 * @param config SPI slave configuration (unused).
 * @return ERR_BAD_MODE; this method cannot be called successfully.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: init_slave(const SPI_Slave_Config &config)
{
    (void) config;
    static_assert(N != N, "USART SPI does not support slave mode");
    return ERR_BAD_MODE;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable the USART SPI peripheral and cancel an active transfer.
 *
 * Cancellation does not wait for a byte already on the wire and does not
 * invoke the completion callback. A blocking transfer cancelled this way
 * returns ERR_ABORTED. Call wait() first if the transfer must finish normally.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void USART_SPI <N, TX_BUF_SIZE> :: disable()
{
    ATOMIC_BLOCK
    {
        if constexpr(regs :: tx_interrupt_in_a)
            regs :: CTRLA = 0;
        else
            clr_bit(regs :: CTRLB, regs :: TX_INTERRUPT);
        regs :: CTRLB = 0;
        while(test_bit(regs :: STATUS, regs :: RX_COMPLETE))
        {
            const uint8_t received = regs :: RXDATA;
            (void)received;
        }
        if(busy)
            master.result = ERR_ABORTED;
        master.callback = nullptr;
        mode = SPI_DISABLED;
        busy = false;
    }
}
//------------------------------------------------------------------------------------------------
/** @brief Check whether a master transfer is active. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline bool USART_SPI <N, TX_BUF_SIZE> :: is_busy()
{
    return busy;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get the currently configured USART SPI mode.
 * @return SPI_DISABLED or SPI_MASTER.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline SPI_Mode USART_SPI <N, TX_BUF_SIZE> :: get_mode()
{
    return mode;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Block until the active transfer completes or is cancelled.
 *
 * Global interrupts must be enabled while waiting. Do not call this method
 * from an interrupt handler.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void USART_SPI <N, TX_BUF_SIZE> :: wait()
{
    while(busy);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmit bytes and discard received data.
 *
 * With a null callback, data is read directly from the caller's buffer and
 * this method waits for completion. The buffer must remain valid until return.
 * With a callback, data is copied into the driver's fixed-size TX buffer and
 * this method returns after starting the transfer. The callback runs from
 * interrupt context and must be short and non-blocking.
 *
 * @param data Non-null buffer containing @p count bytes.
 * @param count Byte count; must be nonzero. With a callback, it must not
 *              exceed TX_BUF_SIZE.
 * @param callback Optional completion callback; null selects blocking mode.
 * @return The final result in blocking mode, or OK when a non-blocking
 *         transfer starts; ERR_BAD_PARAMETER for null data or zero count;
 *         ERR_BAD_MODE if not initialized; ERR_BUSY if a transfer is active;
 *         ERR_BAD_PARAMETER for oversized non-blocking TX data;
 *         ERR_ABORTED if blocking transfer is cancelled by disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: send(const uint8_t *data, uint16_t count,
                                                    void (*callback)(ResultCode))
{
    return transfer(data, nullptr, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Receive bytes while transmitting 0xFF.
 *
 * The receive buffer must remain valid until return in blocking mode or until
 * the completion callback runs in non-blocking mode. Blocking use requires
 * enabled global interrupts and must not be called from an interrupt handler.
 *
 * @param data Non-null destination buffer for @p count bytes.
 * @param count Byte count; must be nonzero. It is not limited by TX_BUF_SIZE.
 * @param callback Optional completion callback; null selects blocking mode.
 * @return The final result in blocking mode, or OK when a non-blocking
 *         transfer starts; ERR_BAD_PARAMETER for null data or zero count;
 *         ERR_BAD_MODE if not initialized; ERR_BUSY if a transfer is active;
 *         ERR_ABORTED if blocking transfer is cancelled by disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: receive(uint8_t *data, uint16_t count,
                                                       void (*callback)(ResultCode))
{
    return transfer(nullptr, data, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transfer bytes in both directions.
 *
 * Either @p tx or @p rx may be null, but not both. A null callback selects
 * blocking mode and reads TX bytes directly from the caller's buffer. A
 * non-null callback selects non-blocking mode and copies TX bytes into the
 * driver's fixed-size buffer. The RX buffer must remain valid until return
 * or until the completion callback runs, respectively.
 *
 * @param tx Optional source buffer for @p count bytes.
 * @param rx Optional destination buffer for @p count received bytes.
 * @param count Byte count; must be nonzero. For non-blocking TX it must not
 *              exceed TX_BUF_SIZE.
 * @param callback Optional completion callback; null selects blocking mode.
 * @return The final result in blocking mode, or OK when a non-blocking
 *         transfer starts; ERR_BAD_PARAMETER for two null buffers or zero
 *         count; ERR_BAD_MODE if not initialized; ERR_BUSY if a transfer is
 *         active; ERR_BAD_PARAMETER for oversized non-blocking TX data;
 *         ERR_ABORTED if blocking transfer is cancelled by disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: duplex(const uint8_t *tx, uint8_t *rx, uint16_t count,
                                                      void (*callback)(ResultCode))
{
    return transfer(tx, rx, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Validate, prepare, and start a master transfer; wait if blocking.
 * @param tx Optional source buffer, copied only for non-blocking transfers.
 * @param rx Optional receive buffer, written by the interrupt handler.
 * @param size Number of bytes to transfer.
 * @param callback Optional completion callback.
 * @return Validation error, OK for a started non-blocking transfer, or the
 *         final result of a blocking transfer.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode USART_SPI <N, TX_BUF_SIZE> :: transfer(const uint8_t *tx, uint8_t *rx, uint16_t size,
                                                     void (*callback)(ResultCode))
{
    if(size == 0 || (!tx && !rx))
        return ERR_BAD_PARAMETER;

    if(mode != SPI_MASTER)
        return ERR_BAD_MODE;

    if(busy)
        return ERR_BUSY;

    if(tx && callback && size > TX_BUF_SIZE)
        return ERR_BAD_PARAMETER;

    master.tx = tx;
    if(tx && callback)
    {
        memcpy(tx_buf, tx, size);
        master.tx = tx_buf;
    }
    master.rx = rx;
    master.count = size;
    master.index = 0;
    master.callback = callback;
    master.result = ERR_UNKNOWN;
    busy = true;

    if(callback)
    {
        _start();
        return OK;
    }

    _start();
    wait();
    return master.result;
}
//------------------------------------------------------------------------------------------------
/** @brief Load the first byte and start the USART SPI transfer. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void USART_SPI <N, TX_BUF_SIZE> :: _start()
{
    regs :: TXDATA = master.tx ? master.tx[0] : 0xFF;
}
//------------------------------------------------------------------------------------------------
/** @brief Publish the transfer result and invoke its optional callback. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void USART_SPI <N, TX_BUF_SIZE> :: complete(ResultCode result)
{
    auto callback = master.callback;
    master.callback = nullptr;
    master.result = result;
    busy = false;
    if(callback)
        callback(result);  // The callback may already have started the next operation.
}
//------------------------------------------------------------------------------------------------
/** @brief Process a completed byte and advance the master transfer. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void USART_SPI <N, TX_BUF_SIZE> :: interrupt()
{
    regs :: STATUS = _bit(regs :: TX_COMPLETE);  // W1C
    const uint8_t received = regs :: RXDATA;     // prevent receiver buffer overflow anyway

    if(master.rx)
        master.rx[master.index] = received;

    if(++master.index == master.count)
        complete(OK);
    else
        regs :: TXDATA = master.tx ? master.tx[master.index] : 0xFF;
}
