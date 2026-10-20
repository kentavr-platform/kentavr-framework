# Watchdog
## Watchdog driver for AVR microcontrollers


### Summary

 - Provides a static API for the hardware watchdog
 - Supports reset, interrupt, and interrupt-then-reset modes where available
 - Selects a hardware timeout and restarts the counter with `kick()`
 - Accepts the timeout callback as the last parameter of `enable(...)`
 - Disables the watchdog during early startup on supported classic AVR targets

The module is included by `core.h`:
```cpp
#include "core.h"
```

No setup macro is required in `config.h`. The application selects the mode
explicitly when calling `enable(...)`.


### Basic workflow

1. Choose a timeout and a mode supported by the MCU.
2. Call `AVR_Watchdog :: enable(timeout, mode, callback)` and check the result.
3. Call `kick()` after the supervised work completes, before the timeout expires.
4. Call `disable()` when watchdog supervision is no longer needed.


### Minimal reset example

```cpp
if(AVR_Watchdog :: enable(WATCHDOG_TIMEOUT_1S, WATCHDOG_MODE_RESET) == OK)
{
    while(true)
    {
        // Complete one iteration of the supervised work.
        AVR_Watchdog :: kick();
    }
}
```

The MCU resets if the application does not service the watchdog before the
selected timeout. `WATCHDOG_MODE_RESET` does not require global interrupts;
its hardware reset also covers a lockup inside an ISR.


### Enabling the watchdog

```cpp
AVR_Watchdog :: enable(WATCHDOG_TIMEOUT_500MS, WATCHDOG_MODE_RESET);
AVR_Watchdog :: enable(WATCHDOG_TIMEOUT_2S, WATCHDOG_MODE_INTERRUPT, on_timeout);
```

`enable(timeout, mode, callback = nullptr)` configures and starts the watchdog,
restarting its counter. Mode is mandatory. The callback has type
`AVR_Watchdog :: Callback`, currently `void (*)()`.

Each successful call replaces the previous callback on interrupt-capable
MCUs. A null callback leaves the ISR without a user callback. Unsupported
requests leave the previous hardware configuration and callback unchanged.


### Timeouts

| Timeout | Approximate period |
|---|---|
| `WATCHDOG_TIMEOUT_15MS` | 15 ms |
| `WATCHDOG_TIMEOUT_30MS` | 30 ms |
| `WATCHDOG_TIMEOUT_60MS` | 60 ms |
| `WATCHDOG_TIMEOUT_120MS` | 120 ms |
| `WATCHDOG_TIMEOUT_250MS` | 250 ms |
| `WATCHDOG_TIMEOUT_500MS` | 500 ms |
| `WATCHDOG_TIMEOUT_1S` | 1 s |
| `WATCHDOG_TIMEOUT_2S` | 2 s |
| `WATCHDOG_TIMEOUT_4S` | 4 s, if supported |
| `WATCHDOG_TIMEOUT_8S` | 8 s, if supported |

Periods depend on the MCU's watchdog oscillator and operating conditions.
The 4 s and 8 s settings require extended-timeout support.


### Operating modes

| Mode | Timeout action |
|---|---|
| `WATCHDOG_MODE_RESET` | Reset the MCU |
| `WATCHDOG_MODE_INTERRUPT` | Request an interrupt on each timeout |
| `WATCHDOG_MODE_INTERRUPT_RESET` | Request an interrupt, then reset on the next timeout after the ISR executes |

Interrupt modes are available only when the MCU has a watchdog interrupt.
They require global interrupts for callback execution.

> [!NOTE]
> Interrupt-only mode cannot recover from a lockup with global interrupts
> disabled: the watchdog ISR cannot execute, and this mode does not reset the MCU.


### Timeout callback

```cpp
void on_timeout()
{
    // Called from watchdog interrupt context.
}

void start_watchdog()
{
    if(AVR_Watchdog :: enable(WATCHDOG_TIMEOUT_1S,
                             WATCHDOG_MODE_INTERRUPT,
                             on_timeout) == OK)
    {
        enable_interrupts();
    }
}
```

The callback runs from ISR context. Keep it short and non-blocking.
The driver does not enable global interrupts automatically.

In combined mode, the hardware clears the watchdog interrupt enable when the
ISR executes. The driver does not rearm it. `kick()` restarts the counter but
does not restore the interrupt stage; call `enable(...)` explicitly to start
a new interrupt/reset cycle.


### Servicing and disabling

```cpp
AVR_Watchdog :: kick();
AVR_Watchdog :: disable();
```

`kick()` executes the `WDR` instruction and restarts the watchdog counter.
It does not reset the MCU.

`disable()` clears the watchdog reset flag and disables the watchdog,
preserving the previous global interrupt state. The stored callback is unchanged.

> [!WARNING]
> A programmed `WDTON` fuse can force reset mode and prevent software shutdown.
> `enable()` returning `OK` does not verify fuse settings.


### Result codes

| Code | Meaning |
|---|---|
| `OK` | Requested configuration written to the watchdog |
| `ERR_BAD_VALUE` | A 4 s or 8 s timeout was requested without extended-timeout support |
| `ERR_BAD_MODE` | No backend is available, or the MCU lacks the requested interrupt mode |

On targets without a backend, `enable()` returns `ERR_BAD_MODE`;
`kick()` and `disable()` do nothing.


## Under the hood

`Watchdog_traits` maps the registers and hardware capabilities.
Configuration writes use adjacent `OUT` or `STS` instructions inside the
four-cycle change window. `ATOMIC_BLOCK` protects configuration and callback
replacement, restoring the previous global interrupt state on exit.

On interrupt-capable targets, the driver stores one callback pointer and
emits `WDT_vect` only in `Core/isr.cpp`.

`avr-watchdog.cpp` supplies `watchdog_early_disable()` in `.init3`, before data
initialization and constructors. It disables the watchdog, which can remain
active after a watchdog reset. The Reset module captures and clears the reset
flags before this hook runs. The hook is retained even when the application
does not call the driver. It cannot override `WDTON`.

The project template includes `avr-watchdog.cpp`. Existing projects must add
that source to their build if it is not already present.

Current targets are ATmega8, ATtiny85, ATmega88P, ATmega328P, ATmega32U4,
ATmega1284P, and ATmega2560. ATtiny10, AVR Dx, and other watchdog layouts are
not supported yet. Build with optimization enabled; `-O0` is not supported.
