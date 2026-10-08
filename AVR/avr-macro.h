/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-macro.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_MACRO_H
#define AVR_MACRO_H
//------------------------------------------------------------------------------------------------
#include <avr/pgmspace.h>
//------------------------------------------------------------------------------------------------
#define enable_interrupts()     __asm__ volatile ("sei")
#define disable_interrupts()    __asm__ volatile ("cli")
//------------------------------------------------------------------------------------------------
class AtomicBlock
{
private:
    uint8_t sreg;
public:
    AtomicBlock()   { sreg = SREG; disable_interrupts(); }
    ~AtomicBlock()  { SREG = sreg; }
};
#define ATOMIC_BLOCK            AtomicBlock _atomic_;
//------------------------------------------------------------------------------------------------
struct FlashStringWrapper { const char *str; };
#define _flash(a)               (FlashStringWrapper{PSTR(a)})
//------------------------------------------------------------------------------------------------
#endif
