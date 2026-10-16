/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins.h
//----------------------------------------------------------------------------------------------*/
#ifndef PINS_H
#define PINS_H
//------------------------------------------------------------------------------------------------
#define LEVEL_LOW  0
#define LEVEL_HIGH 1
//------------------------------------------------------------------------------------------------
template <
    volatile uint8_t port_addr,
    volatile uint8_t dir_addr,
    volatile uint8_t pin_addr,
    volatile uint8_t tgl_addr,
    uint8_t bit>
struct pin
{
    static constexpr uint8_t PORT  = port_addr;
    static constexpr uint8_t DDR   = dir_addr;
    static constexpr uint8_t PIN   = pin_addr;
    static constexpr uint8_t TGL   = tgl_addr;
    static constexpr uint8_t BIT   = bit;
};
//------------------------------------------------------------------------------------------------
struct NC {};       // Not Connected "pin"
//------------------------------------------------------------------------------------------------
#define DECLARE_PIN(ID, PORT, DDR, PIN, TGL, BIT) struct ID : pin <PORT, DDR, PIN, TGL, BIT> {};
//------------------------------------------------------------------------------------------------
// Physical RX and TX pins for hardware UART peripheral N.
template <uint8_t N>
struct UART_pins
{
    using RX_PIN = NC;
    using TX_PIN = NC;
};

#define DECLARE_UART_PINS(N, _RX_PIN, _TX_PIN)  \
  template <>                                   \
  struct UART_pins <N>                          \
  {                                             \
      using RX_PIN = _RX_PIN;                   \
      using TX_PIN = _TX_PIN;                   \
  };
//------------------------------------------------------------------------------------------------
// Physical signals for the hardware SPI peripheral N: MOSI, MISO, SCK, SS.
template <uint8_t N>
struct SPI_pins
{
    using MOSI = NC;
    using MISO = NC;
    using SCK  = NC;
    using SS   = NC;
};

#define DECLARE_SPI_PINS(N, _MOSI, _MISO, _SCK, _SS)    \
  template <>                                           \
  struct SPI_pins <N>                                   \
  {                                                     \
      using MOSI = _MOSI;                               \
      using MISO = _MISO;                               \
      using SCK  = _SCK;                                \
      using SS   = _SS;                                 \
  };
//------------------------------------------------------------------------------------------------
// USART pins used in master SPI mode: MOSI (TXD), MISO (RXD), and SCK (XCK).
template <uint8_t N>
struct USART_SPI_pins
{
    using MOSI = NC;
    using MISO = NC;
    using SCK  = NC;
};

#define DECLARE_USART_SPI_PINS(N, _MOSI, _MISO, _SCK)   \
  template <>                                           \
  struct USART_SPI_pins <N>                             \
  {                                                     \
      using MOSI = _MOSI;                               \
      using MISO = _MISO;                               \
      using SCK  = _SCK;                                \
  };
//------------------------------------------------------------------------------------------------
template <uint8_t N>
struct INT_traits
{
    static constexpr bool exists = false;
    using pin = NC;
};

template <class pin>
struct INT_traits_for_pin
{
    static constexpr bool exists = false;
};

#define DECLARE_INT_PIN(PIN, N, CONTROL_REG, SENSE_BIT, MASK_REG, MASK_BIT, FLAG_REG, FLAG_BIT) \
  template <>                                                                                   \
  struct INT_traits <N>                                                                         \
  {                                                                                             \
      using pin = PIN;                                                                          \
      static inline volatile uint8_t &CONTROL = CONTROL_REG;                                    \
      static inline volatile uint8_t &MASK = MASK_REG;                                          \
      static inline volatile uint8_t &FLAGS = FLAG_REG;                                         \
      static constexpr uint8_t sense_bit_0 = SENSE_BIT;                                         \
      static constexpr uint8_t sense_bit_1 = SENSE_BIT + 1;                                     \
      static constexpr uint8_t mask_bit = MASK_BIT;                                             \
      static constexpr uint8_t flag_bit = FLAG_BIT;                                             \
      static constexpr bool exists = true;                                                      \
  };                                                                                            \
  template <>                                                                                   \
  struct INT_traits_for_pin <PIN> : INT_traits <N>                                              \
  {};
