/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins_m1284.h
//----------------------------------------------------------------------------------------------*/
//           pin | PORT | DDR  | PIN  | TGL  | BIT
DECLARE_PIN( A0,   0x02,  0x01,  0x00,  0x00,  0)
DECLARE_PIN( A1,   0x02,  0x01,  0x00,  0x00,  1)
DECLARE_PIN( A2,   0x02,  0x01,  0x00,  0x00,  2)
DECLARE_PIN( A3,   0x02,  0x01,  0x00,  0x00,  3)
DECLARE_PIN( A4,   0x02,  0x01,  0x00,  0x00,  4)
DECLARE_PIN( A5,   0x02,  0x01,  0x00,  0x00,  5)
DECLARE_PIN( A6,   0x02,  0x01,  0x00,  0x00,  6)
DECLARE_PIN( A7,   0x02,  0x01,  0x00,  0x00,  7)

DECLARE_PIN( B0,   0x05,  0x04,  0x03,  0x03,  0)
DECLARE_PIN( B1,   0x05,  0x04,  0x03,  0x03,  1)
DECLARE_PIN( B2,   0x05,  0x04,  0x03,  0x03,  2)
DECLARE_PIN( B3,   0x05,  0x04,  0x03,  0x03,  3)
DECLARE_PIN( B4,   0x05,  0x04,  0x03,  0x03,  4)
DECLARE_PIN( B5,   0x05,  0x04,  0x03,  0x03,  5)
DECLARE_PIN( B6,   0x05,  0x04,  0x03,  0x03,  6)
DECLARE_PIN( B7,   0x05,  0x04,  0x03,  0x03,  7)

DECLARE_PIN( C0,   0x08,  0x07,  0x06,  0x06,  0)
DECLARE_PIN( C1,   0x08,  0x07,  0x06,  0x06,  1)
DECLARE_PIN( C2,   0x08,  0x07,  0x06,  0x06,  2)
DECLARE_PIN( C3,   0x08,  0x07,  0x06,  0x06,  3)
DECLARE_PIN( C4,   0x08,  0x07,  0x06,  0x06,  4)
DECLARE_PIN( C5,   0x08,  0x07,  0x06,  0x06,  5)
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
//------------------------------------------------------------------------------------------------
//                       pin | timer | channel
DECLARE_TIMER_OUTPUT_PIN( B3,    0,    0)
DECLARE_TIMER_OUTPUT_PIN( B4,    0,    1)
DECLARE_TIMER_OUTPUT_PIN( D5,    1,    0)
DECLARE_TIMER_OUTPUT_PIN( D4,    1,    1)
DECLARE_TIMER_OUTPUT_PIN( D7,    2,    0)
DECLARE_TIMER_OUTPUT_PIN( D6,    2,    1)
DECLARE_TIMER_OUTPUT_PIN( B6,    3,    0)
DECLARE_TIMER_OUTPUT_PIN( B7,    3,    1)
//------------------------------------------------------------------------------------------------
//               pin | INT# | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_INT_PIN( D2,     0,   EICRA,    ISC00,  EIMSK,     INT0,      EIFR,      INTF0)
DECLARE_INT_PIN( D3,     1,   EICRA,    ISC10,  EIMSK,     INT1,      EIFR,      INTF1)
DECLARE_INT_PIN( B2,     2,   EICRA,    ISC20,  EIMSK,     INT2,      EIFR,      INTF2)
//------------------------------------------------------------------------------------------------
//                pin | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_PCINT_PIN( A0,  PCICR,    PCIE0,  PCMSK0,    PCINT0,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A1,  PCICR,    PCIE0,  PCMSK0,    PCINT1,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A2,  PCICR,    PCIE0,  PCMSK0,    PCINT2,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A3,  PCICR,    PCIE0,  PCMSK0,    PCINT3,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A4,  PCICR,    PCIE0,  PCMSK0,    PCINT4,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A5,  PCICR,    PCIE0,  PCMSK0,    PCINT5,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A6,  PCICR,    PCIE0,  PCMSK0,    PCINT6,    PCIFR,     PCIF0)
DECLARE_PCINT_PIN( A7,  PCICR,    PCIE0,  PCMSK0,    PCINT7,    PCIFR,     PCIF0)

