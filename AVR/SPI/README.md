# SPI
## SPI drivers for AVR microcontrollers


### Summary

 - Provides two SPI master implementations: dedicated hardware SPI and SPI mode on a USART
 - The dedicated hardware `SPI` implementation supports master and slave operation
 - `USART_SPI` uses a USART peripheral as an SPI master
 - Supports blocking and interrupt-driven non-blocking transfers
 - Uses compile-time peripheral selection and fixed-size TX buffers


### Choose an SPI implementation

Both options communicate over the SPI bus. Choose the dedicated SPI peripheral
or configure a USART peripheral to generate SPI master signals. Enable the
selected instance in `config.h`; its macro creates a type alias and the
required interrupt handler.

#### Hardware SPI
```cpp
ENABLE_SPI0(16);               // config.h

SPI0 :: init_master(400000);   // 400 kHz
```

#### SPI through a USART (`USART_SPI`)
```cpp
ENABLE_USART_SPI1(16);                // config.h

USART_SPI1 :: init_master(400000);    // 400 kHz
```

The number selects the peripheral instance. Use an instance supported by the
MCU. In this option, the USART's TXD, RXD, and XCK pins carry the SPI MOSI,
MISO, and SCK signals. `USART_SPI` supports master mode only and cannot be
used at the same time as the corresponding UART driver.
Configure any required AVR Dx PORTMUX route in the board configuration.

The macro argument is `TX_BUF_SIZE`, the maximum number of TX bytes copied
for one non-blocking transfer. The buffer is static RAM allocated for each
enabled instance. Blocking TX reads directly from the caller's buffer, and
`receive()` does not use this TX buffer.


### Basic workflow

1. Enable a supported instance with `ENABLE_SPI0(...)`, `ENABLE_SPI1(...)`, or
   an instance macro such as `ENABLE_USART_SPI0(...)` in `config.h`.
2. Initialize it with `init_master(...)` or, for hardware `SPI` only,
   `init_slave(...)`.
3. Transfer data with `send(...)`, `receive(...)`, or `duplex(...)`.
4. Call `disable()` when the peripheral is no longer needed.


### Master initialization

```cpp
SPI0 :: init_master(400000);   // requested SCK frequency in Hz
SPI0 :: init_master(1000000, SPI_CLOCK_MODE_0, SPI_MSB_FIRST);
```

`init_master(frequency, clock_mode, bit_order)` chooses a supported SCK rate
no higher than `frequency`. The defaults are `SPI_CLOCK_MODE_0` and
`SPI_MSB_FIRST`. Frequency limits depend on the peripheral and MCU; an
unsupported value returns `ERR_BAD_PARAMETER`.


### Blocking transfers

Omit the callback to wait for the transfer to finish. The methods return the
transfer result:

```cpp
uint8_t tx[] = {0x9F, 0x00, 0x00, 0x00};
uint8_t rx[sizeof(tx)];

SPI0 :: send(tx, sizeof(tx));
SPI0 :: receive(rx, sizeof(rx));       // transmits 0xFF while receiving
SPI0 :: duplex(tx, rx, sizeof(tx));
```

Blocking transfers poll the SPI peripheral. They read TX data directly from
the caller's buffer, and TX and RX buffers must remain valid until the call
returns. Blocking transfers do not depend on the SPI interrupt and must not be
called from an ISR. Non-blocking transfers require global interrupts.


### Non-blocking transfers

Pass a completion callback to start a transfer and return immediately:

```cpp
void on_spi_done(ResultCode result)
{
    // Called from interrupt context.
}

static uint8_t tx[] = {0x9F, 0x00, 0x00, 0x00};
static uint8_t rx[sizeof(tx)];

void start_transfer()
{
    SPI0 :: duplex(tx, rx, sizeof(tx), on_spi_done);
}
```

`start_transfer()` returns while the transfer is active:

```cpp
start_transfer();
```

The driver copies TX data into its fixed-size buffer, so the source may be
reused after the call. Non-blocking TX length must not exceed `TX_BUF_SIZE`.
RX data is written directly into the caller's buffer; keep it valid until the
callback runs. Callbacks run from interrupt context and must be short and
non-blocking. Only one master transfer may be active at a time.

For non-blocking receive, the TX buffer size does not limit the receive count:
the driver transmits `0xFF` for each received byte.


### Hardware SPI slave mode

Slave mode is available only with the hardware `SPI` driver. USART-based SPI
is master-only.

```cpp
void on_spi_slave_byte(uint8_t received, uint8_t *next_tx)
{
    // Process received and provide the byte for the next transfer.
    *next_tx = received;
}

SPI_Slave_Config config;
config.clock_mode = SPI_CLOCK_MODE_0;
config.bit_order = SPI_MSB_FIRST;
config.first_tx = 0xFF;
config.callback = on_spi_slave_byte;

SPI0 :: init_slave(config);
```

`first_tx` is sent on the first transfer. The callback runs for each received
byte in interrupt context and supplies the next byte through `next_tx`.
Configure the MCU's SPI pins and connect the external master's SS signal to
the hardware SPI SS pin. Keep the callback short and non-blocking.


### Busy state and control

```cpp
if(SPI0 :: is_busy())
{
    // A master transfer is active.
}

SPI0 :: wait();
SPI0 :: get_mode();
SPI0 :: disable();
```

`wait()` blocks until an active master transfer completes and requires global
interrupts. `disable()` cancels an active transfer without calling its
completion callback; a cancelled blocking transfer returns `ERR_ABORTED`. Call
`wait()` first when the transfer must finish normally.


### Result codes

| Code | Meaning |
|---|---|
| `OK` | Transfer completed, or a non-blocking transfer started |
| `ERR_BAD_MODE` | Peripheral is not configured as a master |
| `ERR_BUSY` | Another master transfer is active |
| `ERR_BAD_PARAMETER` | Invalid pointer, zero count, unsupported frequency, or oversized non-blocking TX data |
| `ERR_ABORTED` | An active blocking transfer was cancelled by `disable()` |

`init_slave()` returns `ERR_BAD_PARAMETER` when the hardware SPI callback is
null. Calling `USART_SPI::init_slave()` causes a compile-time error because
USART SPI does not support slave mode.
