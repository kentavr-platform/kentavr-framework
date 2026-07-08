# SerialBitOut
## Bit-banged software UART transmitter for AVR microcontrollers


### Summary

 - Implements a TX-only software UART on a single GPIO pin
 - Uses compile-time pin and baud rate parameters
 - Sends standard UART-style frames: 1 start bit, 8 data bits LSB first, 1 stop bit
 - Supports single-byte writes, RAM strings, and PROGMEM strings
 - Uses cycle-counted inline AVR assembly for deterministic bit timing
 - Does NOT use any hardware peripheral (UART, timers), interrupts, buffers, or dynamic state


### Limitations

 - TX only; there is no receiver
 - Fixed 8N1 frame format
 - Compile-time baud rate definition
 - Blocking writes only
 - No buffering or flow control


> [!WARNING]
> `SerialBitOut` disables interrupts during each write operation to keep bit timing stable.
> Writing long strings blocks the CPU and delays interrupt handling for the whole string.


### Typical usage and definitions

```cpp
SerialBitOut <D1, 115200> debug;

debug.write('R');
debug.write("READY\n");
debug.write(_flash("FLASH TEXT\n"));
```


### Basic workflow
1. Declare a `SerialBitOut <pin, baud>` object.
2. Connect the pin to a UART receiver configured for 8 data bits, no parity, 1 stop bit.
3. Write bytes or strings with `write(...)`.


### Minimal example
```cpp
#include "core.h"
SerialBitOut <D1, 115200> debug;

int main()
{
    debug.write("Hello world!\n");
}
```


### Console transport example

`SerialBitOut` provides the stream methods expected by `Console`. So you can use it for [console](../../console) transport as well:
```cpp
#include "core.h"

SerialBitOut <D1, 2000000> transport;
Console console(transport);

int main()
{
    uint8_t a = 100;
    console.clear();
    console.log(_flash("DEBUG READY"));
    console.log(VAR(a));                    // log variable as 'a=100'
    console.log(REG(SREG));                 // log SREG register as 'SREG=0x0B'
}
```

This is useful when a hardware UART is not available or when a simple debug-only
TX line is enough.


### Pin and baud parameters

Declare the transmitter with:
```cpp
SerialBitOut <PIN, BAUD> stream;
```

`PIN` must be a GPIO pin descriptor such as `D1`, `B0`, or another type defined in `GPIO/pins.h`.

`BAUD` is a compile-time constant in bits per second:
```cpp
SerialBitOut <D1, 9600>    slow_debug;
SerialBitOut <D1, 115200>  debug;
SerialBitOut <D1, 2000000> fast_debug;
```

The baud rate is validated at compile time:
```cpp
static_assert(baud >= 50, "Baud rate too low");
static_assert(baud <= F_CPU / 8, "Baud rate is too high for this F_CPU");
```

> [!WARNING]
> Timing depends on `F_CPU`, compiler output, and AVR instruction timing.
> Re-check generated assembly or real pin timing after changing the low-level
> implementation, compiler settings, MCU family, or clock configuration.


### Interrupt behavior

Each public write method wraps the whole transmission in `ATOMIC_BLOCK`:
```cpp
debug.write(0x55);          // interrupts are disabled for one frame
debug.write("message");     // interrupts are disabled for the whole string
```

This guarantees bit timing but means that ISRs, timer ticks, software delays,
and other interrupt-driven drivers are postponed until the write finishes.

> [!WARNING]
> Avoid long debug strings when the application depends on low-latency interrupt
> handling.
