#include "DateTime.h"
#include "core/format.h"
//------------------------------------------------------------------------------------------------
// 1th January weekday for years 2000...2199
inline static const uint8_t _weekday_year_start[200] PROGMEM =
{
    6, 1, 2, 3, 4, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4, 5, 7, 1, 2,
    3, 5, 6, 7, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 7, 1, 2, 4, 5, 6,
    7, 2, 3, 4, 5, 7, 1, 2, 3, 5, 6, 7, 1, 3, 4, 5, 6, 1, 2, 3,
    4, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4, 5, 7, 1, 2, 3, 5, 6, 7,
    1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4,
    5, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4, 5, 7, 1, 2, 3, 5, 6, 7,
    1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4,
    5, 7, 1, 2, 3, 5, 6, 7, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 7, 1,
    2, 4, 5, 6, 7, 2, 3, 4, 5, 7, 1, 2, 3, 5, 6, 7, 1, 3, 4, 5,
    6, 1, 2, 3, 4, 6, 7, 1, 2, 4, 5, 6, 7, 2, 3, 4, 5, 7, 1, 2
};
//------------------------------------------------------------------------------------------------
inline static const uint8_t _weekday_month_offset[24] PROGMEM =
{
    // normal year
    0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5,
    // leap year
    0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6
};
//------------------------------------------------------------------------------------------------
inline static const uint8_t _weekday_reduce[44] PROGMEM =
{
    0,
    1, 2, 3, 4, 5, 6, 7,
    1, 2, 3, 4, 5, 6, 7,
    1, 2, 3, 4, 5, 6, 7,
    1, 2, 3, 4, 5, 6, 7,
    1, 2, 3, 4, 5, 6, 7,
    1, 2, 3, 4, 5, 6, 7,
    1
};
//------------------------------------------------------------------------------------------------
__inline bool Date :: _is_leap_year(uint16_t _year)
{
    return ((_year & 0x03) == 0) && (_year != 2100);
}
//------------------------------------------------------------------------------------------------
__inline uint8_t Date :: _days_in_month(uint16_t _year, uint8_t _month)
{
    switch(_month)
    {
    case 1:  return 31;
    case 2:  return _is_leap_year(_year) ? 29 : 28;
    case 3:  return 31;
    case 4:  return 30;
    case 5:  return 31;
    case 6:  return 30;
    case 7:  return 31;
    case 8:  return 31;
    case 9:  return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: return 0;
    }
}
//------------------------------------------------------------------------------------------------
uint8_t Date :: get_weekday() const
{
    if(year < 2000 || year > 2199 || !is_valid())
        return 0;

    uint8_t month_index = _is_leap_year(year) ? month - 1 + 12 : month - 1;
    uint8_t sum =
        pgm_read_byte(&_weekday_year_start[year - 2000]) +
        pgm_read_byte(&_weekday_month_offset[month_index]) +
        day - 1;

    return pgm_read_byte(&_weekday_reduce[sum]);
}
//------------------------------------------------------------------------------------------------
void Date :: _fill_year(char *buf, uint16_t year)
{
    if(year >= 2000 && year <= 2099)
    {
        *buf++ = '2'; *buf++ = '0';
        format_2d(buf, year - 2000);
    }
    else if(year >= 1900 && year <= 1999)
    {
        *buf++ = '1'; *buf++ = '9';
        format_2d(buf, year - 1900);
    }
    else if(year >= 2100 && year <= 2199)
    {
        *buf++ = '2'; *buf++ = '1';
        format_2d(buf, year - 2100);
    }
    else
    {
        strcpy_P(buf, PSTR("????"));
    }
}
//------------------------------------------------------------------------------------------------
const char* Date :: to_string(enum DateTimeFormat fmt) const
{
    char *buf = str;
    switch(fmt)
    {
    case FMT_TIME:
        strcpy_P(buf, PSTR("(invalid)"));
        return str;
    case FMT_DEFAULT:
    case FMT_ISO8601:
    case FMT_DATE_ISO:
        _fill_year(buf, year);  buf += 4;
        *buf++ = '-';  format_2d(buf, month);
        *buf++ = '-';  format_2d(buf, day);
        *buf = '\0';
        return str;
    case FMT_DATE_DMY:
        format_2d(buf, day);    *buf++ = '.';
        format_2d(buf, month);  *buf++ = '.';
        _fill_year(buf, year);  buf += 4;
        *buf = '\0';
        return str;
    case FMT_DATE_MDY:
        format_2d(buf, month);  *buf++ = '/';
        format_2d(buf, day);    *buf++ = '/';
        _fill_year(buf, year);  buf += 4;
        *buf = '\0';
        return str;
    }
    return str;
}
//------------------------------------------------------------------------------------------------
bool Date :: is_valid() const
{
    if(month < 1 || month > 12)
        return false;

    if(day < 1 || day > _days_in_month(year, month))
        return false;

    return true;
}
//------------------------------------------------------------------------------------------------
bool DateTime :: is_valid() const
{
    return Date :: is_valid() && (hour < 24) && (minute < 60) && (second < 60);
}
//------------------------------------------------------------------------------------------------
uint32_t DateTime :: to_unix_time() const
{
    if(!is_valid())  return 0;
    if(year < 1970 || year > 2106)  return 0;
    uint32_t days = 0;
    for(uint16_t y = 1970; y < year; y++)   { days += _is_leap_year(y) ? 366 : 365; }
    for(uint8_t m = 1; m < month; m++)      { days += _days_in_month(year, m); }
    days += day - 1;
    if(days > UINT32_MAX / SECONDS_PER_DAY)  return 0;
    uint32_t value = days * SECONDS_PER_DAY;
    uint32_t day_seconds = hour * 3600UL + minute * 60UL + second;
    if(UINT32_MAX - value < day_seconds)  return 0;
    return value + day_seconds;
}
//------------------------------------------------------------------------------------------------
const char* DateTime :: to_string(enum DateTimeFormat fmt) const
{
    char *buf = str;
    switch(fmt)
    {
    case FMT_DATE_ISO:
    case FMT_DEFAULT:
    case FMT_ISO8601:
        _fill_year(buf, year);  buf += 4;
        *buf++ = '-';  format_2d(buf, month);
        *buf++ = '-';  format_2d(buf, day);
        if(fmt == FMT_DATE_ISO)
        {
            *buf = '\0';
            return str;
        }
        *buf++ = (fmt == FMT_ISO8601) ? 'T' : ' ';
        [[fallthrough]];
    case FMT_TIME:
        format_2d(buf, hour);   *buf++ = ':';  format_2d(buf, minute);
        *buf++ = ':';  format_2d(buf, second);
        *buf = '\0';
        return str;
    case FMT_DATE_DMY:
        format_2d(buf, day);    *buf++ = '.';
        format_2d(buf, month);  *buf++ = '.';
        _fill_year(buf, year);  buf += 4;
        *buf = '\0';
        return str;
    case FMT_DATE_MDY:
        format_2d(buf, month);  *buf++ = '/';
        format_2d(buf, day);    *buf++ = '/';
        _fill_year(buf, year);  buf += 4;
        *buf = '\0';
        return str;
    }
    return str;
}
//------------------------------------------------------------------------------------------------
bool Time :: is_valid() const
{
    return (hour < 24) && (minute < 60) && (second < 60);
}
//------------------------------------------------------------------------------------------------
const char* Time :: to_string(enum DateTimeFormat fmt) const
{
    char *buf = str;
    switch(fmt)
    {
    case FMT_ISO8601:
    case FMT_DATE_ISO:
    case FMT_DATE_DMY:
    case FMT_DATE_MDY:
        strcpy_P(buf, PSTR("(invalid)"));
        return str;
    case FMT_DEFAULT:
    case FMT_TIME:
        format_2d(buf, hour);   *buf++ = ':';  format_2d(buf, minute);
        *buf++ = ':';  format_2d(buf, second);
        *buf = '\0';
        return str;
    }
    return str;
}
//------------------------------------------------------------------------------------------------
