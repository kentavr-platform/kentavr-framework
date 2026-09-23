# Servo

## RC Servo Driver


### Summary

 - Controls SG90, MG90, MG946, MG995, MG996 and other PWM servos
 - Uses a 16-bit hardware timer compare output
 - Generates a 20 ms (50 Hz) control frame
 - Supports pulse width and normalized position control
 - Allows a model-specific pulse range

The control value is the high pulse width, not the PWM duty cycle. A typical
servo uses approximately 1000 us for one end, 1500 us for the center, and
2000 us for the other end. Actual limits depend on the servo and can be passed
to the driver.


### Basic usage

```cpp
Servo servo(Timer1::Compare_B);

enable_interrupts();

if(servo.init() == OK)
    servo.set_position(0);
```

The timer must be enabled in `config.h`:

```cpp
ENABLE_TIMER1;
```

`init()` configures the timer for phase-correct PWM with Capture as TOP, starts
it, connects the selected compare channel, and sets a 1500 us center pulse.
Connecting the compare channel configures its OC pin as an output automatically.
The smallest suitable timer clock divider is selected from `F_CPU` to provide
the highest available pulse resolution.


### Pulse range

The default range is 1000...2000 us. Pass another range to the constructor when
the servo requires it:

```cpp
Servo servo(Timer1::Compare_B, 500, 2400);
```

Use the wider range only when it is safe for the servo and its mechanical
load. Driving beyond the physical limits may stall the servo.


### Position and pulse control

Set a normalized position within the configured range:

```cpp
servo.set_position(-127); // min_pulse_us
servo.set_position(0);    // 1500 us
servo.set_position(127);  // max_pulse_us
```

The normalized value does not imply a mechanical angle. The application may
map it to 180, 270, or any other servo travel. Pulse ranges may be asymmetric:
negative values are mapped between `min_pulse_us` and 1500 us, while positive
values are mapped between 1500 us and `max_pulse_us`.

Or set the pulse directly in microseconds:

```cpp
servo.set_pulse(1500);
```

`set_pulse()` returns `ERR_BAD_VALUE` for a pulse outside the configured range.
`set_position()` returns `ERR_BAD_PARAMETER` for a position outside -127...127.


### Output control

Disconnect the OC output without stopping the shared timer:

```cpp
servo.detach();
```

`detach()` waits asynchronously for an active pulse to complete before
disconnecting the output. Enable global interrupts during initialization:

```cpp
enable_interrupts();
```

Without global interrupts the pending disconnection cannot complete.

Reconnect it with:

```cpp
servo.attach();
```

Multiple compare channels may share one configured timer.
