/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: servo.h
//----------------------------------------------------------------------------------------------*/
#ifndef SERVO_H
#define SERVO_H
//------------------------------------------------------------------------------------------------
/**
 * @brief RC servo driver using a hardware timer compare channel.
 *
 * Generates a 20 ms servo control frame. The pulse range defaults to
 * 1000...2000 us and may be adjusted for a particular servo.
 *
 * @tparam Compare_type Timer compare channel type, deduced by the constructor.
 */
template <class Compare_type>
class Servo
{
public:
    Servo(Compare_type &compare, uint16_t min_pulse_us = 1000,
          uint16_t max_pulse_us = 2000);

    ResultCode init(int8_t position = 0);
    ResultCode set_pulse(uint16_t pulse_us);
    ResultCode set_position(int8_t position);
    void attach();
    void detach();

private:
    using Timer_type = typename Compare_type :: Timer_type;
    static constexpr uint16_t frame_us = 20000;
    static constexpr uint16_t center_us = 1500;
    static constexpr uint32_t calculate_top(uint16_t divider)
    {
        return (uint64_t(F_CPU) * frame_us) / (2ULL * divider * 1000000ULL);
    }
    static constexpr uint16_t select_clock_divider()
    {
        if(calculate_top(1) <= UINT16_MAX) return 1;
        if(calculate_top(8) <= UINT16_MAX) return 8;
        if(calculate_top(64) <= UINT16_MAX) return 64;
        if(calculate_top(256) <= UINT16_MAX) return 256;
        if(calculate_top(1024) <= UINT16_MAX) return 1024;
        return 0;
    }

    static constexpr uint16_t clock_divider = select_clock_divider();
    static_assert(clock_divider != 0, "F_CPU is too high for a 20 ms servo frame");

    static constexpr uint32_t top = clock_divider ? calculate_top(clock_divider) : 0;
    static_assert(top != 0, "F_CPU is too low for a 20 ms servo frame");

    static constexpr Timer_clock timer_clock =
        clock_divider == 1   ? TIMER_CLOCK_DIV_1 :
        clock_divider == 8   ? TIMER_CLOCK_DIV_8 :
        clock_divider == 64  ? TIMER_CLOCK_DIV_64 :
        clock_divider == 256 ? TIMER_CLOCK_DIV_256 : TIMER_CLOCK_DIV_1024;

    static uint16_t pulse_to_ticks(uint16_t pulse_us);

    Compare_type &compare;
    uint16_t min_pulse_us;
    uint16_t max_pulse_us;
};
//------------------------------------------------------------------------------------------------
#include "servo.tpp"
//------------------------------------------------------------------------------------------------
#endif
