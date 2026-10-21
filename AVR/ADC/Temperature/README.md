# Temperature
## Built-in AVR temperature sensor

**Warning: the internal sensor is NOT calibrated at all. Using it without
calibration may cause an absolute temperature error up to 10 °C and more.**

**Warning: not all MCU have a built-in temperature sensor. Follow your 
datasheet ADC specification to find it out.**

Warning: built-in AVR temperature sensor has resolution about 1 °C and 
fluctuations about 1 °C between readings.


### Summary

 - Blocking `AVR_Temperature :: get(result)` with optional calibration
 - Measures MCU die temperature, which may differ from ambient temperature
 - Supports ATtiny85, ATmega88P, ATmega328P and ATmega32U4


### Reading

```cpp
AVR_ADC :: init();

Temperature result;
if(AVR_Temperature :: get(result) == OK)
    console.log(result.millis_celsius);
```

Values are in milli-degrees Celsius: `25000` means 25 °C.
Without calibration, MCU-specific defaults are used.


### Calibration

1. Initialize the ADC with `AVR_ADC :: init()`.
2. Let the MCU stabilize at a known temperature and record the raw sensor code:

```cpp
ADC_sample <10> sample;
if(AVR_ADC :: get(sample, ADC_Channel(ADC_traits :: TEMPERATURE_CHANNEL),
                          AVR_Temperature_traits :: REFERENCE) == OK)
    console.log(sample.raw);
```

3. Repeat at another known temperature using the same reference. Use stable
   readings or average several samples at each point.
4. Fill the calibration with both measured codes and their temperatures in
   milli-degrees Celsius, then pass it to `get()`:

```cpp
const AVR_Temperature_calibration calibration
{
    adc_at_20C, 20000,
    adc_at_60C, 60000
};

if(AVR_Temperature :: get(result, calibration) == OK)
    console.log(result.millis_celsius);
```

The ADC codes must differ and use the same reference as the measurement.
Calibration adjusts offset and slope; it does not remove noise.


### Results

`get()` returns `OK`, `ERR_NOT_FOUND` for an unsupported MCU,
`ERR_BAD_VALUE` for equal calibration codes, or an ADC error.
On failure, `result.valid` is cleared and the previous temperature is retained.
