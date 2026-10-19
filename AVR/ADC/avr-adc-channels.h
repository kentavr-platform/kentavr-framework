/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-adc-channels.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_ADC_CHANNELS_H
#define AVR_ADC_CHANNELS_H
//------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <avr/pgmspace.h>
//------------------------------------------------------------------------------------------------
#if defined(__AVR_ATmega8__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC2_1X         = 2,
    ADC3_1X         = 3,
    ADC4_1X         = 4,
    ADC5_1X         = 5,
    ADC6_1X         = 6,
    ADC7_1X         = 7,
    ADC_GND         = 15,
    ADC_VBG         = 14
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 0..7
    0, 0, 0, 0, 0, 0, 0, 0     // MUX 8..15
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_AREF  = 0x00,
    ADC_REFERENCE_AVCC  = 0x40,
    ADC_REFERENCE_2V56  = 0xC0
};
#elif defined(__AVR_ATtiny85__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC2_1X         = 2,
    ADC3_1X         = 3,
    ADC_GND         = 13,
    ADC_TEMPERATURE = 15,
    ADC_VBG         = 12,

    ADC0_0_1X       = 8,
    ADC0_0_20X      = 9,
    ADC0_1_1X       = 10,
    ADC0_1_20X      = 11,
    ADC2_2_1X       = 4,
    ADC2_2_20X      = 5,
    ADC2_3_1X       = 6,
    ADC2_3_20X      = 7
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 1, 1, 1, 1,    // MUX 0..7
    1, 1, 1, 1, 0, 0, 0, 0     // MUX 8..15
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_VCC               = 0x00,
    ADC_REFERENCE_AREF              = 0x40,
    ADC_REFERENCE_1V1               = 0x80,
    ADC_REFERENCE_2V56              = 0x90,
    ADC_REFERENCE_2V56_BYPASS       = 0xD0
};
#elif defined(__AVR_ATmega88P__) || defined(__AVR_ATmega328P__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC2_1X         = 2,
    ADC3_1X         = 3,
    ADC4_1X         = 4,
    ADC5_1X         = 5,
    ADC6_1X         = 6,
    ADC7_1X         = 7,
    ADC_GND         = 15,
    ADC_TEMPERATURE = 8,
    ADC_VBG         = 14
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 0..7
    0, 0, 0, 0, 0, 0, 0, 0     // MUX 8..15
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_AREF  = 0x00,
    ADC_REFERENCE_AVCC  = 0x40,
    ADC_REFERENCE_1V1   = 0xC0
};
#elif defined(__AVR_ATmega32U4__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC4_1X         = 4,
    ADC5_1X         = 5,
    ADC6_1X         = 6,
    ADC7_1X         = 7,
    ADC8_1X         = 32,
    ADC9_1X         = 33,
    ADC10_1X        = 34,
    ADC11_1X        = 35,
    ADC12_1X        = 36,
    ADC13_1X        = 37,
    ADC_GND         = 31,
    ADC_TEMPERATURE = 39,
    ADC_VBG         = 30,

    ADC0_1_1X       = 16,
    ADC1_0_10X      = 9,
    ADC1_0_40X      = 38,
    ADC1_0_200X     = 11,

    ADC4_0_10X      = 40,
    ADC4_0_40X      = 48,
    ADC4_0_200X     = 56,
    ADC4_1_1X       = 20,
    ADC4_1_10X      = 44,
    ADC4_1_40X      = 52,
    ADC4_1_200X     = 60,

    ADC5_0_10X      = 41,
    ADC5_0_40X      = 49,
    ADC5_0_200X     = 57,
    ADC5_1_1X       = 21,
    ADC5_1_10X      = 45,
    ADC5_1_40X      = 53,
    ADC5_1_200X     = 61,

    ADC6_0_10X      = 42,
    ADC6_0_40X      = 50,
    ADC6_0_200X     = 58,
    ADC6_1_1X       = 22,
    ADC6_1_10X      = 46,
    ADC6_1_40X      = 54,
    ADC6_1_200X     = 62,

    ADC7_0_10X      = 43,
    ADC7_0_40X      = 51,
    ADC7_0_200X     = 59,
    ADC7_1_1X       = 23,
    ADC7_1_10X      = 47,
    ADC7_1_40X      = 55,
    ADC7_1_200X     = 63
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 0..7
    0, 1, 0, 1, 0, 0, 0, 0,    // MUX 8..15
    1, 0, 0, 0, 1, 1, 1, 1,    // MUX 16..23
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 24..31
    0, 0, 0, 0, 0, 0, 1, 0,    // MUX 32..39
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 40..47
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 48..55
    1, 1, 1, 1, 1, 1, 1, 1     // MUX 56..63
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_AREF  = 0x00,
    ADC_REFERENCE_AVCC  = 0x40,
    ADC_REFERENCE_2V56  = 0xC0
};
#elif defined(__AVR_ATmega1284P__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC2_1X         = 2,
    ADC3_1X         = 3,
    ADC4_1X         = 4,
    ADC5_1X         = 5,
    ADC6_1X         = 6,
    ADC7_1X         = 7,
    ADC_GND         = 31,
    ADC_VBG         = 30,

    ADC0_0_10X      = 8,
    ADC0_0_200X     = 10,
    ADC0_1_1X       = 16,
    ADC0_2_1X       = 24,

    ADC1_0_10X      = 9,
    ADC1_0_200X     = 11,
    ADC1_1_1X       = 17,
    ADC1_2_1X       = 25,

    ADC2_1_1X       = 18,
    ADC2_2_10X      = 12,
    ADC2_2_1X       = 26,
    ADC2_2_200X     = 14,

    ADC3_1_1X       = 19,
    ADC3_2_10X      = 13,
    ADC3_2_1X       = 27,
    ADC3_2_200X     = 15,

    ADC4_1_1X       = 20,
    ADC4_2_1X       = 28,

    ADC5_1_1X       = 21,
    ADC5_2_1X       = 29,

    ADC6_1_1X       = 22,

    ADC7_1_1X       = 23
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 0..7
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 8..15
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 16..23
    1, 1, 1, 1, 1, 1, 0, 0     // MUX 24..31
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_AREF  = 0x00,
    ADC_REFERENCE_AVCC  = 0x40,
    ADC_REFERENCE_1V1   = 0x80,
    ADC_REFERENCE_2V56  = 0xC0
};
#elif defined(__AVR_ATmega2560__)
enum ADC_Channel : uint8_t
{
    ADC0_1X         = 0,
    ADC1_1X         = 1,
    ADC2_1X         = 2,
    ADC3_1X         = 3,
    ADC4_1X         = 4,
    ADC5_1X         = 5,
    ADC6_1X         = 6,
    ADC7_1X         = 7,
    ADC8_1X         = 32,
    ADC9_1X         = 33,
    ADC10_1X        = 34,
    ADC11_1X        = 35,
    ADC12_1X        = 36,
    ADC13_1X        = 37,
    ADC14_1X        = 38,
    ADC15_1X        = 39,
    ADC_GND         = 31,
    ADC_VBG         = 30,

