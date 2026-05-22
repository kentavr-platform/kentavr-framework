/*------------------------------------------------------------------------------------------------
 * DS18B20.tpp
 *
 * ATTENTION! This file is included from DS18B20.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
template <class Bus>
__inline ResultCode Sensor_DS18B20 <Bus> :: set_resolution(enum DS_Temp_Resolution bits,
                                                           bool make_default)
{
    ResultCode error;
    // read config values
    if((error = this->_read_scratchpad()))
    {
        return error;
    }
    // modify config value
    this->scratchpad.config = (uint8_t) bits;

    // write config values
    if((error = this->_write_scratchpad()))
    {
        return error;
    }

    // verify data
    if((error = this->_read_scratchpad()))
    {
        return error;
    }
    else
    {
        if(this->scratchpad.config != (uint8_t) bits)
        {
            return ERR_NOT_MODIFIED;
        }
    }

    // write to power-on defaults (if requested)
    if(make_default)
    {
        this->_copy_scratchpad();
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
