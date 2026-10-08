/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-gpio.tpp
 *
 * WARNING! This file is included from avr-gpio.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Configure the GPIO pin direction and initial output state.
 *
 * Sets the DDR bit for output modes or clears it for input modes. For output
 * modes the PORT bit is written before enabling the output driver, and for
 * input modes the PORT bit selects pull-up or open input state.
 *
 * @param mode Requested GPIO mode.
 */
template <class pin>
__inline void GPIO <pin> :: set_mode(enum GPIO_mode mode)
{
    switch(mode)
    {
    case OUTPUT_HIGH:
        write_high();
        set_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        break;
    case OUTPUT_LOW:
        write_low();
        set_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        break;
    case INPUT_PULLUP:
        clr_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        write_high();
        break;
    case INPUT_OPEN:
        clr_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        write_low();
        break;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Get the current GPIO direction and output latch mode.
 *
 * @return Current GPIO mode derived from the DDR and PORT registers.
 */
template <class pin>
__inline GPIO_mode GPIO <pin> :: get_mode()
{
    const uint8_t level = test_bit(_SFR_IO8(pin :: PORT), pin :: BIT);

    if(test_bit(_SFR_IO8(pin :: DDR), pin :: BIT))
        return level ? OUTPUT_HIGH : OUTPUT_LOW;

    return level ? INPUT_PULLUP : INPUT_OPEN;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Drive the GPIO output high or enable the input pull-up.
 *
 * Sets the PORT bit associated with the template pin. The exact electrical
 * effect depends on whether the pin is currently configured as output or input.
 */
template <class pin>
__inline void GPIO <pin> :: write_high()
{
    set_bit(_SFR_IO8(pin::PORT), pin :: BIT);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Drive the GPIO output low or disable the input pull-up.
 *
 * Clears the PORT bit associated with the template pin. The exact electrical
 * effect depends on whether the pin is currently configured as output or input.
 */
template <class pin>
__inline void GPIO <pin> :: write_low()
{
    clr_bit(_SFR_IO8(pin :: PORT), pin :: BIT);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read the current logic level from the GPIO input register.
 *
 * @return Non-zero when the pin input level is high, zero when it is low.
 */
template <class pin>
__inline uint8_t GPIO <pin> :: read()
{
    return test_bit(_SFR_IO8(pin :: PIN), pin :: BIT);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Toggle the GPIO output latch.
 *
 * Uses the MCU-specific hardware toggle register when available. On older
 * devices without this feature, reads the output latch and changes only the
 * selected bit with an atomic SBI or CBI instruction.
 */
template <class pin>
__inline void GPIO <pin> :: toggle()
{
    if constexpr(pin :: TGL == NONE)
    {
        if(test_bit(_SFR_IO8(pin :: PORT), pin :: BIT))
            clr_bit(_SFR_IO8(pin :: PORT), pin :: BIT);
        else
            set_bit(_SFR_IO8(pin :: PORT), pin :: BIT);
    }
    else
    {
        set_bit(_SFR_IO8(pin :: TGL), pin :: BIT);
    }

}
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure and enable the pin's external interrupt.
 *
 * Clears the pending flag before enabling the line. The application defines
 * its ISR and enables global interrupts separately.
 *
 * @param mode External interrupt trigger mode.
 */
template <class pin>
__inline void GPIO <pin> :: enable_int(INT_mode mode)
{
    using interrupt = INT_traits_for_pin <pin>;
    static_assert(interrupt :: exists,
                  "This pin has no external INT in this MCU (see AVR/GPIO/pins/...)");

    if constexpr(interrupt :: exists)
    {
        clr_bit(interrupt :: MASK, interrupt :: mask_bit);

        uint8_t control = interrupt :: CONTROL;
        clr_bits(control, interrupt :: sense_bit_0, interrupt :: sense_bit_1);
        if(test_bit(mode, 0))
            set_bit(control, interrupt :: sense_bit_0);
        if(test_bit(mode, 1))
            set_bit(control, interrupt :: sense_bit_1);
        interrupt :: CONTROL = control;
        interrupt :: FLAGS = _bit(interrupt :: flag_bit);
        set_bit(interrupt :: MASK, interrupt :: mask_bit);
    }
}
//------------------------------------------------------------------------------------------------
/** @brief Disable the pin's external interrupt without changing its GPIO mode. */
template <class pin>
__inline void GPIO <pin> :: disable_int()
{
    using interrupt = INT_traits_for_pin <pin>;
    static_assert(interrupt :: exists,
                  "This pin has no external INT in this MCU (see AVR/GPIO/pins/...)");

    if constexpr(interrupt :: exists)
    {
        clr_bit(interrupt :: MASK, interrupt :: mask_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enable pin-change interrupt for this pin.
 *
 * Clears the group flag only when no other pin in the group is enabled.
 * The application defines the shared ISR and enables global interrupts.
 */
template <class pin>
__inline void GPIO <pin> :: enable_pcint()
{
    using PCINT = PCINT_traits <pin>;
    static_assert(PCINT :: exists,
                  "This pin has no PCINT in this MCU (see AVR/GPIO/pins/...)");

    if constexpr(PCINT :: exists)
    {
        if(PCINT :: MASK == 0)
            PCINT :: FLAGS = _bit(PCINT :: flag_bit);
        set_bit(PCINT :: MASK, PCINT :: mask_bit);
        set_bit(PCINT :: CONTROL, PCINT :: control_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Claim exclusive use of the PCINT group for this pin.
 *
 * Disables PCINT for every other pin in the group, clears the pending flag,
 * and enables the group.
 * @warning Further calling enable_pcint() for another pin in this group
 * will cancel this exclusive use.
 */
template <class pin>
__inline void GPIO <pin> :: claim_pcint()
{
    using PCINT = PCINT_traits <pin>;
    static_assert(PCINT :: exists,
                  "This pin has no PCINT in this MCU (see AVR/GPIO/pins/...)");

    if constexpr(PCINT :: exists)
    {
        PCINT :: MASK = 0;
        set_bit(PCINT :: MASK, PCINT :: mask_bit);
        // W1C: direct write clears only this group's flag, without RMW.
        PCINT :: FLAGS = _bit(PCINT :: flag_bit);
        set_bit(PCINT :: CONTROL, PCINT :: control_bit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable pin-change interrupt for this pin.
 *
 * Disables the shared group only when its last enabled pin is removed.
 */
template <class pin>
__inline void GPIO <pin> :: disable_pcint()
{
    using PCINT = PCINT_traits <pin>;
    static_assert(PCINT :: exists,
                  "This pin has no PCINT in this MCU (see AVR/GPIO/pins/...)");

    if constexpr(PCINT :: exists)
    {
        clr_bit(PCINT :: MASK, PCINT :: mask_bit);
        if(PCINT :: MASK == 0)
            clr_bit(PCINT :: CONTROL, PCINT :: control_bit);
    }
}
//------------------------------------------------------------------------------------------------
