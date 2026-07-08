# UART
## Hardware UART driver for AVR microcontrollers


### Summary

 - Uses the AVR USART/UART peripheral as a serial interface
 - Supports RX and TX as independently enabled compile-time features
 - Uses interrupt-driven ring buffers for enabled RX and TX directions
 - Provides blocking, all-or-nothing non-blocking, and partial non-blocking writes
 - Supports RAM strings, PROGMEM strings, and raw byte buffers
 - Tracks RX and TX buffer overflow counters

The driver is enabled with one of the setup macros in `config.h`:
```cpp
ENABLE_UART0(RX_BUF_SIZE, TX_BUF_SIZE)
ENABLE_UART1(RX_BUF_SIZE, TX_BUF_SIZE)
```

`RX_BUF_SIZE` is the receiver ring buffer size.  
`TX_BUF_SIZE` is the transmitter ring buffer size.

A buffer size of `0` disables the corresponding direction completely.

> [!WARNING]
> Buffer sizes must be powers of two and must not exceed `256`.
> Effective ring buffer capacity is one byte less than the configured size.


### Typical usage and definitions

Any of the following code styles may be used.

#### Object-like style
```cpp
ENABLE_UART0(0, 128);      // enable UART0 in config.h

UART0 uart;                // declare UART object
uart.init(115200);         // configure UART and enable interrupts
uart.write_all("READY");
```

#### Constructor style
```cpp
ENABLE_UART0(0, 128);      // enable UART0 in config.h

UART0 debug(2500000);      // configure UART in constructor
```

> [!NOTE]
> Constructors configure the UART peripheral, but do not call `enable_interrupts()`.
> Use `init(...)` when you want UART initialization to enable global interrupts automatically.

#### Static style
```cpp
ENABLE_UART0(64, 128);     // enable UART0 in config.h

UART0 :: init(115200);
UART0 :: write_all("READY");
```

#### Template type style
```cpp
using DebugUART = UART <0, 0, 128>;

DebugUART :: init(115200);
DebugUART :: write_all("READY");
```


### Basic workflow
1. Enable the required UART with `ENABLE_UART0(...)` or `ENABLE_UART1(...)`.
2. Configure the UART with `init(...)` or a constructor.
3. Write data with `write(...)`, `write_all(...)`, `write_any(...)`, or `send(...)`.
4. Read incoming bytes with `available()`, `peek()`, and `read(...)` if RX is enabled.
5. Use `tx_wait()` before disabling the peripheral if pending TX data must be sent.
6. Call `disable()` when the peripheral is no longer needed.

> [!WARNING]
> RX and TX buffering are interrupt-driven.
> Blocking TX methods wait for interrupt-driven buffer progress.
> Global interrupts must be enabled.


### Minimal TX-only example
```cpp
ENABLE_UART0(0, 128);      // enable UART0 in config.h

UART0 uart;
if(uart.init(115200) == OK)
{
    uart.write_all("Hello\r\n");
}
```


### Minimal RX/TX example
```cpp
ENABLE_UART0(64, 128);     // enable UART0 in config.h

UART0 uart;
if(uart.init(115200) == OK)
{
    while(1)
    {
        if(uart.available())
        {
            int value = uart.read();
            if(value >= 0)
            {
                uart.send((uint8_t)value);     // echo
            }
        }
    }
}
```


### Initialization

Configure the UART with a numeric baud rate:
```cpp
uart.init(115200);
uart.init(2500000);
```

Or use a predefined baud rate:
```cpp
uart.init(BAUD_9600);
uart.init(BAUD_115200);
```

Optional frame format parameters:
```cpp
uart.init(115200, DATA_BITS_8, PARITY_NONE, STOP_BITS_1);
uart.init(9600, DATA_BITS_7, PARITY_EVEN, STOP_BITS_2);
```

