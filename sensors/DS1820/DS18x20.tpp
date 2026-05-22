/*------------------------------------------------------------------------------------------------
 * DS18x20.tpp
 *
 * ATTENTION! This file is included from DS18x20.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Checks whether the current device's address belongs to the supported family.
 *
 * @return true if device family is supported, false otherwise.
 */
template <class Bus, class Family>
__inline bool Protocol_DS18x20 <Bus, Family> :: is_valid()
{
    if(!has_address)
    {
        return false;
    }
    return Family :: match_family(address.family());
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Starts temperature conversion on one or all devices.
 *
 * If device address is set, conversion is started for a single sensor.
 * Otherwise, broadcast mode (SKIP_ROM) is used.
 *
 * @return OK if command was issued successfully,
 *         ERR_NOT_FOUND if device/bus is not available.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: start_conversion()
{
    if(has_address)
    {
        if(!bus.select_device(address))
        {
            return ERR_NOT_FOUND;
        };
    }
    else
    {
        if(!bus.start_broadcast())
        {
            return ERR_NOT_FOUND;
        }
    }

    bus.write_byte(0x44);               // CMD START CONVERTION
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Recalls alarm and configuration values from sensor's EEPROM to it's scratchpad.
 *
 * Performs a "recall configuration" action.
 *
 * Sends the RECALL_E2 command to the selected device, causing it to load
 * previously stored TH/TL (and configuration, if supported) from non-volatile memory
 * into the scratchpad.
 *
 * @return OK if command was successfully issued,
 *         ERR_NOT_FOUND if device is not present on the bus.
 *
 * @note This function does not verify completion of the recall operation.
 *       Some devices may require a busy polling mechanism for full correctness.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: reset_defaults()
{
    if(!bus.select_device(address))
    {
        return ERR_NOT_FOUND;
    };
    bus.write_byte(0xB8);               // CMD RECALL E2
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads and converts temperature value from scratchpad.
 *
 * Converts raw sensor data into milli-Celsius format.
 *
 * @param[out] result Temperature structure with validity flag.
 *
 * @return OK on success, error code otherwise.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: read_temperature(Temperature &result)
{
    ResultCode error;

    if((error = _read_scratchpad()))
    {
        result.valid = false;
        return error;
    }

    if constexpr(Family :: HIGH_RESOLUTION)
    {
        result.millis_celsius = (int32_t) scratchpad.temperature * 1000 / 16;
    }
    else
    {
        result.millis_celsius = (int32_t) scratchpad.temperature / 2 * 1000 - 250
                                + (int32_t)(scratchpad.count_per_c - scratchpad.count_remain)
                                * 1000 / scratchpad.count_per_c;
    }
    result.valid = true;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get pointer to the raw scratchpad memory of sensor.
 *
 * @param[out] ptr Pointer to internal scratchpad buffer.
 *
 * @return OK on success, error code otherwise.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: get_scratchpad(uint8_t **ptr)
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
/**
 * @brief Configures alarm thresholds for temperature monitoring.
 *
 * Updates TH and TL values in sensor scratchpad and optionally
 * stores them in non-volatile memory. Performs complete
 * Read - Modify - Write - Verify cycle.
 *
 * @param lower_celsius Lower alarm threshold.
 * @param upper_celsius Upper alarm threshold.
 * @param make_default If true, values are also stored in EEPROM.
 *
 * @return OK on success,
 *         ERR_BAD_PARAMETER if thresholds are invalid,
 *         ERR_NOT_MODIFIED if verification fails.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: set_alarm(int8_t lower_celsius,
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

    if(make_default)
    {
        // write to power-on defaults
        return _copy_scratchpad();
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads sensor scratchpad memory.
*
 * @return OK on success, ERR_BAD_CHECKSUM or ERR_NOT_FOUND otherwise.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: _read_scratchpad()
{
    if(!bus.select_device(address))
    {
        return ERR_NOT_FOUND;
    };
    bus.write_byte(0xBE);               // CMD RAM READ
    for(uint8_t i = 0; i < sizeof(scratchpad.raw); i++)
    {
        scratchpad.raw[i] = bus.read_byte();
    }
    // CRC check
    if(Dallas_CRC8(scratchpad.raw, sizeof(scratchpad.raw) - 1) != scratchpad.CRC)
    {
        return ERR_BAD_CHECKSUM;
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes configuration to sensor scratchpad.
 *
 * Writes TH/TL (and optionally config byte) to device memory.
 *
 * @return OK on success, ERR_NOT_FOUND if device is absent.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: _write_scratchpad()
{
    if(!bus.select_device(address))
    {
        return ERR_NOT_FOUND;
    };
    bus.write_byte(0x4E);               // CMD WRITE SCRATCHPAD
    bus.write_byte(scratchpad.TH);
    bus.write_byte(scratchpad.TL);
    if constexpr(Family :: HAS_CONFIG)
    {
        bus.write_byte(scratchpad.config);
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Copies current scratchpad configuration into sensor EEPROM.
 *
 * Performs a "backup configuration" action.
 *
 * Sends the COPY_SCRATCHPAD command, causing the device to persist the
 * current scratchpad contents (typically TH, TL, and configuration byte)
 * into non-volatile memory.
 *
 * This operation is time-dependent and requires an internal EEPROM write cycle.
 *
 * @return OK if command was successfully issued,
 *         ERR_NOT_FOUND if device is not present on the bus.
 */
template <class Bus, class Family>
__inline ResultCode Protocol_DS18x20 <Bus, Family> :: _copy_scratchpad()
{
    if(!bus.select_device(address))
    {
        return ERR_NOT_FOUND;
    };
    bus.write_byte(0x48);               // CMD COPY SCRATCHPAD
    mdelay(10);
    return OK;
}
//------------------------------------------------------------------------------------------------






