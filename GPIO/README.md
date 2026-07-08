# GPIO

## Zero-overhead GPIO abstraction for AVR microcontrollers


### Summary

 - Provides comfortable GPIO access through compile-time pin descriptors
 - Uses pins names as they are defined in MCU (`A0`, `A1`, `B3`, `D7`, etc)
 - Uses static inline methods; no object state is stored, zero memory allocation
 - Generates minimal code when optimized



### Typical usage and definitions

Pins names are compile-time definitions from `GPIO/pins.h`.

#### Object-like style
```cpp
GPIO <A0> led;
led.set_mode(OUTPUT_LOW);
led.write_high();
```

#### Static style
```cpp
GPIO <D3> :: set_mode(INPUT_PULLUP);
if(GPIO <D3> :: read())
{
    GPIO <A0> :: toggle();
}
```

#### Type alias style
```cpp
using StatusLED = GPIO <A0>;
StatusLED :: set_mode(OUTPUT_LOW);
StatusLED :: toggle();
```


### Basic workflow
1. Select a pin.
2. Configure the pin with `set_mode(...)`.
3. Use `write_high()`, `write_low()`, `toggle()`, or `read()`.


### Pin modes

| Mode | Direction | PORT bit |
|---|---|---|
| `INPUT_OPEN` | input | cleared |
| `INPUT_PULLUP` | input | set |
| `OUTPUT_LOW` | output | cleared before output enable |
| `OUTPUT_HIGH` | output | set before output enable |

Setting the output level before enabling the output driver helps avoid a short
unwanted pulse during mode changes.


### Minimal example
```cpp
#include "core.h"
GPIO <A0> led;
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


### Not Connected pin

Use `NC` as a pin name and if `constexpr(connected <...>)` check to detach the pin
from your code at compile-time:

```cpp
#ifdef DEEBUG
  GPIO <D2> debug_led;
#else
  GPIO <NC> debug_led;
#endif

void main()
{
    if constexpr(connected <debug_led>)
    {
       debug_led.set_mode(OUTPUT_HIGH);
    }
}
```

## Under the hood

`GPIO <pin>` is a type-level wrapper around constant register addresses and a
constant bit number. Because every address and bit is known at compile time,
the abstraction has zero runtime cost for fixed pins. There is no stored pin
number, no object data, no virtual dispatch, and no runtime branch for selecting
a port. With optimization enabled, the compiler folds the template constants
into AVR bit instructions.

#### Write output

Each GPIO write method compiles definitely into one `sbi/cbi` instruction:

```cpp
    GPIO <A0> :: write_high();
    GPIO <A0> :: write_low();
```

Assembler output:

```asm
    sbi 0x02, 0     ; 2 bytes 2 cycles
    cbi 0x02, 0     ; 2 bytes 2 cycles
```

This behaviour does not depend on your GPIO usage style.

#### Read input

GPIO read() method compiles into `in + andi` instructions:

```cpp
    return GPIO <A0> :: read();
```

```asm
    in r24, 0x00    ; 2 bytes 1 cycle
    andi r24, 1     ; 2 bytes 1 cycle
    ret
```
