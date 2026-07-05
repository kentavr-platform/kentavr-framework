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
 * Uses the MCU-specific hardware toggle mechanism without reading port's value.
 */
template <class pin>
__inline void GPIO <pin> :: toggle()
{
#if defined(__AVR_ATmega1284P__)
    // TODO: modify this for whole the family
    // 14.2.2 Toggling the pin
    // Writing a logic one to PINxn toggles the value of PORTxn, independent on the value of DDRxn.
    set_bit(_SFR_IO8(pin :: PIN), pin :: BIT);
#elif defined(AVR128DX_FAMILY)
    // TODO: check this and map TGL addr into pin structure
    set_bit(_SFR_MEM8(pin :: TGL), pin :: BIT);
#endif
}
//------------------------------------------------------------------------------------------------