//------------------------------------------------------------------------------------------------
#define PCINT_VECTOR(PIN)    PCINT_VECTOR_##PIN
//------------------------------------------------------------------------------------------------
template <class pin>
struct PCINT_traits
{
    static constexpr bool exists = false;
};

#define DECLARE_PCINT_PIN(PIN, CONTROL_REG, CONTROL_BIT, MASK_REG, MASK_BIT, FLAG_REG, FLAG_BIT) \
  template <>                                                                                    \
  struct PCINT_traits <PIN>                                                                      \
  {                                                                                              \
      static inline volatile uint8_t &CONTROL = CONTROL_REG;                                     \
      static inline volatile uint8_t &MASK = MASK_REG;                                           \
      static inline volatile uint8_t &FLAGS = FLAG_REG;                                          \
      static constexpr uint8_t control_bit = CONTROL_BIT;                                        \
      static constexpr uint8_t mask_bit = MASK_BIT;                                              \
      static constexpr uint8_t flag_bit = FLAG_BIT;                                              \
      static constexpr bool exists = true;                                                       \
  };
//------------------------------------------------------------------------------------------------
template <uint8_t timer, uint8_t channel>
struct Timer_output_pin
{
    using Type = NC;
};

#define DECLARE_TIMER_OUTPUT_PIN(PIN, TIMER, CHANNEL)   \
  template <>                                           \
  struct Timer_output_pin <TIMER, CHANNEL>              \
  {                                                     \
      using Type = PIN;                                 \
  };
//------------------------------------------------------------------------------------------------
#if defined(__AVR_ATtiny85__)
  #include "pins/pins_tiny85.h"
#elif defined(__AVR_ATmega8__)
  #include "pins/pins_m8.h"
#elif defined(__AVR_ATmega88__)
  #include "pins/pins_m88.h"
#elif defined(__AVR_ATmega88P__)
  #include "pins/pins_m88p.h"
#elif defined(__AVR_ATmega328__)
  #include "pins/pins_m328.h"
#elif defined(__AVR_ATmega328P__)
  #include "pins/pins_m328p.h"
#elif defined(__AVR_ATmega32U4__)
  #include "pins/pins_m32u4.h"
#elif defined(__AVR_ATmega1284P__)
  #include "pins/pins_m1284.h"
#elif defined(__AVR_ATmega2560__)
  #include "pins/pins_m2560.h"
#elif defined(AVR128DX_FAMILY)
  #include "pins/pins_128dx48.h"
#else
  #error "Unsupported or undefined MCU"
#endif
//------------------------------------------------------------------------------------------------
// Support pin names for popular Arduino boards
#if defined(ARDUINO_AVR_UNO)
  #include "boards/arduino-uno.h"
#elif defined(ARDUINO_AVR_NANO)
  #include "boards/arduino-nano.h"
#elif defined(ARDUINO_AVR_LEONARDO)
  #include "boards/arduino-leonardo.h"
#elif defined(ARDUINO_AVR_MINI)
  #include "boards/arduino-mini.h"
#elif defined(ARDUINO_AVR_MICRO)
  #include "boards/arduino-micro.h"
#elif defined(ARDUINO_AVR_PRO_MINI)
  #include "boards/arduino-pro-mini.h"
#elif defined(ARDUINO_AVR_PRO_MICRO)
  #include "boards/arduino-pro-micro.h"
#elif defined(ARDUINO_AVR_LEONARDO)
  #include "boards/arduino-leonardo.h"
#elif defined(ARDUINO_AVR_MEGA2560)
  #include "boards/arduino-mega2560.h"
#endif
//------------------------------------------------------------------------------------------------
#endif
