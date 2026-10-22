/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-powersave-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_POWERSAVE_REGS_H
#define AVR_POWERSAVE_REGS_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include "Core/macro.h"
//------------------------------------------------------------------------------------------------
#ifndef NOREG
#define NOREG _SFR_IO8(NONE)
#endif
//------------------------------------------------------------------------------------------------
#define DEFINE_POWER_REGS(_CPU_ONLY, _SLEEP_CONTROL, _POWER0, _POWER1, _COMPARATOR_CONTROL,            \
                          _SLEEP_ENABLE, _MODE_MASK,                                                   \
                          _IDLE, _ADC_NOISE_REDUCTION, _POWER_DOWN,                                    \
                          _POWER_SAVE, _STANDBY, _EXTENDED_STANDBY,                                    \
                          _UART_MASK0, _UART_MASK1, _TIMERS_MASK0, _TIMERS_MASK1,                      \
                          _SPI_POWER_BIT, _I2C_POWER_BIT, _ADC_POWER_BIT,                              \
                          _USB_POWER_BIT, _USI_POWER_BIT,                                              \
                          _COMPARATOR_DISABLE, _COMPARATOR_FLAG)                                       \
struct AVR_PowerSave_traits                                                                            \
{                                                                                                      \
    static constexpr bool exists = _SLEEP_ENABLE != NONE;                                              \
    static constexpr bool has_cpu_only = _CPU_ONLY;                                                    \
    static constexpr bool has_adc_noise_reduction = _ADC_NOISE_REDUCTION != NONE;                      \
    static constexpr bool has_power_save = _POWER_SAVE != NONE;                                        \
    static constexpr bool has_standby = _STANDBY != NONE;                                              \
    static constexpr bool has_extended_standby = _EXTENDED_STANDBY != NONE;                            \
    static constexpr bool has_spi_power = _SPI_POWER_BIT != NONE;                                      \
    static constexpr bool has_i2c_power = _I2C_POWER_BIT != NONE;                                      \
    static constexpr bool has_adc_power = _ADC_POWER_BIT != NONE;                                      \
    static constexpr bool has_usb_power = _USB_POWER_BIT != NONE;                                      \
    static constexpr bool has_usi_power = _USI_POWER_BIT != NONE;                                      \
    static constexpr bool has_comparator_power = _COMPARATOR_DISABLE != NONE;                          \
                                                                                                       \
    static inline volatile uint8_t& SLEEP_CONTROL = _SLEEP_CONTROL;                                    \
    static inline volatile uint8_t& POWER0 = _POWER0;                                                  \
    static inline volatile uint8_t& POWER1 = _POWER1;                                                  \
    static inline volatile uint8_t& COMPARATOR_CONTROL = _COMPARATOR_CONTROL;                          \
                                                                                                       \
    static constexpr uint8_t SLEEP_ENABLE = exists ? _SLEEP_ENABLE : 0;                                \
    static constexpr uint8_t MODE_MASK = _MODE_MASK;                                                   \
    static constexpr uint8_t IDLE = _IDLE;                                                             \
    static constexpr uint8_t POWER_DOWN = _POWER_DOWN;                                                 \
    static constexpr uint8_t ADC_NOISE_REDUCTION = has_adc_noise_reduction ? _ADC_NOISE_REDUCTION : 0; \
    static constexpr uint8_t POWER_SAVE = has_power_save ? _POWER_SAVE : 0;                            \
    static constexpr uint8_t STANDBY = has_standby ? _STANDBY : 0;                                     \
    static constexpr uint8_t EXTENDED_STANDBY = has_extended_standby ? _EXTENDED_STANDBY : 0;          \
    static constexpr uint8_t UART_MASK0 = _UART_MASK0;                                                 \
    static constexpr uint8_t UART_MASK1 = _UART_MASK1;                                                 \
    static constexpr uint8_t TIMERS_MASK0 = _TIMERS_MASK0;                                             \
    static constexpr uint8_t TIMERS_MASK1 = _TIMERS_MASK1;                                             \
    static constexpr uint8_t SPI_POWER_BIT = has_spi_power ? _SPI_POWER_BIT : 0;                       \
    static constexpr uint8_t I2C_POWER_BIT = has_i2c_power ? _I2C_POWER_BIT : 0;                       \
    static constexpr uint8_t ADC_POWER_BIT = has_adc_power ? _ADC_POWER_BIT : 0;                       \
    static constexpr uint8_t USB_POWER_BIT = has_usb_power ? _USB_POWER_BIT : 0;                       \
    static constexpr uint8_t USI_POWER_BIT = has_usi_power ? _USI_POWER_BIT : 0;                       \
    static constexpr uint8_t COMPARATOR_DISABLE = has_comparator_power ? _COMPARATOR_DISABLE : 0;      \
    static constexpr uint8_t COMPARATOR_FLAG = has_comparator_power ? _COMPARATOR_FLAG : 0;            \
};
//------------------------------------------------------------------------------------------------
#if defined(__AVR_ATmega8__)
DEFINE_POWER_REGS(false, MCUCR, NOREG, NOREG, ACSR,
                  SE, _bits(SM0, SM1, SM2),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, NONE,
                  0, 0, 0, 0,
                  NONE, NONE, NONE, NONE, NONE,
                  ACD, ACI)

