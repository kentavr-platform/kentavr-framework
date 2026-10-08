# I2C
## I2C driver for AVR microcontrollers


### Summary

 - Uses the classic AVR TWI peripheral as an I2C bus interface
 - Supports master transmitter and master receiver modes
 - Supports slave receiver and slave transmitter modes
 - Provides blocking and non-blocking master transfers
 - Uses interrupt-driven transfer state machine internally

The driver is enabled with one of the setup macros in `config.h`:
```cpp
ENABLE_I2C0(TX_BUF_SIZE)
ENABLE_I2C1(TX_BUF_SIZE)
```

`TX_BUF_SIZE` is the internal transmit buffer size for non-blocking master writes.


### Typical usage and definitions

Any of the following code styles may be used.

#### Object-like style
```cpp
ENABLE_I2C0(16);             // create I2C0 type and ISR

I2C0 i2c;                    // declare bus object
i2c.init_master(400000);     // configure bus as master
```

#### Static style
```cpp
ENABLE_I2C0(16);             // create I2C0 type and ISR

I2C0 :: init_master(400000); // configure bus as master
I2C0 :: send(...);           // send data
I2C0 :: receive(...);        // receive data
```

#### Template type style
```cpp
using Bus = TWI <0, 16>;

Bus :: init_master(400000);
Bus :: send(...);
```


### Basic workflow
1. Enable the required I2C bus with `ENABLE_I2C0(...)` or `ENABLE_I2C1(...)`.
2. Configure the bus with `init_master(...)` or `init_slave(...)`.
3. Use `send(...)` and `receive(...)` in master mode.
4. Use callbacks in slave mode.
5. Call `disable()` when the peripheral is no longer needed.

> [!WARNING]
> Master transfers are interrupt-driven.  
> Blocking `send(...)` and `receive(...)` wait until the interrupt handler completes the transfer.  
> Global interrupts must be enabled.


### Minimal master example (blocking mode)
```cpp
ENABLE_I2C0(16);    // in config.h

I2C0 i2c;
uint8_t data[] = {0x00, 0x55};
if(i2c.init_master(400000) == OK)
{
    i2c.send(0x68, data, sizeof(data));     // send data to i2c-device with address = 0x68
}
```


### Master initialization
Configure the bus as master:
```cpp
i2c.init_master(400000);     // 400 kHz
i2c.init_master(100000);     // 100 kHz
```

The requested frequency is in Hz.

`init_master(...)` also enables I2C interrupts automatically.


### Non-blocking write
Pass a callback to `send(...)` for non-blocking operation:
```cpp
// setup a callback function
void on_i2c_done(ResultCode result)
{
    if(result == OK)
    {
        // transfer completed
    }
}

// somewhere in main loop or other region
uint8_t data[] = {0x10, 0x42};
i2c.send(0x50, data, sizeof(data), on_i2c_done);    // non-blocking transmission to address = 0x50
```

In non-blocking mode the driver does NOT wait the operation to be completed and returns immediately. Callback function will be called by the driver when it will complete the transmission.

* The driver copies data buffer into the internal TX buffer. So the source buffer may be deleted or reused after the call.

> [!WARNING]
> Non-blocking write size must not exceed `TX_BUF_SIZE`.


### Non-blocking read
Pass a callback to `receive(...)` for non-blocking operation:
```cpp
// setup a callback function
uint8_t data[8];
void on_i2c_done(ResultCode result)
{
    if(result == OK)
    {
        // data[] is ready here
    }
}

// somewhere in main loop or other region
i2c.receive(0x68, data, sizeof(data), on_i2c_done); // non-blocking reception from address = 0x68
```

* In non-blocking read mode the driver writes directly into the user buffer.
The receive buffer must remain valid until the callback is called.

> [!WARNING]
> Transfer callbacks are called from ISR context.  
> Keep them short. Do not wait, print large logs, or start long operations inside them.


### Busy state and waiting
Check whether a transfer is active:
```cpp
if(i2c.is_busy())
{
    // transfer is still active
}
```

Wait until the active transfer is completed:
```cpp
i2c.wait();
```

`wait()` is normally not needed in application code, because blocking `send(...)` and `receive(...)` call it internally.


### Result codes
Common master transfer results:

| Code | Meaning |
|---|---|
| `OK` | Transfer completed successfully |
| `ERR_BAD_MODE` | Bus is not configured as master |
| `ERR_BUSY` | Another transfer is already active |
| `ERR_BAD_PARAMETER` | Invalid pointer, size, or read address |
| `ERR_NOT_FOUND` | Slave address was not acknowledged |
| `ERR_REJECTED` | First data byte was rejected by slave |
| `ERR_ABORTED` | Slave stopped accepting data after transfer started |


### Slave mode
Configure the bus as I2C slave with `I2C_Slave_Config`:
```cpp
ResultCode on_receive(I2C_Slave_Action action, uint8_t data)
{
    switch(action)
    {
    case I2C_SLAVE_START:
        return OK;

    case I2C_SLAVE_DATA:
        // process received byte
        return OK;

    case I2C_SLAVE_END:
        return OK;

    default:
        return OK;
    }
}

ResultCode on_transmit(I2C_Slave_Action action, uint8_t *data)
{
    if(action == I2C_SLAVE_DATA)
    {
        *data = 0x55;
        return OK;
    }
    return OK;
}

I2C_Slave_Config config;
config.address = 0x12;
config.receive_broadcasts = false;
config.receiver_callback = on_receive;
config.transmitter_callback = on_transmit;

i2c.init_slave(config);
```

Both callbacks are required.


### Slave receive actions
The receiver callback can receive the following actions:

| Action | Meaning |
|---|---|
| `I2C_SLAVE_START` | Master started writing to this slave |
| `I2C_SLAVE_BROADCAST_START` | Broadcast write started |
| `I2C_SLAVE_DATA` | One data byte was received |
| `I2C_SLAVE_END` | STOP or repeated START was received |

Return `OK` to ACK the event when applicable.
Return another `ResultCode` to reject it.


### Slave transmit actions
The transmitter callback can receive the following actions:

| Action | Meaning |
|---|---|
| `I2C_SLAVE_DATA` | Master requests next byte |
| `I2C_SLAVE_END` | Master ended reading |
| `I2C_SLAVE_MORE` | Last byte was sent and master still requested more |

When action is `I2C_SLAVE_DATA`, write the next byte to `*data` and return `OK`:
```cpp
*data = next_byte;
return OK;
```


## Under the hood

The driver is built around the classic AVR TWI status-code state machine.

`ENABLE_I2C0(TX_BUF_SIZE)` creates the bus type and installs the ISR:
```cpp
using I2C0 = TWI <0, TX_BUF_SIZE>;
```

`ENABLE_I2C1(TX_BUF_SIZE)` does the same for the second TWI peripheral if the MCU has one.

All the transfers are interrupt-driven.
