/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-adc.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_ADC_H
#define AVR_ADC_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "core.h"
#include "config.h"
#include "avr-adc-channels.h"
#include "avr-adc-regs.h"
//------------------------------------------------------------------------------------------------
static constexpr uint32_t AVR_ADC_RECOMMENDED_CLOCK = 125000UL;
//------------------------------------------------------------------------------------------------
struct ADC_dispatcher;
//------------------------------------------------------------------------------------------------
class AVR_ADC
{
public:
    using Callback = void (*)(uint8_t id, ADC_sample <10> result);
    static ResultCode   init(uint32_t adc_clock = AVR_ADC_RECOMMENDED_CLOCK);
    static uint32_t     get_clock_frequency();
    static ResultCode   get(ADC_sample <10> &result, ADC_Channel channel, ADC_reference reference);
    static void         reset();
    static ResultCode   schedule(Callback callback,
                                 uint8_t id,
                                 ADC_Channel channel,
                                 ADC_reference reference);
private:
    using regs = ADC_traits;
    static struct Queue
    {
        struct Task
        {
            ADC_reference ref;
            ADC_Channel ch;
            uint8_t id;
            Callback callback;
        } tasks[regs :: CHANNEL_COUNT];
        uint8_t head = 0;
        uint8_t tail = 0;
        uint8_t size = 0;
        ResultCode add(Callback callback, uint8_t id, ADC_Channel channel, ADC_reference reference);
    } queue;
    static uint16_t         skip;
    static volatile bool    active;
    static uint8_t          skip_125us;
    static uint32_t         clock_frequency;
    static ADC_Channel      prev_channel;
    static ADC_reference    prev_reference;
#ifdef ENABLE_ADC_ASYNC_MODE
    static constexpr bool async_enabled = true;
#else
    static constexpr bool async_enabled = false;
#endif

    static uint8_t          is_differential(ADC_Channel channel);
    static uint16_t         calc_skip(ADC_Channel channel, ADC_reference reference);
    static uint16_t         start_conversion(ADC_Channel channel, ADC_reference reference);
    static void             read_result(ADC_sample <10> &result, ADC_Channel channel, ADC_reference);
    static void             interrupt();

    friend struct ADC_dispatcher;
};
//------------------------------------------------------------------------------------------------
#if defined(ENABLE_ADC_ASYNC_MODE) && defined(ISR_HANDLERS_MODULE)
    struct ADC_dispatcher
    {
        static void interrupt() { AVR_ADC :: interrupt(); }
    };

    ISR(ADC_vect)
    {
        ADC_dispatcher :: interrupt();
    }
#endif
//------------------------------------------------------------------------------------------------
__inline FlashStringWrapper console_type_name(const AVR_ADC &)
{
    return _flash("ADC");
}
//------------------------------------------------------------------------------------------------
#endif