Available predefined baud rates:
```cpp
BAUD_2400
BAUD_4800
BAUD_9600
BAUD_19200
BAUD_38400
BAUD_57600
BAUD_115200
```

`init(...)` returns `ERR_BAD_PARAMETER` if the baud rate cannot be generated with acceptable error.


### TX buffer modes

The driver provides three write policies.

#### All-or-nothing non-blocking
```cpp
uart.write("message");
uart.write(_flash("message"));
uart.write(buffer, size);
```

These methods check currently available TX buffer space first. If the whole
payload does not fit, nothing is written.

#### Blocking full write
```cpp
uart.write_all("message");
uart.write_all(_flash("message"));
uart.write_all(buffer, size);
```

These methods wait until every byte is accepted for transmission.

#### Partial non-blocking write
```cpp
uint8_t sent = uart.write_any("message");
uint8_t sent = uart.write_any(_flash("message"));
uint8_t sent = uart.write_any(buffer, size);
```

These methods write as much as currently possible and return the number of
bytes accepted for transmission.


### Single-byte writes

Non-blocking single-byte write:
```cpp
uart.write(0x55);
```

Blocking single-byte write:
```cpp
uart.send(0x55);
```

`write(...)` drops the byte if it cannot be accepted.  
`send(...)` waits until the byte is accepted.


### PROGMEM strings

Use `_flash(...)` for string literals that should stay in flash memory:
```cpp
uart.write_all(_flash("DEBUG READY\r\n"));
```

This saves RAM on AVR.


### Reading

Check how many bytes are available:
```cpp
uint8_t count = uart.available();
```

Peek the next byte without removing it from the RX buffer:
```cpp
int value = uart.peek();
```

Read one byte:
```cpp
int value = uart.read();
if(value >= 0)
{
    uint8_t byte = value;
}
```

Read multiple bytes:
```cpp
uint8_t buf[16];
uint8_t count = uart.read(buf, sizeof(buf));
```

`peek()` and `read()` return `-1` if no byte is available or RX is disabled.


### Errors

RX errors count bytes discarded because the RX buffer was full:
```cpp
uint8_t rx_errors = uart.get_rx_errors();
```

TX errors count bytes rejected because the TX buffer was full:
```cpp
uint8_t tx_errors = uart.get_tx_errors();
```

The counters saturate at `255`.

They are cleared by:
```cpp
uart.flush_rx();
uart.flush_tx();
```


### Busy state and flushing

Check whether TX still has queued data or an active hardware transmission:
```cpp
if(uart.tx_busy())
{
    // transmission is still active
}
```

Wait for all queued and hardware TX data to finish:
```cpp
uart.tx_wait();
```

Clear buffers and error counters:
```cpp
uart.flush_rx();
uart.flush_tx();
```

> [!WARNING]
> `flush_tx()` drops queued TX bytes and disables the UDR-empty interrupt.
> Use `tx_wait()` first if pending bytes must be transmitted.


### Control

Enable or disable directions independently:
```cpp
uart.enable_rx();
uart.disable_rx();

uart.enable_tx();
uart.disable_tx();
```

Enable or disable all configured directions:
```cpp
uart.enable();
uart.disable();
```

Direction methods compile to no code for directions disabled by buffer size `0`.


## Under the hood

`ENABLE_UART0(RX_BUF_SIZE, TX_BUF_SIZE)` creates the UART type and installs ISR handlers:

`ENABLE_UART1(RX_BUF_SIZE, TX_BUF_SIZE)` does the same for the second UART peripheral if the MCU has one.

The RX ISR appends received bytes to the RX ring buffer. If the buffer is full,
the byte is discarded and `rx_errors` is incremented.

The TX path writes directly to the hardware data register when possible.
Otherwise it queues bytes in the TX ring buffer and uses the data-register-empty
interrupt to continue transmission.

Baud rate setup tries normal mode and double-speed mode, then selects the
configuration with the lower baud-rate error.
