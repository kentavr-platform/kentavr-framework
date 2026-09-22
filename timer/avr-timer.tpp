/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-timer.tpp
 *
 * WARNING! This file is included from avr-timer.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
template <uint8_t N>
Timer <N> :: Timer()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Setup a callback function on compare match for this channel.
 *
 * Passing nullptr removes the handler. Pending match events are discarded.
 * Global interrupts must be enabled.
 *
 * @param callback Function to call, or nullptr to disable the interrupt.
 */
template <uint8_t N>
template <uint8_t channel>
void Timer <N> :: Compare <channel> :: on_match(typename Timer <N> :: Callback callback)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    static_assert(channel != Timer <N> :: C || regs :: has_compare_c,
                  "Selected timer does not have Compare C channel");

    if constexpr(regs :: exists)
    {
        match_callback = callback;

        if constexpr(channel == Timer <N> :: A)
        {
            // TIFRn flags are cleared by writing one (W1C).
            regs :: INT_FLAGS = _bit(regs :: compare_a_flag_bit);

            if(callback)
                set_bit(regs :: INT_MASK, regs :: compare_a_interrupt_bit);
            else
                clr_bit(regs :: INT_MASK, regs :: compare_a_interrupt_bit);
        }
        else if constexpr(channel == Timer <N> :: B)
        {
            // TIFRn flags are cleared by writing one (W1C).
            regs :: INT_FLAGS = _bit(regs :: compare_b_flag_bit);

            if(callback)
                set_bit(regs :: INT_MASK, regs :: compare_b_interrupt_bit);
            else
                clr_bit(regs :: INT_MASK, regs :: compare_b_interrupt_bit);
        }
        else if constexpr(regs :: has_compare_c)
        {
            // TIFRn flags are cleared by writing one (W1C).
            regs :: INT_FLAGS = _bit(regs :: compare_c_flag_bit);

            if(callback)
                set_bit(regs :: INT_MASK, regs :: compare_c_interrupt_bit);
            else
                clr_bit(regs :: INT_MASK, regs :: compare_c_interrupt_bit);
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set the compare value for this channel.
 *
 * In PWM modes this sets the duty cycle, unless Compare A is used as TOP.
 * Compare A also sets the period in CTC mode.
 *
 * @param value Counter value at which the channel matches.
 */
template <uint8_t N>
template <uint8_t channel>
void Timer <N> :: Compare <channel> :: set_match(typename Timer <N> :: Type value)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(channel != Timer <N> :: C || regs :: has_compare_c,
                  "Selected timer does not have Compare C channel");

    if constexpr(regs :: exists)
    {
        if constexpr(channel == Timer <N> :: A)
            regs :: COMPARE_A = value;
        else if constexpr(channel == Timer <N> :: B)
            regs :: COMPARE_B = value;
        else if constexpr(regs :: has_compare_c)
            regs :: COMPARE_C = value;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Connect the compare channel to its hardware OC output.
 *
 * Use TIMER_OUTPUT_PWM or TIMER_OUTPUT_PWM_INVERTED in PWM modes. In non-PWM modes, select
 * whether the OC pin is toggled, cleared, or set on a compare match. Select
 * TIMER_OUTPUT_DISCONNECTED to return the pin to normal GPIO operation.
 *
 * @attention The corresponding OC pin must be configured as an OUTPUT through
 * its GPIO Data Direction Register (DDR) separately. This method configures the
 * timer output behavior but does NOT enable the physical pin output driver.
 * You may use 'GPIO <D6> :: set_mode(OUTPUT...);' for this.
 *
 * @param mode Required output behavior for this compare channel.
 */
template <uint8_t N>
template <uint8_t channel>
void Timer <N> :: Compare <channel> :: set_output(enum Timer_compare_output mode)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(channel != Timer <N> :: C || regs :: has_compare_c,
                  "Selected timer does not have Compare C channel");

    if constexpr(regs :: exists)
    {
        constexpr uint8_t mode_bit_0 = 6 - channel * 2;
        constexpr uint8_t mode_bit_1 = mode_bit_0 + 1;

        clr_bits(regs :: CONTROL_A, mode_bit_0, mode_bit_1);

        switch(mode)
        {
        case TIMER_OUTPUT_TOGGLE_ON_MATCH:
            set_bit(regs :: CONTROL_A, mode_bit_0);
            break;
        case TIMER_OUTPUT_CLEAR_ON_MATCH:
        case TIMER_OUTPUT_PWM:
            set_bit(regs :: CONTROL_A, mode_bit_1);
            break;
        case TIMER_OUTPUT_SET_ON_MATCH:
        case TIMER_OUTPUT_PWM_INVERTED:
            set_bits(regs :: CONTROL_A, mode_bit_1, mode_bit_0);
            break;
        case TIMER_OUTPUT_DISCONNECTED:
        default:
            break;
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Immediately apply the configured compare-match action to the OC output.
 *
 * This operation affects only the hardware OC output in non-PWM modes. It does
 * not set the compare-match flag, invoke the callback, or clear the counter in
 * CTC mode.
 */
template <uint8_t N>
template <uint8_t channel>
void Timer <N> :: Compare <channel> :: force_match_output()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(channel != Timer <N> :: C || regs :: has_compare_c,
                  "Selected timer does not have Compare C channel");

    if constexpr(regs :: exists)
    {
        if constexpr(channel == Timer <N> :: A)
            set_bit(regs :: FORCE_CONTROL, regs :: force_a_bit);
        else if constexpr(channel == Timer <N> :: B)
            set_bit(regs :: FORCE_CONTROL, regs :: force_b_bit);
        else if constexpr(regs :: has_compare_c)
            set_bit(regs :: FORCE_CONTROL, regs :: force_c_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Setup a callback function for the selected edge on the input capture pin.
 *
 * Passing nullptr removes the callback. Global interrupts must be enabled.
 *
 * @param callback Callback function, or nullptr to disable the interrupt.
 * @param edge Capture edge and optional noise filter.
 */
template <uint8_t N>
void Timer <N> :: Capture_input :: on_pin_change(typename Timer <N> :: Callback callback,
                                                 enum Timer_capture_edge edge)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(regs :: has_capture, "Selected timer does not have input capture pin");

    if constexpr(regs :: exists && regs :: has_capture)
    {
        pin_change_callback = callback;

        switch(edge)
        {
        case CAPTURE_FALLING_UNFILTERED:
            clr_bit(regs :: CONTROL_B, regs :: capture_edge_bit);
            clr_bit(regs :: CONTROL_B, regs :: capture_noise_canceler_bit);
            break;
        case CAPTURE_FALLING_FILTERED:
            clr_bit(regs :: CONTROL_B, regs :: capture_edge_bit);
            set_bit(regs :: CONTROL_B, regs :: capture_noise_canceler_bit);
            break;
        case CAPTURE_RISING_UNFILTERED:
            set_bit(regs :: CONTROL_B, regs :: capture_edge_bit);
            clr_bit(regs :: CONTROL_B, regs :: capture_noise_canceler_bit);
            break;
        case CAPTURE_RISING_FILTERED:
            set_bit(regs :: CONTROL_B, regs :: capture_edge_bit);
            set_bit(regs :: CONTROL_B, regs :: capture_noise_canceler_bit);
            break;
        }

        // TIFRn flags are cleared by writing one (W1C).
        regs :: INT_FLAGS = _bit(regs :: capture_flag_bit);

        if(callback)
            set_bit(regs :: INT_MASK, regs :: capture_interrupt_bit);
        else
            clr_bit(regs :: INT_MASK, regs :: capture_interrupt_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set the capture value.
 *
 * In CAPTURE PWM modes this method may be used to set the timer period.
 *
 * @param value Capture value.
 */
template <uint8_t N>
void Timer <N> :: Capture_input :: set_value(typename Timer <N> :: Type value)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(regs :: has_capture, "Selected timer does not have Input Capture");

    if constexpr(regs :: exists && regs :: has_capture)
        regs :: CAPTURE = value;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get the captured value.
 *
 * @return Current capture value.
 */
template <uint8_t N>
typename Timer <N> :: Type Timer <N> :: Capture_input :: get_value()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");
    static_assert(regs :: has_capture, "Selected timer does not have Input Capture");

    if constexpr(regs :: exists && regs :: has_capture)
        return regs :: CAPTURE;
    else
        return 0;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Setup a callback function on timer overflow.
 *
 * Passing nullptr removes the callback. Pending overflow events are discarded.
 * Global interrupts must be enabled.
 *
 * @param callback Callback function, or nullptr to disable the interrupt.
 */
template <uint8_t N>
void Timer <N> :: on_overflow(Callback callback)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        overflow_callback = callback;
        // TIFRn flags are cleared by writing one (W1C).
        regs :: INT_FLAGS = _bit(regs :: overflow_flag_bit);

        if(callback)
            set_bit(regs :: INT_MASK, regs :: overflow_interrupt_bit);
        else
            clr_bit(regs :: INT_MASK, regs :: overflow_interrupt_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Select the timer waveform generation mode.
 *
 * @return OK on success; ERR_BAD_PARAMETER if this timer does not support the
 * requested mode or mode is not a valid Timer_mode value.
 */
template <uint8_t N>
ResultCode Timer <N> :: set_mode(enum Timer_mode mode)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        uint8_t wgm = 0;
        bool supported = true;

        switch(mode)
        {
        case TIMER_MODE_NORMAL:
            wgm = 0;
            break;
        case TIMER_MODE_CTC_OCRA:
            if constexpr(sizeof(Type) == 1)
                wgm = 2;
            else
                wgm = 4;
            break;
        case TIMER_MODE_CTC_ICR:
            if constexpr(sizeof(Type) > 1 && regs :: has_icr_top)
                wgm = 12;
            else
                supported = false;
            break;
        case TIMER_MODE_FAST_PWM_8:
            if constexpr(sizeof(Type) == 1)
                wgm = 3;
            else
                wgm = 5;
            break;
        case TIMER_MODE_FAST_PWM_9:
            if constexpr(sizeof(Type) > 1)
                wgm = 6;
            else
                supported = false;
            break;
        case TIMER_MODE_FAST_PWM_10:
            if constexpr(sizeof(Type) > 1)
                wgm = 7;
            else
                supported = false;
            break;
        case TIMER_MODE_FAST_PWM_COMPARE_A:
            if constexpr(sizeof(Type) == 1)
                wgm = 7;
            else
                wgm = 15;
            break;
        case TIMER_MODE_FAST_PWM_CAPTURE:
            if constexpr(sizeof(Type) > 1 && regs :: has_icr_top)
                wgm = 14;
            else
                supported = false;
            break;
        case TIMER_MODE_PHASE_PWM_8:
            wgm = 1;
            break;
        case TIMER_MODE_PHASE_PWM_9:
            if constexpr(sizeof(Type) > 1)
                wgm = 2;
            else
                supported = false;
            break;
        case TIMER_MODE_PHASE_PWM_10:
            if constexpr(sizeof(Type) > 1)
                wgm = 3;
            else
                supported = false;
            break;
        case TIMER_MODE_PHASE_PWM_COMPARE_A:
            if constexpr(sizeof(Type) == 1)
                wgm = 5;
            else
                wgm = 11;
            break;
        case TIMER_MODE_PHASE_PWM_CAPTURE:
            if constexpr(sizeof(Type) > 1 && regs :: has_icr_top)
                wgm = 10;
            else
                supported = false;
            break;
        case TIMER_MODE_PHASE_FREQ_PWM_COMPARE_A:
            if constexpr(sizeof(Type) > 1)
                wgm = 9;
            else
                supported = false;
            break;
        case TIMER_MODE_PHASE_FREQ_PWM_CAPTURE:
            if constexpr(sizeof(Type) > 1 && regs :: has_icr_top)
                wgm = 8;
            else
                supported = false;
            break;
        default:
            supported = false;
            break;
        }

        if(supported)
        {
            regs :: CONTROL_A = (regs :: CONTROL_A & ~uint8_t(0x03)) | (wgm & 0x03);
            regs :: CONTROL_B = (regs :: CONTROL_B & ~_bit(3)) | ((wgm & 0x04) << 1);

            if constexpr(sizeof(Type) > 1)
                regs :: CONTROL_B = (regs :: CONTROL_B & ~_bit(4)) | ((wgm & 0x08) << 1);

            return OK;
        }

        return ERR_BAD_PARAMETER;
    }

    return ERR_BAD_PARAMETER;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Select the clock source.
 *
 * @return OK on success; ERR_BAD_PARAMETER if this timer does not support the
 * requested divider or source, or value is not a valid Timer_clock value.
 */
template <uint8_t N>
ResultCode Timer <N> :: set_clock(enum Timer_clock value)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        uint8_t new_clock_bits = 0;
        bool supported = true;

        switch(value)
        {
        case TIMER_CLOCK_DIV_1:
            new_clock_bits = _bit(regs :: clock_bit_0);
            break;
        case TIMER_CLOCK_DIV_8:
            new_clock_bits = _bit(regs :: clock_bit_1);
            break;
        case TIMER_CLOCK_DIV_32:
            if constexpr(regs :: has_extended_prescaler)
                new_clock_bits = _bits(regs :: clock_bit_1, regs :: clock_bit_0);
            else
                supported = false;
            break;
        case TIMER_CLOCK_DIV_64:
            if constexpr(regs :: has_extended_prescaler)
                new_clock_bits = _bit(regs :: clock_bit_2);
            else
                new_clock_bits = _bits(regs :: clock_bit_1, regs :: clock_bit_0);
            break;
        case TIMER_CLOCK_DIV_128:
            if constexpr(regs :: has_extended_prescaler)
                new_clock_bits = _bits(regs :: clock_bit_2, regs :: clock_bit_0);
            else
                supported = false;
            break;
        case TIMER_CLOCK_DIV_256:
            if constexpr(regs :: has_extended_prescaler)
                new_clock_bits = _bits(regs :: clock_bit_2, regs :: clock_bit_1);
            else
                new_clock_bits = _bit(regs :: clock_bit_2);
            break;
        case TIMER_CLOCK_DIV_1024:
            if constexpr(regs :: has_extended_prescaler)
                new_clock_bits = _bits(regs :: clock_bit_2, regs :: clock_bit_1,
                                        regs :: clock_bit_0);
            else
                new_clock_bits = _bits(regs :: clock_bit_2, regs :: clock_bit_0);
            break;
        case TIMER_CLOCK_EXTERNAL_FALLING:
            if constexpr(regs :: has_external_clock)
                new_clock_bits = _bits(regs :: clock_bit_2, regs :: clock_bit_1);
            else
                supported = false;
            break;
        case TIMER_CLOCK_EXTERNAL_RISING:
            if constexpr(regs :: has_external_clock)
            {
                new_clock_bits = _bits(regs :: clock_bit_2,
                                       regs :: clock_bit_1,
                                       regs :: clock_bit_0);
            }
            else
                supported = false;
            break;
        default:
            supported = false;
            break;
        }

        if(!supported)
            return ERR_BAD_PARAMETER;

        clock_bits = new_clock_bits;
        return OK;
    }

    return ERR_BAD_PARAMETER;
}
//------------------------------------------------------------------------------------------------
/** @brief Start the timer from zero using the selected clock. */
template <uint8_t N>
void Timer <N> :: start()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        clear();
        resume();
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stops counting while preserving the current counter value.
 *
 * @attention The timer prescaler continues running even while the counter is stopped.
 * After resume(), the first counter increment may therefore occur before a complete
 * prescaler period has elapsed.
 */
template <uint8_t N>
__inline void Timer <N> :: stop()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        clr_bits(regs :: CONTROL_B,
                 regs :: clock_bit_0,
                 regs :: clock_bit_1,
                 regs :: clock_bit_2);
    }

}
//------------------------------------------------------------------------------------------------
/** @brief Resume the timer from its current counter value. */
template <uint8_t N>
__inline void Timer <N> :: resume()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        constexpr uint8_t clock_mask = _bits(regs :: clock_bit_0,
                                             regs :: clock_bit_1,
                                             regs :: clock_bit_2);
        regs :: CONTROL_B = (regs :: CONTROL_B & ~clock_mask) | clock_bits;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Set the timer counter value.
 *
 * @param value Counter value to load.
 */
template <uint8_t N>
void Timer <N> :: set_counter(Type value)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
        regs :: COUNTER = value;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Clear the counter, optionally resetting its prescaler.
 *
 * @attention Resetting a shared synchronous prescaler also affects the timing
 * of OTHER TIMERS connected to that prescaler!
 *
 * @param reset_prescaler Reset the hardware prescaler associated with this
 * timer before clearing the counter.
 */
template <uint8_t N>
void Timer <N> :: clear(bool reset_prescaler)
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        if(reset_prescaler)
        {
            if constexpr(regs :: has_async_clock)
            {
                #if defined(GTCCR) && defined(PSRASY)
                    set_bit(GTCCR, PSRASY);
                #elif defined(GTCCR) && defined(PSR2)
                    set_bit(GTCCR, PSR2);
                #elif defined(SFIOR) && defined(PSR2)
                    set_bit(SFIOR, PSR2);
                #elif defined(GTCCR) && defined(PSR)
                    set_bit(GTCCR, PSR);
                #endif
            }
            else
            {
                #if defined(GTCCR) && defined(PSRSYNC)
                    set_bit(GTCCR, PSRSYNC);
                #elif defined(GTCCR) && defined(PSR10)
                    set_bit(GTCCR, PSR10);
                #elif defined(SFIOR) && defined(PSR10)
                    set_bit(SFIOR, PSR10);
                #elif defined(GTCCR) && defined(PSR)
                    set_bit(GTCCR, PSR);
                #elif defined(GTCCR) && defined(PSR0) && defined(PSR1)
                    if constexpr(N == 0)
                        set_bit(GTCCR, PSR0);
                    else if constexpr(N == 1)
                        set_bit(GTCCR, PSR1);
                #endif
            }
        }
        regs :: COUNTER = 0;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore the timer peripheral and its callbacks to their reset state.
 *
 * Stops the timer, disconnects compare outputs, clears waveform configuration,
 * counter, compare and capture registers, disables this timer's interrupts,
 * clears its pending flags and removes every registered callback. GPIO direction
 * and output registers are not part of the timer and remain unchanged.
 */
template <uint8_t N>
void Timer <N> :: reset()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
    {
        ATOMIC_BLOCK
        {
            regs :: CONTROL_A = 0;
            regs :: CONTROL_B = 0;

            uint8_t interrupt_mask = _bit(regs :: overflow_interrupt_bit)
                                   | _bit(regs :: compare_a_interrupt_bit)
                                   | _bit(regs :: compare_b_interrupt_bit);
            uint8_t flag_mask = _bit(regs :: overflow_flag_bit)
                              | _bit(regs :: compare_a_flag_bit)
                              | _bit(regs :: compare_b_flag_bit);

            if constexpr(regs :: has_compare_c)
            {
                interrupt_mask |= _bit(regs :: compare_c_interrupt_bit);
                flag_mask |= _bit(regs :: compare_c_flag_bit);
            }

            if constexpr(regs :: has_capture)
            {
                interrupt_mask |= _bit(regs :: capture_interrupt_bit);
                flag_mask |= _bit(regs :: capture_flag_bit);
            }


            regs :: INT_MASK &= ~interrupt_mask;

            regs :: COUNTER = 0;
            regs :: COMPARE_A = 0;
            regs :: COMPARE_B = 0;

            if constexpr(regs :: has_compare_c)
                regs :: COMPARE_C = 0;

            if constexpr(regs :: has_capture)
                regs :: CAPTURE = 0;

            regs :: INT_FLAGS = flag_mask;

        clock_bits = _bit(regs :: clock_bit_0);
        overflow_callback = nullptr;
        Compare_A.match_callback = nullptr;
        Compare_B.match_callback = nullptr;
        Compare_C.match_callback = nullptr;
        Capture.pin_change_callback = nullptr;
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get the timer counter value.
 *
 * @return Current counter value.
 */
template <uint8_t N>
typename Timer <N> :: Type Timer <N> :: get_counter()
{
    static_assert(regs :: exists, "Selected timer does not exist in this MCU");

    if constexpr(regs :: exists)
        return regs :: COUNTER;
    else
        return 0;
}
//------------------------------------------------------------------------------------------------
