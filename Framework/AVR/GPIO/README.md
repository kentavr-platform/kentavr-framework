# GPIO

## Zero-overhead GPIO abstraction for AVR microcontrollers


### Summary

 - Provides comfortable GPIO access through compile-time pin descriptors
 - Uses pins names as they are defined in MCU (`A0`, `A1`, `B3`, `D7`, etc)
 - Uses static inline methods; no object state is stored, zero memory allocation
 - Generates minimal code when optimized



### Typical usage and definitions

Pins names are compile-time definitions from `Framework/AVR/GPIO/pins.h`.

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
#include "Framework/core.h"
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

## External interrupts (INT)

`enable_int()` configures the selected pin's INT trigger mode, clears its pending
flag, and enables that interrupt line. `disable_int()` disables the line. These
methods only configure the hardware: they do **not** define or install an ISR,
and they do not enable global interrupts. The application must define the ISR
for the MCU vector and call `enable_interrupts()` when it is ready to accept
interrupts.

For example, on an ATmega88-class MCU, pin `D2` is `INT0`:

```cpp
ISR(INT0_vect)
{
    GPIO <A0> :: toggle();
}

int main()
{
    GPIO <A0> :: set_mode(OUTPUT_LOW);
    GPIO <D2> :: enable_int(INT_FALLING);
    enable_interrupts();

    while(1) {}
}
```

The regular `ISR(...)` macro supplies the compiler's interrupt entry/exit
sequence. Define each hardware vector only once in the application.

## Pin-change interrupts (PCINT)

`enable_pcint()` enables this pin in its shared PCINT group, while
`disable_pcint()` disables this pin and disables the group if no pins remain
enabled. `claim_pcint()` instead replaces the group's mask with only this pin.
These methods configure the hardware only: they do **not** define or install
the group's ISR, and do not enable global interrupts. The application must
define one ISR for the shared group vector and call `enable_interrupts()` when
appropriate.

For example, on an ATmega88-class MCU, `B0` belongs to the `PCINT0` group:

```cpp
ISR(PCINT_VECTOR(B0))
{
    GPIO <A0> :: toggle();
}

int main()
{
    GPIO <A0> :: set_mode(OUTPUT_LOW);
    GPIO <B0> :: claim_pcint();
    enable_interrupts();

    while(1) {}
}
```

The PCINT vector is shared by every pin in its group. If multiple pins are
enabled in that group, the application ISR must determine which pin changed,
typically by comparing the current port value with a value saved by the
application.

### Exclusive pin-change interrupt group

```cpp
GPIO <C5> :: claim_pcint();
```

`claim_pcint()` replaces its group's mask with only this pin,
clears the group's pending flag, and enables the group. Other groups, GPIO
mode and the previous global interrupt state remain unchanged. The application
provides the ISR and enables global interrupts when needed.

This is an explicit takeover, not a reservation: other pins in the group lose
their interrupt enable, and its pending event is discarded. No ownership data
is stored in RAM. A later `enable_pcint()` on another pin in this group ends
exclusivity. Use `disable_pcint()` to disable the claimed pin; it does not
restore the old mask. For `GPIO <NC>`, the method does nothing.

## Naked ISR

`ISR(vector, ISR_NAKED)` suppresses the compiler-generated register/SREG save
and restore sequence and does not emit the normal `reti`. Use it only when the
application needs full control of ISR timing or entry/exit. The ISR must save
and restore every register and status value it changes, keep the stack
balanced, and finish with `reti`. Its body should be hand-written assembly;
ordinary C++ code is unsafe because the compiler assumes the normal ISR
prologue and epilogue.

This minimal example preserves `r24` and `SREG` around a placeholder `nop`:

```cpp
ISR(INT0_vect, ISR_NAKED)
{
    asm volatile(
        "push r24"             "\n\t"
        "in   r24, __SREG__"   "\n\t"
        "push r24"             "\n\t"
        "nop"                  "\n\t"
        "pop  r24"             "\n\t"
        "out  __SREG__, r24"   "\n\t"
        "pop  r24"             "\n\t"
        "reti"
    );
}
```

This is only an entry/exit skeleton, not a complete application ISR. If the
assembly body uses other registers or changes additional machine state, it must
preserve those as well.

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
