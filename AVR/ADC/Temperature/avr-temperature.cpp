/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-temperature.cpp
//----------------------------------------------------------------------------------------------*/
#include "avr-temperature.h"
//------------------------------------------------------------------------------------------------
/**
 * @brief Read the built-in temperature sensor using typical MCU calibration.
 * @param[out] result Temperature in milli-degrees Celsius and its validity flag.
 * @pre Initialize AVR_ADC explicitly before calling this method.
 * @details Uses default points at 25 C and 85 C. ATmega32U4 currently uses
 * provisional points for measurement-based adjustment; other supported MCUs use
 * typical datasheet points. These are not individual chip calibration.
 * @retval ERR_NOT_FOUND The MCU has no supported built-in temperature sensor.
 * @return Otherwise propagates the calibrated get() result.
 */
ResultCode AVR_Temperature :: get(Temperature &result)
{
    return get(result, { AVR_Temperature_traits :: TYPICAL_RAW_25C, 25000,
                         AVR_Temperature_traits :: TYPICAL_RAW_85C, 85000 });
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read the built-in MCU temperature sensor using the shared ADC.
 * @param[out] result Temperature in milli-degrees Celsius and its validity flag.
 * @param calibration Two measured ADC codes and their known temperatures.
 * @pre Initialize AVR_ADC explicitly before calling this method.
 * @details Uses the MCU-specific channel and internal reference. ADC handles settling
 * conversions and temporarily suspends and resumes queued work in async mode.
 * On failure, clears result.valid and leaves the previous temperature unchanged.
 * @retval OK Temperature measured and converted.
 * @retval ERR_NOT_FOUND The MCU has no supported built-in temperature sensor.
 * @retval ERR_BAD_VALUE Calibration ADC codes are equal.
 * @return Propagates errors returned by AVR_ADC::get().
 */
ResultCode AVR_Temperature :: get(Temperature &result, const AVR_Temperature_calibration &calibration)
{
    result.valid = false;
    if constexpr(ADC_traits :: TEMPERATURE_CHANNEL == NONE)
        return ERR_NOT_FOUND;

    ADC_sample <10> sample;
    ResultCode error = AVR_ADC :: get(sample, ADC_Channel(ADC_traits :: TEMPERATURE_CHANNEL),
                                              AVR_Temperature_traits :: REFERENCE);
    if(error != OK)
        return error;

    return convert(result, sample, calibration);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Convert a temperature-sensor sample using typical MCU calibration.
 * @param[out] result Temperature in milli-degrees Celsius and its validity flag.
 * @param sample Settled sensor sample acquired with the MCU-specific reference.
 * @details Uses the same default points as get(result).
 * @retval ERR_NOT_FOUND The MCU has no supported built-in temperature sensor.
 * @return Otherwise propagates the calibrated convert() result.
 */
__inline ResultCode AVR_Temperature :: convert(Temperature &result, const ADC_sample <10> &sample)
{
    return convert(result, sample, { AVR_Temperature_traits :: TYPICAL_RAW_25C, 25000,
                                     AVR_Temperature_traits :: TYPICAL_RAW_85C, 85000 });
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Convert a temperature-sensor ADC sample using two-point calibration.
 * @param[out] result Temperature in milli-degrees Celsius and its validity flag.
 * @param sample Settled sensor sample, read with the MCU-specific internal reference.
 * @param calibration Measured ADC codes at two distinct known temperatures.
 * @pre ADC codes are ten-bit single-ended values; calibration temperatures are
 * within the MCU operating range.
 * @details Works directly in ADC counts using signed integer linear interpolation.
 * Values outside the calibration interval are extrapolated. Division truncates toward
 * zero. Calibration and measurement must use the same reference and ADC configuration.
 * @retval OK Converted value stored and marked valid.
 * @retval ERR_BAD_VALUE Calibration ADC codes are equal; result.valid is cleared.
 */
__inline ResultCode AVR_Temperature :: convert(Temperature &result, const ADC_sample <10> &sample,
                                               const AVR_Temperature_calibration &calibration)
{
    result.valid = false;
    const int16_t raw_span = calibration.raw_high - calibration.raw_low;
    if(raw_span == 0)
        return ERR_BAD_VALUE;

    result.millis_celsius = calibration.millis_celsius_low
                         + int32_t(sample.raw - calibration.raw_low)
                         * (calibration.millis_celsius_high - calibration.millis_celsius_low)
                         / raw_span;
    result.valid = true;
    return OK;
}
//------------------------------------------------------------------------------------------------
