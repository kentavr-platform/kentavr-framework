//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: start_conversion()
{
    if(bus.reset())
    {
        return ERR_NOT_FOUND;
    }

    if(has_address)
    {
        bus.select_device(address);
    }
    else
    {
        bus.start_broadcast();
    }

    bus.write_byte(0x44);   // CMD START CONVERTION
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: reset_defaults()
{
    if(bus.reset())
    {
        return ERR_NOT_FOUND;
    }
    bus.select_device(address);
    bus.write_byte(0xB8);   // CMD RECALL E2
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: read_temperature(Temperature &result)
{
    ResultCode error;

    if((error = _read_scratchpad()))
    {
        result.valid = false;
        return error;
    }

    int16_t raw = scratchpad.temperature;
    result.millis_celsius = (int32_t) raw * 1000 / 16;
    result.valid = true;
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: get_scratchpad(uint8_t **ptr)
{
    ResultCode error;
    if((error = _read_scratchpad()))
    {
        return error;
    }

    *ptr = scratchpad.raw;
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: set_alarm(int8_t lower_celsius,
                                                            int8_t upper_celsius,
                                                            bool make_default)
{
    if(lower_celsius >= upper_celsius)
    {
        // ambiguous values required
        return ERR_BAD_PARAMETER;
    }
    // read config values
    ResultCode error;
    if((error = _read_scratchpad()))
    {
        return error;
    }

    // modify config data
    scratchpad.TH = upper_celsius;
    scratchpad.TL = lower_celsius;

    // write config values
    if((error = _write_scratchpad()))
    {
        return error;
    }

    // verify data
    if((error = _read_scratchpad()))
    {
        return error;
    }
    else
    {
        if(scratchpad.TH != upper_celsius || scratchpad.TL != lower_celsius)
        {
            return ERR_NOT_MODIFIED;
        }
    }

    // write to power-on defaults (if requested)
    if(make_default)
    {
        return _copy_scratchpad();
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: set_resolution(enum DS_Temp_Resolution bits,
                                                                  bool make_default)
{
    ResultCode error;
    // read config values
    if((error = _read_scratchpad()))
    {
        return error;
    }
    // modify config value
    scratchpad.config = (uint8_t) bits;

    // write config values
    if((error = _write_scratchpad()))
    {
        return error;
    }

    // verify data
    if((error = _read_scratchpad()))
    {
        return error;
    }
    else
    {
        if(scratchpad.config != (uint8_t) bits)
        {
            return ERR_NOT_MODIFIED;
        }
    }

    // write to power-on defaults (if requested)
    if(make_default)
    {
        _copy_scratchpad();
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: _read_scratchpad()
{
    if(bus.reset())
    {
        return ERR_NOT_FOUND;
    }
    bus.select_device(address);
    bus.write_byte(0xBE);   // CMD RAM READ
    for(uint8_t i = 0; i < 9; i++)
    {
        scratchpad.raw[i] = bus.read_byte();
    }
    // CRC check
    if(Dallas_CRC8(scratchpad.raw, 8) != scratchpad.CRC)
    {
        return ERR_BAD_CHECKSUM;
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: _write_scratchpad()
{
    if(bus.reset())
    {
        return ERR_NOT_FOUND;
    }
    bus.select_device(address);
    bus.write_byte(0x4E);   // CMD WRITE SCRATCHPAD
    bus.write_byte(scratchpad.TH);
    bus.write_byte(scratchpad.TL);
    bus.write_byte(scratchpad.config);
    return OK;
}
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
__inline ResultCode Sensor_DS18B20 <OneWireBus> :: _copy_scratchpad()
{
    if(bus.reset())
    {
        return ERR_NOT_FOUND;
    }
    bus.select_device(address);
    bus.write_byte(0x48);   // CMD COPY SCRATCHPAD
    mdelay(10);
    return OK;
}
//------------------------------------------------------------------------------------------------






