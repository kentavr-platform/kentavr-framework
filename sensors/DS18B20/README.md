# DS18B20
## Driver for the DS18B20 1-Wire temperature sensor


### Summary
`Sensor_DS18B20 sensor(bus, address);`
 - Use `bus` as a low-level [1-Wire interface](../../interfaces/OneWire)
 - Represents one physical `sensor` with a known `address`

`Sensor_DS18B20_Group sensors(bus);`
 - Represents all DS18B20 `sensors`, connected to the `bus`.


### Basic workflow
1. Create a `OneWireBus <PIN>` object.
2. Find a sensor address with `find_first()` / `find_next()`.
3. Create a `Sensor_DS18B20` object.
4. Start temperature conversion with `start_conversion()`.
5. Wait until conversion is complete.
6. Read the temperature with `read_temperature()`.

Note: `read_temperature()` reads an already converted value from the sensor scratchpad.
It **does not** start a new conversion automatically.


### Minimal example 
```cpp
OneWireBus <A7> bus;
OneWireAddress addr;
Temperature temp;

if(bus.find_first(addr))
{
    Sensor_DS18B20 sensor(bus, addr);
    if(sensor.is_valid())
    {
        sensor.start_conversion();
        mdelay(750);  // maximum conversion time (for 12-bit resolution) 
        if(sensor.read_temperature(temp) == OK && temp.is_valid())
        {
            // Temperature is stored in milli-degrees Celsius.
            // Example: 25375 means 25.375 °C.
            console.log(temp.millis_celsius);
        }
    }
}
```


### Multiple sensors on one bus
```cpp
OneWireBus <A7> bus;
OneWireAddress addr;
Temperature temp;
Sensor_DS18B20_Group sensors(bus);

sensors.start_conversion();  // start conversion on all devices at once
mdelay(750);  // maximum conversion time (for 12-bit resolution) 

bus.find_reset(addr);
while(bus.find_next(addr))
{
    Sensor_DS18B20 sensor(bus, addr);
    if(!sensor.is_valid())
    {
        continue;
    }
    if(sensor.read_temperature(temp) == OK && temp.is_valid())
    {
        console.log(temp.millis_celsius);
    }
}
```


### Resolution
DS18B20 supports 9-bit to 12-bit temperature resolution.

```cpp
Sensor_DS18B20 sensor(bus, addr);
sensor.set_resolution(BITS_10);         // temporary
sensor.set_resolution(BITS_10, true);   // stored as power-on default
```

Available values:
```cpp
BITS_9
BITS_10
BITS_11
BITS_12
```

Higher resolution gives a smaller temperature step, but conversion takes longer.

| Resolution | Temperature step | Max conversion time |
|---|---:|---:|
| 9 bit  | 0.5 °C    | 94 ms  |
| 10 bit | 0.25 °C   | 188 ms |
| 11 bit | 0.125 °C  | 375 ms |
| 12 bit | 0.0625 °C | 750 ms |

For simple code, waiting `750 ms` always works.  
For faster polling, reduce the resolution and use a shorter delay.


### Waiting for conversion
The simplest approach is a fixed delay:
```cpp
sensor.start_conversion();
mdelay(750);
sensor.read_temperature(temp);
```

However, for externally powered sensors, the bus can be polled:
```cpp
sensor.start_conversion();
while(bus.busy())
{
    // Wait until conversion is completed.
}
sensor.read_temperature(temp);
```


### Temperature format
The result is returned as a `Temperature` object.
The main field `millis_celsius` stores the temperature in integer milli-degrees Celsius:
```cpp
25375   // means 25.375 °C
-10500  // means -10.500 °C
```

Some convenience methods are also available:
```cpp
temp.get_int_celsius();
temp.get_int_fahrenheit();
temp.get_int_kelvin();

temp.get_float_celsius();
temp.get_float_fahrenheit();
temp.get_float_kelvin();
```
> [!WARNING]
> Floating-point methods are very expensive on AVR.


### Alarm thresholds
DS18B20 can store lower and upper alarm thresholds. This feature allows to discover only the devices with out-of-bounds temperature values.
```cpp
Sensor_DS18B20 sensor(bus, addr);
sensor.set_alarm(10, 30);  // lower threshold: 10 °C, upper threshold: 30 °C
```

Alarm search example:
```cpp
OneWireBus <A7> bus;
Sensor_DS18B20_Group sensors(bus);
OneWireAddress addr;
Temperature temp;

sensors.start_conversion();
mdelay(750);

while(1)
{
    
    bus.find_reset(addr);
    while(bus.find_alarm(addr))
    {
        Sensor_DS18B20 sensor(bus, addr);
        if(!sensor.is_valid())
        {
            continue;
        }
        if(sensor.read_temperature(temp) == OK && temp.is_valid())
        {
            console.log(temp.millis_celsius);
        }
    }
    sensors.start_conversion();
    delay(1);
}
```


### Raw scratchpad access
For diagnostic purposes the raw sensor scratchpad can be read directly.
However application code usually does not need this.
```cpp
uint8_t *raw = nullptr;

if(sensor.get_scratchpad(&raw) == OK)
{
    for(uint8_t i = 0; i < 9; i++)
    {
        console.log(raw[i]);
    }
}
```


## Under the hood
`Sensor_DS18B20` is a thin device-specific wrapper around the common `Protocol_DS18x20` implementation.

The driver is split into three layers:
- `OneWireBus` handles low-level 1-Wire signaling, ROM search, device selection and byte I/O.
- `Protocol_DS18x20` implements the common Dallas/Maxim temperature sensor protocol.
- `Sensor_DS18B20` adds DS18B20-specific features, mainly configurable resolution.

The sensor object stores a reference to the bus and one ROM address.  
All device-specific operations use this address to select the sensor before sending a command.
```cpp
Sensor_DS18B20 sensor(bus, addr);
```

Group operations use a separate type:
```cpp
Sensor_DS18B20_Group sensors(bus);
```

`Sensor_DS18B20_Group` does not represent a specific device and does not store a ROM address.  
It uses a broadcast command to address all sensors on the bus at once. This is useful for starting temperature conversion on all sensors simultaneously.

Temperature measurement is intentionally split into two steps:
```cpp
sensor.start_conversion();
mdelay(750);
sensor.read_temperature(temp);
```

`start_conversion()` only tells the sensor to begin measuring.  
`read_temperature()` reads the scratchpad later, checks CRC and converts the raw sensor value to `millis_celsius`.

Configuration methods such as `set_resolution()` and `set_alarm()` use a read-modify-write-verify sequence:

1. read current scratchpad;
2. modify only required fields;
3. write scratchpad back to the sensor;
4. read scratchpad again and verify the change;
5. optionally copy scratchpad to sensor EEPROM.

The `make_default` argument controls whether the new configuration is only temporary or stored in the sensor EEPROM:
```cpp
sensor.set_resolution(BITS_10);       // temporary
sensor.set_resolution(BITS_10, true); // stored as power-on default
```
