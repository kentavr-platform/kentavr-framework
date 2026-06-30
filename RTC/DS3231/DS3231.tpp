/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: DS3231.tpp
 *
 * WARNING! This file is included from DS3231.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Decode the DS3231 hour register value.
 *
 * Supports both DS3231 hour formats: 24-hour mode and 12-hour AM/PM mode.
 * The returned value is always in 24-hour format, in the range 0..23.
 *
 * @param value Raw DS3231 hour register value.
 *
 * @return Decoded hour in 24-hour format.
 */
static __inline uint8_t _decode_hour(uint8_t value)
{
    if(value & 0x40)    // bit 6 defines 12h or 24h mode
    {
        // 12-hour mode
        uint8_t hour = bcd2bin(value & 0x1F);
        if(value & 0x20)    // bit 5 = PM
        {
            if(hour != 12)  hour += 12;
        }
        else
        {
            if(hour == 12)  hour = 0;
        }
        return hour;
    }
    // 24-hour mode
    return bcd2bin(value & 0x3F);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Multiply an unsigned value by 250.
 *
 * Used to convert DS3231 temperature units of 0.25 degrees Celsius to
 * milli-degrees Celsius.
 *
 * @param value Unsigned input value.
 *
 * @return value * 250.
 */
static __inline uint32_t _mul250(uint16_t value)
{
    uint32_t v = value;
    return (v << 8) - (v << 2) - (v << 1);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Multiply a signed value by 250.
 *
 * Used to convert signed DS3231 temperature units of 0.25 degrees Celsius to
 * milli-degrees Celsius.
 *
 * @param value Signed input value.
 *
 * @return value * 250.
 */
static __inline int32_t _mul250(int16_t value)
{
    if(value < 0)
    {
        uint16_t abs_value = 0u - (uint16_t)value;
        return -(int32_t)_mul250(abs_value);
    }
    return (int32_t)_mul250((uint16_t)value);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read full date and time from the DS3231.
 *
 * Reads seconds, minutes, hours, weekday, day, month, and year.
 * The hour register is decoded correctly in both 24-hour and 12-hour modes.
 *
 * @param dt Reference to a DateTime object to receive the result.
 *
 * @return OK on success.
 * @return ERR_INVALID if the received date/time fields are not valid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: get_time(DateTime &dt)
{
    static constexpr uint8_t REG_TIME = 0x00;
    uint8_t data[7];

    ResultCode result = _read(REG_TIME, data, sizeof(data));
    if(result != OK)
        return result;

    dt.second  = bcd2bin(data[0]);
    dt.minute  = bcd2bin(data[1]);
    dt.hour    = _decode_hour(data[2]);
    dt.weekday = data[3];
    dt.day     = bcd2bin(data[4]);
    dt.month   = bcd2bin(data[5] & 0x1F);
    dt.year    = (data[5] & 0x80 ? 2100 : 2000) + bcd2bin(data[6]);
    return dt.is_valid() ? OK : ERR_INVALID;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read calendar date from the DS3231.
 *
 * Reads weekday, day, month, and year.
 * This method is intended for projects that only need calendar date and do not
 * use time-of-day.
 *
 * @param date Reference to a Date object to receive the result.
 *
 * @return OK on success.
 * @return ERR_INVALID if the received date fields are not valid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: get_time(Date &date)
{
    static constexpr uint8_t REG_DATE = 0x03;
    uint8_t data[4];

    ResultCode result = _read(REG_DATE, data, sizeof(data));
    if(result != OK)
        return result;

    date.weekday = data[0];
    date.day     = bcd2bin(data[1]);
    date.month   = bcd2bin(data[2] & 0x1F);
    date.year    = (data[2] & 0x80 ? 2100 : 2000) + bcd2bin(data[3]);
    return date.is_valid() ? OK : ERR_INVALID;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read time-of-day from the DS3231.
 *
 * Reads seconds, minutes, and hours.
 * The hour register is decoded correctly in both 24-hour and 12-hour modes.
 * This method is intended for projects that only need time-of-day and do not
 * use calendar date.
 *
 * @param time Reference to a Time object to receive the result.
 *
 * @return OK on success.
 * @return ERR_INVALID if the received time fields are not valid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: get_time(Time &time)
{
    static constexpr uint8_t REG_TIME = 0x00;
    uint8_t data[3];

    ResultCode result = _read(REG_TIME, data, sizeof(data));
    if(result != OK)
        return result;

    time.second  = bcd2bin(data[0]);
    time.minute  = bcd2bin(data[1]);
    time.hour    = _decode_hour(data[2]);
    return time.is_valid() ? OK : ERR_INVALID;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set full date and time in the DS3231.
 *
 * Writes seconds, minutes, hours, weekday, day, month, and year.
 * The weekday value is calculated from the date because the DS3231 does not
 * calculate weekday automatically.
 *
 * The hour register is written in 24-hour mode.
 * On successful write this method clears the DS3231 oscillator stop flag.
 *
 * Supported year range: 2000..2199.
 *
 * @param dt DateTime value to write.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if the DateTime value is invalid or the year is
 *         outside the supported range.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: set_time(const DateTime &dt)
{
    static constexpr uint8_t REG_TIME = 0x00;
    ResultCode result;

    if(!dt.is_valid() || dt.year < 2000 || dt.year > 2199)
        return ERR_BAD_PARAMETER;

    uint8_t year;
    uint8_t month = bin2bcd(dt.month);
    if(dt.year >= 2100)
    {
        year = dt.year - 2100;
        month |= 0x80; // century bit
    }
    else
    {
        year = dt.year - 2000;
    }

    uint8_t data[7];
    data[0] = bin2bcd(dt.second);
    data[1] = bin2bcd(dt.minute);
    data[2] = bin2bcd(dt.hour);     // 24-hour mode
    data[3] = dt.get_weekday();     // calculate weekday manually, DS3231 does NOT do this
    data[4] = bin2bcd(dt.day);
    data[5] = month;
    data[6] = bin2bcd(year);
    result = _write(REG_TIME, data);
    if(result != OK)
        return result;

    return _clear_time_lost_flag();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set calendar date in the DS3231.
 *
 * Writes weekday, day, month, and year.
 * The weekday value is calculated from the date because the DS3231 does not
 * calculate weekday automatically.
 *
 * This method is intended for projects that only use calendar date and do not
 * use time-of-day.
 *
 * On successful write this method clears the DS3231 oscillator stop flag.
 *
 * Supported year range: 2000..2199.
 *
 * @param date Date value to write.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if the Date value is invalid or the year is outside
 *         the supported range.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: set_time(const Date &date)
{
    static constexpr uint8_t REG_DATE = 0x03;
    ResultCode result;

    if(!date.is_valid() || date.year < 2000 || date.year > 2199)
        return ERR_BAD_PARAMETER;

    uint8_t year;
    uint8_t month = bin2bcd(date.month);
    if(date.year >= 2100)
    {
        year = date.year - 2100;
        month |= 0x80; // century bit
    }
    else
    {
        year = date.year - 2000;
    }

    uint8_t data[4];
    data[0] = date.get_weekday();     // calculate weekday manually, DS3231 does NOT do this
    data[1] = bin2bcd(date.day);
    data[2] = month;
    data[3] = bin2bcd(year);
    result = _write(REG_DATE, data);
    if(result != OK)
        return result;

    return _clear_time_lost_flag();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set time-of-day in the DS3231.
 *
 * Writes seconds, minutes, and hours.
 * The hour register is written in 24-hour mode.
 *
 * This method is intended for projects that only use time-of-day and do not
 * use calendar date.
 *
 * On successful write this method clears the DS3231 oscillator stop flag.
 *
 * @param time Time value to write.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if the Time value is invalid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: set_time(const Time &time)
{
    static constexpr uint8_t REG_TIME = 0x00;
    ResultCode result;

    if(!time.is_valid())
        return ERR_BAD_PARAMETER;

    uint8_t data[3];
    data[0] = bin2bcd(time.second);
    data[1] = bin2bcd(time.minute);
    data[2] = bin2bcd(time.hour);     // 24-hour mode
    result = _write(REG_TIME, data);
    if(result != OK)
        return result;

    return _clear_time_lost_flag();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check whether the DS3231 has lost the time.
 *
 * Reads the OSF bit from the DS3231 status register.
 * If this flag is set, the oscillator has stopped at least once and the stored
 * date/time may be invalid.
 *
 * The flag is cleared automatically by set_time() after a successful write,
 * according to the driver contract.
 *
 * @param lost Reference to a bool variable to receive the result.
 *             true if the RTC time may be invalid, false otherwise.
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: time_lost(bool &lost)
{
    static constexpr uint8_t REG_STATUS = 0x0F;
    static constexpr uint8_t STATUS_OSF = 0x80;

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    lost = (status & STATUS_OSF) != 0;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set one of the DS3231 hardware alarms.
 *
 * Configures the selected hardware alarm using minute-resolution RTC_Alarm
 * settings.
 *
 * This method only writes alarm condition registers.
 * It does not enable the alarm interrupt and does not reset the alarm flag.
 *
 * Alarm 1 has a seconds register, but this driver fixes seconds to 00.
 * Alarm 2 has no seconds register and also triggers at second 00 of the
 * matching minute.
 *
 * Supported alarm patterns:
 * - every minute;
 * - every hour at the selected minute;
 * - every day at the selected hour and minute;
 * - every month on the selected day at the selected hour and minute;
 * - every week on the selected weekday at the selected hour and minute.
 *
 * @param alarm_id Alarm number: 1 for Alarm 1, 2 for Alarm 2.
 * @param alarm Alarm configuration.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if alarm_id is invalid or the alarm configuration
 *         is invalid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: set_alarm(uint8_t alarm_id, const RTC_Alarm &alarm)
{
    static constexpr uint8_t REG_ALARM1 = 0x07;
    static constexpr uint8_t REG_ALARM2 = 0x0B;
    static constexpr uint8_t MASK  = 0x80;
    static constexpr uint8_t DY_DT = 0x40;

    uint8_t reg;
    bool alarm1;

    switch(alarm_id)
    {
    case 1:
        reg = REG_ALARM1;
        alarm1 = true;
        break;

    case 2:
        reg = REG_ALARM2;
        alarm1 = false;
        break;

    default:
        return ERR_BAD_PARAMETER;
    }

    bool has_minute  = alarm.minute  != RTC_ANY;
    bool has_hour    = alarm.hour    != RTC_ANY;
    bool has_day     = alarm.day     != RTC_ANY;
    bool has_weekday = alarm.weekday != RTC_ANY;

    if(has_day && has_weekday)
        return ERR_BAD_PARAMETER;

    // DS3231 alarm matching must be continuous:
    // minute -> hour -> day/weekday.
    if(has_hour && !has_minute)
        return ERR_BAD_PARAMETER;

    if((has_day || has_weekday) && (!has_minute || !has_hour))
        return ERR_BAD_PARAMETER;

    if(has_minute && alarm.minute > 59)
        return ERR_BAD_PARAMETER;

    if(has_hour && alarm.hour > 23)
        return ERR_BAD_PARAMETER;

    uint8_t day_reg = MASK;

    if(has_day)
    {
        if(alarm.day < 1 || alarm.day > 31)
            return ERR_BAD_PARAMETER;

        day_reg = bin2bcd(alarm.day);
    }

    if(has_weekday)
    {
        if(alarm.weekday < 1 || alarm.weekday > 7)
            return ERR_BAD_PARAMETER;

        day_reg = bin2bcd(alarm.weekday) | DY_DT;
    }

    uint8_t minute_reg = has_minute ? bin2bcd(alarm.minute) : MASK;
    uint8_t hour_reg   = has_hour   ? bin2bcd(alarm.hour)   : MASK;

    if(alarm1)
    {
        uint8_t data[4];
        data[0] = 0;          // seconds = 00, A1M1 = 0
        data[1] = minute_reg; // minutes
        data[2] = hour_reg;   // hours
        data[3] = day_reg;    // day/date

        return _write(reg, data);
    }

    // Alarm2 has no seconds register.
    // It triggers at second 00 of the matching minute.
    uint8_t data[3];
    data[0] = minute_reg; // minutes
    data[1] = hour_reg;   // hours
    data[2] = day_reg;    // day/date

    return _write(reg, data);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable one of the DS3231 hardware alarms.
 *
 * Enables the selected alarm interrupt bit in the Control register.
 * Also sets INTCN, switching INT/SQW pin to interrupt mode.
 *
 * This method does not modify alarm condition registers and does not reset
 * alarm flags.
 *
 * @param alarm_id Alarm number: 1 for Alarm 1, 2 for Alarm 2.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if alarm_id is invalid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: enable_alarm(uint8_t alarm_id)
{
    static constexpr uint8_t REG_CONTROL = 0x0E;
    static constexpr uint8_t CTRL_INTCN = 0x04;
    static constexpr uint8_t CTRL_A2IE  = 0x02;
    static constexpr uint8_t CTRL_A1IE  = 0x01;

    uint8_t alarm_bit;

    switch(alarm_id)
    {
    case 1:
        alarm_bit = CTRL_A1IE;
        break;

    case 2:
        alarm_bit = CTRL_A2IE;
        break;

    default:
        return ERR_BAD_PARAMETER;
    }

    uint8_t control;

    ResultCode result = _read(REG_CONTROL, &control, 1);
    if(result != OK)
        return result;

    control |= CTRL_INTCN | alarm_bit;
    return _write(REG_CONTROL, control);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable one of the DS3231 hardware alarms.
 *
 * Clears the selected alarm interrupt bit in the Control register.
 *
 * This method does not modify alarm condition registers and does not reset
 * alarm flags.
 *
 * @param alarm_id Alarm number: 1 for Alarm 1, 2 for Alarm 2.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if alarm_id is invalid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: disable_alarm(uint8_t alarm_id)
{
    static constexpr uint8_t REG_CONTROL = 0x0E;
    static constexpr uint8_t CTRL_A2IE = 0x02;
    static constexpr uint8_t CTRL_A1IE = 0x01;

    uint8_t alarm_bit;

    switch(alarm_id)
    {
    case 1:
        alarm_bit = CTRL_A1IE;
        break;

    case 2:
        alarm_bit = CTRL_A2IE;
        break;

    default:
        return ERR_BAD_PARAMETER;
    }

    uint8_t control;

    ResultCode result = _read(REG_CONTROL, &control, 1);
    if(result != OK)
        return result;

    control &= static_cast <uint8_t> (~alarm_bit);
    return _write(REG_CONTROL, control);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reset alarm flag.
 *
 * Clears the selected alarm flag in the Status register:
 * A1F for Alarm 1 or A2F for Alarm 2.
 *
 * This method does not modify alarm condition registers and does not enable or
 * disable alarm interrupts.
 *
 * @param alarm_id Alarm number: 1 for Alarm 1, 2 for Alarm 2.
 *
 * @return OK on success.
 * @return ERR_BAD_PARAMETER if alarm_id is invalid.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: reset_alarm(uint8_t alarm_id)
{
    static constexpr uint8_t REG_STATUS = 0x0F;
    static constexpr uint8_t STATUS_A2F = 0x02;
    static constexpr uint8_t STATUS_A1F = 0x01;

    uint8_t alarm_flag;

    switch(alarm_id)
    {
    case 1:
        alarm_flag = STATUS_A1F;
        break;

    case 2:
        alarm_flag = STATUS_A2F;
        break;

    default:
        return ERR_BAD_PARAMETER;
    }

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    status &= static_cast <uint8_t> (~alarm_flag);
    return _write(REG_STATUS, status);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check DS3231 alarm flags.
 *
 * Reads the DS3231 status register and checks A1F/A2F alarm flags.
 *
 * If Alarm 1 flag is set, alarm_id is set to 1 and A1F is reset.
 * If only Alarm 2 flag is set, alarm_id is set to 2 and A2F is reset.
 * If no alarm flag is set, alarm_id is set to 0.
 *
 * If both alarm flags are set at the same time, Alarm 1 has priority.
 * Alarm 2 remains pending and will be returned by the next call.
 *
 * @param alarm_id Reference to a variable to receive alarm number:
 *                 0 - no alarm;
 *                 1 - Alarm 1;
 *                 2 - Alarm 2.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: check_alarm(uint8_t &alarm_id)
{
    static constexpr uint8_t REG_STATUS = 0x0F;
    static constexpr uint8_t STATUS_A1F = 0x01;
    static constexpr uint8_t STATUS_A2F = 0x02;

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    if(status & STATUS_A1F)
    {
        alarm_id = 1;
        return _write(REG_STATUS, status & ~STATUS_A1F);
    }

    if(status & STATUS_A2F)
    {
        alarm_id = 2;
        return _write(REG_STATUS, status & ~STATUS_A2F);
    }

    alarm_id = 0;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable 1 Hz square-wave output on INT/SQW pin.
 *
 * Configures the DS3231 INT/SQW pin as a square-wave output and selects
 * the 1 Hz rate.
 *
 * This clears the INTCN bit and clears RS1/RS2 rate-select bits.
 * Alarm flags and alarm configuration registers are not modified.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: enable_1hz_output()
{
    static constexpr uint8_t REG_CONTROL = 0x0E;
    static constexpr uint8_t CTRL_INTCN  = 0x04;
    static constexpr uint8_t CTRL_RS1    = 0x08;
    static constexpr uint8_t CTRL_RS2    = 0x10;

    uint8_t control;

    ResultCode result = _read(REG_CONTROL, &control, 1);
    if(result != OK)
        return result;

    control &= ~(CTRL_INTCN | CTRL_RS1 | CTRL_RS2);
    return _write(REG_CONTROL, control);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable square-wave output on INT/SQW pin.
 *
 * Switches the DS3231 INT/SQW pin back to interrupt-control mode by setting
 * the INTCN bit.
 *
 * This method does not change alarm enable bits or alarm flags.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: disable_1hz_output()
{
    static constexpr uint8_t REG_CONTROL = 0x0E;
    static constexpr uint8_t CTRL_INTCN  = 0x04;

    uint8_t control;

    ResultCode result = _read(REG_CONTROL, &control, 1);
    if(result != OK)
        return result;

    control |= CTRL_INTCN;
    return _write(REG_CONTROL, control);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable 32 kHz output.
 *
 * Sets the EN32kHz bit in the DS3231 status register.
 *
 * This method only controls the DS3231 32 kHz output enable bit.
 * It does not affect the INT/SQW pin mode.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: enable_32khz_output()
{
    static constexpr uint8_t REG_STATUS    = 0x0F;
    static constexpr uint8_t STATUS_EN32KHZ = 0x08;

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    return _write(REG_STATUS, status | STATUS_EN32KHZ);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable 32 kHz output.
 *
 * Clears the EN32kHz bit in the DS3231 status register.
 *
 * This method only controls the DS3231 32 kHz output enable bit.
 * It does not affect the INT/SQW pin mode.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: disable_32khz_output()
{
    static constexpr uint8_t REG_STATUS     = 0x0F;
    static constexpr uint8_t STATUS_EN32KHZ = 0x08;

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    return _write(REG_STATUS, status & ~STATUS_EN32KHZ);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read the internal DS3231 temperature sensor.
 *
 * Reads the DS3231 temperature registers and stores the result as a Temperature
 * value. The DS3231 temperature resolution is 0.25 degrees Celsius.
 *
 * This method only reads the last converted temperature value. It does not
 * start a forced temperature conversion.
 *
 * @param temp Reference to a Temperature object to receive the result.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: get_temperature(Temperature &temp)
{
    static constexpr uint8_t REG_TEMPERATURE = 0x11;
    uint8_t data[2];
    ResultCode result = _read(REG_TEMPERATURE, data, 2);
    if(result != OK)
    {
        temp.valid = false;
        return result;
    }

    int16_t raw_x4 = (int16_t)(int8_t)data[0] * 4 + (data[1] >> 6);
    temp.millis_celsius = _mul250(raw_x4);
    temp.valid = true;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Start a forced temperature conversion.
 *
 * Sets the CONV bit in the DS3231 control register if the RTC is not busy.
 *
 * For DS3231M this method is usually not needed while the chip is powered from
 * VCC, because temperature conversion is performed automatically.
 *
 * @return OK on success.
 * @return ERR_BUSY if the DS3231 is already performing a temperature conversion.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231<I2C> :: force_temperature_conversion()
{
    static constexpr uint8_t REG_CONTROL = 0x0E;
    static constexpr uint8_t REG_STATUS  = 0x0F;
    static constexpr uint8_t CTRL_CONV   = 0x20; // bit 5
    static constexpr uint8_t STATUS_BSY  = 0x04; // bit 2
    uint8_t tmp;

    ResultCode result = _read(REG_STATUS, &tmp, 1);
    if(result != OK)
        return result;
    if(tmp & STATUS_BSY)
        return ERR_BUSY;

    result = _read(REG_CONTROL, &tmp, 1);
    if(result != OK)
        return result;

    return _write(REG_CONTROL, tmp | CTRL_CONV);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read bytes from DS3231 registers.
 *
 * Writes the register address first and then reads the requested number of
 * bytes from the DS3231.
 *
 * The I2C bus is initialized automatically if it is currently disabled.
 *
 * @param reg First DS3231 register address to read from.
 * @param data Destination buffer.
 * @param size Number of bytes to read.
 *
 * @return OK on success.
 * @return ERR_BAD_MODE if the I2C bus is enabled but not in master mode.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
__inline ResultCode RTC_DS3231 <I2C> :: _read(uint8_t reg, void *data, uint8_t size)
{
    ResultCode result = _ensure_i2c();
    if(result != OK)
        return result;

    result = I2C :: send(address, &reg, 1);
    if(result != OK)
        return result;
    return I2C :: receive(address, data, size);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Write one byte to a DS3231 register.
 *
 * The I2C bus is initialized automatically if it is currently disabled.
 *
 * @param reg DS3231 register address to write to.
 * @param value Byte value to write.
 *
 * @return OK on success.
 * @return ERR_BAD_MODE if the I2C bus is enabled but not in master mode.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
__inline ResultCode RTC_DS3231 <I2C> :: _write(uint8_t reg, uint8_t value)
{
    ResultCode result = _ensure_i2c();
    if(result != OK)
        return result;

    uint8_t buf[2] = { reg, value };
    return I2C :: send(address, buf, sizeof(buf));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Write a fixed-size byte block to DS3231 registers.
 *
 * Writes the register address followed by the provided data block.
 * This helper is used for multi-register writes such as DateTime, Date, and
 * Time updates.
 *
 * The I2C bus is initialized automatically if it is currently disabled.
 *
 * @tparam size Number of data bytes to write.
 * @param reg First DS3231 register address to write to.
 * @param data Data array to write.
 *
 * @return OK on success.
 * @return ERR_BAD_MODE if the I2C bus is enabled but not in master mode.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
template <uint8_t size>
__inline ResultCode RTC_DS3231<I2C> :: _write(uint8_t reg, const uint8_t (&data)[size])
{
    ResultCode result = _ensure_i2c();
    if(result != OK)
        return result;

    uint8_t buf[size + 1];

    buf[0] = reg;

    for(uint8_t i = 0; i < size; i++)
        buf[i + 1] = data[i];

    return I2C :: send(address, buf, sizeof(buf));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Ensure that the I2C bus is ready for DS3231 communication.
 *
 * If the I2C bus is disabled, it is initialized in master mode using the
 * maximum DS3231 I2C frequency.
 *
 * If the bus is already enabled but not in master mode, the method returns
 * ERR_BAD_MODE.
 *
 * @return OK if the bus is ready.
 * @return ERR_BAD_MODE if the bus is enabled in a non-master mode.
 * @return Other ResultCode values returned by I2C initialization.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: _ensure_i2c()
{
    static constexpr uint32_t DS3231_MAX_FREQ = 400000;

    if(I2C :: get_mode() == I2C_DISABLED)
        return I2C :: init_master(DS3231_MAX_FREQ);

    if(I2C :: get_mode() != I2C_MASTER)
        return ERR_BAD_MODE;

    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Clear the DS3231 oscillator stopped flag.
 *
 * Clears the OSF bit in the DS3231 status register. This flag indicates that
 * the oscillator was temporary stopped and the stored time may be invalid.
 *
 * This helper is called after successful time/date updates according to the
 * driver contract.
 *
 * @return OK on success.
 * @return Other ResultCode values returned by the I2C driver.
 */
template <class I2C>
ResultCode RTC_DS3231 <I2C> :: _clear_time_lost_flag()
{
    static constexpr uint8_t REG_STATUS = 0x0F;
    static constexpr uint8_t STATUS_OSF = 0x80;

    uint8_t status;

    ResultCode result = _read(REG_STATUS, &status, 1);
    if(result != OK)
        return result;

    return _write(REG_STATUS, status & ~STATUS_OSF);
}
//------------------------------------------------------------------------------------------------


