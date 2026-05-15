/*------------------------------------------------------------------------------------------------
 * console.tpp
 *
 * ATTENTION! This file is included from console.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Writes a null-terminated string followed by CRLF.
 *
 * Sends a RAM-resident string directly to the underlying stream.
 *
 * @param str Pointer to a null-terminated string in RAM.
 */
template <class Stream>
__inline void Console <Stream> :: log(const char *str)
{
    print(str);
    print_ln();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes integer or enum value followed by CRLF.
 *
 * This is a "default" method for logging other unoverloaded types, that
 * expects and supports only
 * - integer types,
 * - enum types.
 *
 * @tparam Type Integer or enum type.
 * @param value Value to print.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: log(Type value)
{
    print(value);
    print_ln();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes pointer's address in hexadecimal form followed by CRLF.
 *
 * Outputs pointer address as:
 * @code
 * 0x1234
 * @endcode
 *
 * @tparam Type Pointer type.
 * @param ptr Pointer value.
 */
 template <class Stream>
template <class Type>
__inline void Console <Stream> :: log(Type *ptr)
{
    static_assert(!is_function <Type> :: value, "Function pointers are not supported.");
    stream.write(_flash("0x"));
    _write_hex <sizeof(uintptr_t) * 2> ((uintptr_t)ptr);
    print_ln();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes integer or enum value in decimal form.
 *
 * Supports:
 * - signed integers,
 * - unsigned integers,
 * - enum types.
 *
 * Conversion is performed without libc formatting functions.
 *
 * @tparam Type Integer or enum type.
 * @param value Value to print.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: print(Type value)
{
    static_assert(is_integer <Type> :: value || is_enum <Type> :: value,
                  "Integer values were expected here.");
    if constexpr(is_enum <Type> :: value)
    {
        _write_int((__underlying_type(Type))value);
    }
    else
    {
        _write_int(value);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes a null-terminated string to the console.
 *
 * Sends the specified string directly to the underlying stream.
 *
 * @param str Pointer to a null-terminated string in RAM.
 */
template <class Stream>
__inline void Console <Stream> :: print(const char *str)
{
    stream.write(str);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes boolean value as text.
 *
 * Output values:
 * - TRUE
 * - FALSE
 *
 * @param value Boolean value.
 */
template <class Stream>
__inline void Console <Stream> :: print(bool value)
{
    if(value)
    {
        stream.write(_flash("TRUE"));
    }
    else
    {
        stream.write(_flash("FALSE"));
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes a null-terminated string from flash (PROGMEM) to the console.
 *
 * Sends a PROGMEM-resident string through the underlying stream
 * directly without copying it into RAM.
 *
 * @param fs Flash string wrapper object.
 */
template <class Stream>
__inline void Console <Stream> :: print(FlashStringWrapper fs)
{
    stream.write(fs);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes floating-point value in decimal form.
 *
 * Output uses fixed-point notation only.
 * Scientific notation is NOT supported.
 *
 * May expose special values (NaN, INF, -INF)
 *
 * @param value Floating-point value.
 * @param align_digits Number of digits after decimal point.
 */
template <class Stream>
__inline void Console <Stream> :: print(float value, const uint8_t align_digits)
{
    _print_floating <float> (value, align_digits);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes floating-point value in decimal form.
 *
 * Output uses fixed-point notation only.
 * Scientific notation is NOT supported.
 *
 * Supports special values (NaN, INF, -INF).
 *
 * @param value Floating-point value.
 * @param align_digits Number of digits after decimal point.
 */
template <class Stream>
__inline void Console <Stream> :: print(double value, const uint8_t align_digits)
{
    _print_floating <double> (value, align_digits);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Internal floating-point formatter.
 *
 * Produces fixed-point decimal output without
 * using libc formatting functions.
 *
 * @tparam Type Floating-point type.
 * @param value Floating-point value.
 * @param align_digits Number of digits after decimal point OR first meaning digit.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: _print_floating(Type value, const uint8_t align_digits)
{
    if(value != value)
    {
        stream.write(_flash("NaN"));
        return;
    }

    if(value == (Type) 1.0 / 0.0)
    {
        stream.write(_flash("INF"));
        return;
    }

    if(value == -(Type) 1.0 / 0.0)
    {
        stream.write(_flash("-INF"));
        return;
    }

    if(value < 0)
    {
        stream.write('-');
        value = -value;
    }

    if(value == 0)
    {
        stream.write('0');
        return;
    }

    int8_t scale = 0;
    uint8_t digit;

    // normalize small values
    if(value < 0.10)
    {
        stream.write("0.");
        value *= 10;
        scale = -1;
        while(value < 0.1)
        {
            value *= 10;
            stream.write('0');
            scale--;
        }
    }

    // round to align_digits
    Type rounding = 0.5;
    for(uint8_t i = 0; i < align_digits; i++)
    {
        rounding /= 10;
    }
    value += rounding;

    // normalize large values
    while(value >= 10.0)
    {
        value /= 10;
        scale++;
    }

    // shift out large values
    while(scale > 0)
    {
        digit = (uint8_t) value;
        value = (value - digit) * 10;
        stream.write('0' + digit);
        scale--;
    }
    digit = (uint8_t) value;
    value = (value - digit) * 10 ;
    stream.write('0' + digit);
    if(scale == 0)
    {
       stream.write('.');
    }

    // shift out decimal digits
    for(uint8_t i = 0; i < align_digits; i++)
    {
        digit = (uint8_t) value;
        value = (value - digit) * 10 ;
        stream.write('0' + digit);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes CRLF sequence.
 *
 * Outputs:
 * @code
 * \r\n
 * @endcode
 */
template <class Stream>
__inline void Console <Stream> :: print_ln()
{
    stream.write(_flash("\r\n"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Clears the terminal screen and resets text attributes.
 *
 * Performs the following actions:
 * - clears the entire screen,
 * - resets ANSI text styles,
 * - moves cursor to home position,
 * - hides the cursor.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: clear()
{
    stream.write(_flash("\x1B[2J"));    // clear screen
    reset_style();
    home();
    hide_cursor();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Clears the current terminal line.
 *
 * Erases the entire current line and moves the cursor
 * to the beginning of the line.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: clear_line()
{
    stream.write(_flash("\x1B[2K\r"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Moves cursor to the home position.
 *
 * Positions the cursor at the top-left corner of the screen.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: home()
{
    stream.write(_flash("\x1B[H"));
}
//------------------------------------------------------------------------------------------------
template <class Stream>
/**
 * @brief Moves cursor to specified screen coordinates.
 *
 * Coordinates are zero-based:
 * - pos = horizontal position,
 * - line = vertical position (line number).
 *
 *
 * @param pos Horizontal cursor position.
 * @param line Vertical cursor position.
 *
 * Requires ANSI-compatible terminal support.
 */
__inline void Console <Stream> :: goto_xy(uint8_t pos, uint8_t line)
{
    stream.write(_flash("\x1B["));
    _write_int(line + 1);
    stream.write(_flash(";"));
    _write_int(pos + 1);
    stream.write(_flash("H"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Hides the terminal cursor.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: hide_cursor()
{
    stream.write(_flash("\x1B[?25l"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Shows the terminal cursor.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: show_cursor()
{
    stream.write(_flash("\x1B[?25h"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enables bold text attribute.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: bold_on()
{
    stream.write(_flash("\x1B[1m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disables bold text attribute.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: bold_off()
{
    stream.write(_flash("\x1B[22m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Enables inverse video mode.
 *
 * Swaps foreground and background colors.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: inverse_on()
{
    stream.write(_flash("\x1B[7m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Disables inverse video mode.
 *
 * Restores normal foreground/background rendering.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: inverse_off()
{
     stream.write(_flash("\x1B[27m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Resets all ANSI text attributes.
 *
 * Clears all active text formatting including:
 * - colors,
 * - bold,
 * - inverse mode,
 * - underline,
 * - other terminal attributes.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: reset_style()
{
     stream.write(_flash("\x1B[0m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Sets foreground text color.
 *
 * Supported color values:
 * - 0 black
 * - 1 red
 * - 2 green
 * - 3 yellow
 * - 4 blue
 * - 5 magenta
 * - 6 cyan
 * - 7 white
 *
 * Only lower 3 bits are used.
 *
 * @param font_color ANSI foreground color index.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: set_color(uint8_t font_color)
{
    stream.write(_flash("\x1B[3"));
    stream.write('0' + (font_color & 0x07));
    stream.write(_flash("m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Sets background text color.
 *
 * Supported color values:
 * - 0 black
 * - 1 red
 * - 2 green
 * - 3 yellow
 * - 4 blue
 * - 5 magenta
 * - 6 cyan
 * - 7 white
 *
 * Only lower 3 bits are used.
 *
 * @param bg_color ANSI background color index.
 *
 * Requires ANSI-compatible terminal support.
 */
template <class Stream>
__inline void Console <Stream> :: set_background(uint8_t bg_color)
{
    stream.write(_flash("\x1B[4"));
    stream.write('0' + (bg_color & 0x07));
    stream.write(_flash("m"));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes integer value in decimal form.
 *
 * Performs conversion without using libc formatting functions.
 *
 * Supports both signed and unsigned integer types and enums.
 *
 * @tparam Type Integer type.
 * @param value Integer value to write.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: _write_int(Type value)
{
    static_assert(is_integer <Type> :: value || is_enum <Type> :: value,
                  "_write_int works with integer types only!");
    char buf[sizeof(Type) * 3];     // mirrored numbers buffer
    uint8_t pos = 0;
    bool negative = false;
    // signed-type check
    if ((Type) - 1 < 0)
    {
        if (value < 0)
        {
            negative = true;
            // avoid overflow on min value
            value = -(value + 1);
            value += 1;
        }
    }
    do
    {
        Type div = value / 10;
        buf[pos++] = '0' + (value - div * 10);
        value = div;
    } while (value);
    // add sign for negative values
    if(negative)
    {
        buf[pos++] = '-';
    }
    // stream out
    while(pos)
    {
        stream.write(buf[--pos]);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes integer value in hexadecimal form.
 *
 * Hex digits are written without leading prefix.
 *
 * If width is zero, full type width is used automatically.
 *
 * @tparam width Fixed hexadecimal width in digits.
 * @tparam Type Integer type.
 * @param value Value to write in hexadecimal form.
 */
template <class Stream>
template < uint8_t width, class Type>
inline void Console <Stream> :: _write_hex(Type value)
{
    constexpr uint8_t digits = width ? width : sizeof(Type) * 2;
    for(int8_t i = digits - 1; i >= 0; --i)
    {
        uint8_t byte = (value >> (i * 4)) & 0x0F;
        stream.write(byte < 10 ? ('0' + byte) : ('A' + byte - 10));
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes named integer value in decimal form.
 *
 * Useful for debugging variables.
 *
 * Output format:
 * @code
 * name=value
 * @endcode
 *
 * Automatically appends CRLF.
 *
 * Pointer types are not allowed.
 *
 * @tparam Type Any integer or enum type.
 * @param some Debug wrapper object.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: log(const DebugDEC <Type> &some)
{
    static_assert(!is_pointer <Type> :: value, "Pointers are not allowed here!");
    stream.write(some.name);
    stream.write(_flash("="));
    _write_int(some.value);
    print_ln();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes named integer value in hexadecimal form.
 *
 * Useful for debugging registers.
 *
 * Output format:
 * @code
 * name=0xXX
 * @endcode
 *
 * Automatically appends CRLF.
 *
 * Pointer types are not allowed.
 *
 * @tparam Type Integer type.
 * @param some Debug wrapper object.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: log(const DebugHEX <Type> &some)
{
    static_assert(!is_pointer <Type> :: value, "Pointers are not allowed here!");
    stream.write(some.name);
    stream.write(_flash("=0x"));
    _write_hex(some.value);
    print_ln();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Dumps RAM contents in hexadecimal form.
 *
 * Produces formatted hexadecimal memory dump.
 *
 * Optional ASCII visualization may be enabled.
 *
 * @param ptr Pointer to RAM region.
 * @param size Number of bytes to dump.
 * @param show_ascii Enables ASCII visualization (disabled by-default).
 *
 * @note When ASCII visualization is enabled,
 *       dump output is aligned to full line width.
 */
template <class Stream>
template <class Type>
__inline void Console <Stream> :: dump_mem(Type *ptr, size_t size, bool show_ascii)
{
    const uint8_t* p = reinterpret_cast<const uint8_t*>(ptr);
    _print_dump <MemoryArea :: RAM> (p, size, show_ascii);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Dumps RAM contents in hexadecimal form.
 *
 * Produces formatted hexadecimal memory dump.
 * Inline const-value overload.
 *
 * Optional ASCII visualization may be enabled.
 *
 * @param ptr Pointer to RAM region.
 * @param size Number of bytes to dump.
 * @param show_ascii Enables ASCII visualization (disabled by-default).
 *
 * @note When ASCII visualization is enabled,
 *       dump output is aligned to full line width.
 */
template <class Stream>
__inline void Console <Stream> :: dump_mem(const uint8_t *ptr, size_t size, bool show_ascii)
{
    _print_dump <MemoryArea :: RAM> (ptr, size, show_ascii);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Dumps FLASH contents in hexadecimal form.
 *
 * Reads memory using pgm_read_byte().
 *
 * Optional ASCII visualization may be enabled.
 *
 * @param ptr Pointer to FLASH region.
 * @param size Number of bytes to dump.
 * @param show_ascii Enables ASCII visualization (disabled by-default).
 *
 * @note When ASCII visualization is enabled,
 *       dump output is aligned to full line width.
 */
template <class Stream>
__inline void Console <Stream> :: dump_flash(PGM_P ptr, size_t size, bool show_ascii)
{
    _print_dump <MemoryArea :: FLASH> (ptr, size, show_ascii);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Dumps EEPROM contents in hexadecimal form.
 *
 * Reads memory using eeprom_read_byte().
 *
 * Optional ASCII visualization may be enabled.
 *
 * @param ptr EEPROM address pointer.
 * @param size Number of bytes to dump.
 * @param show_ascii Enables ASCII visualization (disabled by-default).
 *
 * @note When ASCII visualization is enabled,
 *       dump output is aligned to full line width.
 */
template <class Stream>
__inline void Console <Stream> :: dump_eeprom(uint8_t *ptr, size_t size, bool show_ascii)
{
    _print_dump <MemoryArea :: EEPROM> (ptr, size, show_ascii);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Internal generic memory dump implementation.
 *
 * Specialized at compile time for
 * - RAM,
 * - FLASH,
 * - EEPROM.
 *
 * Produces formatted hexadecimal dump with optional
 * ASCII visualization.
 *
 * @tparam area Target memory region type.
 * @param ptr Memory region pointer.
 * @param size Number of bytes to dump.
 * @param show_ascii Enables ASCII visualization.
 *
 * @note When ASCII visualization is enabled,
 *       dump output is aligned to full line width.
 */
template <class Stream>
template <MemoryArea area>
__inline void Console <Stream> :: _print_dump(const void *ptr, size_t size, bool show_ascii)
{
    constexpr uint8_t addr_width = []() constexpr
    {
        if constexpr(area == MemoryArea :: FLASH)
        {
            return
                (FLASHEND <= 0xFF)       ? 2 :
                (FLASHEND <= 0xFFFF)     ? 4 :
                (FLASHEND <= 0xFFFFFF)   ? 6 :
                                           8;
        }
        else if constexpr(area == MemoryArea :: EEPROM)
        {
            return
                (E2END <= 0xFF)       ? 2 :
                (E2END <= 0xFFFF)     ? 4 :
                (E2END <= 0xFFFFFF)   ? 6 :
                                        8;
        }
        else
        {
            return
                (RAMEND <= 0xFF)       ? 2 :
                (RAMEND <= 0xFFFF)     ? 4 :
                (RAMEND <= 0xFFFFFF)   ? 6 :
                                         8;
        }
    }();
    constexpr uint8_t bytes_per_line = 16;
    char ascii[]="|................|\r\n";
    size_t index;
    uint8_t ascii_pos;
    if(!size)
    {
        return;
    }
    // align size to full-line border for better ascii output
    size = show_ascii ? ((size + bytes_per_line - 1) / bytes_per_line) * bytes_per_line : size;

    for(size_t k = 0; k <= (size - 1) / bytes_per_line; k++)
    {
        _write_hex <addr_width> ((uintptr_t)(ptr) + k * bytes_per_line);
        stream.write(_flash(": "));
        ascii_pos = 1;  // skip formatting chars, see ascii[] definition
        for(size_t i = 0; i < bytes_per_line; i++)
        {
            index = k * bytes_per_line + i;
            if(index < size)
            {
                uint8_t val = 0;
                if constexpr(area == MemoryArea :: RAM)
                {
                    val = ((const uint8_t*)ptr)[index];
                }
                else if constexpr(area == MemoryArea :: FLASH)
                {
                    val = pgm_read_byte((const uint8_t*)ptr + index);
                }
                else if constexpr(area == MemoryArea :: EEPROM)
                {
                   val = eeprom_read_byte((const uint8_t*)ptr + index);
                }
                _write_hex(val);
                if(show_ascii)
                {
                    ascii[ascii_pos++] = (val >= 32 && val <= 126) ? val : '.';
                }
            }
            else
            {
                stream.write(_flash("  "));
            }
            stream.write(' ');
        }
        if(show_ascii)
        {
            stream.write(ascii);
        }
        else
        {
            print_ln();
        }
    }
}
//------------------------------------------------------------------------------------------------





