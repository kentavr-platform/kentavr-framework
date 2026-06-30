# DS3231
## Real-time clock (RTC) driver for DS3231


### Summary
`RTC_DS3231 RTC(i2c);`

 - Uses `bus` as a communication [I2C](../../AVR/I2C) interface
 - Represents one DS3231-compatible RTC at the fixed I2C address (`0x68`)
 - Provides date/time access, oscillator-stop detection, hardware alarms, temperature reading, and clock outputs

### Typical usage and definitions

Any of the following code styles may be used.
 
#### Object-like CTAD style
```cpp
I2C0 i2c;                   // declare bus object
i2c.init_master(...);       // configure I2C bus
RTC_DS3231 RTC(i2c);        // declare RTC object
RTC.get_time(...);          // get time
```

#### Template parameter style
```cpp
RTC_DS3231 <I2C0> RTC;      // declare RTC object
RTC.get_time(...)           // get time
```
 
#### Object-like CTAD style
```cpp
I2C0 i2c;                   // declare bus object
i2c.init_master(...);       // configure I2C bus
RTC_DS3231 RTC(i2c);        // declare RTC object
RTC.get_time(...);          // get time
```

#### Static style
```cpp
I2C0 :: init_master(...);           // configure I2C bus
using RTC = RTC_DS3231 <I2C0>;      // create alias
RTC :: get_time(...);               // get time

// hardcore static style works too
RTC_DS3231 <I2C0> :: get_time(...);     
```


### Basic workflow
1. Enable and configure I2C bus.
2. Check whether the RTC has lost time with `time_lost()`.
3. If the time was lost, write a valid date/time with `set_time()`.
4. Read the current date/time with `get_time()`.
5. Configure alarms or clock output if needed.

* The driver initializes the I2C bus automatically in master mode at up to `400 kHz`, if the bus is disabled.


### Minimal example
```cpp
RTC_DS3231 RTC(I2C0);
DateTime dt;
bool lost;

if(RTC.time_lost(lost) == OK && lost)
{
    RTC.set_time({2026, 6, 29, 14, 30, 0});
}

if(RTC.get_time(dt) == OK)
{
    console.log(dt);
}
```


### Setting date and time
The full date and time can be written with `set_time(const DateTime &dt)`:
```cpp
RTC_DS3231 <I2C_Bus> rtc;
DateTime dt = {2026, 6, 29, 14, 30, 0};

if(rtc.set_time(dt) == OK)
{
    // time was written successfully.
}
```

* The driver writes the hour register in 24-hour mode and clears time_lost flag (OSF) automatically.

* The weekday is calculated from the date, because the DS3231 can not calculate weekday by itself.



### Reading date and time
Read full date and time:
```cpp
RTC_DS3231 <I2C_Bus> rtc;
DateTime dt;

if(rtc.get_time(dt) == OK)
{
    // process date and time
}
```

* The driver always decodes time to 24-hour format.


### Date-only and time-only access
Use `Date` structure when only the calendar date is needed:
```cpp
Date date;

if(rtc.get_time(date) == OK)
{
    // process date
}
```

Use `Time` structure when only time-of-day is needed:
```cpp
Time time;

if(rtc.get_time(time) == OK)
{
    // process time
}
```


`set_time(const Date &date)` writes weekday, day, month, and year.

`set_time(const Time &time)` writes seconds, minutes, and hours.

Both methods clear the oscillator-stop flag after a successful write.


### Oscillator-stop flag
The DS3231 status register contains the oscillator-stop flag (OSF).
This flag indicates that the oscillator was stopped at least once and the stored time may be invalid.

```cpp
bool lost;

if(rtc.time_lost(lost) == OK && lost)
{
    rtc.set_time({2026, 6, 29, 14, 30, 0});
}
```

`time_lost()` only reads the flag.

The flag is cleared automatically after a successful `set_time()` call.


### Hardware alarms
DS3231 has two hardware alarms.

The driver exposes both alarms through one common API:
```cpp
rtc.set_alarm(1, config);
rtc.enable_alarm(1);
rtc.disable_alarm(1);
rtc.reset_alarm(1);
```

Valid alarm IDs:
```cpp
1   // for alarm # 1
2   // for alarm # 2
```

> [!WARNING]
> `set_alarm()` only writes the alarm condition registers.  
> It does **not** enable the alarm interrupt and does **not** reset the alarm flag.


### Alarm workflow
A typical alarm setup uses three explicit steps:
```cpp
RTC_Alarm alarm;
alarm.minute  = 30;
alarm.hour    = 14;
alarm.day     = RTC_ANY;
alarm.weekday = RTC_ANY;

rtc.set_alarm(1, alarm);    // write condition only
rtc.reset_alarm(1);         // clear old pending flag
rtc.enable_alarm(1);        // enable Alarm 1 and interrupt output
```

