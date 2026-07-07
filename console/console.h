/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: console.h
//----------------------------------------------------------------------------------------------*/
/**
 * @file console.h
 * @brief Lightweight ANSI-capable console utility for embedded systems.
 *
 * Multiple independent Console instances may coexist simultaneously
 * and operate independently over different stream interfaces.
 *
 * Provides formatted text output over arbitrary stream transport interface.
 *
 * Designed for resource-constrained embedded targets.
 *
 * Suitable for
 * - building terminal interfaces,
 * - building embedded command shells,
 * - debugging output.
 *
 * Supports:
 * - plain values through print() / log(),
 * - pointer addresses,
 * - named debug wrappers VAR(...) and REG(...),
 * - terminal control sequences,
 * - RAM / FLASH / EEPROM memory dumps.
 *
 * Values are normalized through console_value() function before formatting.
 * Unsupported object values are printed as "Object" or "Object(TypeName)"
 * when console_type_name() is provided by the corresponding type module.
 *
 * Characteristics:
 * - no dynamic allocation,
 * - no STD,
 * - no STL,
 * - no libc or other dependencies,
 * - compile-time type checking,
 * - stream-oriented architecture.
 *
 * The Stream transport should provide the following methods:
 * @code
 * write(char)
 * write(const char *)
 * write(FlashStringWrapper)
 * @endcode
 *
 * Memory dump methods also require blocking line output and TX drain support:
 * @code
 * write_all(const char *)
 * tx_wait()
 * @endcode
 *
 * Typical usage:
 *
 * @code
 * // init transport interfaces first
 * UART0 console_transport;
 * console_transport.init(2000000);
 *
 * OR
 *
 * SerialBitOut <D1, 2000000> console_transport;
 *
 * // then declare console(s)
 * Console console(console_transport);
 *
 * // and start using (see class methods for more information)
 * console.clear();
 * console.log(REG(SREG));
 * console.print(_flash("SOME TEXT"));  // RAM usage economy for literals
 * ...
 * @endcode
 *
 * ANSI-related methods require compatible terminal support.
 *
 *
 * @note Disabled console mode
 *
 * When console is instantiated without a stream, it is completely disabled
 * at run-time and almost completely cleared from code while all the methods
 * calls are still supported. This mode is useful for disabling debug outputs
 * without changing user code.
 *
 * Example:
 *
 * @code
 * #ifdef DEBUG
 *   SerialBitOut <D1, 2000000> debug_stream;
 *   Console console(debug_stream);
 * #else
 *   Console console;   // creates no-output console
 * #endif
 * ...
 * console.clear();
 * console.log(_flash("DEBUG READY"));
 * ...
 * @endcode
 *
 * @warning Use Console console; or Console console{}; for a no-output console.
 * Console console(); declares a function, not an object!
 *
 * @warning Disabled console mode suppresses output and formatting code,
 * but arguments passed to methods may still be evaluated by C++ rules.
 * Avoid side-effect or expensive expressions in debug-only calls when
 * they must disappear completely.
 */
 //------------------------------------------------------------------------------------------------
#ifndef CONSOLE_H
#define CONSOLE_H
//------------------------------------------------------------------------------------------------
#include <limits.h>
#include <avr/eeprom.h>
//------------------------------------------------------------------------------------------------
enum class MemoryArea : uint8_t
{
    RAM,
    FLASH,
    EEPROM
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Embedded text console over arbitrary stream transport interface.
 *
 * Provides lightweight formatted output,
 * ANSI terminal control and debugging utilities.
 *
 * The class does not use global state or dynamic allocation.
 *
 * @tparam Stream Output stream implementation.
 */
template <class Stream = _nostream>
class Console
{
public:
    Console() : stream(__nostream()) {};
    explicit    Console(Stream& stream) : stream(stream) {};
    //          writers
    void        print(bool value);
    void        print(const char *str);
    void        print(float value, const uint8_t align_digits = 3);
    void        print(double value, const uint8_t align_digits = 3);
    void        print(FlashStringWrapper fs);
    template <class Type> void print(const Type *ptr);      // writer for pointers
    template <class Type> void print(const Type &value);    // default writer (for variable integers)
    void        print_ln();
    //          decorators
    void        clear();
    void        clear_line();
    void        home();
    void        goto_xy(uint8_t pos, uint8_t line);
    void        hide_cursor();
    void        show_cursor();
    void        set_color(uint8_t fg);
    void        set_background(uint8_t bg);
    void        bold_on();
    void        bold_off();
    void        inverse_on();
    void        inverse_off();
    void        reset_style();
    //          debugging methods
    void        log(const char *str);
    template <class Type> void log(const Type *ptr);
    template <class Type> void log(const Type &value);
    template <class Type> void log(const DebugDEC <Type> &some);
    template <class Type> void log(const DebugHEX <Type> &some);
    void        dump_mem(const uint8_t *ptr, size_t size, bool show_ascii = false);
    template <class Type> void dump_mem(Type *ptr, size_t size, bool show_ascii = false);
    void        dump_flash(PGM_P ptr, size_t size, bool show_ascii = false);
    void        dump_eeprom(uint8_t *ptr, size_t size, bool show_ascii = false);
    void        check_result(ResultCode code, bool show_OK = true);
private:
    Stream      &stream;
    static Stream &__nostream() { static Stream stream; return stream; }
    template <class Type> void _print_floating(Type value, const uint8_t align_digits);
    template <MemoryArea> void _print_dump(const void *ptr, size_t size, bool show_ascii);
    template <class Type> void _write_int(Type value);
    template <uint8_t width = 0, class Type> void _write_hex(Type value);
};
//------------------------------------------------------------------------------------------------
template <class Stream> Console(Stream &) -> Console<Stream>;
Console() -> Console<>;
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(Console);
//------------------------------------------------------------------------------------------------
#include "console.tpp"
//------------------------------------------------------------------------------------------------
#endif // CONSOLE_H