    ADC0_0_10X      = 8,
    ADC0_0_200X     = 10,
    ADC0_1_1X       = 16,
    ADC0_2_1X       = 24,

    ADC1_0_10X      = 9,
    ADC1_0_200X     = 11,
    ADC1_1_1X       = 17,
    ADC1_2_1X       = 25,

    ADC2_1_1X       = 18,
    ADC2_2_10X      = 12,
    ADC2_2_1X       = 26,
    ADC2_2_200X     = 14,

    ADC3_1_1X       = 19,
    ADC3_2_10X      = 13,
    ADC3_2_1X       = 27,
    ADC3_2_200X     = 15,

    ADC4_1_1X       = 20,
    ADC4_2_1X       = 28,

    ADC5_1_1X       = 21,
    ADC5_2_1X       = 29,

    ADC6_1_1X       = 22,

    ADC7_1_1X       = 23,

    ADC8_8_10X      = 40,
    ADC8_8_200X     = 42,
    ADC8_9_1X       = 48,
    ADC8_10_1X      = 56,

    ADC9_8_10X      = 41,
    ADC9_8_200X     = 43,
    ADC9_9_1X       = 49,
    ADC9_10_1X      = 57,

    ADC10_9_1X      = 50,
    ADC10_10_10X    = 44,
    ADC10_10_200X   = 46,
    ADC10_10_1X     = 58,

    ADC11_9_1X      = 51,
    ADC11_10_10X    = 45,
    ADC11_10_200X   = 47,
    ADC11_10_1X     = 59,

    ADC12_9_1X      = 52,
    ADC12_10_1X     = 60,

    ADC13_9_1X      = 53,
    ADC13_10_1X     = 61,

    ADC14_9_1X      = 54,

    ADC15_9_1X      = 55
};
// Indexed by the ADC_Channel MUX code; unused codes are zero.
static const uint8_t diff_table[] PROGMEM =
{
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 0..7
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 8..15
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 16..23
    1, 1, 1, 1, 1, 1, 0, 0,    // MUX 24..31
    0, 0, 0, 0, 0, 0, 0, 0,    // MUX 32..39
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 40..47
    1, 1, 1, 1, 1, 1, 1, 1,    // MUX 48..55
    1, 1, 1, 1, 1, 1, 0, 0     // MUX 56..63
};
enum ADC_reference : uint8_t
{
    ADC_REFERENCE_AREF  = 0x00,
    ADC_REFERENCE_AVCC  = 0x40,
    ADC_REFERENCE_1V1   = 0x80,
    ADC_REFERENCE_2V56  = 0xC0
};
#else
enum ADC_reference : uint8_t
{
    // not defined for this MCU
};
#endif
//------------------------------------------------------------------------------------------------
#endif // AVR_ADC_CHANNELS_H
