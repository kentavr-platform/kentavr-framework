/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-spi-regs.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_SPI_REGS_H
#define AVR_SPI_REGS_H
//------------------------------------------------------------------------------------------------
template <uint8_t N>
struct SPI_traits
{
    static constexpr bool exists = false;
};
//------------------------------------------------------------------------------------------------
// The device header identifies which power-reduction register contains PRSPI.
#if defined(__AVR_HAVE_PRR_PRSPI)
  #define SPI_POWER_CONTROL_REGS                                \
    static constexpr bool has_power_control = true;             \
    static inline volatile uint8_t& POWER = PRR;                \
    static constexpr uint8_t POWER_BIT = PRSPI;
#elif defined(__AVR_HAVE_PRR0_PRSPI)
  #define SPI_POWER_CONTROL_REGS                                \
    static constexpr bool has_power_control = true;             \
    static inline volatile uint8_t& POWER = PRR0;               \
    static constexpr uint8_t POWER_BIT = PRSPI;
#elif defined(__AVR_HAVE_PRR1_PRSPI)
  #define SPI_POWER_CONTROL_REGS                                \
    static constexpr bool has_power_control = true;             \
    static inline volatile uint8_t& POWER = PRR1;               \
    static constexpr uint8_t POWER_BIT = PRSPI;
#else
  #define SPI_POWER_CONTROL_REGS                                \
    static constexpr bool has_power_control = false;
#endif
//------------------------------------------------------------------------------------------------
#define DEFINE_SPI_REGS(N, _CONTROL, _STATUS,                   \
                        _DATA, _ENABLE, _MASTER,                \
                        _ORDER, _PHASE, _POLARITY,              \
                        _PRESCALE, _DOUBLE, _INTERRUPT)         \
template <>                                                     \
struct SPI_traits <N>                                           \
{                                                               \
    static constexpr bool exists              = true;           \
    static inline volatile uint8_t& CONTROL   = _CONTROL;       \
    static inline volatile uint8_t& STATUS    = _STATUS;        \
    static inline volatile uint8_t& DATA      = _DATA;          \
    static constexpr uint8_t ENABLE           = _ENABLE;        \
    static constexpr uint8_t MASTER           = _MASTER;        \
    static constexpr uint8_t ORDER            = _ORDER;         \
    static constexpr uint8_t PHASE            = _PHASE;         \
    static constexpr uint8_t POLARITY         = _POLARITY;      \
    static constexpr uint8_t PRESCALE         = _PRESCALE;      \
    static constexpr uint8_t DOUBLE           = _DOUBLE;        \
    static constexpr uint8_t INTERRUPT        = _INTERRUPT;     \
    SPI_POWER_CONTROL_REGS                                      \
};
//------------------------------------------------------------------------------------------------
#define DEFINE_SPI_DX_REGS(N, _SPI)                             \
template <>                                                     \
struct SPI_traits <N>                                           \
{                                                               \
    static constexpr bool exists              = true;           \
    static inline volatile uint8_t& CONTROL   = _SPI.CTRLA;     \
    static inline volatile uint8_t& CONTROL_B = _SPI.CTRLB;     \
    static inline volatile uint8_t& INT_MASK  = _SPI.INTCTRL;   \
    static inline volatile uint8_t& STATUS    = _SPI.INTFLAGS;  \
    static inline volatile uint8_t& DATA      = _SPI.DATA;      \
    static constexpr uint8_t ENABLE           = SPI_ENABLE_bp;  \
    static constexpr uint8_t MASTER           = SPI_MASTER_bp;  \
    static constexpr uint8_t ORDER            = SPI_DORD_bp;    \
    static constexpr uint8_t PRESCALE         = SPI_PRESC_0_bp; \
    static constexpr uint8_t DOUBLE           = SPI_CLK2X_bp;   \
    static constexpr uint8_t INTERRUPT        = SPI_IE_bp;      \
    static constexpr uint8_t SS_DISABLE       = SPI_SSD_bp;     \
    SPI_POWER_CONTROL_REGS                                      \
};
//------------------------------------------------------------------------------------------------
# if defined(SPI_STC_vect)
  // classic families style
  DEFINE_SPI_REGS(0, SPCR, SPSR, SPDR, SPE, MSTR, DORD, CPHA, CPOL, SPR0, SPI2X, SPIE)
  #define SPI0_SUPPORTED
#elif defined(SPI0_INT_vect)
  // Dx family style
  DEFINE_SPI_DX_REGS(0, SPI0)
  #define SPI0_SUPPORTED
  #undef SPI0  // release MCU register names to use SPI1 as a type
#endif

#if defined(SPI1_INT_vect)
  // SPI1 exists in DX_FAMILY only
  DEFINE_SPI_DX_REGS(1, SPI1)
  #define SPI1_SUPPORTED
  #undef SPI1  // release MCU register names to use SPI1 as a type
#endif
//------------------------------------------------------------------------------------------------
#endif // AVR_SPI_REGS_H
