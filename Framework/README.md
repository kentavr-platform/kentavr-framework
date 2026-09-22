# KentAVR Framework

## Framework layout and getting started


### Overview

KentAVR is a modern C++17 framework for classic AVR microcontrollers. It provides
compile-time GPIO, hardware peripheral drivers, communication interfaces,
device drivers, and common firmware services without dynamic allocation or an
Arduino dependency.

Application code normally uses the single framework entry point:

```cpp
#include "Framework/core.h"
#include "config.h"
```

`core.h` makes the complete framework API available. Individual framework
headers do not need to be included by the application.


### Directory structure

| Directory | Purpose |
|---|---|
| [`Core`](Core) | Result codes, type traits, formatting, units, and common utilities |
| [`AVR`](AVR) | MCU-specific GPIO, delays, macros and peripheral drivers |
| [`Interfaces`](Interfaces) | Software communication interfaces such as 1-Wire and bit-banged serial output |
| [`Devices`](Devices) | Drivers for LEDs, sensors, RTCs, and other external devices |
| [`Services`](Services) | Application services such as console output and persistent settings |

### Project configuration

`config.h` belongs to the application, not to the framework. It selects the
clock source, fuse values, hardware peripherals, buffer sizes, and optional
services used by that firmware.

For example:

```cpp
ENABLE_TIMER1;
ENABLE_UART0(64, 128);
ENABLE_I2C0(32);
ENABLE_SETTINGS(512);
```

Enable only peripherals that exist on the selected MCU. Enabling a peripheral
declares its public type and, where required, its interrupt handlers. The
peripheral still has to be configured and started in application code.


### Minimal application

```cpp
#include "Framework/core.h"
#include "config.h"

GPIO <B0> led;

int main()
{
    led.set_mode(OUTPUT_LOW);

    while(1)
    {
        led.toggle();
        mdelay(500);
    }
}
```

Pin names are native AVR port and bit names. The example uses `B0`, meaning
bit 0 of port B, rather than a board-specific pin number. However they are
also supported for Arduino targets as `AP_n`. AP means 'Arduino pin': 
`AP_5`, `AP_A0`.
