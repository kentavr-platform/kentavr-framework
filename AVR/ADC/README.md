# ADC
## Built-in analog-to-digital converter driver for AVR microcontrollers


### Summary

 - Controls the ADC built into the AVR microcontroller
 - Provides one static API for the on-chip ADC peripheral
 - Supports blocking reads and interrupt-driven queued conversions
 - Supports single-ended, differential, amplified, and internal inputs where available
 - Selects the ADC clock from the available hardware dividers
 - Discards settling conversions after input or reference changes when required
 - Returns raw 10-bit samples with helpers for conversion to millivolts

The module is included by `core.h`:
```cpp
#include "core.h"
```

Blocking reads require no setup macro. Define `ENABLE_ADC_ASYNC_MODE` in
`config.h` to enable queued conversions.


### Basic workflow

1. Initialize the ADC with `AVR_ADC :: init(...)`.
2. Select an input from `ADC_Channel` and a reference from `ADC_reference`.
3. Read a sample with `get(...)`, or enqueue a conversion with `schedule(...)`.
4. Use the raw result or convert a single-ended sample to millivolts.
5. Call `reset()` to cancel pending asynchronous work when needed.


### Minimal blocking example

Read ADC0 against AVCC on an ATmega328P:

```cpp
ADC_sample <10> sample;

if(AVR_ADC :: init() == OK)
{
    AVR_ADC :: get(sample, ADC0_1X, ADC_REFERENCE_AVCC);

    int16_t raw = sample.raw;
    int16_t millivolts = sample.scale_to_mV(5000);  // actual AVCC in mV
}
```

`get(...)` waits for the conversion and any required settling conversions.
It returns `OK` after filling the sample. Blocking reads do not require global
interrupts and have no timeout.


### ADC clock

```cpp
AVR_ADC :: init();          // request 125 kHz
AVR_ADC :: init(250000);    // request 250 kHz

uint32_t frequency = AVR_ADC :: get_clock_frequency();
```

`init(adc_clock)` takes the requested ADC clock in Hz, not the sample rate.
The default is `AVR_ADC_RECOMMENDED_CLOCK`, currently `125000UL`.

The driver chooses the nearest available clock using CPU-clock dividers
2, 4, 8, 16, 32, 64, and 128. Equal differences select the larger divider.
The selected rate can be above or below the request. `get_clock_frequency()`
returns that selected rate in Hz, or zero before initialization.

Requests above 5 MHz return `ERR_BAD_PARAMETER`. The driver does not validate
the selected rate against the MCU's accuracy limits; choose a suitable rate
for the selected device and required resolution.


### Inputs and references

Pass one input code and one reference to each conversion:

```cpp
AVR_ADC :: get(sample, ADC0_1X, ADC_REFERENCE_AVCC);
```

`ADC_Channel` and `ADC_reference` are defined for the selected MCU in
`avr-adc-channels.h`. Available inputs depend on the device and package.

| Input name | Meaning |
|---|---|
| `ADC0_1X`, `ADC1_1X`, ... | Single-ended input without amplification |
| `ADC0_1_1X` | Differential ADC0 minus ADC1, gain 1 |
| `ADC1_0_10X` | Differential ADC1 minus ADC0, gain 10 |
| `ADC_GND` | Internal ground input |
| `ADC_VBG` | Internal bandgap input |
| `ADC_TEMPERATURE` | Internal temperature sensor input, where available |

Not every input listed above exists on every MCU. Differential combinations
and gains are selected by the channel name, not by separate arguments.

| Reference | Meaning |
|---|---|
| `ADC_REFERENCE_AREF` | External voltage on AREF |
| `ADC_REFERENCE_AVCC` | AVCC on supported ATmega devices |
| `ADC_REFERENCE_VCC` | VCC on ATtiny85 |
| `ADC_REFERENCE_1V1` | Internal nominal 1.1 V reference, where available |
| `ADC_REFERENCE_2V56` | Internal nominal 2.56 V reference, where available |
| `ADC_REFERENCE_2V56_BYPASS` | ATtiny85 2.56 V reference with external bypass capacitor |

Select a channel/reference combination supported by the device. On ATmega1284P,
differential conversions using an internal reference require 2.56 V.


### Sample values and millivolts

