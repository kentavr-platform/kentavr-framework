/*------------------------------------------------------------------------------------------------
 * AVR/avr-gpio.h
 *
 *  This file contains hardware-specific macros and definitions.
 *
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_MACRO_H
#define AVR_MACRO_H
//------------------------------------------------------------------------------------------------
#if defined(__AVR_AVR128DA48__) || defined(__AVR_AVR128DB48__) || defined(__AVR_AVR128DD48__)
#define AVR128DX_FAMILY
#endif
//------------------------------------------------------------------------------------------------
#define CAT(x,y) x ## y
#define CONCAT(x,y) CAT(x,y)
#define __EXTENSION    8,7,6,5,4,3,2,1,0
#define __GET8(_0,_1,_2,_3,_4,_5,_6,_7,_8,N,...) N
#define __GET_SIZE(...) __GET8(__VA_ARGS__)
#define __VA_SIZE(...) __GET_SIZE(_,##__VA_ARGS__,__EXTENSION)
#define _BITS1(b1)     _bit(b1)
#define _BITS2(b1,...) _bit(b1) | _BITS1(__VA_ARGS__)
#define _BITS3(b1,...) _bit(b1) | _BITS2(__VA_ARGS__)
#define _BITS4(b1,...) _bit(b1) | _BITS3(__VA_ARGS__)
#define _BITS5(b1,...) _bit(b1) | _BITS4(__VA_ARGS__)
#define _BITS6(b1,...) _bit(b1) | _BITS5(__VA_ARGS__)
#define _BITS7(b1,...) _bit(b1) | _BITS6(__VA_ARGS__)
#define _BITS8(b1,...) _bit(b1) | _BITS7(__VA_ARGS__)
#define _BITS(...)  CONCAT(_BITS,__VA_SIZE(__VA_ARGS__))(__VA_ARGS__)

#define _bit(b) (1 << (b))
#define set_bit(reg,b) (reg |= _bit(b))
#define clr_bit(reg,b) (reg &= ~_bit(b))
#define test_bit(reg,b) ((reg & _bit(b)) >> b)

#define _bits(...) _BITS(__VA_ARGS__)
#define set_bits(reg,...) reg = reg | _bits(__VA_ARGS__)
#define clr_bits(reg,...) reg = reg & ~(_bits(__VA_ARGS__))
#define test_bits(var,bits) (((var & (bits)) == (bits)) ? 1 : 0)

#define HBYTE(word) ((word) >> 8)
#define LBYTE(word) ((BYTE)(word))
#define enable_interrupts() __asm__ volatile ("sei")
#define disable_interrupts() { __asm__ volatile ("cli"); }
//------------------------------------------------------------------------------------------------
class ATOMIC_BLOCK
{
private:
    uint8_t sreg;
public:
    ATOMIC_BLOCK()   { sreg = SREG; disable_interrupts(); }
    ~ATOMIC_BLOCK()  { SREG = sreg; }
};
#define ATOMIC_BLOCK AtomicBlock _atomic_;
//------------------------------------------------------------------------------------------------
#endif
