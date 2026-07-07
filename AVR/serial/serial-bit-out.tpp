/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: serial-bit-out.tpp
 *
 * WARNING! This file is included from serial-bit-out.h and must NOT be built.
//----------------------------------------------------------------------------------------------*/
/**
 * @brief Initializes TX pin for output.
 *
 * Configures the GPIO pin as output and sets initial idle state to HIGH,
 * as required by UART protocol.
 *
 * @note Line idle state is logic HIGH.
 * @note No runtime configuration of baud rate is performed; all timing
 *       is compile-time fixed.
 */
template <class pin, uint32_t baud>
SerialBitOut <pin, baud> :: SerialBitOut()
{
    static_assert(baud >= 50,  "Baud rate too low");
    static_assert(baud <= F_CPU / _bit_cycles, "Baud rate is too high for this F_CPU");
    GPIO <pin> :: set_mode(OUTPUT_HIGH);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmits a single byte via SerialBitOut.
 *
 * Sends one start bit, 8 data bits (LSB first), and one stop bit.
 * Execution time is deterministic and depends only on F_CPU and baud.
 *
 * @param data Byte to transmit.
 *
 * @note This function is inlined for zero-call overhead.
 */
template <class pin, uint32_t baud>
void SerialBitOut <pin, baud> :: write(uint8_t data)
{
    ATOMIC_BLOCK
    {
        _write_char(data);
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmits a null-terminated string from RAM via SerialBitOut.
 *
 *
 * @param str Pointer to null-terminated ASCII string in RAM.
 *
 * @note No buffering is used.
 * @note Timing is strictly serial and blocking.
 */
template <class pin, uint32_t baud>
void SerialBitOut <pin, baud> :: write(const char *str)
{
    ATOMIC_BLOCK
    {
        while(*str)
        {
            _write_char(*str++);
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmits a null-terminated string from RAM via SerialBitOut.
 *
 * Alias for write(const char*) because SerialBitOut is already blocking.
 *
 * @param str Pointer to null-terminated ASCII string in RAM.
 */
template <class pin, uint32_t baud>
void SerialBitOut <pin, baud> :: write_all(const char *str)
{
    write(str);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmits a null-terminated string stored in flash (PROGMEM) via SerialBitOut.
 *
 * Reads characters from program memory and transmits them via SerialBitOut.
 *
 * Entire transmission is wrapped in atomic block to prevent interrupt
 * interference and maintain strict timing requirements.
 *
 * @param fs Flash string wrapper containing pointer to PROGMEM string.
 *
 * @note No buffering is used.
 * @note Timing is strictly serial and blocking.
 */
template <class pin, uint32_t baud>
void SerialBitOut <pin, baud> :: write(FlashStringWrapper fs)
{
    ATOMIC_BLOCK
    {
        PGM_P ptr = fs.str;
        char ch;
        while((ch = pgm_read_byte(ptr++)))
        {
            _write_char(ch);
        }
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Transmits a single data bit using cycle-optimized branch logic.
 *
 * This macro expands to inline assembly that encodes one TX bit period.
 * It uses branch-based timing (sbrc + rjmp) to differentiate between
 * logic 0 and logic 1 timing paths. Both branches takes exact 8 cycles.
 *
 * TIMING CONTRACT:
 * - Each bit consumes exactly 8+ CPU cycles
 * - Instruction order must not be modified
 * - Compiler optimizations must preserve inline ASM blocks
 * - Designed for AVR core deterministic execution
 *
 * @param N Bit index (0..7)
 *
 * @warning Do not modify instruction order or spacing.
 */
#define SEND_DATA_BIT(N)                                \
asm volatile                                            \
(             /* branch cycles count:   ONE ZERO */     \
    "sbrc %[data], " #N "   \n\t"   /*   1   2   */     \
    "rjmp .+8               \n\t"   /*   2   0   */     \
    "nop                    \n\t"   /*   0   1   */     \
    "nop                    \n\t"   /*   0   1   */     \
    "cbi  %[port], %[pin]   \n\t"   /*   0   2_  */     \
    "rjmp .+8               \n\t"   /*   0   2   */     \
    "nop                    \n\t"   /*   1   0   */     \
    "sbi  %[port], %[pin]   \n\t"   /*   2_  0   */     \
    "nop                    \n\t"   /*   1   0   */     \
    "nop                    \n\t"   /*   1   0   */     \
    :                     /* Summary:    8   8   */     \
    : [port] "I" (pin :: PORT),                         \
      [pin]  "I" (pin :: BIT),                          \
      [data] "r" (data)                                 \
);                                                      \
delay_cycles(_bit_delay);
//------------------------------------------------------------------------------------------------
/**
 * @brief Low-level character transmission routine.
 *
 * Implements full frame:
 * - 1 start bit (LOW)
 * - 8 data bits (LSB first)
 * - 1 stop bit (HIGH)
 *
 * Bit timing is implemented via inline assembly with cycle-accurate
 * delays tuned for F_CPU and baud rate.
 *
 * @param data Byte to transmit.
 *
 * @warning This function is highly timing-sensitive.
 *          Any modification requires full re-verification of ASM timing.
 */
template <class pin, uint32_t baud>
__inline void SerialBitOut <pin, baud> :: _write_char(uint8_t data)
{
    asm volatile
    (
        // START BIT
        "cbi %[port], %[pin]      \n\t"
        "nop                      \n\t"
        "nop                      \n\t"
        :
        : [port] "I" (pin :: PORT),
          [pin]  "I" (pin :: BIT)
    );
    delay_cycles(_bit_delay);
    SEND_DATA_BIT(0);
    SEND_DATA_BIT(1);
    SEND_DATA_BIT(2);
    SEND_DATA_BIT(3);
    SEND_DATA_BIT(4);
    SEND_DATA_BIT(5);
    SEND_DATA_BIT(6);
    SEND_DATA_BIT(7);
    asm volatile
    (
        // stop-bit
        "nop                    \n\t"
        "nop                    \n\t"
        "nop                    \n\t"
        "nop                    \n\t"
        "sbi  %[port], %[pin]   \n\t"
        :
        : [port] "I" (pin :: PORT),
          [pin]  "I" (pin :: BIT)
    );
    delay_cycles(_bit_delay);
}
//------------------------------------------------------------------------------------------------

