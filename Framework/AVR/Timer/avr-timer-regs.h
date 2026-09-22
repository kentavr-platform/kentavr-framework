/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-timer-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_TIMER_REGS_H
#define AVR_TIMER_REGS_H
//------------------------------------------------------------------------------------------------
#define NONE 0
//------------------------------------------------------------------------------------------------
template <uint8_t N>
struct Timer_regs
{
    using Type                                  = uint8_t;
    static constexpr bool exists                = false;
    static constexpr bool has_compare_c         = false;
    static constexpr bool has_capture           = false;
    static constexpr bool has_external_clock    = false;
    static constexpr bool has_extended_prescaler = false;
    static constexpr bool has_async_clock       = false;
    static constexpr bool has_icr_top           = false;
    static constexpr uint8_t wgm_bits           = 0;
};
#define DEFINE_TIMER_REGS(N, _VALUE_TYPE, _WGM_BITS,                                    \
                          _HAS_COMPARE_C, _HAS_CAPTURE, _HAS_EXTERNAL_CLOCK,            \
                          _HAS_EXTENDED_PRESCALER, _HAS_ASYNC_CLOCK, _HAS_ICR_TOP,      \
                          _CONTROL_A, _CONTROL_B, _FORCE_CONTROL, _INT_MASK, _INT_FLAGS,\
                          _COUNTER, _COMPARE_A, _COMPARE_B, _COMPARE_C, _CAPTURE,       \
                          _CTC_BIT,                                                     \
                          _COMPARE_A_INTERRUPT_BIT, _COMPARE_A_FLAG_BIT,                \
                          _COMPARE_B_INTERRUPT_BIT, _COMPARE_B_FLAG_BIT,                \
                          _COMPARE_C_INTERRUPT_BIT, _COMPARE_C_FLAG_BIT,                \
                          _CAPTURE_INTERRUPT_BIT, _CAPTURE_FLAG_BIT,                    \
                          _CAPTURE_EDGE_BIT, _CAPTURE_NOISE_CANCELER_BIT,               \
                          _OVERFLOW_INTERRUPT_BIT, _OVERFLOW_FLAG_BIT,                  \
                          _FORCE_A_BIT, _FORCE_B_BIT, _FORCE_C_BIT,                     \
                          _CLOCK_BIT_0, _CLOCK_BIT_1, _CLOCK_BIT_2)                     \
