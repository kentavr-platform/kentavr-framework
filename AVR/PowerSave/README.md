# PowerSave
## Sleep and peripheral power control for AVR microcontrollers


### Summary

 - Enters an explicitly selected sleep mode
 - Controls power for UART, SPI, I2C, timers, ADC, USB, USI, and the comparator
 - Provides the global object `power`, included by `core.h`
 - Requires no initialization, configuration macro, or dedicated ISR


### Sleep

```cpp
// Configure a suitable wake-up interrupt beforehand.
power.sleep(POWERSAVE_SLEEP);
```

| Mode | Operation |
|---|---|
| `POWERSAVE_IDLE` | Stop the CPU, keep peripheral clocks |
| `POWERSAVE_ADC_NOISE_REDUCTION` | Stop clocks that interfere with ADC conversion |
| `POWERSAVE_SLEEP` | Stop synchronous clocks |
| `POWERSAVE_SAVE` | Keep the asynchronous timer running |
| `POWERSAVE_STANDBY` | Keep the main oscillator available |
| `POWERSAVE_EXTENDED_SAVE` | Keep the main oscillator and asynchronous timer |

Wake-up sources depend on the MCU and mode. Classic AVR Standby modes require
a compatible external oscillator configuration. On ATmega32U4, Power-save
equals Power-down, and Extended Standby equals Standby.

`sleep()` returns after wake-up and the interrupt handler. It enables interrupts
for sleep and restores their previous state before returning. Call it from normal
code. BOD configuration is preserved.

When sleep depends on a flag set by an ISR, test the flag atomically:

```cpp
{
    ATOMIC_BLOCK
    if(!event_pending)  // volatile flag set by the wake-up ISR
        power.sleep(POWERSAVE_IDLE);
}
```


### Peripheral power

Startup calls `cpu_only()` before global constructors on MCUs with a complete
power-control backend.
UART, SPI, USART_SPI, I2C, ADC, and SerialUSB restore their clocks during initialization.
`Timer :: set_mode()` restores timer clocks; call it before configuring other timer registers.
UART and timer power methods affect the whole group.
The comparator and USI require an explicit `enable_*_power()` before direct use.
ATmega8, AVR128DB48, and unsupported backends retain their startup power state.

```cpp
power.disable_spi_power();
// ...
power.enable_spi_power();
// Reinitialize the SPI driver before use.
```

The same `disable_*_power()` / `enable_*_power()` pairs exist for
`uart`, `i2c`, `timers`, `adc`, `usb`, `usi`, and `comparator`.
UART and timer methods affect all hardware instances in their group.
USART used as SPI belongs to the UART group.

Finish transfers and disable the peripheral before stopping its clock.
ADC must have ADEN cleared before power-down. Registers of a clock-gated block
must not be accessed. Restoring clocks does not initialize the driver.
Coordinate USB shutdown and restart with the USB stack.

The comparator uses ACD instead of PRR. Disable its interrupt before changing
power; its configuration and pending interrupt flag are preserved.

Power-control methods do not mask interrupts. If an ISR modifies the same
registers, protect the calls with an enclosing `ATOMIC_BLOCK`.

```cpp
power.cpu_only();
```

`cpu_only()` applies all eight group shutdowns available on the MCU.
The same prerequisites apply: finish operations, disable the peripherals,
clear ADC ADEN, and disable the comparator interrupt first.
Watchdog and BOD settings are preserved.
ATmega8, AVR128DB48, and unsupported backends return `ERR_BAD_MODE` without
changing hardware because complete peripheral shutdown is unavailable.


### Targets and results

Classic backends cover ATmega8, ATtiny85, ATmega88P, ATmega328P, ATmega32U4,
ATmega1284P, and ATmega2560. ATmega8 has no PRR power control.
AVR128DB48 has an SLPCTRL sleep backend; peripheral power control is not
implemented for its different register layout.

All methods return `OK` on success or `ERR_BAD_MODE` when the requested
operation is unavailable. Unsupported requests leave hardware unchanged.
The public interface remains available across targets.

`AVR_PowerSave_traits` contains register mappings and compile-time capabilities.
Methods are also callable through `AVR_PowerSave :: method(...)`.
The module has no runtime state or dedicated interrupt handlers.
