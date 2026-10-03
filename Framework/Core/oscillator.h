/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: Core/oscillator.h
//----------------------------------------------------------------------------------------------*/
#ifndef OSCILLATOR_H
#define OSCILLATOR_H
//------------------------------------------------------------------------------------------------
#ifdef F_CPU
  #error ! F_CPU should not be defined directly
#endif
//------------------------------------------------------------------------------------------------
#if defined(CRYSTAL_FREQ)
  #define F_CPU             CRYSTAL_FREQ        // external crystal or ceramic resonator
#elif defined(EXTERNAL_CLOCK)
  #define F_CPU             EXTERNAL_CLOCK      // external clock source
#elif defined(INTERNAL_CLOCK_8MHZ)
  #define F_CPU             8000000UL           // internal RC clock generator
#else
  #error ! Define CRYSTAL_FREQ=, EXTERNAL_CLOCK= or INTERNAL_CLOCK_8MHZ
  #define F_CPU
#endif
//------------------------------------------------------------------------------------------------
#endif