DS3231 has only one interrupt output for both alarms.
Use `check_alarm(...)` to resolve pending alarm id:
```cpp
uint8_t alarm_id;
if(rtc.check_alarm(alarm_id) == OK && alarm_id != 0)
{
    console.log(alarm_id);
}
```

0 means 'no alarm'. `check_alarm(...)` also resets the returned alarm flag. So, if both alarms are pending, three sequentiall `check_alarm(...)` calls will give the following result: 1, 2, 0.



### Alarm patterns
`RTC_Alarm` uses `RTC_ANY` for fields that should be ignored.

So the following patterns are supported.

#### Every minute alarm
```cpp
RTC_Alarm alarm;
alarm.minute  = RTC_ANY;
alarm.hour    = RTC_ANY;
alarm.day     = RTC_ANY;
alarm.weekday = RTC_ANY;

rtc.set_alarm(1, alarm);
rtc.reset_alarm(1);
rtc.enable_alarm(1);
```

#### Every hour at selected minute
```cpp
RTC_Alarm alarm;
alarm.minute  = 15;
alarm.hour    = RTC_ANY;
alarm.day     = RTC_ANY;
alarm.weekday = RTC_ANY;

rtc.set_alarm(1, alarm);
```

#### Every day at selected hour and minute
```cpp
RTC_Alarm alarm;
alarm.minute  = 30;
alarm.hour    = 7;
alarm.day     = RTC_ANY;
alarm.weekday = RTC_ANY;

rtc.set_alarm(1, alarm);
```

#### Every month on selected day at selected hour and minute
```cpp
RTC_Alarm alarm;
alarm.minute  = 0;
alarm.hour    = 8;
alarm.day     = 1;
alarm.weekday = RTC_ANY;

rtc.set_alarm(1, alarm);
```

#### Every week on selected weekday at selected hour and minute:
```cpp
RTC_Alarm alarm;
alarm.minute  = 0;
alarm.hour    = 9;
alarm.day     = RTC_ANY;
alarm.weekday = 1;       // Monday

rtc.set_alarm(1, alarm);
```

* Weekday values use the same convention as the project `DateTime` code:
```cpp
1   // Monday
2   // Tuesday
3   // Wednesday
4   // Thursday
5   // Friday
6   // Saturday
7   // Sunday
```


### INT/SQW pin
The DS3231 `INT/SQW` pin is shared between alarm interrupt output and square-wave output.

Use alarm output:
```cpp
rtc.enable_alarm(1);
```

Use 1 Hz square-wave output:
```cpp
rtc.enable_1hz_output();
```

`enable_1hz_output()` clears `INTCN` and selects the 1 Hz square-wave rate.
`disable_1hz_output()` sets `INTCN` again, returning the pin to interrupt-control mode.

Alarm enable bits are not modified by `enable_1hz_output()` or `disable_1hz_output()`.


### 1 Hz output
The 1 Hz signal is available on the DS3231 `INT/SQW` pin.
On common breakout modules this pin is usually labeled `SQW` or `INT/SQW`.

```cpp
rtc.enable_1hz_output();
```

Disable square-wave mode:
```cpp
rtc.disable_1hz_output();
```




### 32 kHz output
The 32 kHz signal is available on the separate DS3231 `32kHz` pin.
On common breakout modules this pin is usually labeled `32K` or `32kHz`.

```cpp
rtc.enable_32khz_output();
```

Disable it:
```cpp
rtc.disable_32khz_output();
```

This output is controlled by the `EN32kHz` bit in the status register.
It is independent from the `INT/SQW` pin mode.


### Built-in temperature sensor
DS3231 has an internal temperature sensor used for oscillator compensation.
The driver can read the last converted temperature value:
```cpp
Temperature temp;

if(rtc.get_temperature(temp) == OK && temp.is_valid())
{
    console.log(temp.millis_celsius);
}
```

The result is returned as a `Temperature` object.
The main field `millis_celsius` stores the temperature in integer milli-degrees Celsius:
```cpp
25375   // means 25.375 °C
-10500  // means -10.500 °C
```

The DS3231 temperature register resolution is `0.25 °C`.

Some convenience methods may also be available through `Temperature`:
```cpp
temp.get_int_celsius();
temp.get_float_celsius();
```

> [!WARNING]
> Floating-point methods are very expensive on AVR.



## Under the hood

All public methods use the same low-level helpers:
```cpp
_read(reg, data, size);
_write(reg, value);
_write(reg, data_array);
```

Before every transfer, the driver checks the I2C bus mode:
```cpp
if(I2C :: get_mode() == I2C_DISABLED)
    I2C :: init_master(400000);

if(I2C :: get_mode() != I2C_MASTER)
    return ERR_BAD_MODE;
```

This makes simple code work without an explicit I2C initialization step, while still rejecting accidental use of a bus configured for another mode.