template <>                                                                             \
struct Timer_regs <N>                                                                   \
{                                                                                       \
    using Type = _VALUE_TYPE;                                                           \
    static constexpr bool exists = true;                                                \
                                                                                        \
    static inline volatile uint8_t& CONTROL_A = _CONTROL_A;                             \
    static inline volatile uint8_t& CONTROL_B = _CONTROL_B;                             \
    static inline volatile uint8_t& FORCE_CONTROL = _FORCE_CONTROL;                     \
    static inline volatile Type& COUNTER      = _COUNTER;                               \
    static inline volatile Type& COMPARE_A    = _COMPARE_A;                             \
    static inline volatile Type& COMPARE_B    = _COMPARE_B;                             \
    static inline volatile Type& COMPARE_C    = _COMPARE_C;                             \
    static inline volatile Type& CAPTURE      = _CAPTURE;                               \
    static inline volatile uint8_t& INT_MASK  = _INT_MASK;                              \
    static inline volatile uint8_t& INT_FLAGS = _INT_FLAGS;                             \
                                                                                        \
    static constexpr uint32_t max_count       = (uint32_t(1) << (sizeof(Type) * 8));    \
    static constexpr bool ctc_mode_in_b       = sizeof(Type) > 1;                       \
    static constexpr uint8_t ctc_bit          = _CTC_BIT;                               \
    static constexpr uint8_t compare_a_interrupt_bit = _COMPARE_A_INTERRUPT_BIT;        \
    static constexpr uint8_t compare_a_flag_bit      = _COMPARE_A_FLAG_BIT;             \
    static constexpr uint8_t compare_b_interrupt_bit = _COMPARE_B_INTERRUPT_BIT;        \
    static constexpr uint8_t compare_b_flag_bit      = _COMPARE_B_FLAG_BIT;             \
    static constexpr uint8_t compare_c_interrupt_bit = _COMPARE_C_INTERRUPT_BIT;        \
    static constexpr uint8_t compare_c_flag_bit      = _COMPARE_C_FLAG_BIT;             \
    static constexpr uint8_t capture_interrupt_bit   = _CAPTURE_INTERRUPT_BIT;          \
    static constexpr uint8_t capture_flag_bit        = _CAPTURE_FLAG_BIT;               \
    static constexpr uint8_t capture_edge_bit        = _CAPTURE_EDGE_BIT;               \
    static constexpr uint8_t capture_noise_canceler_bit = _CAPTURE_NOISE_CANCELER_BIT;  \
    static constexpr uint8_t overflow_interrupt_bit  = _OVERFLOW_INTERRUPT_BIT;         \
    static constexpr uint8_t overflow_flag_bit       = _OVERFLOW_FLAG_BIT;              \
    static constexpr uint8_t force_a_bit      = _FORCE_A_BIT;                           \
    static constexpr uint8_t force_b_bit      = _FORCE_B_BIT;                           \
    static constexpr uint8_t force_c_bit      = _FORCE_C_BIT;                           \
    static constexpr uint8_t clock_bit_0      = _CLOCK_BIT_0;                           \
    static constexpr uint8_t clock_bit_1      = _CLOCK_BIT_1;                           \
    static constexpr uint8_t clock_bit_2      = _CLOCK_BIT_2;                           \
                                                                                        \
    static constexpr uint8_t wgm_bits         = _WGM_BITS;                              \
    static constexpr bool has_compare_c       = _HAS_COMPARE_C;                         \
    static constexpr bool has_capture         = _HAS_CAPTURE;                           \
    static constexpr bool has_external_clock  = _HAS_EXTERNAL_CLOCK;                    \
    static constexpr bool has_extended_prescaler = _HAS_EXTENDED_PRESCALER;             \
    static constexpr bool has_async_clock     = _HAS_ASYNC_CLOCK;                       \
    static constexpr bool has_icr_top         = _HAS_ICR_TOP;                           \
};
//------------------------------------------------------------------------------------------------
#if !defined(TIMSK0) && defined(TIMSK)
  #define TIMSK0 TIMSK
#endif
//------------------------------------------------------------------------------------------------
#if !defined(TIFR0) && defined(TIFR)
  #define TIFR0 TIFR
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM01) && defined(OCR0B)
  #if defined(TCCR0C)
    #define TIMER0_FORCE_CONTROL TCCR0C
  #else
    #define TIMER0_FORCE_CONTROL TCCR0B
  #endif

  #if defined(TCNT0H)
    #define TIMER0_TYPE uint16_t
    #define TIMER0_NOREG _SFR_IO16(NONE)
  #else
    #define TIMER0_TYPE uint8_t
    #define TIMER0_NOREG _SFR_IO8(NONE)
  #endif

