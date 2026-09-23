/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: servo.tpp
 *
 * WARNING! This file is included from servo.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
template <class Compare_type>
Servo(Compare_type&, uint16_t = 1000, uint16_t = 2000) -> Servo <Compare_type>;
//------------------------------------------------------------------------------------------------
template <class Compare_type>
Servo <Compare_type> :: Servo(Compare_type &compare, uint16_t min_pulse_us,
                              uint16_t max_pulse_us) :
    compare(compare), min_pulse_us(min_pulse_us), max_pulse_us(max_pulse_us)
{
    static_assert(sizeof(decltype(Timer_type().get_counter())) == 2,
                  "Servo requires a 16-bit timer");
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure and start the timer for servo control.
 *
 * @param position Initial normalized position from -127 to 127. Zero selects
 * the 1500 us center pulse.
 *
 * @return OK on success;
 * ERR_BAD_VALUE for an invalid pulse range;
 * ERR_BAD_PARAMETER for invalid position;
 * or an error returned by the timer configuration.
 */
template <class Compare_type>
ResultCode Servo <Compare_type> :: init(int8_t position)
{
    if(min_pulse_us >= center_us || max_pulse_us <= center_us || max_pulse_us >= frame_us)
        return ERR_BAD_VALUE;

    if(position < -127)
        return ERR_BAD_PARAMETER;

    Timer_type timer;
    ResultCode result = timer.set_mode(TIMER_MODE_PHASE_PWM_CAPTURE);
    if(result != OK)
        return result;

    result = timer.set_clock(timer_clock);
    if(result != OK)
        return result;

    timer.Capture.set_value(top);
    result = set_position(position);
    if(result != OK)
        return result;

    attach();
    timer.start();
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set the servo pulse width.
 *
 * @param pulse_us Pulse width in microseconds.
 * @return OK on success; ERR_BAD_VALUE if the pulse is outside the configured range.
 */
template <class Compare_type>
ResultCode Servo <Compare_type> :: set_pulse(uint16_t pulse_us)
{
    if(pulse_us < min_pulse_us || pulse_us > max_pulse_us)
        return ERR_BAD_VALUE;

    compare.set_match(pulse_to_ticks(pulse_us));
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set the normalized servo position within its configured pulse range.
 *
 * @param position Position from -127 to 127. Zero selects the 1500 us center.
 * @return OK on success; ERR_BAD_PARAMETER if position is outside the valid range.
 */
template <class Compare_type>
ResultCode Servo <Compare_type> :: set_position(int8_t position)
{
    if(position < -127)
        return ERR_BAD_PARAMETER;

    uint16_t pulse_us;
    if(position < 0)
    {
        pulse_us = center_us
                 - uint32_t(center_us - min_pulse_us)
                 * uint8_t(-int16_t(position)) / 127;
    }
    else
    {
        pulse_us = center_us
                 + uint32_t(max_pulse_us - center_us)
                 * uint8_t(position) / 127;
    }

    return set_pulse(pulse_us);
}
//------------------------------------------------------------------------------------------------
/** @brief Connect the timer compare channel to its OC output. */
template <class Compare_type>
__inline void Servo <Compare_type> :: attach()
{
    compare.set_output(TIMER_OUTPUT_PWM);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disconnect the timer compare channel after the current pulse.
 *
 * @warning Global interrupts must be enabled before calling this method.
 */
template <class Compare_type>
__inline void Servo <Compare_type> :: detach()
{
    compare.set_output(TIMER_OUTPUT_DISCONNECTED);
}
//------------------------------------------------------------------------------------------------
template <class Compare_type>
uint16_t Servo <Compare_type> :: pulse_to_ticks(uint16_t pulse_us)
{
    return (uint64_t(F_CPU) * pulse_us + clock_divider * 1000000ULL)
         / (2ULL * clock_divider * 1000000ULL);
}
//------------------------------------------------------------------------------------------------
