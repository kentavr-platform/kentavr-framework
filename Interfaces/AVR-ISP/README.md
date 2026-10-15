# AVR-ISP
## AVR In-System Programming interface


### Summary

 - Reads and writes AVR signatures, fuses, Flash, and EEPROM
 - Uses either the `SPI` master or the `USART_SPI` master
 - Controls the target RESET line through a GPIO pin
 - Provides blocking programming operations


### Choose the SPI transport

Enable one supported SPI master in `config.h`. `SPI` uses the dedicated SPI
peripheral; `USART_SPI` uses a USART configured in master SPI mode. Both
implementations communicate over the SPI bus.

#### `SPI`
```cpp
ENABLE_SPI0(1);                 // config.h

AVR_ISP <SPI0, B0> isp;        // replace B0 with the GPIO connected to target RESET
```

#### `USART_SPI`
```cpp
ENABLE_USART_SPI1(1);           // config.h

AVR_ISP <USART_SPI1, B0> isp;   // replace B0 with the GPIO connected to target RESET
```

Use a peripheral instance supported by the MCU. `USART_SPI` is master-only
and cannot be used simultaneously with the corresponding UART driver.

The macro argument `TX_BUF_SIZE` sets the driver's buffer for non-blocking TX
transfers and its static RAM use. ISP operations are blocking, so they do not
use this buffer; a minimal positive size is sufficient for ISP alone.


### Basic workflow

```cpp
uint8_t signature[3];

ResultCode result = isp.init(100000);   // requested SCK frequency in Hz
if(result == OK)
    result = isp.enter_programming_mode();
if(result == OK)
    result = isp.read_signature(signature);

isp.leave_programming_mode();
```

`init()` configures the SPI master in mode 0, MSB first, and releases target
RESET. `enter_programming_mode()` asserts RESET and sends the programming-enable
instruction. Call it before accessing the target. `leave_programming_mode()`
releases RESET. Call `forget_target()` before using the same driver instance
with a different target.


### Target operations

```cpp
uint8_t low_fuse;
uint8_t data[16];

isp.read_fuse(AVR_ISP_FUSE_LOW, low_fuse);
isp.read_flash(0x0000, data, sizeof(data));
isp.read_eeprom(0x0000, data, sizeof(data));
```

The API also provides `write_fuse()`, `write_eeprom()`, `chip_erase()`, and
`command()` for a raw four-byte ISP instruction. `chip_erase()` resets the
target and re-enters programming mode after the erase.

`read_flash()` and `read_eeprom()` use byte addresses. Flash reads fetch each
word's low and high bytes in one continuous SPI transfer. `write_flash_page()`
writes one complete page; `address` must be page-aligned and `page_size` must
be the target's actual power-of-two page size in bytes. Erase the target before
writing Flash when required by its existing contents.


### Connections

| Programmer signal | Target signal |
|---|---|
| `SPI` MOSI, or `USART_SPI` TXD | MOSI |
| `SPI` MISO, or `USART_SPI` RXD | MISO |
| `SPI` SCK, or `USART_SPI` XCK | SCK |
| `RST_PIN` GPIO | RESET |
| GND | GND |

Use the pin mapping configured for the selected peripheral. The target RESET
signal is driven by `RST_PIN`; it is separate from the SPI peripheral's SS pin.


### Timing and requirements

 - Choose an SCK frequency allowed by the target and the selected peripheral.
   The peripheral selects a supported rate no higher than the requested rate.
 - ISP operations use blocking, interrupt-driven SPI transfers. Global
   interrupts must be enabled; do not call these methods from an ISR.
 - Reserve the selected SPI peripheral for the entire programming session.
 - Flash and EEPROM writes use the ISP `RDY/BSY` command (`F0 00 00 00`) for
   recognized classic megaAVR and tinyAVR targets. Recognition uses the full
   three-byte signature; unknown signatures retain the fixed 20 ms wait. This
   includes ATmega16/32/64/128, ATmega164/324/644/1284, ATmega48/88/168/328,
   ATmega640/1280/1281/2560/2561, USB and CAN variants, and the listed classic
   tinyAVR ISP families. Devices without the documented `0xF0` instruction,
   such as ATmega8/A, keep the fixed wait. Fuse and chip-erase operations also
   retain the fixed 20 ms wait.

`command()` requires four-byte command and response buffers. Operations that
access the target return `ERR_BAD_MODE` until programming mode has been entered.
