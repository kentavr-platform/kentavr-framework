/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-adc-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_ADC_REGS_H
#define AVR_ADC_REGS_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "Core/macro.h"
#include "AVR/avr-mcu.h"
//------------------------------------------------------------------------------------------------
#ifndef NOREG
#define NOREG _SFR_IO8(NONE)
#endif
//------------------------------------------------------------------------------------------------
#define DEFINE_ADC_REGS(_CHANNEL_COUNT, _POWERSAVE, _POWERSAVE_BIT,           \
                        _CONTROL_A, _CONTROL_B, _MULTIPLEXER, _DATA,          \
                        _MUX_MASK, _REFERENCE_MASK, _MUX_HIGH_BIT,             \
                        _BIPOLAR_BIT, _POLARITY_BIT)                            \
struct ADC_traits                                                             \
{                                                                             \
    static constexpr uint8_t CHANNEL_COUNT = _CHANNEL_COUNT;                  \
                                                                              \
    static inline volatile uint8_t& POWERSAVE = _POWERSAVE;                   \
    static constexpr uint8_t POWERSAVE_BIT = _POWERSAVE_BIT;                  \
                                                                              \
    static inline volatile uint8_t& CONTROL_A = _CONTROL_A;                   \
    static inline volatile uint8_t& CONTROL_B = _CONTROL_B;                   \
    static inline volatile uint8_t& MULTIPLEXER = _MULTIPLEXER;               \
    static inline volatile uint16_t& DATA = _DATA;                            \
                                                                              \
    static constexpr uint8_t ENABLE = ADEN;                                   \
    static constexpr uint8_t INTERRUPT = ADIE;                                \
    static constexpr uint8_t START = ADSC;                                    \
    static constexpr uint8_t COMPLETE = ADIF;                                 \
    static constexpr uint8_t PRESCALER_0 = ADPS0;                             \
    static constexpr uint8_t PRESCALER_1 = ADPS1;                             \
    static constexpr uint8_t PRESCALER_2 = ADPS2;                             \
    static constexpr uint8_t ADJUST = ADLAR;                                  \
    static constexpr uint8_t MUX_MASK = _MUX_MASK;                            \
    static constexpr uint8_t REFERENCE_MASK = _REFERENCE_MASK;                \
    static constexpr uint8_t MUX_HIGH_BIT = _MUX_HIGH_BIT;                    \
    static constexpr uint8_t BIPOLAR_BIT = _BIPOLAR_BIT;                        \
    static constexpr uint8_t POLARITY_BIT = _POLARITY_BIT;                      \
};
//------------------------------------------------------------------------------------------------
#if defined(AVR_MEGA_8_FAMILY)
DEFINE_ADC_REGS(8, NOREG, NONE, ADCSRA, NOREG, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3), _bits(REFS0, REFS1), NONE, NONE, NONE)

#elif defined(AVR_TINY_X5_FAMILY)
DEFINE_ADC_REGS(4, PRR, PRADC, ADCSRA, ADCSRB, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3), _bits(REFS0, REFS1, REFS2), NONE, BIN, IPR)
#define ADC_HAS_POWER_CONTROL

#elif defined(AVR_MEGA_X8_FAMILY)
DEFINE_ADC_REGS(8, PRR, PRADC, ADCSRA, ADCSRB, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3), _bits(REFS0, REFS1), NONE, NONE, NONE)
#define ADC_HAS_POWER_CONTROL

#elif defined(AVR_MEGA_X4_FAMILY)
DEFINE_ADC_REGS(8, PRR0, PRADC, ADCSRA, ADCSRB, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3, MUX4), _bits(REFS0, REFS1), NONE, NONE, NONE)
#define ADC_HAS_POWER_CONTROL

#elif defined(AVR_MEGA_U4_FAMILY)
DEFINE_ADC_REGS(12, PRR0, PRADC, ADCSRA, ADCSRB, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3, MUX4), _bits(REFS0, REFS1), MUX5, NONE, NONE)
#define ADC_HAS_POWER_CONTROL

#elif defined(AVR_MEGA_X0_FAMILY)
DEFINE_ADC_REGS(16, PRR0, PRADC, ADCSRA, ADCSRB, ADMUX, ADCW,
                _bits(MUX0, MUX1, MUX2, MUX3, MUX4), _bits(REFS0, REFS1), MUX5, NONE, NONE)
#define ADC_HAS_POWER_CONTROL

#else
#error "ADC register mapping is not defined for this MCU subfamily"
#endif
//------------------------------------------------------------------------------------------------
#undef DEFINE_ADC_REGS
#undef ADC_NOREG
//------------------------------------------------------------------------------------------------
#endif