DEFINE_TIMER_REGS(0,        // N
                  TIMER0_TYPE,
                  3,        // WGM_BITS
                  false,    // COMP_C
                  false,    // CAPTURE
                  true,     // EXT_CLK
                  false,    // EXTENDED_PRESCALER
                  false,    // ASYNC_CLOCK
                  false,    // HAS_ICR_TOP
                  TCCR0A, TCCR0B, TIMER0_FORCE_CONTROL, TIMSK0, TIFR0,
                  TCNT0, OCR0A, OCR0B, TIMER0_NOREG, TIMER0_NOREG, WGM01,
                  OCIE0A, OCF0A, OCIE0B, OCF0B, NONE, NONE,
                  NONE, NONE, NONE, NONE, TOIE0, TOV0,
                  FOC0A, FOC0B, NONE,
                  CS00, CS01, CS02);
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM12) && defined(OCR1B) && defined(ICR1)
  #if defined(TCCR1C)
    #define TIMER1_FORCE_CONTROL TCCR1C
  #else
    #define TIMER1_FORCE_CONTROL TCCR1A
  #endif

  #if defined(TCNT1H)
    #define TIMER1_TYPE uint16_t
  #else
    #define TIMER1_TYPE uint8_t
  #endif

  #if defined(OCR1C)
    #define TIMER1_HAS_COMPARE_C true
    #define TIMER1_FORCE_C FOC1C
  #else
    #define TIMER1_HAS_COMPARE_C false
    #define TIMER1_FORCE_C NONE
    #define OCR1C   _SFR_IO16(NONE)
    #define OCIE1C  NONE
    #define OCF1C   NONE
  #endif

  DEFINE_TIMER_REGS(1,                    // N
                    TIMER1_TYPE,
                    4,                    // WGM_BITS
                    TIMER1_HAS_COMPARE_C, // COMP_C
                    true,                 // CAPTURE
                    true,                 // EXT_CLK
                    false,                // EXTENDED_PRESCALER
                    false,                // ASYNC_CLOCK
                    true,                 // HAS_ICR_TOP
                    TCCR1A, TCCR1B, TIMER1_FORCE_CONTROL, TIMSK1, TIFR1,
                    TCNT1, OCR1A, OCR1B, OCR1C, ICR1, WGM12,
                    OCIE1A, OCF1A, OCIE1B, OCF1B, OCIE1C, OCF1C,
                    ICIE1, ICF1, ICES1, ICNC1, TOIE1, TOV1,
                    FOC1A, FOC1B, TIMER1_FORCE_C,
                    CS10, CS11, CS12);
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM21) && defined(OCR2B)
  #if defined(ASSR) && defined(AS2)
    #define TIMER2_HAS_EXTENDED_PRESCALER true
    #define TIMER2_HAS_ASYNC_CLOCK true
  #else
    #define TIMER2_HAS_EXTENDED_PRESCALER false
    #define TIMER2_HAS_ASYNC_CLOCK false
  #endif

  #if defined(TCCR2C)
    #define TIMER2_FORCE_CONTROL TCCR2C
  #else
    #define TIMER2_FORCE_CONTROL TCCR2B
  #endif

  #if defined(TCNT2H)
    #define TIMER2_TYPE uint16_t
    #define TIMER2_NOREG _SFR_IO16(NONE)
  #else
    #define TIMER2_TYPE uint8_t
    #define TIMER2_NOREG _SFR_IO8(NONE)
  #endif

  DEFINE_TIMER_REGS(2,        // N
                    TIMER2_TYPE,
                    3,        // WGM_BITS
                    false,    // COMP_C
                    false,    // CAPTURE
                    false,    // EXT_CLK
                    TIMER2_HAS_EXTENDED_PRESCALER,
                    TIMER2_HAS_ASYNC_CLOCK,
                    false,    // HAS_ICR_TOP
                    TCCR2A, TCCR2B, TIMER2_FORCE_CONTROL, TIMSK2, TIFR2,
                    TCNT2, OCR2A, OCR2B, TIMER2_NOREG, TIMER2_NOREG, WGM21,
                    OCIE2A, OCF2A, OCIE2B, OCF2B, NONE, NONE,
                    NONE, NONE, NONE, NONE, TOIE2, TOV2,
                    FOC2A, FOC2B, NONE,
                    CS20, CS21, CS22);
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM32) && defined(OCR3B) && defined(ICR3)
  #if defined(TCCR3C)
    #define TIMER3_FORCE_CONTROL TCCR3C
  #else
    #define TIMER3_FORCE_CONTROL TCCR3A
  #endif

  #if defined(TCNT3H)
    #define TIMER3_TYPE uint16_t
  #else
    #define TIMER3_TYPE uint8_t
  #endif

  #if defined(OCR3C)
    #define TIMER3_HAS_COMPARE_C true
    #define TIMER3_FORCE_C FOC3C
  #else
    #define TIMER3_HAS_COMPARE_C false
    #define TIMER3_FORCE_C NONE
    #define OCR3C   _SFR_IO16(NONE)
    #define OCIE3C  NONE
    #define OCF3C   NONE
  #endif

  DEFINE_TIMER_REGS(3,                    // N
                    TIMER3_TYPE,
                    4,                    // WGM_BITS
                    TIMER3_HAS_COMPARE_C, // COMP_C
                    true,                 // CAPTURE
                    true,                 // EXT_CLK
                    false,                // EXTENDED_PRESCALER
                    false,                // ASYNC_CLOCK
                    true,                 // HAS_ICR_TOP
                    TCCR3A, TCCR3B, TIMER3_FORCE_CONTROL, TIMSK3, TIFR3,
                    TCNT3, OCR3A, OCR3B, OCR3C, ICR3, WGM32,
                    OCIE3A, OCF3A, OCIE3B, OCF3B, OCIE3C, OCF3C,
                    ICIE3, ICF3, ICES3, ICNC3, TOIE3, TOV3,
                    FOC3A, FOC3B, TIMER3_FORCE_C,
                    CS30, CS31, CS32);
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM42) && defined(OCR4B) && defined(ICR4)
  #if defined(TCCR4C)
    #define TIMER4_FORCE_CONTROL TCCR4C
  #else
    #define TIMER4_FORCE_CONTROL TCCR4A
  #endif

  #if defined(TCNT4H)
    #define TIMER4_TYPE uint16_t
  #else
    #define TIMER4_TYPE uint8_t
  #endif

  #if defined(OCR4C)
    #define TIMER4_HAS_COMPARE_C true
    #define TIMER4_FORCE_C FOC4C
  #else
    #define TIMER4_HAS_COMPARE_C false
    #define TIMER4_FORCE_C NONE
    #define OCR4C   _SFR_IO16(NONE)
    #define OCIE4C  NONE
    #define OCF4C   NONE
  #endif

  DEFINE_TIMER_REGS(4,                    // N
                    TIMER4_TYPE,
                    4,                    // WGM_BITS
                    TIMER4_HAS_COMPARE_C, // COMP_C
                    true,                 // CAPTURE
                    true,                 // EXT_CLK
                    false,                // EXTENDED_PRESCALER
                    false,                // ASYNC_CLOCK
                    true,                 // HAS_ICR_TOP
                    TCCR4A, TCCR4B, TIMER4_FORCE_CONTROL, TIMSK4, TIFR4,
                    TCNT4, OCR4A, OCR4B, OCR4C, ICR4, WGM42,
                    OCIE4A, OCF4A, OCIE4B, OCF4B, OCIE4C, OCF4C,
                    ICIE4, ICF4, ICES4, ICNC4, TOIE4, TOV4,
                    FOC4A, FOC4B, TIMER4_FORCE_C,
                    CS40, CS41, CS42);
