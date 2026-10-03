/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: pins_m8.h
//----------------------------------------------------------------------------------------------*/
//           pin | PORT | DDR  | PIN  | TGL  | BIT
DECLARE_PIN( B0,   0x18,  0x17,  0x16,  NONE,  0)
DECLARE_PIN( B1,   0x18,  0x17,  0x16,  NONE,  1)
DECLARE_PIN( B2,   0x18,  0x17,  0x16,  NONE,  2)
DECLARE_PIN( B3,   0x18,  0x17,  0x16,  NONE,  3)
DECLARE_PIN( B4,   0x18,  0x17,  0x16,  NONE,  4)
DECLARE_PIN( B5,   0x18,  0x17,  0x16,  NONE,  5)
DECLARE_PIN( B6,   0x18,  0x17,  0x16,  NONE,  6)
DECLARE_PIN( B7,   0x18,  0x17,  0x16,  NONE,  7)

DECLARE_PIN( C0,   0x15,  0x14,  0x13,  NONE,  0)
DECLARE_PIN( C1,   0x15,  0x14,  0x13,  NONE,  1)
DECLARE_PIN( C2,   0x15,  0x14,  0x13,  NONE,  2)
DECLARE_PIN( C3,   0x15,  0x14,  0x13,  NONE,  3)
DECLARE_PIN( C4,   0x15,  0x14,  0x13,  NONE,  4)
DECLARE_PIN( C5,   0x15,  0x14,  0x13,  NONE,  5)
DECLARE_PIN( C6,   0x15,  0x14,  0x13,  NONE,  6) // RESET unless RSTDISBL

DECLARE_PIN( D0,   0x12,  0x11,  0x10,  NONE,  0)
DECLARE_PIN( D1,   0x12,  0x11,  0x10,  NONE,  1)
DECLARE_PIN( D2,   0x12,  0x11,  0x10,  NONE,  2)
DECLARE_PIN( D3,   0x12,  0x11,  0x10,  NONE,  3)
DECLARE_PIN( D4,   0x12,  0x11,  0x10,  NONE,  4)
DECLARE_PIN( D5,   0x12,  0x11,  0x10,  NONE,  5)
DECLARE_PIN( D6,   0x12,  0x11,  0x10,  NONE,  6)
DECLARE_PIN( D7,   0x12,  0x11,  0x10,  NONE,  7)
//------------------------------------------------------------------------------------------------
//                       pin | timer | channel
DECLARE_TIMER_OUTPUT_PIN( B1,    1,    0)
DECLARE_TIMER_OUTPUT_PIN( B2,    1,    1)
DECLARE_TIMER_OUTPUT_PIN( B3,    2,    0)
//------------------------------------------------------------------------------------------------
//               pin | INT# | control | sense | mask reg | mask bit | flag reg | flag bit
DECLARE_INT_PIN( D2,     0,   MCUCR,    ISC00,  GICR,      INT0,      GIFR,      INTF0)
DECLARE_INT_PIN( D3,     1,   MCUCR,    ISC10,  GICR,      INT1,      GIFR,      INTF1)
//------------------------------------------------------------------------------------------------
