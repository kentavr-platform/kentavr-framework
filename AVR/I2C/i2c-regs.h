#ifndef AVR_I2C_REGS_H
#define AVR_I2C_REGS_H
//------------------------------------------------------------------------------------------------
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
// Register traits for classic AVR I2C peripheral.  The template lets the driver
// be instantiated as I2C<0>, I2C<1>, ... on MCUs that expose several hardware
// I2C/I2C modules with numbered register sets.
template <uint8_t N> struct I2C_traits;
//------------------------------------------------------------------------------------------------
#define DEFINE_I2C_REGS(N, _TWBR, _TWSR, _TWAR, _TWDR, _TWCR,                 \
                        _TWINT, _TWEA, _TWSTA, _TWSTO, _TWWC, _TWEN, _TWIE)  \
template <>                                                                    \
struct I2C_traits <N> {                                                        \
    static inline volatile uint8_t& BR   = _TWBR;                              \
    static inline volatile uint8_t& SR   = _TWSR;                              \
    static inline volatile uint8_t& AR   = _TWAR;                              \
    static inline volatile uint8_t& DR   = _TWDR;                              \
    static inline volatile uint8_t& CR   = _TWCR;                              \
    static constexpr uint8_t INT  = _TWINT;                                    \
    static constexpr uint8_t EA   = _TWEA;                                     \
    static constexpr uint8_t STA  = _TWSTA;                                    \
    static constexpr uint8_t STO  = _TWSTO;                                    \
    static constexpr uint8_t WWC  = _TWWC;                                     \
    static constexpr uint8_t EN   = _TWEN;                                     \
    static constexpr uint8_t IE   = _TWIE;                                     \
};
//------------------------------------------------------------------------------------------------
// Old/single-I2C devices: ATmega1284P, ATmega328P, ATmega32, etc.
#if defined(TWBR) && defined(TWSR) && defined(TWAR) && defined(TWDR) && defined(TWCR)
DEFINE_I2C_REGS(0, TWBR, TWSR, TWAR, TWDR, TWCR,
                TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, TWIE)
#define I2C0_SUPPORTED
#endif
//------------------------------------------------------------------------------------------------
// Numbered classic I2C devices, for example some *PB parts.  These are still
// the old status-code based I2C units, not the new megaAVR-0/tinyAVR-1/AVR Dx
// I2C peripherals with a different register model.
#if defined(TWBR0) && defined(TWSR0) && defined(TWAR0) && defined(TWDR0) && defined(TWCR0)
DEFINE_I2C_REGS(0, TWBR0, TWSR0, TWAR0, TWDR0, TWCR0,
                TWINT0, TWEA0, TWSTA0, TWSTO0, TWWC0, TWEN0, TWIE0)
#define I2C0_SUPPORTED
#endif

#if defined(TWBR1) && defined(TWSR1) && defined(TWAR1) && defined(TWDR1) && defined(TWCR1)
DEFINE_I2C_REGS(1, TWBR1, TWSR1, TWAR1, TWDR1, TWCR1,
                TWINT1, TWEA1, TWSTA1, TWSTO1, TWWC1, TWEN1, TWIE1)
#define I2C1_SUPPORTED
#endif
//------------------------------------------------------------------------------------------------
#undef DEFINE_I2C_REGS
//------------------------------------------------------------------------------------------------
#endif



