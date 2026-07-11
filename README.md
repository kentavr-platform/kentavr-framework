# KentAVR

**A standalone C++17 framework for AVR microcontrollers.**

KentAVR provides type-safe, compile-time hardware abstractions, efficient peripheral drivers, and reusable device drivers.

It is designed for developers who want convenient modern C++ interfaces while keeping direct control over the MCU, generated code, memory usage, interrupts, and peripheral configuration.

> KentAVR is **not Arduino** and does not depend on it.

## Why KentAVR instead of Arduino?

Arduino is excellent for quick prototypes and beginner-friendly examples. KentAVR targets a different use case: compact, controlled, maintainable firmware where hardware details must remain explicit.

| Arduino approach | KentAVR approach |
|---|---|
| Special pin names/numbers | Native AVR pin names |
| Runtime pin resolving | Pin types resolved at compile time |
| Generic `digitalWrite()` abstraction | Direct register operations and AVR bit instructions |
| Global peripheral objects and implicit setup | Explicit peripheral types, configuration, and initialization |
| Features commonly included by a general-purpose core | Drivers and directions enabled only when required |
| Arduino-specific API and build environment | Standard C++17 with AVR-GCC |
| Convenience-first abstraction | Control, predictability, and minimal overhead |

KentAVR does not try to hide the microcontroller. Registers, interrupts, buffers, bus modes, timing, and error handling remain visible through structured C++ interfaces.

## Key features

- **Compile-time GPIO** using native AVR pin names such as `B0`, `C6`, or `D7`
- **Zero-overhead fixed-pin access** with no stored pin number, virtual dispatch, or runtime port lookup
- **Hardware UART drivers** with independently configurable RX and TX ring buffers
- **Hardware I2C/TWI driver** supporting master and slave modes, blocking and asynchronous transfers
- **EEPROM access and structured settings storage**
- **1-Wire interface** with ROM search and device addressing
- **Reusable device drivers**, including DS18x20 sensors and DS3231 RTC
- **PROGMEM-aware strings** for keeping constant text out of scarce SRAM
- **Optional debug console** with a no-op implementation when debugging is disabled
- **Explicit result codes** instead of hidden failure states
- **Static, object-like, and type-alias usage styles** for the same hardware interfaces
- **No dynamic allocation required** by the framework's core hardware abstractions

## Example

```cpp
#include "core.h"
#include "config.h"

GPIO <B5> led;
UART0 serial;

int main()
{
    led.set_mode(OUTPUT_LOW);

    if(serial.init(115200) == OK)
    {
        serial.write_all(_flash("KentAVR ready\r\n"));
    }

    while(1)
    {
        led.toggle();
        mdelay(500);
    }
}
```

The pin is known at compile time. With optimization enabled, GPIO writes are reduced to direct AVR instructions rather than a runtime pin lookup.

## Compile-time peripheral configuration

Hardware instances and their buffers are enabled explicitly in `config.h`:

```cpp
ENABLE_UART0(64, 128);  // 64-byte RX buffer, 128-byte TX buffer
ENABLE_I2C0(32);        // I2C0 with a 32-byte asynchronous TX buffer
ENABLE_SETTINGS(512);   // reserve 512 EEPROM bytes for settings
```

## Requirements

- AVR-GCC toolchain
- C++17
- an explicitly defined target MCU and `F_CPU`
- optimization enabled for the intended zero-overhead code generation

Configure fuses, enabled peripherals, and optional storage in `config.h` for the target firmware.


## Project status

KentAVR is under active development. APIs, supported peripherals, and device coverage may evolve while the framework is being expanded and tested on additional AVR families.
