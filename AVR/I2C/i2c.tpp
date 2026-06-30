/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: i2c.tpp
 *
 * ATTENTION! This file is included from i2c.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
template <uint8_t N, uint8_t TX_BUF_SIZE>
uint8_t TWI <N, TX_BUF_SIZE> :: tx_buf[TX_BUF_SIZE];
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
volatile bool TWI <N, TX_BUF_SIZE> :: busy = false;
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
I2C_Mode TWI <N, TX_BUF_SIZE> :: mode = I2C_DISABLED;
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
typename TWI <N, TX_BUF_SIZE> :: MasterState
TWI <N, TX_BUF_SIZE> :: master {};
//------------------------------------------------------------------------------------------------
template <uint8_t N, uint8_t TX_BUF_SIZE>
I2C_Slave_Config
TWI <N, TX_BUF_SIZE> :: slave {};
//------------------------------------------------------------------------------------------------
/**
 * @brief Handle the TWI interrupt state machine.
 *
 * This method is called from the hardware TWI ISR declared by ENABLE_I2C macro
 *
 * It handles both master and slave modes:
 * - master transmitter;
 * - master receiver;
 * - slave receiver;
 * - slave transmitter;
 * - arbitration lost;
 * - address/data NACK;
 * - bus error recovery.
 *
 * In master mode the method advances the active transfer and completes it with
 * _complete() when the transfer finishes or fails.
 *
 * In slave mode it calls user-provided slave callbacks from
 * I2C_Slave_Config. These callbacks are executed directly from ISR context and
 * must be short and non-blocking.
 *
 * Application code should not call this method directly.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: interrupt()
{
    switch(regs :: SR & 0xF8)   // TWI status register
    {
    //-- Master states ---------------------------------------------------------------------------
    case TW_START:
    case TW_REP_START:
        _write_dr(master.address);
        _nack();                         // TWEA is irrelevant while transmitting address/data.
        break;
    case TW_MT_SLA_ACK:
    case TW_MT_DATA_ACK:
        if(master.index < master.size)
        {
            _write_dr(master.buf[master.index++]);
            _nack();
        }
        else
        {
            _complete(OK);
        }
        break;
    case TW_MR_SLA_ACK:
        // ACK every byte except the last one.  NACK after the last byte is the
        // standard TWI way to tell the slave that the master receiver is done.
        if(master.size > 1)
        {  _ack();  }  else  {  _nack();  }
        break;
    case TW_MR_DATA_ACK:
        _read_dr();
        if(master.index < (master.size - 1))
        {  _ack();  }  else  {  _nack();  }
        break;
    case TW_MR_DATA_NACK:
        _read_dr();
        _complete(OK);
        break;
    case TW_MT_ARB_LOST:
        // Another master won arbitration.  Re-request START; hardware will wait
        // until the bus becomes free.
        _start();
        break;
    case TW_MT_SLA_NACK:
    case TW_MR_SLA_NACK:
        if(--master.tries_left)
            _start();
        else
            _complete(ERR_NOT_FOUND);
        break;
    case TW_MT_DATA_NACK:
        // index was incremented before this status appeared.  index == 1 means
        // the first payload byte was rejected; later means the transfer started
        // but the slave stopped accepting data.
        _complete(master.index > 1 ? ERR_ABORTED : ERR_REJECTED);
        break;
    //-- Slave receiver states -------------------------------------------------------------------
    case TW_SR_SLA_ACK:
        if(slave.receiver_callback(I2C_SLAVE_START, 0) == OK)
        {  _ack();  }  else  {  _nack();  }
        break;
    case TW_SR_GCALL_ACK:
        if(slave.receiver_callback(I2C_SLAVE_BROADCAST_START, 0) == OK)
        {  _ack();  }  else  {  _nack();  }
        break;
    case TW_SR_DATA_ACK:
    case TW_SR_GCALL_DATA_ACK:
        if(slave.receiver_callback(I2C_SLAVE_DATA, regs :: DR) == OK)
        {  _ack();  }  else  {  _nack();  }
        break;
    case TW_SR_STOP:
        slave.receiver_callback(I2C_SLAVE_END, 0);
        _listen();
        break;
    //-- Slave transmitter states ----------------------------------------------------------------
    case TW_ST_SLA_ACK:
    case TW_ST_DATA_ACK:
    {
        uint8_t data = 0xFF;
        ResultCode res = slave.transmitter_callback(I2C_SLAVE_DATA, &data);
        _write_dr(data);
        if(res == OK)
        {  _ack();  }  else  {  _nack();  }
        break;
    }
    case TW_ST_DATA_NACK:
        slave.transmitter_callback(I2C_SLAVE_END, 0);
        _listen();
        break;
    case TW_ST_LAST_DATA:
        slave.transmitter_callback(I2C_SLAVE_MORE, 0);
        _listen();
        break;
    case TW_SR_DATA_NACK:
        _nack();
        break;
    case TW_NO_INFO:
        break;
    case TW_BUS_ERROR:
    default:
        _reset();
        break;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Initialize the TWI peripheral in master mode.
 *
 * Configures the hardware TWI peripheral as an I2C master and selects the SCL
 * clock frequency.
 *
 * The driver uses TWI prescaler = 1. The resulting SCL frequency is calculated
 * by the AVR TWI formula:
 *
 * @code
 * SCL = F_CPU / (16 + 2 * TWBR)
 * @endcode
 *
 * Because TWBR is an 8-bit register, only frequencies that can be represented
 * with prescaler = 1 are accepted.
 *
 * This method resets the TWI control state and enables TWI interrupts
 * automatically.
 *
 * @param freq Requested I2C clock frequency in Hz.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if freq is outside the supported range.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline ResultCode TWI <N, TX_BUF_SIZE> :: init_master(uint32_t freq)
{
    // AVR TWI SCL frequency:
    // SCL = F_CPU / (16 + 2 * TWBR * prescaler)
    //
    // This driver uses prescaler = 1, so:
    // min divider = 16 + 2 * 255 = 526
    // max divider = 16 + 2 * 0   = 16
    static constexpr uint32_t BASE_DIVIDER = 16;
    static constexpr uint32_t MAX_TWBR     = 255;
    static constexpr uint32_t MAX_DIVIDER  = BASE_DIVIDER + 2 * MAX_TWBR;
    static constexpr uint32_t min_freq = (F_CPU + MAX_DIVIDER - 1) / MAX_DIVIDER;
    static constexpr uint32_t max_freq = F_CPU / BASE_DIVIDER;

    if(freq < min_freq || freq > max_freq)
        return ERR_BAD_PARAMETER;

    mode = I2C_MASTER;
    regs :: SR = 0;
    regs :: BR = static_cast <uint8_t> (((F_CPU / freq) - 16) / 2);
    _reset();
    enable_interrupts();
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Initialize the TWI peripheral in slave mode.
 *
 * Configures the hardware TWI peripheral as an I2C slave device.
 *
 * The slave address and callback functions are taken from @p config.
 * The configuration is copied into the driver, so the original config object
 * does not need to remain alive after this call.
 *
 * Both receiver_callback and transmitter_callback are required.
 * If one of them is missing, the peripheral is disabled and
 * ERR_BAD_PARAMETER is returned.
 *
 * Slave callbacks are called from ISR context:
 * - receiver_callback() handles slave receive events;
 * - transmitter_callback() provides bytes when the master reads from this slave.
 *
 * If receive_broadcasts is true, the slave also acknowledges the I2C general
 * call address.
 *
 * This method resets the TWI control state and enables TWI interrupts
 * automatically.
 *
 * @param config Slave configuration.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if required callbacks are missing.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline ResultCode TWI <N, TX_BUF_SIZE> :: init_slave(const I2C_Slave_Config &config)
{
    if(!config.receiver_callback || !config.transmitter_callback)
    {
        disable();
        return ERR_BAD_PARAMETER;
    }
    slave = config;
    mode = I2C_SLAVE;
    regs :: AR = (slave.address << 1) | (slave.receive_broadcasts ? 1 : 0);
    _reset();
    enable_interrupts();
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send data to an I2C slave device.
 *
 * Starts a master transmit operation.
 *
 * If @p callback is nullptr, the method works in blocking mode:
 * it starts the transfer, waits until it is completed, and returns the final
 * transfer result.
 *
 * If @p callback is not nullptr, the method works in non-blocking mode:
 * it copies the data into the internal TX buffer, starts the transfer and
 * returns immediately. The callback is called when the transfer is completed
 * or failed.
 *
 * In non-blocking mode @p size must not exceed TX_BUF_SIZE.
 * The user data buffer may be temporary because the data is copied before the
 * transfer starts.
 *
 * The callback is executed from ISR context and must be short and non-blocking.
 *
 * @param address 7-bit I2C slave address. Address 0 may be used for general
 *           call write.
 * @param data Pointer to the data to send.
 * @param size Number of bytes to send.
 * @param callback Optional completion callback. nullptr selects blocking mode.
 *
 * @return OK if a non-blocking transfer was started successfully.
 * @return OK if a blocking transfer completed successfully.
 * @return ERR_BAD_MODE if the bus is not initialized in master mode.
 * @return ERR_BUSY if another master transfer is already active.
 * @return ERR_BAD_PARAMETER if data is nullptr, size is zero, or the
 *         non-blocking payload is larger than TX_BUF_SIZE.
 * @return ERR_NOT_FOUND if the slave address was not acknowledged.
 * @return ERR_REJECTED if the first data byte was rejected by the slave.
 * @return ERR_ABORTED if the slave stopped accepting data after the transfer
 *         had already started.
 * @return Other ResultCode values produced by the transfer state machine.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline ResultCode TWI <N, TX_BUF_SIZE> :: send(uint8_t address,
                                                 const void *data,
                                                 uint8_t size,
                                                 void (*callback)(ResultCode result))
{
    if(mode != I2C_MASTER)
        return ERR_BAD_MODE;

    if(busy)
        return ERR_BUSY;

    if(!data || !size)
        return ERR_BAD_PARAMETER;

    busy = true;
    master.address = (address << 1) | TW_WRITE;
    master.index = 0;
    master.size = size;
    master.tries_left = max_tries;
    if(callback)
    {
        // non-blocking mode
        if(size > TX_BUF_SIZE)
        {
            busy = false;
            return ERR_BAD_PARAMETER;
        }
        memcpy(tx_buf, data, size);
        master.buf = tx_buf;
        master.callback = callback;
        _start();
        return OK;
    }
    else
    {
        master.callback = nullptr;      // clear potentiall previous callback
    }
    master.buf = (uint8_t*) data;
    _start();
    wait();
    return master.result;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Receive data from an I2C slave device.
 *
 * Starts a master receive operation.
 *
 * If @p callback is nullptr, the method works in blocking mode:
 * it starts the transfer, waits until it is completed, and returns the final
 * transfer result.
 *
 * If @p callback is not nullptr, the method works in non-blocking mode:
 * it starts the transfer and returns immediately. The callback is called when
 * the transfer is completed or failed.
 *
 * In non-blocking mode the receive buffer is not copied and must remain valid
 * until the callback is called.
 *
 * The callback is executed from ISR context and must be short and non-blocking.
 *
 * @param address 7-bit I2C slave address. Address 0 is rejected for read
 *                operations.
 * @param data Pointer to the receive buffer.
 * @param size Number of bytes to receive.
 * @param callback Optional completion callback. nullptr selects blocking mode.
 *
 * @return OK if a non-blocking transfer was started successfully.
 * @return OK if a blocking transfer completed successfully.
 * @return ERR_BAD_MODE if the bus is not initialized in master mode.
 * @return ERR_BUSY if another master transfer is already active.
 * @return ERR_BAD_PARAMETER if address is zero, data is nullptr, or size is
 *         zero.
 * @return ERR_NOT_FOUND if the slave address was not acknowledged.
 * @return Other ResultCode values produced by the transfer state machine.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline ResultCode TWI <N, TX_BUF_SIZE> :: receive(uint8_t address,
                                                    void *data,
                                                    uint8_t size,
                                                    void (*callback)(ResultCode result))
{
    if(mode != I2C_MASTER)
        return ERR_BAD_MODE;

    if(busy)
        return ERR_BUSY;

    if(!address || !data || !size)
        return ERR_BAD_PARAMETER;

    busy = true;
    master.address = (address << 1) | TW_READ;
    master.buf = (uint8_t*) data;
    master.size = size;
    master.index = 0;
    master.tries_left = max_tries;
    if(callback)
    {
        // non-blocking mode
        master.callback = callback;
        _start();
        return OK;
    }
    else
    {
        master.callback = nullptr;      // clear potentiall previous callback
    }
    _start();
    wait();
    return master.result;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check whether the I2C bus driver is busy.
 *
 * Returns the current master transfer state.
 *
 * The flag is set when a master transfer starts and is cleared when the
 * transfer completes, fails, or the peripheral is disabled.
 *
 * @return true if a master transfer is active.
 * @return false if no master transfer is active.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline bool TWI <N, TX_BUF_SIZE> :: is_busy()
{
    return busy;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Wait until the active master transfer is completed.
 *
 * Blocks in a spin loop while the driver busy flag is set.
 *
 * This method is used internally by blocking send() and receive() calls.
 * It relies on TWI interrupts to advance and complete the transfer.
 *
 * @warning Do not call this method from an ISR.
 * @warning Global interrupts must be enabled, otherwise this method may wait
 *          forever.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: wait()
{
    while(busy);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable the TWI peripheral.
 *
 * Disables the hardware TWI control register, switches the driver mode to
 * I2C_DISABLED and clears the busy flag.
 *
 * If a transfer is active, it is aborted locally. No completion callback is
 * generated by this method.
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: disable()
{
    regs :: CR = 0;
    mode = I2C_DISABLED;
    busy = false;
    master.callback = nullptr;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reset the internal TWI control state.
 *
 * Reinitializes the TWI control register according to the current driver mode.
 *
 * In master mode the peripheral is left enabled but idle.
 * In slave mode the peripheral is returned to address-listening state.
 * In disabled mode no listening or master operation is started.
 *
 * The driver busy flag is cleared.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _reset()
{
    // stop and clear bus error
    regs :: CR = _bit(regs :: STO);
    if(mode == I2C_MASTER)
    {
        regs :: CR = _bit(regs :: EN);
    }
    else if(mode == I2C_SLAVE)
    {
        _listen();
    }
    busy = false;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enter slave address-listening state.
 *
 * Configures the TWI control register to:
 * - clear the interrupt flag;
 * - keep the TWI peripheral enabled;
 * - keep TWI interrupt enabled;
 * - acknowledge own slave address or general call if configured.
 *
 * This method is used in slave mode after initialization and after slave
 * receive/transmit transactions end.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _listen()
{
    regs :: CR = _bit(regs :: INT) | _bit(regs :: EN) | _bit(regs :: IE) | _bit(regs :: EA);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Request a START condition.
 *
 * Configures the TWI control register to request a START condition and enable
 * TWI interrupt handling.
 *
 * In master mode this begins a new transfer or retries address transmission
 * after an address NACK or arbitration loss.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _start()
{
    regs :: CR = _bit(regs :: INT) | _bit(regs :: EN) | _bit(regs :: IE) | _bit(regs :: STA);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Request a STOP condition and mark the master transfer as finished.
 *
 * Configures the TWI control register to send STOP on the bus and disables TWI
 * interrupt handling for the completed master transfer.
 *
 * The driver busy flag is cleared immediately after requesting STOP.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _stop()
{
    regs :: CR = _bit(regs :: INT) | _bit(regs :: EN) | _bit(regs :: STO);
    busy = false;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Continue the current TWI operation with ACK enabled.
 *
 * Clears the TWI interrupt flag, keeps the peripheral and interrupt enabled,
 * and sets the acknowledge bit.
 *
 * In master receiver mode this tells the slave that another byte is expected.
 * In slave mode this acknowledges the current address or data byte.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _ack()
{
    regs :: CR = _bit(regs :: INT) | _bit(regs :: EN) | _bit(regs :: IE) | _bit(regs :: EA);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Continue the current TWI operation with ACK disabled.
 *
 * Clears the TWI interrupt flag and keeps the peripheral and interrupt enabled,
 * but leaves the acknowledge bit cleared.
 *
 * In master receiver mode this is used before receiving the last byte.
 * In slave mode this rejects the current address or data byte.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _nack()
{
    regs :: CR = _bit(regs :: INT) | _bit(regs :: EN) | _bit(regs :: IE);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Write one byte to the TWI data register.
 *
 * Used by the interrupt state machine to send an address byte or a payload byte.
 *
 * @param data Byte to write into the TWI data register.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _write_dr(uint8_t data)
{
    regs :: DR = data;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read one byte from the TWI data register.
 *
 * Stores the received byte into the current master receive buffer and advances
 * the master buffer index.
 *
 * The receive buffer must be valid for the whole transfer.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _read_dr()
{
    master.buf[master.index++] = regs :: DR;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Complete the active master transfer.
 *
 * Stores the final transfer result, requests STOP, clears the busy flag and
 * calls the completion callback if the transfer was started in non-blocking
 * mode.
 *
 * The callback is called after the transfer has been marked as no longer busy.
 * The callback is executed from ISR context and must be short and non-blocking.
 *
 * @param result Final transfer result.
 *
 * @internal
 */
template <uint8_t N, uint8_t TX_BUF_SIZE>
__inline void TWI <N, TX_BUF_SIZE> :: _complete(ResultCode result)
{
    master.result = result;
    _stop();
    if(master.callback)
    {
        auto callback = master.callback;
        master.callback = nullptr;
        callback(result);
    }
}
//------------------------------------------------------------------------------------------------



