/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-adc-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_ADC_REGS_H
#define AVR_ADC_REGS_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
struct ADC_traits
{
    static constexpr uint8_t CHANNEL_COUNT = 8;

    static inline volatile uint8_t& POWERSAVE = PRR0;
    static constexpr uint8_t POWERSAVE_BIT = PRADC;

    static inline volatile uint8_t& CONTROL_A = ADCSRA;
    static inline volatile uint8_t& CONTROL_B = ADCSRB;
    static inline volatile uint8_t& MULTIPLEXER = ADMUX;
    static inline volatile uint16_t& DATA = ADCW;

    static constexpr uint8_t ENABLE = ADEN;
    static constexpr uint8_t INTERRUPT = ADIE;
    static constexpr uint8_t START = ADSC;
    static constexpr uint8_t COMPLETE = ADIF;
    static constexpr uint8_t PRESCALER_0 = ADPS0;
    static constexpr uint8_t PRESCALER_1 = ADPS1;
    static constexpr uint8_t PRESCALER_2 = ADPS2;
    static constexpr uint8_t REFERENCE_0 = REFS0;
    static constexpr uint8_t REFERENCE_1 = REFS1;
    static constexpr uint8_t ADJUST = ADLAR;
    static constexpr uint8_t MUX_MASK = 0x1F;
};
//------------------------------------------------------------------------------------------------
#endif