#elif defined(__AVR_ATtiny85__)
DEFINE_POWER_REGS(true, MCUCR, PRR, NOREG, ACSR,
                  SE, _bits(SM0, SM1),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  NONE, NONE, NONE,
                  0, 0, _bits(PRTIM0, PRTIM1), 0,
                  NONE, NONE, PRADC, NONE, PRUSI,
                  ACD, ACI)

#elif defined(__AVR_ATmega88P__) || defined(__AVR_ATmega328P__)
DEFINE_POWER_REGS(true, SMCR, PRR, NOREG, ACSR,
                  SE, _bits(SM0, SM1, SM2),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY,
                  _bit(PRUSART0), 0, _bits(PRTIM0, PRTIM1, PRTIM2), 0,
                  PRSPI, PRTWI, PRADC, NONE, NONE,
                  ACD, ACI)

#elif defined(__AVR_ATmega32U4__)
// PRUSART0 and PRTIM2 are reserved despite avr-libc definitions.
DEFINE_POWER_REGS(true, SMCR, PRR0, PRR1, ACSR,
                  SE, _bits(SM0, SM1, SM2),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY,
                  0, _bit(PRUSART1), _bits(PRTIM0, PRTIM1), _bits(PRTIM3, PRTIM4),
                  PRSPI, PRTWI, PRADC, PRUSB, NONE,
                  ACD, ACI)

#elif defined(__AVR_ATmega1284P__)
DEFINE_POWER_REGS(true, SMCR, PRR0, PRR1, ACSR,
                  SE, _bits(SM0, SM1, SM2),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY,
                  _bits(PRUSART0, PRUSART1), 0, _bits(PRTIM0, PRTIM1, PRTIM2), _bit(PRTIM3),
                  PRSPI, PRTWI, PRADC, NONE, NONE,
                  ACD, ACI)

#elif defined(__AVR_ATmega2560__)
DEFINE_POWER_REGS(true, SMCR, PRR0, PRR1, ACSR,
                  SE, _bits(SM0, SM1, SM2),
                  SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN,
                  SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY,
                  _bit(PRUSART0), _bits(PRUSART1, PRUSART2, PRUSART3), _bits(PRTIM0, PRTIM1, PRTIM2), _bits(PRTIM3, PRTIM4, PRTIM5),
                  PRSPI, PRTWI, PRADC, NONE, NONE,
                  ACD, ACI)

#elif defined(__AVR_AVR128DB48__)
DEFINE_POWER_REGS(false, SLPCTRL_CTRLA, NOREG, NOREG, NOREG,
                  SLPCTRL_SEN_bp, SLPCTRL_SMODE_gm,
                  SLPCTRL_SMODE_IDLE_gc, NONE, SLPCTRL_SMODE_PDOWN_gc,
                  NONE, SLPCTRL_SMODE_STDBY_gc, NONE,
                  0, 0, 0, 0,
                  NONE, NONE, NONE, NONE, NONE,
                  NONE, NONE)

#else
DEFINE_POWER_REGS(false, NOREG, NOREG, NOREG, NOREG,
                  NONE, 0,
                  0, NONE, 0,
                  NONE, NONE, NONE,
                  0, 0, 0, 0,
                  NONE, NONE, NONE, NONE, NONE,
                  NONE, NONE)
#endif
//------------------------------------------------------------------------------------------------
#undef DEFINE_POWER_REGS
//------------------------------------------------------------------------------------------------
#endif
