# Timer

## Hardware timers for AVR microcontrollers


### Summary

 - Supports the available hardware timers through `Timer0`, `Timer1`, and other timer types
 - Provides normal, CTC, fast PWM, phase-correct PWM, and phase-and-frequency-correct PWM modes
 - Controls compare outputs and input capture where the selected timer supports them
 - Supports callbacks for overflow, compare match, and input capture

The compiller will prevent using timers, that are not present in your MCU.


### Basic workflow

1. Enable the timer in `config.h`.
2. Select a mode with `set_mode(...)` and a clock with `set_clock(...)`.
3. Set TOP and compare values if the selected mode needs them.
4. Configure the compare output if required.
5. Call `start()`.

`set_mode(...)` and `set_clock(...)` return `OK` or `ERR_BAD_PARAMETER`.
Check both results before starting: an unsupported setting leaves the previous
configuration in place. The clock setting defaults to division by 1; the
constructor does not reset the hardware timer.


### Minimal PWM example

Timer1 phase-correct PWM on OC1B, for an ATmega328P running at 20 MHz:

```cpp
Timer1 timer;

if(timer.set_mode(TIMER_MODE_PHASE_PWM_CAPTURE) == OK &&
   timer.set_clock(TIMER_CLOCK_DIV_64) == OK)
{
    timer.Capture.set_value(96);          // TOP
    timer.Compare_B.set_match(25);        // duty cycle
    timer.Compare_B.set_output(TIMER_OUTPUT_PWM);
    timer.start();
}
```

The period is `2 * 96 * 64 / 20 MHz = 614.4 us`; the duty cycle is
`25 / 96 = 26.04%`. The OC pin depends on the MCU and compare channel.

> [!WARNING]
> Timer1 on this MCU does not support `TIMER_CLOCK_DIV_128`.
> If `set_clock(...)` returns `ERR_BAD_PARAMETER` and execution still reaches
> `start()`, the timer starts with its previous clock setting.


### Clock and modes

Available dividers are 1, 8, 32, 64, 128, 256, and 1024; select one with
`TIMER_CLOCK_DIV_N`, replacing `N` with the divider. External clock on a
rising or falling edge is also available, if supported. Not every timer
supports every setting. `set_clock(...)` selects the clock only; it does
not start the timer.

Use `TIMER_MODE_NORMAL` for free-running counting, `TIMER_MODE_CTC_OCRA` or
`TIMER_MODE_CTC_ICR` for a period set by Compare A or Capture, and the
`TIMER_MODE_FAST_PWM_*`, `TIMER_MODE_PHASE_PWM_*`, or
`TIMER_MODE_PHASE_FREQ_PWM_*` modes for PWM. The mode name identifies whether
TOP is fixed, set by Compare A, or set by Capture.

For PWM with Capture as TOP, set it with `timer.Capture.set_value(...)`.
For modes with Compare A as TOP, use `timer.Compare_A.set_match(...)` and use
Compare B or C for duty cycle. Channel C is available only on few MCU.


### Compare outputs

Connect a compare channel to its OC pin with `set_output(...)`:

```cpp
timer.Compare_B.set_match(25);
timer.Compare_B.set_output(TIMER_OUTPUT_PWM);
```

`TIMER_OUTPUT_PWM` produces non-inverted PWM;
`TIMER_OUTPUT_PWM_INVERTED` produces inverted PWM. In non-PWM modes, choose
`TIMER_OUTPUT_TOGGLE_ON_MATCH`, `TIMER_OUTPUT_CLEAR_ON_MATCH`, or
`TIMER_OUTPUT_SET_ON_MATCH`. Connecting a channel automatically configures its
OC pin as `OUTPUT_LOW`, or `OUTPUT_HIGH` for `TIMER_OUTPUT_PWM_INVERTED`. Use
`TIMER_OUTPUT_DISCONNECTED` to return control of the pin to GPIO and configure
it as `INPUT_OPEN`. PWM disconnection occurs after the output returns to its
idle level and requires global interrupts to be enabled. Non-PWM outputs are
disconnected immediately.


### Callbacks

Set callbacks for overflow, compare match, or input capture:

```cpp
void on_overflow()
{
    // Keep interrupt work short.
}

void on_compare()
{
    // Compare B matched.
}

void on_capture()
{
    // Input capture edge detected.
}

timer.on_overflow(on_overflow);
timer.Compare_B.on_match(on_compare);
timer.Capture.on_pin_change(on_capture, CAPTURE_RISING_UNFILTERED);
enable_interrupts();
```

Callbacks run in interrupt context. Passing `nullptr` removes a callback and
disables its interrupt unless an output disconnection is pending. Input
capture can select a rising or falling edge, with or without the noise filter.
The capture callback responds to the timer's input capture pin.

### Counter control

```cpp
timer.start();           // clear the counter and run
timer.stop();            // stop, preserve the counter and disconnect outputs
timer.resume();          // continue from the preserved value
timer.clear();           // clear the counter
timer.reset();           // restore the timer and callbacks to reset state
```

Use `set_counter(...)` and `get_counter()` to write or read the counter.
`clear(true)` also resets the timer prescaler; on some MCUs this affects other
timers sharing that prescaler. `stop()` immediately returns compare pins to
`INPUT_OPEN` and does not reset the prescaler, so the first tick after `resume()`
may arrive sooner than a full prescaler interval. Configure compare outputs
again before `resume()` when they are still required.
