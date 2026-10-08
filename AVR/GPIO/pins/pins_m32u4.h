/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins_m32u4.h
//----------------------------------------------------------------------------------------------*/
//           pin | PORT | DDR  | PIN  | TGL  | BIT
DECLARE_PIN( B0,   0x05,  0x04,  0x03,  0x03,  0)
DECLARE_PIN( B1,   0x05,  0x04,  0x03,  0x03,  1)
DECLARE_PIN( B2,   0x05,  0x04,  0x03,  0x03,  2)
DECLARE_PIN( B3,   0x05,  0x04,  0x03,  0x03,  3)
DECLARE_PIN( B4,   0x05,  0x04,  0x03,  0x03,  4)
DECLARE_PIN( B5,   0x05,  0x04,  0x03,  0x03,  5)
DECLARE_PIN( B6,   0x05,  0x04,  0x03,  0x03,  6)
DECLARE_PIN( B7,   0x05,  0x04,  0x03,  0x03,  7)

DECLARE_PIN( C6,   0x08,  0x07,  0x06,  0x06,  6)
DECLARE_PIN( C7,   0x08,  0x07,  0x06,  0x06,  7)

DECLARE_PIN( D0,   0x0B,  0x0A,  0x09,  0x09,  0)
DECLARE_PIN( D1,   0x0B,  0x0A,  0x09,  0x09,  1)
DECLARE_PIN( D2,   0x0B,  0x0A,  0x09,  0x09,  2)
DECLARE_PIN( D3,   0x0B,  0x0A,  0x09,  0x09,  3)
DECLARE_PIN( D4,   0x0B,  0x0A,  0x09,  0x09,  4)
DECLARE_PIN( D5,   0x0B,  0x0A,  0x09,  0x09,  5)
DECLARE_PIN( D6,   0x0B,  0x0A,  0x09,  0x09,  6)
DECLARE_PIN( D7,   0x0B,  0x0A,  0x09,  0x09,  7)

DECLARE_PIN( E2,   0x0E,  0x0D,  0x0C,  0x0C,  2)
DECLARE_PIN( E6,   0x0E,  0x0D,  0x0C,  0x0C,  6)

DECLARE_PIN( F0,   0x11,  0x10,  0x0F,  0x0F,  0)
DECLARE_PIN( F1,   0x11,  0x10,  0x0F,  0x0F,  1)
DECLARE_PIN( F4,   0x11,  0x10,  0x0F,  0x0F,  4)
DECLARE_PIN( F5,   0x11,  0x10,  0x0F,  0x0F,  5)
DECLARE_PIN( F6,   0x11,  0x10,  0x0F,  0x0F,  6)
DECLARE_PIN( F7,   0x11,  0x10,  0x0F,  0x0F,  7)
//------------------------------------------------------------------------------------------------
//                       pin | timer | channel
DECLARE_TIMER_OUTPUT_PIN( B7,    0,    0)
DECLARE_TIMER_OUTPUT_PIN( D0,    0,    1)
DECLARE_TIMER_OUTPUT_PIN( B5,    1,    0)
DECLARE_TIMER_OUTPUT_PIN( B6,    1,    1)
DECLARE_TIMER_OUTPUT_PIN( B7,    1,    2)
DECLARE_TIMER_OUTPUT_PIN( C6,    3,    0)
//------------------------------------------------------------------------------------------------
//               pin | INT# | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_INT_PIN( D0,     0,   EICRA,    ISC00,  EIMSK,     INT0,      EIFR,      INTF0)
DECLARE_INT_PIN( D1,     1,   EICRA,    ISC10,  EIMSK,     INT1,      EIFR,      INTF1)
DECLARE_INT_PIN( D2,     2,   EICRA,    ISC20,  EIMSK,     INT2,      EIFR,      INTF2)
DECLARE_INT_PIN( D3,     3,   EICRA,    ISC30,  EIMSK,     INT3,      EIFR,      INTF3)
DECLARE_INT_PIN( E6,     6,   EICRB,    ISC60,  EIMSK,     INT6,      EIFR,      INTF6)
//------------------------------------------------------------------------------------------------
//                pin | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_PCINT_PIN( B0,  PCICR,    PCIE0,  PCMSK0,    PCINT0,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B1,  PCICR,    PCIE0,  PCMSK0,    PCINT1,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B2,  PCICR,    PCIE0,  PCMSK0,    PCINT2,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B3,  PCICR,    PCIE0,  PCMSK0,    PCINT3,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B4,  PCICR,    PCIE0,  PCMSK0,    PCINT4,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B5,  PCICR,    PCIE0,  PCMSK0,    PCINT5,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B6,  PCICR,    PCIE0,  PCMSK0,    PCINT6,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( B7,  PCICR,    PCIE0,  PCMSK0,    PCINT7,    PCIFR,     PCIF0)
//------------------------------------------------------------------------------------------------
#define PCINT_VECTOR_B0   PCINT0_vect
#define PCINT_VECTOR_B1   PCINT0_vect
#define PCINT_VECTOR_B2   PCINT0_vect
#define PCINT_VECTOR_B3   PCINT0_vect
#define PCINT_VECTOR_B4   PCINT0_vect
#define PCINT_VECTOR_B5   PCINT0_vect
#define PCINT_VECTOR_B6   PCINT0_vect
#define PCINT_VECTOR_B7   PCINT0_vect