DECLARE_PCINT_PIN( B0,  PCICR,    PCIE1,  PCMSK1,    PCINT8,    PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B1,  PCICR,    PCIE1,  PCMSK1,    PCINT9,    PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B2,  PCICR,    PCIE1,  PCMSK1,    PCINT10,   PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B3,  PCICR,    PCIE1,  PCMSK1,    PCINT11,   PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B4,  PCICR,    PCIE1,  PCMSK1,    PCINT12,   PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B5,  PCICR,    PCIE1,  PCMSK1,    PCINT13,   PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B6,  PCICR,    PCIE1,  PCMSK1,    PCINT14,   PCIFR,     PCIF1)
DECLARE_PCINT_PIN( B7,  PCICR,    PCIE1,  PCMSK1,    PCINT15,   PCIFR,     PCIF1)

DECLARE_PCINT_PIN( C0,  PCICR,    PCIE2,  PCMSK2,    PCINT16,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C1,  PCICR,    PCIE2,  PCMSK2,    PCINT17,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C2,  PCICR,    PCIE2,  PCMSK2,    PCINT18,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C3,  PCICR,    PCIE2,  PCMSK2,    PCINT19,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C4,  PCICR,    PCIE2,  PCMSK2,    PCINT20,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C5,  PCICR,    PCIE2,  PCMSK2,    PCINT21,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C6,  PCICR,    PCIE2,  PCMSK2,    PCINT22,   PCIFR,     PCIF2)
DECLARE_PCINT_PIN( C7,  PCICR,    PCIE2,  PCMSK2,    PCINT23,   PCIFR,     PCIF2)

DECLARE_PCINT_PIN( D0,  PCICR,    PCIE3,  PCMSK3,    PCINT24,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D1,  PCICR,    PCIE3,  PCMSK3,    PCINT25,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D2,  PCICR,    PCIE3,  PCMSK3,    PCINT26,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D3,  PCICR,    PCIE3,  PCMSK3,    PCINT27,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D4,  PCICR,    PCIE3,  PCMSK3,    PCINT28,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D5,  PCICR,    PCIE3,  PCMSK3,    PCINT29,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D6,  PCICR,    PCIE3,  PCMSK3,    PCINT30,   PCIFR,     PCIF3)
DECLARE_PCINT_PIN( D7,  PCICR,    PCIE3,  PCMSK3,    PCINT31,   PCIFR,     PCIF3)
//------------------------------------------------------------------------------------------------
#define PCINT_VECTOR_A0   PCINT0_vect
#define PCINT_VECTOR_A1   PCINT0_vect
#define PCINT_VECTOR_A2   PCINT0_vect
#define PCINT_VECTOR_A3   PCINT0_vect
#define PCINT_VECTOR_A4   PCINT0_vect
#define PCINT_VECTOR_A5   PCINT0_vect
#define PCINT_VECTOR_A6   PCINT0_vect
#define PCINT_VECTOR_A7   PCINT0_vect

#define PCINT_VECTOR_B0   PCINT1_vect
#define PCINT_VECTOR_B1   PCINT1_vect
#define PCINT_VECTOR_B2   PCINT1_vect
#define PCINT_VECTOR_B3   PCINT1_vect
#define PCINT_VECTOR_B4   PCINT1_vect
#define PCINT_VECTOR_B5   PCINT1_vect
#define PCINT_VECTOR_B6   PCINT1_vect
#define PCINT_VECTOR_B7   PCINT1_vect

#define PCINT_VECTOR_C0   PCINT2_vect
#define PCINT_VECTOR_C1   PCINT2_vect
#define PCINT_VECTOR_C2   PCINT2_vect
#define PCINT_VECTOR_C3   PCINT2_vect
#define PCINT_VECTOR_C4   PCINT2_vect
#define PCINT_VECTOR_C5   PCINT2_vect
#define PCINT_VECTOR_C6   PCINT2_vect
#define PCINT_VECTOR_C7   PCINT2_vect

#define PCINT_VECTOR_D0   PCINT3_vect
#define PCINT_VECTOR_D1   PCINT3_vect
#define PCINT_VECTOR_D2   PCINT3_vect
#define PCINT_VECTOR_D3   PCINT3_vect
#define PCINT_VECTOR_D4   PCINT3_vect
#define PCINT_VECTOR_D5   PCINT3_vect
#define PCINT_VECTOR_D6   PCINT3_vect
#define PCINT_VECTOR_D7   PCINT3_vect
