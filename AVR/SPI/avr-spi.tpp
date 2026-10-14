/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-spi.tpp
 * Included from avr-spi.h; do not compile separately.
//----------------------------------------------------------------------------------------------*/
#include <string.h>
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint16_t TX_BUF_SIZE>
typename SPI <N, TX_BUF_SIZE> :: MasterState
SPI <N, TX_BUF_SIZE> :: master {};
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure this peripheral as an SPI master.
 *
 * The selected SCK frequency is the fastest hardware-supported rate that
 * does not exceed @p frequency. This function does not enable global
 * interrupts; they must be enabled by the application for transfers to
 * complete asynchronously.
 *
 * @param frequency Requested maximum SCK frequency in Hz. It must be
 *                   between ceil(F_CPU / 128) and floor(F_CPU / 2), inclusive.
 * @param clock_mode SPI clock polarity and phase; use SPI_CLOCK_MODE_0
 *                   through SPI_CLOCK_MODE_3.
 * @param bit_order Bit transmission order; use SPI_MSB_FIRST or
 *                  SPI_LSB_FIRST.
 * @return OK on success, ERR_BUSY if a master transfer is active, or
 *         ERR_BAD_PARAMETER if the frequency is out of range.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: init_master(uint32_t frequency,
    SPI_Clock_Mode clock_mode, SPI_Bit_Order bit_order)
{
    if(busy)
        return ERR_BUSY;

    if(frequency == 0 || frequency > F_CPU / 2 || frequency < (F_CPU + 127UL) / 128UL)
        return ERR_BAD_PARAMETER;

    regs :: CONTROL = 0;

    // Choose the fastest supported rate that does not exceed the requested rate.
    uint32_t rate = (F_CPU + 1UL) / 2UL;
    uint8_t step = 0;
    while(rate > frequency)
    {
        rate = (rate + 1UL) / 2UL;
        ++step;
    }
    const uint8_t prescaler = step == 6 ? 3 : uint8_t(step / 2);
    const bool double_speed = step < 6 && !(step & 1);
    mode = SPI_MASTER;
    configure(clock_mode, bit_order, true, prescaler, double_speed);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure this peripheral as an SPI slave.
 *
 * The first outgoing byte is loaded from @p config.first_tx. Each received
 * byte is passed to @p config.callback from interrupt context, and the
 * callback supplies the byte for the following transfer. This function
 * does not enable global interrupts; they must be enabled by the
 * application for the callback to run.
 *
 * @param config Slave clock mode, bit order, first outgoing byte, and
 *               required byte callback. Enum values must be valid members
 *               of their respective enums.
 * @return OK on success, ERR_BUSY if a master transfer is active, or
 *         ERR_BAD_PARAMETER if the callback is null.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: init_slave(const SPI_Slave_Config &config)
{
    if(busy)
        return ERR_BUSY;

    if(!config.callback)
        return ERR_BAD_PARAMETER;

    regs :: CONTROL = 0;
    slave = config;
    regs :: DATA = config.first_tx;
    mode = SPI_SLAVE;
    configure(config.clock_mode, config.bit_order, false, 0, false);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure the peripheral registers and SPI pin directions.
 * @param clock_mode SPI clock polarity and phase.
 * @param bit_order Bit transmission order.
 * @param master true to configure master mode; false for slave mode.
 * @param prescaler Encoded clock prescaler value for master mode.
 * @param double_speed true to select the peripheral's double-speed setting.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: configure(SPI_Clock_Mode clock_mode, SPI_Bit_Order bit_order,
                                                bool master, uint8_t prescaler, bool double_speed)
{
    if constexpr(regs :: has_power_control)
        clr_bit(regs :: POWER, regs :: POWER_BIT);

#if defined(AVR_DX_FAMILY)
    regs :: INT_MASK = 0;
    regs :: CONTROL_B = (uint8_t) clock_mode;
#endif

    uint8_t control = _bit(regs :: ENABLE);

    if(master)
    {
#if defined(AVR_DX_FAMILY)
        set_bit(regs :: CONTROL_B, regs :: SS_DISABLE);
#else
        GPIO <typename pins :: SS>   :: set_mode(OUTPUT_HIGH);  // this disables slave sense
#endif
        GPIO <typename pins :: MOSI> :: set_mode(OUTPUT_LOW);
        GPIO <typename pins :: MISO> :: set_mode(INPUT_OPEN);
        if(clock_mode >= SPI_CLOCK_MODE_2)
            GPIO <typename pins :: SCK> :: set_mode(OUTPUT_HIGH);
        else
            GPIO <typename pins :: SCK> :: set_mode(OUTPUT_LOW);
        set_bits(control, regs :: MASTER);
    }
    else
    {
        GPIO <typename pins :: SS>   :: set_mode(INPUT_PULLUP);
        GPIO <typename pins :: MOSI> :: set_mode(INPUT_OPEN);
        GPIO <typename pins :: MISO> :: set_mode(OUTPUT_HIGH);
        GPIO <typename pins :: SCK>  :: set_mode(INPUT_OPEN);
    }

    if(bit_order == SPI_LSB_FIRST)
        set_bits(control, regs :: ORDER);

    control |= uint8_t(prescaler << regs :: PRESCALE);

#if defined(AVR_DX_FAMILY)
    if(double_speed)
        set_bit(control, regs :: DOUBLE);
    // Normal mode: read STATUS then DATA to clear IF and WRCOL
    const uint8_t status = regs :: STATUS; (void) status;   // read status to clear it
    const uint8_t data = regs :: DATA; (void) data;         // read data to clear it
    regs :: CONTROL = control;
    regs :: INT_MASK = _bit(regs :: INTERRUPT);
#else

    if(clock_mode & 1)
        set_bit(control, regs :: PHASE);
    if(clock_mode & 2)
        set_bit(control, regs :: POLARITY);
    regs :: STATUS = double_speed ? _bit(regs :: DOUBLE) : 0;
    const uint8_t status = regs :: STATUS; (void) status;   // read status to clear it
    const uint8_t data = regs :: DATA; (void) data;         // read data to clear it
    set_bit(control, regs :: INTERRUPT);
    regs :: CONTROL = control;
#endif
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable SPI and cancel any active master transfer.
 *
 * Cancellation does not invoke the transfer completion callback. The
 * current mode becomes SPI_DISABLED and is_busy() returns false. A blocking
 * transfer cancelled this way returns ERR_ABORTED.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: disable()
{
    ATOMIC_BLOCK
    {
        #if defined(AVR_DX_FAMILY)
            regs :: INT_MASK = 0;
        #endif
        regs :: CONTROL = 0;
        if(busy)
            master.result = ERR_ABORTED;
        master.callback = nullptr;
        mode = SPI_DISABLED;
        busy = false;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check whether a master transfer is active.
 * @return true while a master transfer is in progress; false otherwise.
 *         Slave byte handling does not set this flag.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline bool SPI <N, TX_BUF_SIZE> :: is_busy()
{
    return busy;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Block until the active master transfer completes or is cancelled.
 *
 * Global interrupts must be enabled while waiting. Do not call this method
 * from an interrupt handler. In slave or disabled mode it returns
 * immediately because no master transfer is active.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: wait()
{
    while(busy);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get the currently configured SPI mode.
 * @return SPI_DISABLED, SPI_MASTER, or SPI_SLAVE.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline SPI_Mode SPI <N, TX_BUF_SIZE> :: get_mode()
{
    return mode;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Start a master transfer and discard all received bytes.
 *
 * If @p callback is null, this method transmits directly from @p data, waits
 * for completion, and returns its result. The source buffer must remain valid
 * until the method returns. If @p callback is non-null, the data is copied to
 * the driver's fixed-size buffer and the method returns after starting the
 * transfer. The callback runs from interrupt context and must be short and
 * non-blocking. Blocking use requires global interrupts and must not be called
 * from an interrupt handler.
 *
 * @param data Non-null source buffer containing @p count bytes.
 * @param count Number of bytes to transmit; must be nonzero and must not
 *              exceed TX_BUF_SIZE when @p callback is non-null.
 * @param callback Optional completion callback. Null selects blocking mode.
 * @return The transfer result in blocking mode, or OK when the transfer starts
 *         in non-blocking mode; ERR_BAD_PARAMETER for a null data
 *         pointer, zero count, or an oversized non-blocking TX buffer;
 *         ERR_BAD_MODE unless initialized as master; ERR_BUSY if another
 *         master transfer is active; ERR_ABORTED if blocking transfer is
 *         cancelled with disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: send(const uint8_t *data, uint16_t count,
                                                 void (*callback)(ResultCode))
{
    return transfer(data, nullptr, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Receive bytes as master, transmitting 0xFF for each byte.
 *
 * The receive buffer remains owned by the caller. It must stay valid and
 * untouched until this method returns in blocking mode, or until the
 * completion callback runs in non-blocking mode. The count is not limited by
 * TX_BUF_SIZE because no caller transmit data is copied. Blocking use requires
 * global interrupts and must not be called from an interrupt handler.
 *
 * @param data Non-null destination buffer for @p count received bytes.
 * @param count Number of bytes to receive; must be nonzero.
 * @param callback Optional completion callback. Null selects blocking mode;
 *                 otherwise it is called from interrupt context.
 * @return The transfer result in blocking mode, or OK when the transfer starts
 *         in non-blocking mode; ERR_BAD_PARAMETER for a null data
 *         pointer or zero count; ERR_BAD_MODE unless initialized as
 *         master; ERR_BUSY if another master transfer is active;
 *         ERR_ABORTED if blocking transfer is cancelled with disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: receive(uint8_t *data, uint16_t count,
                                                    void (*callback)(ResultCode))
{
    return transfer(nullptr, data, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Start a master transfer with optional transmit and receive data.
 *
 * If @p callback is null, non-null transmit data is read directly from @p tx;
 * it must remain valid until this method returns. If @p callback is non-null,
 * transmit data is copied into the driver's fixed-size buffer before return.
 * If @p tx is null, 0xFF is transmitted; if @p rx is null, received bytes
 * are discarded. At least one pointer must be non-null. A supplied
 * receive buffer must remain valid and untouched until this method returns
 * in blocking mode, or until completion in non-blocking mode. A null
 * @p callback selects blocking mode; otherwise the callback runs from
 * interrupt context and must be short and non-blocking. Blocking use requires
 * global interrupts and must not be called from an interrupt handler.
 *
 * @param tx Optional source buffer; when non-null, must provide @p count
 *           bytes. Blocking mode reads it directly; non-blocking mode copies
 *           it and requires @p count not to exceed TX_BUF_SIZE.
 * @param rx Optional destination buffer for received bytes.
 * @param count Number of bytes to transfer; must be nonzero.
 * @param callback Optional completion callback. Null selects blocking mode.
 * @return The transfer result in blocking mode, or OK when the transfer starts
 *         in non-blocking mode; ERR_BAD_PARAMETER for two null buffers, zero
 *         count, or oversized non-blocking TX data; ERR_BAD_MODE unless
 *         initialized as master; ERR_BUSY if another master transfer is
 *         active; ERR_ABORTED if blocking transfer is cancelled with
 *         disable().
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: duplex(const uint8_t *tx, uint8_t *rx, uint16_t count,
                                                   void (*callback)(ResultCode))
{
    return transfer(tx, rx, count, callback);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Validate, prepare, and start a master transfer; wait if blocking.
 * @param tx Optional transmit buffer; copied for non-blocking transfers and
 *           read directly for blocking transfers.
 * @param rx Optional receive buffer; written by the interrupt handler.
 * @param size Number of bytes to transfer.
 * @param callback Optional completion callback.
 * @return The result code for validation or transfer completion.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline ResultCode SPI <N, TX_BUF_SIZE> :: transfer(const uint8_t *tx, uint8_t *rx, uint16_t size,
                                                 void (*callback)(ResultCode))
{
    if(!size || (!tx && !rx))
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
        // non-blocking mode
        _start();
        return OK;
    }

    // blocking mode
    _start();
    wait();
    return master.result;
}
//------------------------------------------------------------------------------------------------
/** @brief Write the first master byte and start the SPI transfer. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: _start()
{
    regs :: DATA = master.tx ? master.tx[0] : 0xFF;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Store the master transfer result and invoke its optional callback.
 * @param result Result passed to the completion callback.
 */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: complete(ResultCode result)
{
    auto callback = master.callback;
    master.callback = nullptr;
    master.result = result;
    busy = false;
    if(callback)
        callback(result);  // The callback may already have started the next operation.
}
//------------------------------------------------------------------------------------------------
/** @brief Read the completed byte and advance the master or slave transfer. */
template <uint8_t N, uint16_t TX_BUF_SIZE>
__inline void SPI <N, TX_BUF_SIZE> :: interrupt()
{
    // read status and data to clear interrupt flag
    const uint8_t status = regs :: STATUS; (void) status;
    const uint8_t received = regs :: DATA;
    if(mode == SPI_SLAVE)
    {
        uint8_t next = 0xFF;
        slave.callback(received, &next);
        regs :: DATA = next;
        return;
    }

    if(master.rx)
        master.rx[master.index] = received;

    if(++master.index == master.count)
        complete(OK);
    else
        regs :: DATA = master.tx ? master.tx[master.index] : 0xFF;
}
//------------------------------------------------------------------------------------------------
