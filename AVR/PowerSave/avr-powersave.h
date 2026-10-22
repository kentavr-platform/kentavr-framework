/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-powersave.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_POWERSAVE_H
#define AVR_POWERSAVE_H
//------------------------------------------------------------------------------------------------
#include <avr/sleep.h>
#include "Core/macro.h"
#include "Core/errors.h"
#include "AVR/avr-macro.h"
#include "avr-powersave-regs.h"
//------------------------------------------------------------------------------------------------
enum PowerSave_mode : uint8_t
{
    /** Pause the program while enabled peripherals continue working: UART can transfer
    // data, timers can count, and ADC can measure. Any enabled interrupt wakes the CPU.
    // Useful when the program is waiting for a peripheral to finish its work. */
    POWERSAVE_IDLE = 0,

    /** Pause the program and stop most digital peripheral clocks to reduce interference
    // with the ADC measurement. The ADC continues converting; its completion interrupt
    // can wake the CPU. This mode improves measurement conditions rather than providing
    // the lowest possible power consumption. */
    POWERSAVE_ADC_NOISE_REDUCTION = 1,

    /** Pause the program while both the main crystal/resonator oscillator and the
    // asynchronous timer keep running. The timer can wake the CPU periodically,
    // and execution resumes without waiting for the main oscillator to start. */
    POWERSAVE_EXTENDED_SAVE = 2,

    /** Pause the program and stop the main oscillator, but let the asynchronous timer
    // count using its own clock. Its interrupt can wake the CPU at a scheduled time.
    // Configure the timer for asynchronous operation before entering sleep. */
    POWERSAVE_SAVE = 3,

    /** Pause the program and stop peripheral clocks, but keep the main crystal/resonator
    // oscillator running. Wake-up is faster because the oscillator does not need to start
    // it again; keeping it running consumes additional power. */
    POWERSAVE_STANDBY = 4,

    /** Stop the CPU and main oscillator. Timers driven by this oscillator stop counting
    // and cannot wake the CPU. An external pin interrupt can wake it; watchdog interrupt
    // can also be used to wake up MCU (if available).
    // RAM is preserved. After wake-up, the interrupt handler runs, then sleep() returns. */
    POWERSAVE_SLEEP = 5,
};
//------------------------------------------------------------------------------------------------
class AVR_PowerSave
{
public:
    static ResultCode sleep(PowerSave_mode mode);
    static ResultCode cpu_only();

    static ResultCode disable_uart_power();
    static ResultCode enable_uart_power();

    static ResultCode disable_spi_power();
    static ResultCode enable_spi_power();

    static ResultCode disable_i2c_power();
    static ResultCode enable_i2c_power();

    static ResultCode disable_timers_power();
    static ResultCode enable_timers_power();

    static ResultCode disable_adc_power();
    static ResultCode enable_adc_power();

    static ResultCode disable_usb_power();
    static ResultCode enable_usb_power();

    static ResultCode disable_usi_power();
    static ResultCode enable_usi_power();

    static ResultCode disable_comparator_power();
    static ResultCode enable_comparator_power();

private:
    using regs = AVR_PowerSave_traits;
};
//------------------------------------------------------------------------------------------------
extern AVR_PowerSave power;
//------------------------------------------------------------------------------------------------
#include "avr-powersave.tpp"
//------------------------------------------------------------------------------------------------
#endif
