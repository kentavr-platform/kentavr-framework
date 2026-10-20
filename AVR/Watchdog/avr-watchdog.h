/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-watchdog.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_WATCHDOG_H
#define AVR_WATCHDOG_H
//------------------------------------------------------------------------------------------------
#include "core.h"
#include "config.h"
#include "avr-watchdog-regs.h"
//------------------------------------------------------------------------------------------------
enum Watchdog_timeout
{
    WATCHDOG_TIMEOUT_15MS  = 0,
    WATCHDOG_TIMEOUT_30MS  = 1,
    WATCHDOG_TIMEOUT_60MS  = 2,
    WATCHDOG_TIMEOUT_120MS = 3,
    WATCHDOG_TIMEOUT_250MS = 4,
    WATCHDOG_TIMEOUT_500MS = 5,
    WATCHDOG_TIMEOUT_1S    = 6,
    WATCHDOG_TIMEOUT_2S    = 7,
    WATCHDOG_TIMEOUT_4S    = 8,
    WATCHDOG_TIMEOUT_8S    = 9
};
//------------------------------------------------------------------------------------------------
enum Watchdog_mode
{
    WATCHDOG_MODE_RESET           = 0, // reset on timeout
    WATCHDOG_MODE_INTERRUPT       = 1, // interrupt on each timeout
    WATCHDOG_MODE_INTERRUPT_RESET = 2  // interrupt on the first timeout, reset on the second timeout
};
//------------------------------------------------------------------------------------------------
struct Watchdog_dispatcher;
//------------------------------------------------------------------------------------------------
class AVR_Watchdog
{
public:
    using Callback = void (*)();
    static ResultCode enable(Watchdog_timeout timeout,
                             Watchdog_mode mode,
                             Callback callback = nullptr);
    static void disable();
    static __inline void kick()
    {
        if constexpr(Watchdog_traits :: exists)
            __asm__ __volatile__("wdr");
    }
private:
    inline static Callback timeout_callback = nullptr;
    static void interrupt()  { if(timeout_callback) timeout_callback(); }
    friend struct Watchdog_dispatcher;
};
#ifdef ENABLE_WATCHDOG
    extern AVR_Watchdog watchdog;

    #if defined(ISR_HANDLERS_MODULE) && defined(WATCHDOG_HAS_INTERRUPT)
        struct Watchdog_dispatcher
        {
            static void interrupt() { AVR_Watchdog :: interrupt(); }
        };

        ISR(WDT_vect)
        {
            Watchdog_dispatcher :: interrupt();
        }
    #endif
#endif
//------------------------------------------------------------------------------------------------
#endif
