/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-watchdog.cpp
//----------------------------------------------------------------------------------------------*/
#include "avr-watchdog.h"
#include "AVR/avr-macro.h"
//------------------------------------------------------------------------------------------------
using regs = Watchdog_traits;
//------------------------------------------------------------------------------------------------
#if (defined(WDTCSR) || defined(WDTCR)) && defined(ENABLE_WATCHDOG)
//------------------------------------------------------------------------------------------------
// Startup falls through into .init4; no ordinary function call or return is allowed here.
/**
 * @brief Disable the watchdog during startup.
 * @details Runs in .init3, after Reset captures and clears the reset flags,
 * before data initialization and constructors. Interrupts are already disabled
 * and the zero register is initialized. Falls through to the next startup section
 * without returning.
 * @note The WDTON fuse can prevent software shutdown.
 */
extern "C" void watchdog_early_disable() __attribute__((naked, used, section(".init3")));
void watchdog_early_disable()
{
    if(_SFR_IO_REG_P(regs :: CONTROL))
    {
        __asm__ __volatile__(
            "ldi r24, %[unlock]\n\t"
            "out %[control], r24\n\t"
            "out %[control], __zero_reg__"
            :
            : [control] "I" (_SFR_IO_ADDR(regs :: CONTROL)),
              [unlock] "M" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE)))
            : "r24", "memory"
        );
    }
    else
    {
        __asm__ __volatile__(
            "ldi r24, %[unlock]\n\t"
            "sts %[control], r24\n\t"
            "sts %[control], __zero_reg__"
            :
            : [control] "n" (_SFR_MEM_ADDR(regs :: CONTROL)),
              [unlock] "M" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE)))
            : "r24", "memory"
        );
    }
}
//------------------------------------------------------------------------------------------------
AVR_Watchdog watchdog;    // global object
#endif
//------------------------------------------------------------------------------------------------
/**
 * @brief Configure and start the watchdog, restarting its counter.
 * @param timeout Requested watchdog timeout; actual periods depend on the MCU oscillator.
 * @param mode Reset, interrupt, or interrupt followed by reset; selected explicitly.
 * @param callback Timeout callback of type void (*)(), called in ISR context.
 * nullptr installs no user callback. Each successful call replaces the previous callback
 * on interrupt-capable targets; reset-only targets ignore this parameter.
 * @retval OK Requested configuration written to the watchdog.
 * @retval ERR_BAD_VALUE A 4 s or 8 s timeout was requested without extended-timeout support.
 * @retval ERR_BAD_MODE No backend is available, or the MCU lacks the requested interrupt mode.
 * @details Unsupported requests return before changing hardware or the callback.
 * Configuration and callback replacement preserve the previous interrupt state.
 * Pending watchdog interrupt flags are cleared on interrupt-capable targets.
 * @note Interrupt callbacks require global interrupts to be enabled. In combined mode,
 * hardware clears the interrupt enable when the ISR executes; this driver does not rearm it.
 * @note The WDTON fuse can force reset mode; OK does not verify fuse settings.
 */
ResultCode AVR_Watchdog :: enable(Watchdog_timeout timeout, Watchdog_mode mode, Callback callback)
{
    if constexpr(!regs :: exists)
        return ERR_BAD_MODE;

    if constexpr(!regs :: has_extended_timeout)
    {
        if(timeout == WATCHDOG_TIMEOUT_4S || timeout == WATCHDOG_TIMEOUT_8S)
            return ERR_BAD_VALUE;
    }

    uint8_t value = uint8_t(timeout) & regs :: PRESCALER_MASK;

    if constexpr(regs :: has_extended_timeout)
    {
        if(timeout == WATCHDOG_TIMEOUT_4S || timeout == WATCHDOG_TIMEOUT_8S)
            set_bit(value, regs :: PRESCALER_HIGH);
    }

    switch(mode)
    {
        case WATCHDOG_MODE_RESET:
            set_bit(value, regs :: ENABLE);
            break;

        case WATCHDOG_MODE_INTERRUPT:
            if constexpr(regs :: has_interrupt)
                set_bit(value, regs :: INTERRUPT);
            else
                return ERR_BAD_MODE;
            break;

        case WATCHDOG_MODE_INTERRUPT_RESET:
            if constexpr(regs :: has_interrupt)
                set_bits(value, regs :: ENABLE, regs :: INTERRUPT);
            else
                return ERR_BAD_MODE;
            break;
    }

    if constexpr(regs :: has_interrupt)
        set_bit(value, regs :: INTERRUPT_FLAG);   // W1C

    {
        ATOMIC_BLOCK
        if constexpr(regs :: has_interrupt)
            timeout_callback = callback;
        // Both writes must be adjacent: the change window is four CPU cycles only.
        if(_SFR_IO_REG_P(regs :: CONTROL))
        {
            __asm__ __volatile__(
                "wdr\n\t"
                "out %[control], %[unlock]\n\t"
                "out %[control], %[value]"
                :
                : [control] "I" (_SFR_IO_ADDR(regs :: CONTROL)),
                  [unlock] "r" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE))),
                  [value] "r" (value)
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__(
                "wdr\n\t"
                "sts %[control], %[unlock]\n\t"
                "sts %[control], %[value]"
                :
                : [control] "n" (_SFR_MEM_ADDR(regs :: CONTROL)),
                  [unlock] "r" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE))),
                  [value] "r" (value)
                : "memory"
            );
        }
    }
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disable the watchdog.
 * @details Uses the protected register-write sequence inside an ATOMIC_BLOCK,
 * restoring the previous interrupt state afterward. Leaves the stored callback unchanged.
 * Does nothing when no backend is available.
 * @note The WDTON fuse can prevent software shutdown; this method does not check it.
 */
void AVR_Watchdog :: disable()
{
    if constexpr(!regs :: exists)
        return;
    {
        ATOMIC_BLOCK
        if(_SFR_IO_REG_P(regs :: CONTROL))
        {
            __asm__ __volatile__(
                "wdr\n\t"
                "out %[control], %[unlock]\n\t"
                "out %[control], __zero_reg__"
                :
                : [control] "I" (_SFR_IO_ADDR(regs :: CONTROL)),
                  [unlock] "r" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE)))
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__(
                "wdr\n\t"
                "sts %[control], %[unlock]\n\t"
                "sts %[control], __zero_reg__"
                :
                : [control] "n" (_SFR_MEM_ADDR(regs :: CONTROL)),
                  [unlock] "r" (uint8_t(_bits(regs :: CHANGE_ENABLE, regs :: ENABLE)))
                : "memory"
            );
        }
    }
}
//------------------------------------------------------------------------------------------------
