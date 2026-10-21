/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-temperature-traits.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_TEMPERATURE_TRAITS_H
#define AVR_TEMPERATURE_TRAITS_H
//------------------------------------------------------------------------------------------------
#include "AVR/ADC/avr-adc-channels.h"
//------------------------------------------------------------------------------------------------
struct AVR_Temperature_traits
{
#if defined(__AVR_ATtiny85__)
    static constexpr ADC_reference REFERENCE = ADC_REFERENCE_1V1;
    static constexpr int16_t TYPICAL_RAW_25C = 300;
    static constexpr int16_t TYPICAL_RAW_85C = 370;

#elif defined(__AVR_ATmega88P__) || defined(__AVR_ATmega328P__)
    static constexpr ADC_reference REFERENCE = ADC_REFERENCE_1V1;
    static constexpr int16_t TYPICAL_RAW_25C = (314L * 1024 + 550) / 1100;
    static constexpr int16_t TYPICAL_RAW_85C = (380L * 1024 + 550) / 1100;

#elif defined(__AVR_ATmega32U4__)
    static constexpr ADC_reference REFERENCE = ADC_REFERENCE_2V56;
    static constexpr int16_t TYPICAL_RAW_25C = 298;
    static constexpr int16_t TYPICAL_RAW_85C = 358;

#else
    static constexpr ADC_reference REFERENCE = ADC_REFERENCE_AREF;
    static constexpr int16_t TYPICAL_RAW_25C = 0;
    static constexpr int16_t TYPICAL_RAW_85C = 0;
#endif
};
//------------------------------------------------------------------------------------------------
#endif
