# External interrupts

AVR external interrupts are available only on dedicated `INTn` pins. The pin
connected to each line depends on the selected MCU. Check the MCU pinout or its
file under `AVR/GPIO/pins/` before choosing a line.

Enable every line used by the application in `config.h`:

```cpp
ENABLE_INT0;
ENABLE_INT1;
```

Enabling a line installs its interrupt vector and allows the corresponding GPIO
to store a callback. No callback storage or ISR code is generated for lines
which are not enabled.

Configure the pin as an input and install its callback:

```cpp
void button_pressed()
{
    // Runs in interrupt context. Keep it short.
}

GPIO <D2> :: set_mode(INPUT_PULLUP);
GPIO <D2> :: on_change(button_pressed, INT_FALLING);
```

The supported trigger modes are:

| Mode | Trigger |
|---|---|
| `INT_LOW_LEVEL` | while the pin is low |
| `INT_ANY_CHANGE` | either level change |
| `INT_FALLING` | high-to-low transition |
| `INT_RISING` | low-to-high transition |

`INT_ANY_CHANGE` is used when the mode argument is omitted:

```cpp
GPIO <D2> :: on_change(button_changed);
```

Pass `nullptr` to disable the interrupt. The GPIO mode is not changed:

```cpp
GPIO <D2> :: on_change(nullptr);
```

Compilation fails if the selected GPIO has no external INT input or its line was
not enabled in `config.h`.

PCINT and AVR Dx per-port interrupts are not currently supported.