#endif
//------------------------------------------------------------------------------------------------
#if defined(WGM52) && defined(OCR5B) && defined(ICR5)
  #if defined(TCCR5C)
    #define TIMER5_FORCE_CONTROL TCCR5C
  #else
    #define TIMER5_FORCE_CONTROL TCCR5A
  #endif

  #if defined(TCNT5H)
    #define TIMER5_TYPE uint16_t
  #else
    #define TIMER5_TYPE uint8_t
  #endif

  #if defined(OCR5C)
    #define TIMER5_HAS_COMPARE_C true
    #define TIMER5_FORCE_C FOC5C
  #else
    #define TIMER5_HAS_COMPARE_C false
    #define TIMER5_FORCE_C NONE
    #define OCR5C   _SFR_IO16(NONE)
    #define OCIE5C  NONE
    #define OCF5C   NONE
  #endif

  DEFINE_TIMER_REGS(5,                    // N
                    TIMER5_TYPE,
                    4,                    // WGM_BITS
                    TIMER5_HAS_COMPARE_C, // COMP_C
                    true,                 // CAPTURE
                    true,                 // EXT_CLK
                    false,                // EXTENDED_PRESCALER
                    false,                // ASYNC_CLOCK
                    true,                 // HAS_ICR_TOP
                    TCCR5A, TCCR5B, TIMER5_FORCE_CONTROL, TIMSK5, TIFR5,
                    TCNT5, OCR5A, OCR5B, OCR5C, ICR5, WGM52,
                    OCIE5A, OCF5A, OCIE5B, OCF5B, OCIE5C, OCF5C,
                    ICIE5, ICF5, ICES5, ICNC5, TOIE5, TOV5,
                    FOC5A, FOC5B, TIMER5_FORCE_C,
                    CS50, CS51, CS52);
#endif
//------------------------------------------------------------------------------------------------
#endif