Results use `ADC_sample <10>`:

```cpp
sample.raw;                    // signed storage for the ADC result
sample.ref_mV;                 // nominal internal reference in mV, or zero
sample.scale_to_mV();           // use sample.ref_mV
sample.scale_to_mV(3300);       // use an explicitly supplied reference in mV
```

Single-ended results range from 0 to 1023. Differential results are
sign-extended and range from -512 to 511.

For internal references, the driver sets `ref_mV` to the nominal 1100 or
2560 mV. For AREF, AVCC, and VCC it sets `ref_mV` to zero; pass the actual
reference voltage explicitly to `scale_to_mV(reference_mV)`.

The helper calculates `raw * reference_mV / 1024` using integer arithmetic.
Internal reference values are nominal and are not calibrated.

> [!NOTE]
> `scale_to_mV()` uses single-ended scaling. Differential conversions require
> separate handling of the signed range and selected gain.


### Non-blocking conversions

Enable asynchronous operation in `config.h`:

```cpp
#define ENABLE_ADC_ASYNC_MODE
```

Pass a callback, a user identifier, an input, and a reference to `schedule(...)`:

```cpp
void on_adc_result(uint8_t id, ADC_sample <10> sample)
{
    // Called from ADC interrupt context.
    // id identifies the request; sample contains its result.
}

void start_measurement()
{
    AVR_ADC :: schedule(on_adc_result, 1, ADC0_1X, ADC_REFERENCE_AVCC);
}

// After a successful AVR_ADC :: init():
enable_interrupts();
start_measurement();
```

`schedule(...)` returns after accepting the task. The driver starts the first
conversion immediately when idle and processes queued tasks in order.
The identifier is passed unchanged to the callback and need not be unique.
The callback receives the sample by value, so no caller-owned result buffer
has to remain valid.

Queue capacity is `ADC_traits :: CHANNEL_COUNT`, including the active task.
The driver starts the next queued conversion before invoking the completed
task's callback.

> [!WARNING]
> Queued conversions require global interrupts to complete callbacks.
> Callbacks run from ISR context; keep them short and non-blocking.


### Blocking reads during asynchronous work

`get(...)` can be used while asynchronous tasks are queued. It suspends
asynchronous processing, performs the blocking read, then restarts the
interrupted task and resumes the queue. The blocking read does not invoke
a callback or remove a queued task.

Calls to `get(...)` must not overlap. Do not call `init()` or `reset()` from
another interrupt while a blocking read is in progress.


### Cancelling queued conversions

```cpp
AVR_ADC :: reset();
```

`reset()` stops an active asynchronous conversion and empties the queue
without invoking callbacks. The ADC remains enabled. In blocking-only builds,
`reset()` does nothing.

Calling `init()` again also clears pending asynchronous tasks.


### Result codes

| Method | Code | Meaning |
|---|---|---|
| `init(...)` | `OK` | ADC configured and enabled |
| `init(...)` | `ERR_BAD_PARAMETER` | Requested ADC clock exceeds 5 MHz |
| `get(...)` | `OK` | Blocking conversion completed |
| `schedule(...)` | `OK` | Task accepted |
| `schedule(...)` | `ERR_BAD_MODE` | Asynchronous mode is not enabled |
| `schedule(...)` | `ERR_BAD_PARAMETER` | Callback is null |
| `schedule(...)` | `ERR_NO_SPACE_LEFT` | Queue capacity, including the active task, is exhausted |


## Under the hood

`AVR_ADC` is a single static driver for the MCU's built-in ADC. `ADC_traits`
maps registers and peripheral capabilities, while `avr-adc-channels.h` provides
MCU-specific input codes and differential-input metadata.

Settling results are discarded internally after relevant input or reference
changes. This handling applies to both blocking reads and queued conversions.

With `ENABLE_ADC_ASYNC_MODE`, the ADC interrupt handler is emitted only in
`Core/isr.cpp`. The queue stores each task's input, reference, identifier, and
callback. Asynchronous processing is removed when the option is disabled.

Current targets are ATmega8, ATtiny85, ATmega88P, ATmega328P, ATmega32U4,
ATmega1284P, and ATmega2560. AVR Dx and other ADC register layouts are not
implemented.
