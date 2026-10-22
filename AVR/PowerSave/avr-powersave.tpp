/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-powersave.tpp
 *
 * WARNING! This file is included from avr-powersave.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Enter the requested sleep mode and return after wake-up.
 * @param mode Sleep mode selected explicitly by the caller.
 * @retval OK The MCU woke up and execution resumed.
 * @retval ERR_BAD_MODE The MCU or requested sleep mode is not supported.
 * @details Enables interrupts for sleep and restores their previous state on return.
 * A wake-up interrupt must be configured beforehand. Call from normal code, not an ISR.
 * Test any application sleep condition inside an enclosing ATOMIC_BLOCK to avoid
 * losing an event between the test and sleep. BOD settings are not changed.
 * @note Classic AVR Standby modes require a compatible external oscillator configuration.
 */
__inline ResultCode AVR_PowerSave :: sleep(PowerSave_mode mode)
{
    if constexpr(!regs :: exists)
        return ERR_REJECTED;

    uint8_t value = regs :: IDLE;
    switch(mode)
    {
        case POWERSAVE_IDLE:
            value = regs :: IDLE;
            break;

        case POWERSAVE_ADC_NOISE_REDUCTION:
            if constexpr(regs :: has_adc_noise_reduction)
                value = regs :: ADC_NOISE_REDUCTION;
            else
                return ERR_BAD_MODE;
            break;

        case POWERSAVE_SLEEP:
            value = regs :: POWER_DOWN;
            break;

        case POWERSAVE_SAVE:
            if constexpr(regs :: has_power_save)
                value = regs :: POWER_SAVE;
            else
                return ERR_BAD_MODE;
            break;

        case POWERSAVE_STANDBY:
            if constexpr(regs :: has_standby)
                value = regs :: STANDBY;
            else
                return ERR_BAD_MODE;
            break;

        case POWERSAVE_EXTENDED_SAVE:
            if constexpr(regs :: has_extended_standby)
                value = regs :: EXTENDED_STANDBY;
            else
                return ERR_BAD_MODE;
            break;
    }

    {
        ATOMIC_BLOCK
        uint8_t control = regs :: SLEEP_CONTROL;
        control &= ~regs :: MODE_MASK;
        control |= value;
        set_bit(control, regs :: SLEEP_ENABLE);
        regs :: SLEEP_CONTROL = control;
        // The instruction after SEI executes before a pending interrupt is serviced.
        __asm__ __volatile__("sei\n\tsleep\n\tcli" ::: "memory");
        clr_bit(regs :: SLEEP_CONTROL, regs :: SLEEP_ENABLE);
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for all peripheral groups and power down the comparator.
 * @retval OK All groups supported by this backend have been powered down.
 * @retval ERR_BAD_MODE This backend cannot shut down all peripheral groups.
 * @note Finish pending operations and disable the peripherals before calling.
 * ADC must have ADEN cleared and the comparator interrupt must be disabled.
 * This method does not change the global interrupt state.
 */
__inline ResultCode AVR_PowerSave :: cpu_only()
{
    if constexpr(!regs :: has_cpu_only)
        return ERR_BAD_MODE;

    if constexpr(regs :: UART_MASK0 != 0 || regs :: UART_MASK1 != 0)
        disable_uart_power();
    if constexpr(regs :: has_spi_power)
        disable_spi_power();
    if constexpr(regs :: has_i2c_power)
        disable_i2c_power();
    if constexpr(regs :: TIMERS_MASK0 != 0 || regs :: TIMERS_MASK1 != 0)
        disable_timers_power();
    if constexpr(regs :: has_adc_power)
        disable_adc_power();
    if constexpr(regs :: has_usb_power)
        disable_usb_power();
    if constexpr(regs :: has_usi_power)
        disable_usi_power();
    if constexpr(regs :: has_comparator_power)
        disable_comparator_power();
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for all hardware UARTs.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_uart_power()
{
    if constexpr(regs :: UART_MASK0 == 0 && regs :: UART_MASK1 == 0)
        return ERR_BAD_MODE;

    if constexpr(regs :: UART_MASK0 != 0)
        regs :: POWER0 |= regs :: UART_MASK0;
    if constexpr(regs :: UART_MASK1 != 0)
        regs :: POWER1 |= regs :: UART_MASK1;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for all hardware UARTs.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_uart_power()
{
    if constexpr(regs :: UART_MASK0 == 0 && regs :: UART_MASK1 == 0)
        return ERR_BAD_MODE;

    if constexpr(regs :: UART_MASK0 != 0)
        regs :: POWER0 &= ~regs :: UART_MASK0;
    if constexpr(regs :: UART_MASK1 != 0)
        regs :: POWER1 &= ~regs :: UART_MASK1;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for the SPI peripheral.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_spi_power()
{
    if constexpr(!regs :: has_spi_power)
        return ERR_BAD_MODE;

    set_bit(regs :: POWER0, regs :: SPI_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for the SPI peripheral.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_spi_power()
{
    if constexpr(!regs :: has_spi_power)
        return ERR_BAD_MODE;

    clr_bit(regs :: POWER0, regs :: SPI_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for the I2C peripheral.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_i2c_power()
{
    if constexpr(!regs :: has_i2c_power)
        return ERR_BAD_MODE;

    set_bit(regs :: POWER0, regs :: I2C_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for the I2C peripheral.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_i2c_power()
{
    if constexpr(!regs :: has_i2c_power)
        return ERR_BAD_MODE;

    clr_bit(regs :: POWER0, regs :: I2C_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for all hardware timers.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_timers_power()
{
    if constexpr(regs :: TIMERS_MASK0 == 0 && regs :: TIMERS_MASK1 == 0)
        return ERR_BAD_MODE;

    if constexpr(regs :: TIMERS_MASK0 != 0)
        regs :: POWER0 |= regs :: TIMERS_MASK0;
    if constexpr(regs :: TIMERS_MASK1 != 0)
        regs :: POWER1 |= regs :: TIMERS_MASK1;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for all hardware timers.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_timers_power()
{
    if constexpr(regs :: TIMERS_MASK0 == 0 && regs :: TIMERS_MASK1 == 0)
        return ERR_BAD_MODE;

    if constexpr(regs :: TIMERS_MASK0 != 0)
        regs :: POWER0 &= ~regs :: TIMERS_MASK0;
    if constexpr(regs :: TIMERS_MASK1 != 0)
        regs :: POWER1 &= ~regs :: TIMERS_MASK1;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for the ADC peripheral.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_adc_power()
{
    if constexpr(!regs :: has_adc_power)
        return ERR_BAD_MODE;

    set_bit(regs :: POWER0, regs :: ADC_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for the ADC peripheral.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_adc_power()
{
    if constexpr(!regs :: has_adc_power)
        return ERR_BAD_MODE;

    clr_bit(regs :: POWER0, regs :: ADC_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for the USB peripheral.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_usb_power()
{
    if constexpr(!regs :: has_usb_power)
        return ERR_BAD_MODE;

    set_bit(regs :: POWER1, regs :: USB_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for the USB peripheral.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_usb_power()
{
    if constexpr(!regs :: has_usb_power)
        return ERR_BAD_MODE;

    clr_bit(regs :: POWER1, regs :: USB_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Stop clocks for the USI peripheral.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Finish pending operations and disable the peripheral before stopping its clock.
 */
__inline ResultCode AVR_PowerSave :: disable_usi_power()
{
    if constexpr(!regs :: has_usi_power)
        return ERR_BAD_MODE;

    set_bit(regs :: POWER0, regs :: USI_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Restore clocks for the USI peripheral.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Does not initialize the peripheral; reinitialize its driver where required.
 */
__inline ResultCode AVR_PowerSave :: enable_usi_power()
{
    if constexpr(!regs :: has_usi_power)
        return ERR_BAD_MODE;

    clr_bit(regs :: POWER0, regs :: USI_POWER_BIT);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Power down the analog comparator.
 * @retval OK Power disabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Disable the comparator interrupt before changing power. The driver
 * preserves its configuration and does not acknowledge pending flags.
 */
__inline ResultCode AVR_PowerSave :: disable_comparator_power()
{
    if constexpr(!regs :: has_comparator_power)
        return ERR_BAD_MODE;

    uint8_t control = regs :: COMPARATOR_CONTROL;
    clr_bit(control, regs :: COMPARATOR_FLAG);   // W1C: preserve pending interrupt
    set_bit(control, regs :: COMPARATOR_DISABLE);
    regs :: COMPARATOR_CONTROL = control;
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Power up the analog comparator.
 * @retval OK Power enabled.
 * @retval ERR_BAD_MODE Power control for this group is unavailable.
 * @note Disable the comparator interrupt before changing power. The driver
 * preserves its configuration and does not acknowledge pending flags.
 */
__inline ResultCode AVR_PowerSave :: enable_comparator_power()
{
    if constexpr(!regs :: has_comparator_power)
        return ERR_BAD_MODE;

    uint8_t control = regs :: COMPARATOR_CONTROL;
    clr_bit(control, regs :: COMPARATOR_FLAG);   // W1C: preserve pending interrupt
    clr_bit(control, regs :: COMPARATOR_DISABLE);
    regs :: COMPARATOR_CONTROL = control;
    return OK;
}
//------------------------------------------------------------------------------------------------
