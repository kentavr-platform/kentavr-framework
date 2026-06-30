/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: DS3231.h
//----------------------------------------------------------------------------------------------*/
#ifndef DS3231_H
#define DS3231_H
//------------------------------------------------------------------------------------------------
#include "RTC/DateTime.h"
//------------------------------------------------------------------------------------------------
template <class I2C>
class RTC_DS3231
{
public:
    explicit RTC_DS3231() = default;
    explicit RTC_DS3231(I2C &) {};      // CTAD constructor

    // standard RTC methods
    static ResultCode get_time(DateTime &dt);
    static ResultCode get_time(Date &date);
    static ResultCode get_time(Time &time);
    static ResultCode set_time(const DateTime &dt);
    static ResultCode set_time(const Date &date);
    static ResultCode set_time(const Time &time);
    static ResultCode time_lost(bool &lost);

    // built-in alarms
    static ResultCode set_alarm(uint8_t alarm_id, const RTC_Alarm &alarm);
    static ResultCode enable_alarm(uint8_t alarm_id);
    static ResultCode disable_alarm(uint8_t alarm_id);
    static ResultCode reset_alarm(uint8_t alarm_id);
    static ResultCode check_alarm(uint8_t &alarm_id);

    // hardware-specific methods
    static ResultCode get_temperature(Temperature &temp);
    static ResultCode force_temperature_conversion();

    static ResultCode enable_1hz_output();
    static ResultCode enable_32khz_output();
    static ResultCode disable_1hz_output();
    static ResultCode disable_32khz_output();

private:
    static constexpr uint8_t address = 0x68;        // built-in I2C address
    static __inline ResultCode _read(uint8_t reg, void *data, uint8_t size);
    static __inline ResultCode _write(uint8_t reg, uint8_t value);
    template <uint8_t size>
    static __inline ResultCode _write(uint8_t reg, const uint8_t (&data)[size]);
    static __inline ResultCode _ensure_i2c();
    static __inline ResultCode _clear_time_lost_flag();
};
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(RTC_DS3231);
//------------------------------------------------------------------------------------------------
#include "DS3231.tpp"
//------------------------------------------------------------------------------------------------
#endif
