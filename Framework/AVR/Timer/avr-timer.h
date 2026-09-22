/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-timer.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_TIMER_H
#define AVR_TIMER_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../Core/errors.h"
#include "../avr-macro.h"
#include "avr-timer-regs.h"
//------------------------------------------------------------------------------------------------
enum Timer_mode
{
    TIMER_MODE_NORMAL,
    TIMER_MODE_CTC_OCRA,
    TIMER_MODE_CTC_ICR,
    TIMER_MODE_FAST_PWM_8,               // F = FT / DIV / 256, duty: Compare A/B/C
    TIMER_MODE_FAST_PWM_9,               // F = FT / DIV / 512, duty: Compare A/B/C
    TIMER_MODE_FAST_PWM_10,              // F = FT / DIV / 1024,duty: Compare A/B/C
    TIMER_MODE_FAST_PWM_COMPARE_A,       // F = FT / DIV / (Compare A + 1), duty: Compare B/C
    TIMER_MODE_FAST_PWM_CAPTURE,         // F = FT / DIV / (Capture + 1), duty: Compare A/B/C
    TIMER_MODE_PHASE_PWM_8,              // F = FT / DIV / 510, duty: Compare A/B/C
    TIMER_MODE_PHASE_PWM_9,              // F = FT / DIV / 1022, duty: Compare A/B/C
    TIMER_MODE_PHASE_PWM_10,             // F = FT / DIV / 2046, duty: Compare A/B/C
    TIMER_MODE_PHASE_PWM_COMPARE_A,      // F = FT / DIV / (2 x Compare A), duty: Compare B/C
    TIMER_MODE_PHASE_PWM_CAPTURE,        // F = FT / DIV / (2 x Capture A), duty: Compare A/B/C
    TIMER_MODE_PHASE_FREQ_PWM_COMPARE_A, // same as PHASE_PWM_COMPARE_A with correct next period reload
    TIMER_MODE_PHASE_FREQ_PWM_CAPTURE    // same as PHASE_PWM_CAPTURE with correct next period reload
};
//------------------------------------------------------------------------------------------------
enum Timer_clock
{
    TIMER_CLOCK_DIV_1,
    TIMER_CLOCK_DIV_8,
    TIMER_CLOCK_DIV_32,
    TIMER_CLOCK_DIV_64,
    TIMER_CLOCK_DIV_128,
    TIMER_CLOCK_DIV_256,
    TIMER_CLOCK_DIV_1024,
    TIMER_CLOCK_EXTERNAL_FALLING,
    TIMER_CLOCK_EXTERNAL_RISING
};
//------------------------------------------------------------------------------------------------
enum Timer_compare_output
{
    TIMER_OUTPUT_DISCONNECTED,
    TIMER_OUTPUT_SET_ON_MATCH,
    TIMER_OUTPUT_CLEAR_ON_MATCH,
    TIMER_OUTPUT_TOGGLE_ON_MATCH,
    TIMER_OUTPUT_PWM,
    TIMER_OUTPUT_PWM_INVERTED
};
//------------------------------------------------------------------------------------------------
enum Timer_capture_edge
{
    CAPTURE_FALLING_UNFILTERED,
    CAPTURE_FALLING_FILTERED,
    CAPTURE_RISING_UNFILTERED,
    CAPTURE_RISING_FILTERED
};
//------------------------------------------------------------------------------------------------
template <uint8_t N>
class Timer
{
private:
    enum Channel
    {
        A = 0,
        B = 1,
        C = 2
    };
    using regs = Timer_regs <N>;
    using Type = typename regs :: Type;
    using Callback = void (*)();
    inline static uint8_t clock_bits            = _bit(regs :: clock_bit_0);
    inline static Callback overflow_callback    = nullptr;

    template <uint8_t channel>
    class Compare
    {
    public:
        void on_match(Callback callback);
        void set_match(Type value);
        void set_output(enum Timer_compare_output mode);
        void force_match_output();
        void match_interrupt() { if(match_callback) match_callback(); }
    private:
        friend class Timer <N>;
        Callback match_callback = nullptr;
    };

    class Capture_input
    {
    public:
        void set_value(Type value);
        Type get_value();
        void on_pin_change(Callback callback, enum Timer_capture_edge edge);
        void capture_interrupt() { if(pin_change_callback) pin_change_callback(); }
    private:
        friend class Timer <N>;
        Callback pin_change_callback = nullptr;
    };

public:
    inline static Compare <A> Compare_A;
    inline static Compare <B> Compare_B;
    inline static Compare <C> Compare_C;
    inline static Capture_input Capture;

    Timer();
    ResultCode set_mode(enum Timer_mode mode);
    ResultCode set_clock(enum Timer_clock value);
    void set_counter(Type value);
    void on_overflow(Callback callback);
    void clear(bool reset_prescaler = false);
    void start();
    void stop();
    void resume();
    void reset();
    Type get_counter();
    static void overflow_interrupt() { if(overflow_callback) overflow_callback(); }
};
//------------------------------------------------------------------------------------------------
#include "avr-timer-isr.h"
#include "avr-timer.tpp"
//------------------------------------------------------------------------------------------------
#define _DECLARE_TIMER_TYPE(N)          \
  using Timer##N = Timer <N>;           \
  static_assert(Timer_regs <N> :: exists, "Timer" #N " does not exist in this MCU");

#define _ENABLE_TIMER(N)                \
  _DECLARE_TIMER_TYPE(N)                \
  _ENABLE_TIMER##N##_OVF_ISR            \
  _ENABLE_TIMER_COMPARE_ISR(N)          \
  _ENABLE_TIMER##N##_CAPTURE_ISR

#define ENABLE_TIMER0 _ENABLE_TIMER(0)
#define ENABLE_TIMER1 _ENABLE_TIMER(1)
#define ENABLE_TIMER2 _ENABLE_TIMER(2)
#define ENABLE_TIMER3 _ENABLE_TIMER(3)
#define ENABLE_TIMER4 _ENABLE_TIMER(4)
#define ENABLE_TIMER5 _ENABLE_TIMER(5)

#define ENABLE_TIMER(N) ENABLE_TIMER##N
//------------------------------------------------------------------------------------------------
#endif
