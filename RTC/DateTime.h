#ifndef DATETIME_H
#define DATETIME_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "console/debug.h"
//------------------------------------------------------------------------------------------------
enum DateTimeFormat : uint8_t
{
    FMT_DEFAULT,    // YYYY-MM-DD HH:MM:SS
    FMT_ISO8601,    // YYYY-MM-DDTHH:MM:SS
    FMT_TIME,       // HH:MM:SS
    FMT_DATE_ISO,   // YYYY-MM-DD
    FMT_DATE_DMY,   // DD.MM.YYYY
    FMT_DATE_MDY    // MM/DD/YYYY
};
//------------------------------------------------------------------------------------------------
class Date
{
public:
    Date() = default;
    Date(uint16_t year, uint8_t month, uint8_t day)
         : year(year), month(month), day(day) {};
    bool is_valid() const;
    const char* to_string(enum DateTimeFormat fmt = FMT_DATE_ISO) const;
    uint16_t year       = 0;
    uint8_t  month      = 0;
    uint8_t  day        = 0;
    uint8_t  weekday    = 0;    // 1 = Monday ... 7 = Sunday, 0 = unknown/invalid
    uint8_t  get_weekday() const;
protected:
    static __inline void _fill_year(char *buf, uint16_t year);
    static __inline bool _is_leap_year(uint16_t _year);
    static __inline uint8_t _days_in_month(uint16_t _year, uint8_t _month);
private:
    mutable char str[11] = {};
};
//------------------------------------------------------------------------------------------------
class DateTime : public Date
{
public:
    DateTime() = default;
    DateTime(uint16_t year, uint8_t month, uint8_t day,
             uint8_t hour, uint8_t minute, uint8_t second)
             : Date(year, month, day), hour(hour), minute(minute), second(second) {};
    bool is_valid() const;
    uint32_t to_unix_time() const;
    const char* to_string(enum DateTimeFormat fmt = FMT_DEFAULT) const;
    uint8_t  hour       = 0;
    uint8_t  minute     = 0;
    uint8_t  second     = 0;
private:
    mutable char str[22] = {};
    static constexpr uint32_t SECONDS_PER_DAY = 86400;
};
//------------------------------------------------------------------------------------------------
struct Time
{
public:
    Time() = default;
    Time(uint8_t hour, uint8_t minute)
         : hour(hour), minute(minute), second(0) {};
    Time(uint8_t hour, uint8_t minute, uint8_t second)
         : hour(hour), minute(minute), second(second) {};
    bool is_valid() const;
    const char* to_string(enum DateTimeFormat fmt = FMT_DEFAULT) const;
    uint8_t  hour   = 0;
    uint8_t  minute = 0;
    uint8_t  second = 0;
private:
    mutable char str[10] = {};
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Minute-resolution RTC alarm configuration.
 *
 * Fields set to RTC_ANY are treated as wildcards.
 *
 * Valid combinations:
 * - all fields RTC_ANY: every minute;
 * - minute only: every hour at the selected minute;
 * - minute + hour: every day at the selected time;
 * - minute + hour + day: every month on the selected day;
 * - minute + hour + weekday: every week on the selected weekday.
 *
 * The day and weekday fields are mutually exclusive.
 */
static constexpr uint8_t RTC_ANY = 0xFF;
struct RTC_Alarm
{
    uint8_t minute  = RTC_ANY;  // 0..59
    uint8_t hour    = RTC_ANY;  // 0..23
    uint8_t day     = RTC_ANY;  // 1..31, day of month
    uint8_t weekday = RTC_ANY;  // 1..7,  day of week: 1 = Monday, 2 = Tuesday, etc
};
//------------------------------------------------------------------------------------------------
__inline const char* console_value(const DateTime &value)   { return value.to_string(); }
__inline const char* console_value(const Date &value)       { return value.to_string(); }
__inline const char* console_value(const Time &value)       { return value.to_string(); }
SET_CONSOLE_TYPE_NAME(DateTimeFormat);
SET_CONSOLE_TYPE_NAME(RTC_Alarm);
//------------------------------------------------------------------------------------------------
#endif
