/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-temperature.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_TEMPERATURE_H
#define AVR_TEMPERATURE_H
//------------------------------------------------------------------------------------------------
#include "core.h"
#include "avr-temperature-traits.h"
//------------------------------------------------------------------------------------------------
struct AVR_Temperature_calibration
{
    int16_t raw_low;
    int32_t millis_celsius_low;
    int16_t raw_high;
    int32_t millis_celsius_high;
};
//------------------------------------------------------------------------------------------------
class AVR_Temperature
{
public:
    static ResultCode get(Temperature &result);
    static ResultCode get(Temperature &result, const AVR_Temperature_calibration &calibration);
private:
    static ResultCode convert(Temperature &result, const ADC_sample <10> &sample);
    static ResultCode convert(Temperature &result, const ADC_sample <10> &sample,
                              const AVR_Temperature_calibration &calibration);
};
//------------------------------------------------------------------------------------------------
__inline FlashStringWrapper console_type_name(const AVR_Temperature &)
{
    return _flash("Temperature");
}
//------------------------------------------------------------------------------------------------
#endif
