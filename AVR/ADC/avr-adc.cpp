/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-adc.cpp
//----------------------------------------------------------------------------------------------*/
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "avr-adc.h"
#include "config.h"
//------------------------------------------------------------------------------------------------
// static initializers
volatile bool AVR_ADC :: active = false;
uint8_t AVR_ADC :: skip_125us = 0;
uint32_t AVR_ADC :: clock_frequency = 0;
ADC_Channel AVR_ADC :: prev_channel {};
ADC_reference AVR_ADC :: prev_reference {};
uint16_t AVR_ADC :: skip = 0;
AVR_ADC :: Queue AVR_ADC :: queue {};
//------------------------------------------------------------------------------------------------
/**
 * @brief Select the nearest available ADC clock and enable the ADC.
 * @param adc_clock Requested ADC clock in Hz, not the sampling rate.
 * @retval OK ADC configured and enabled.
 * @retval ERR_BAD_PARAMETER Requested clock exceeds 5 MHz; ADC state is unchanged.
 * @details Selects a divider from 2 through 128; equal differences select the
 * larger divider. Only clocks at or below 5 MHz are considered.
 * Computes the number of conversions covering 125 us and
 * remembers the input/reference currently selected in the multiplexer.
 * In async mode, clears the queue and enables the ADC interrupt.
 * ATtinyX5 uses bipolar differential results with normal input polarity.
 * @note The requested clock is not checked against the MCU's accuracy limits.
 * The selected clock may differ from adc_clock. Call before requesting conversions.
 * Reinitialization preserves the selected input/reference as the previous settings;
 * the next request for the same settings does not add settling conversions.
 */
