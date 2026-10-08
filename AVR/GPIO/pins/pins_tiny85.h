/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins_tiny85.h
//----------------------------------------------------------------------------------------------*/
//           pin | PORT | DDR  | PIN  | TGL  | BIT
DECLARE_PIN( B0,   0x18,  0x17,  0x16,  0x16,  0)
DECLARE_PIN( B1,   0x18,  0x17,  0x16,  0x16,  1)
DECLARE_PIN( B2,   0x18,  0x17,  0x16,  0x16,  2)
DECLARE_PIN( B3,   0x18,  0x17,  0x16,  0x16,  3)
DECLARE_PIN( B4,   0x18,  0x17,  0x16,  0x16,  4)
DECLARE_PIN( B5,   0x18,  0x17,  0x16,  0x16,  5)   // RESET unless RSTDISBL
//------------------------------------------------------------------------------------------------
//                       pin | timer | channel
DECLARE_TIMER_OUTPUT_PIN( B0,    0,    0)
DECLARE_TIMER_OUTPUT_PIN( B1,    0,    1)
//------------------------------------------------------------------------------------------------
//               pin | INT# | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_INT_PIN( B2,     0,   MCUCR,    ISC00,  GIMSK,     INT0,      GIFR,      INTF0)
//------------------------------------------------------------------------------------------------
//                pin | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_PCINT_PIN( B0,  GIMSK,     PCIE,   PCMSK,    PCINT0,    GIFR,      PCIF)
DECLARE_PCINT_PIN( B1,  GIMSK,     PCIE,   PCMSK,    PCINT1,    GIFR,      PCIF)
DECLARE_PCINT_PIN( B2,  GIMSK,     PCIE,   PCMSK,    PCINT2,    GIFR,      PCIF)
DECLARE_PCINT_PIN( B3,  GIMSK,     PCIE,   PCMSK,    PCINT3,    GIFR,      PCIF)
DECLARE_PCINT_PIN( B4,  GIMSK,     PCIE,   PCMSK,    PCINT4,    GIFR,      PCIF)
DECLARE_PCINT_PIN( B5,  GIMSK,     PCIE,   PCMSK,    PCINT5,    GIFR,      PCIF)
//------------------------------------------------------------------------------------------------
#define PCINT_VECTOR_B0   PCINT0_vect
#define PCINT_VECTOR_B1   PCINT0_vect
#define PCINT_VECTOR_B2   PCINT0_vect
#define PCINT_VECTOR_B3   PCINT0_vect
#define PCINT_VECTOR_B4   PCINT0_vect
#define PCINT_VECTOR_B5   PCINT0_vect