ResultCode AVR_ADC :: init(uint32_t adc_clock)
{
    static const uint8_t dividers[] PROGMEM =
    {
        2,   4,   8,  16,  32,  64, 128,    // <-- divider
        1,   2,   3,   4,   5,   6,   7     // <-- bits
    };
    constexpr uint8_t DIV_COUNT = sizeof(dividers) / 2;
    constexpr uint32_t MAX_ADC_CLOCK = 5000000UL;

    if(adc_clock > MAX_ADC_CLOCK)
        return ERR_BAD_PARAMETER;

    // select the nearest ADC clock
    uint8_t selected_prescaler = pgm_read_byte(&dividers[DIV_COUNT]);
    uint8_t selected_divider = 2;
    uint32_t clock_difference = UINT32_MAX;
    for(uint8_t i = 0; i < DIV_COUNT; i++)
    {
        const uint8_t divider = pgm_read_byte(&dividers[i]);
        const uint32_t candidate_clock = F_CPU / divider;
        if(candidate_clock > MAX_ADC_CLOCK)
            continue;
        const uint32_t candidate_difference = candidate_clock > adc_clock
                                              ? candidate_clock - adc_clock
                                              : adc_clock - candidate_clock;
        if(candidate_difference <= clock_difference)
        {
            selected_prescaler = pgm_read_byte(&dividers[DIV_COUNT + i]);
            clock_difference = candidate_difference;
            selected_divider = divider;
        }
    }
    power.enable_adc_power();
    regs :: CONTROL_A = selected_prescaler;

#if defined(AVR_TINY_X5_FAMILY)
    set_bit(regs :: CONTROL_B, regs :: BIPOLAR_BIT);
    clr_bit(regs :: CONTROL_B, regs :: POLARITY_BIT);
#endif

    // recover previous channel and reference from registers
    prev_channel = ADC_Channel(regs :: MULTIPLEXER & regs :: MUX_MASK);
#if defined(AVR_MEGA_U4_FAMILY) || defined(AVR_MEGA_X0_FAMILY)
    if(test_bit(regs :: CONTROL_B, regs :: MUX_HIGH_BIT))
        prev_channel = ADC_Channel(uint8_t(prev_channel) | _bit(5));
#endif
    prev_reference = ADC_reference(regs :: MULTIPLEXER & regs :: REFERENCE_MASK);

    // Number of 13-clock conversions covering 125 us.
    constexpr uint32_t conversion_rate = 13UL * 1000000UL / 125UL;
    clock_frequency = (F_CPU + selected_divider - 1) / selected_divider;
    skip_125us = (clock_frequency + conversion_rate - 1) / conversion_rate;

    if constexpr(async_enabled)
    {
        skip = 0;
        reset();
        set_bit(regs :: CONTROL_A, regs :: INTERRUPT);
    }
    set_bit(regs :: CONTROL_A, regs :: ENABLE);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Return the ADC clock selected by the last successful init().
 * @return Clock frequency in Hz; zero if not initialized.
 */
uint32_t AVR_ADC :: get_clock_frequency()
{
    return clock_frequency;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read the differential-input flag from the MCU-specific flash table.
 * @param channel Valid ADC_Channel code for the target MCU.
 * @return Nonzero for a differential input, zero otherwise.
 */
__inline uint8_t AVR_ADC :: is_differential(ADC_Channel channel)
{
    return pgm_read_byte(&diff_table[uint8_t(channel)]);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Calculate how many upcoming conversion results must be discarded.
 * @param channel Requested input code.
 * @param reference Requested reference selection.
 * @return Settling count for changed settings. For unchanged settings, returns
 * the remaining async skip count, or zero in sync mode.
 * @details Changed differential settings use skip_125us. For VBG, all targets use
 * ten times that count; this covers the ATtinyX5 1 ms settling requirement and
 * retains the empirical delay used on ATmega1284P. Temperature inputs use eight
 * times skip_125us to cover the ATtinyX5 internal reference's 1 ms settling time
 * and the first-conversion discard required by ATmegaU4. Other single-ended
 * inputs discard one conversion when the reference changes and none otherwise.
 * This function does not update the remembered settings.
 * @note skip_125us is already rounded up; multiplying it does not calculate an
 * exact settling interval. The returned count is limited to uint16_t.
 */
__inline uint16_t AVR_ADC :: calc_skip(ADC_Channel channel, ADC_reference reference)
{
    if(channel == prev_channel && reference == prev_reference)
    {
        if constexpr(async_enabled)
            return skip;
        else
            return 0;
    }

    if(is_differential(channel))
        return skip_125us;

    if(channel == regs :: TEMPERATURE_CHANNEL)
        return skip_125us * 8; // 1 ms is the longest settling time among supported temperature inputs

    if(channel == ADC_VBG)
        return skip_125us * 10; // undocumented slow charge from VBG (experimentally got value)

    if(reference != prev_reference)
        return 1;
    else
        return 0;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Select the input and reference, remember them and start a conversion.
 * @param channel Requested input code.
 * @param reference Requested reference selection.
 * @return Number of settling conversions to discard.
 * @details In async mode, also stores the returned count in skip for the ISR.
 * ATmegaU4 and ATmegaX0 write MUX5 separately in CONTROL_B.
 */
__inline uint16_t AVR_ADC :: start_conversion(ADC_Channel channel, ADC_reference reference)
{
    const uint16_t conversion_skip = calc_skip(channel, reference);
    if constexpr(async_enabled)
        skip = conversion_skip;
    prev_channel = channel;
    prev_reference = reference;

#if defined(AVR_MEGA_U4_FAMILY) || defined(AVR_MEGA_X0_FAMILY)
    // ADC_Channel stores MUX5 in bit 5; its ADCSRB position depends on the MCU.
    if(test_bit(uint8_t(channel), 5))
        set_bit(regs :: CONTROL_B, regs :: MUX_HIGH_BIT);
    else
        clr_bit(regs :: CONTROL_B, regs :: MUX_HIGH_BIT);
#endif

    regs :: MULTIPLEXER = (uint8_t(channel) & regs :: MUX_MASK) | uint8_t(reference);
    set_bit(regs :: CONTROL_A, regs :: START);
    return conversion_skip;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read a right-adjusted ADC sample and its reference in mV.
 * @param[out] result Raw ADC value and nominal internal reference voltage in mV.
 * @param channel Input code used for this conversion.
 * @param reference Reference selection used for this conversion.
 * @pre The conversion has completed.
 * @details Differential results are sign-extended from ten bits.
 * scale_to_mV() does not account for differential scaling or gain.
 * External and supply references leave ref_mV at zero; pass their actual mV value
 * to scale_to_mV(ref). Both ATtinyX5 2.56 V modes return 2560 mV.
 * Internal references set nominal values of 1100 or 2560 mV, without calibration.
 */
__inline void AVR_ADC :: read_result(ADC_sample <10> &result, ADC_Channel channel, ADC_reference reference)
{
    const uint16_t value = regs :: DATA;
    result.raw = is_differential(channel) && value >= 512 ?
                                               int16_t(value) - 1024 :
                                               int16_t(value);
    switch(reference)
    {

#if !defined(AVR_MEGA_8_FAMILY) && !defined(AVR_MEGA_U4_FAMILY)
    case ADC_REFERENCE_1V1:
        result.ref_mV = 1100;
        break;
#endif

#if !defined(AVR_MEGA_X8_FAMILY)
    case ADC_REFERENCE_2V56:
#if defined(AVR_TINY_X5_FAMILY)
    case ADC_REFERENCE_2V56_BYPASS:
#endif
        result.ref_mV = 2560;
        break;
#endif

    default:
        result.ref_mV = 0;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Append a task to the ring and start its conversion if the ADC is idle.
 * @param callback Non-null completion callback.
 * @param id User identifier passed unchanged to the callback.
 * @param channel Input code for the task.
 * @param reference Reference selection for the task.
 * @retval OK Task accepted.
 * @retval ERR_BAD_PARAMETER Callback is null in async mode.
 * @retval ERR_NO_SPACE_LEFT The ring is full in async mode.
 * @retval ERR_BAD_MODE Async mode is disabled.
 * @details The task in progress remains at head and counts towards capacity.
 * Capacity checking, task insertion and starting an idle ADC form one atomic operation.
 */
ResultCode AVR_ADC :: Queue :: add(Callback callback, uint8_t id, ADC_Channel channel,
                                                                  ADC_reference reference)
{
    if constexpr(async_enabled)
    {
        if(!callback)
            return ERR_BAD_PARAMETER;
        {
            ATOMIC_BLOCK
            if(size == regs :: CHANNEL_COUNT)
                return ERR_NO_SPACE_LEFT;

            tasks[tail++] = { reference, channel, id, callback };
            if(tail == regs :: CHANNEL_COUNT)
                tail = 0;   // ring the buffer
            size++;
            if(!active)
            {
                active = true;
                start_conversion(tasks[head].ch, tasks[head].ref);
            }
        }
        return OK;
    }
    return ERR_BAD_MODE;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Cancel asynchronous work and empty the queue without calling callbacks.
 * @details Stops an in-progress conversion, clears the pending completion flag
 * and releases the ADC. Hardware cancellation and queue clearing are atomic.
 * Does nothing when async mode is disabled.
 * The selected input, reference and remaining settling count are preserved.
 * @pre Must not interrupt a blocking get() call.
 */
void AVR_ADC :: reset()
{
    if constexpr(async_enabled)
    {
        {
            ATOMIC_BLOCK
            if(test_bit(regs :: CONTROL_A, regs :: START))
            {
                clr_bit(regs :: CONTROL_A, regs :: ENABLE);
                set_bit(regs :: CONTROL_A, regs :: ENABLE);
            }
            set_bit(regs :: CONTROL_A, regs :: COMPLETE);   // W1C
            queue.head = 0;
            queue.tail = 0;
            queue.size = 0;
            active = false;
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Perform a blocking read, discarding settling conversions as needed.
 * @param[out] result ADC result, interpreted by read_result().
 * @param channel Requested input code for the target MCU.
 * @param reference Requested reference selection for the target MCU.
 * @return OK after reading the result.
 * @pre init() has configured the ADC. Calls to get() must not overlap.
 * init() and reset() must not be called from another interrupt during this read.
 * The channel/reference combination must be supported by the target MCU.
 * On ATmega1284P, differential inputs require 2.56V when using an internal reference.
 * @details In async mode, suspends the ADC interrupt and aborts an in-progress
 * conversion without removing its queued task. After the blocking read,
 * restores the interrupt-enable state and restarts the queue head, if present.
 * Settling conversions use a local counter; the async remainder is cleared before
 * resuming queued work. The ADC reservation and queue resumption are atomic,
 * while the blocking conversion loop leaves the global interrupt state unchanged.
 * The blocking result does not invoke a callback. There is no timeout.
 */
ResultCode AVR_ADC :: get(ADC_sample <10> &result, ADC_Channel channel, ADC_reference reference)
{
    bool interrupt_enabled;
    if constexpr(async_enabled)
    {
        {
            ATOMIC_BLOCK
            // suspend asynchronous processing
            interrupt_enabled = test_bit(regs :: CONTROL_A, regs :: INTERRUPT);
            clr_bit(regs :: CONTROL_A, regs :: INTERRUPT);
            if(test_bit(regs :: CONTROL_A, regs :: START))
            {
                // stop current conversion
                clr_bit(regs :: CONTROL_A, regs :: ENABLE);
                set_bit(regs :: CONTROL_A, regs :: ENABLE);
            }
            // Reserve the ADC: schedule() may enqueue tasks, but must not start them.
            active = true;
        }
    }

    // get() has a maximum conversion priority
    uint16_t _get_skip = start_conversion(channel, reference);
    while(true)
    {
        while(test_bit(regs :: CONTROL_A, regs :: START)) {}    // blocking wait
        // Discard settling conversions in both modes.
        if(!_get_skip)
            break;
        _get_skip--;
        set_bit(regs :: CONTROL_A, regs :: START);
    }
    read_result(result, channel, reference);

    // recover asynchronous processing and restart the suspended task
    if constexpr(async_enabled)
    {
        {
            ATOMIC_BLOCK
            set_bit(regs :: CONTROL_A, regs :: COMPLETE);   // W1C pending interrupt flag
            skip = 0;   // get() has completed all settling conversions.
            active = (queue.size != 0);
            if(interrupt_enabled)
                set_bit(regs :: CONTROL_A, regs :: INTERRUPT);
            if(active)
                start_conversion(queue.tasks[queue.head].ch, queue.tasks[queue.head].ref);
        }
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enqueue a conversion without waiting for its result.
 * @param callback Non-null callback receiving id and result.
 * @param id User identifier passed unchanged to the callback.
 * @param channel Input code for the target MCU.
 * @param reference Reference selection for the target MCU.
 * @retval OK Task accepted.
 * @retval ERR_BAD_PARAMETER Callback is null in async mode.
 * @retval ERR_NO_SPACE_LEFT Queue capacity, including the active task, is exhausted.
 * @retval ERR_BAD_MODE Async mode is disabled.
 * @pre init() has configured the ADC.
 * @details Define ENABLE_ADC_ASYNC_MODE in config.h to enable async mode.
 * Callbacks execute in ADC interrupt context; the next
 * queued conversion is started before the completed task's callback runs.
 * Queue capacity is regs :: CHANNEL_COUNT, including the active task. The id
 * is returned unchanged and need not be unique. Task insertion is atomic.
 * Global interrupts must be enabled for queued conversions to complete callbacks.
 * @pre The channel/reference combination must be supported by the target MCU.
 */
ResultCode AVR_ADC :: schedule(Callback callback, uint8_t id, ADC_Channel channel,
                                                              ADC_reference reference)
{
    if constexpr(async_enabled)
    {
        return queue.add(callback, id, channel, reference);
    }
    return ERR_BAD_MODE;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Process ADC completion in interrupt context.
 * @details Discards settling results and restarts conversion until skip reaches
 * zero. Then removes the completed task, starts the next one if present and
 * invokes the completed task's callback with its id and result.
 */
void AVR_ADC :: interrupt()
{
    if constexpr(async_enabled)
    {
        if(skip)
        {
            skip--;
            // skip previous unreliable measurement and start again
            set_bit(regs :: CONTROL_A, regs :: START);
            return;
        }

        const Queue :: Task task = queue.tasks[queue.head];
        ADC_sample <10> result;
        read_result(result, task.ch, task.ref);

        if(queue.head++ == regs :: CHANNEL_COUNT - 1)
        {
            queue.head = 0; // ring the buffer
        }

        active = (--queue.size != 0);

        if(active)
            start_conversion(queue.tasks[queue.head].ch, queue.tasks[queue.head].ref);

        task.callback(task.id, result);
    }
}
//------------------------------------------------------------------------------------------------
