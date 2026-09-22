/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-timer-isr.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_TIMER_ISR_H
#define AVR_TIMER_ISR_H
//------------------------------------------------------------------------------------------------
// Rename some old vector's macro definitions
#if !defined(TIMER0_CAPT_vect) && defined(TIM0_CAPT_vect)
  #define TIMER0_CAPT_vect TIM0_CAPT_vect
#endif

#if !defined(TIMER1_CAPT_vect) && defined(TIM1_CAPT_vect)
  #define TIMER1_CAPT_vect TIM1_CAPT_vect
#endif

#if !defined(TIMER0_OVF_vect) && defined(TIM0_OVF_vect)
  #define TIMER0_OVF_vect TIM0_OVF_vect
#endif
#if !defined(TIMER1_OVF_vect) && defined(TIM1_OVF_vect)
  #define TIMER1_OVF_vect TIM1_OVF_vect
#endif
#if !defined(TIMER2_OVF_vect) && defined(TIM2_OVF_vect)
  #define TIMER2_OVF_vect TIM2_OVF_vect
#endif
#if !defined(TIMER3_OVF_vect) && defined(TIM3_OVF_vect)
  #define TIMER3_OVF_vect TIM3_OVF_vect
#endif
#if !defined(TIMER4_OVF_vect) && defined(TIM4_OVF_vect)
  #define TIMER4_OVF_vect TIM4_OVF_vect
#endif
#if !defined(TIMER5_OVF_vect) && defined(TIM5_OVF_vect)
  #define TIMER5_OVF_vect TIM5_OVF_vect
#endif
//------------------------------------------------------------------------------------------------
#define _ENABLE_TIMER_COMPA_ISR(N) \
ISR(TIMER##N##_COMPA_vect) { Timer##N :: Compare_A.match_interrupt(); }

#define _ENABLE_TIMER_COMPB_ISR(N) \
ISR(TIMER##N##_COMPB_vect) { Timer##N :: Compare_B.match_interrupt(); }

#define _ENABLE_TIMER_COMPC_ISR(N) \
ISR(TIMER##N##_COMPC_vect) { Timer##N :: Compare_C.match_interrupt(); }

#define _ENABLE_TIMER_OVF_ISR(N) \
ISR(TIMER##N##_OVF_vect) { Timer##N :: overflow_interrupt(); }

#define _ENABLE_TIMER_CAPTURE_ISR(N) \
ISR(TIMER##N##_CAPT_vect) { Timer##N :: Capture.capture_interrupt(); }

#if defined(TIMER0_COMPA_vect)
  #define _ENABLE_TIMER0_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(0)
#else
  #define _ENABLE_TIMER0_COMPA_ISR
#endif
#if defined(TIMER0_COMPB_vect)
  #define _ENABLE_TIMER0_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(0)
#else
  #define _ENABLE_TIMER0_COMPB_ISR
#endif
#if defined(TIMER0_COMPC_vect)
  #define _ENABLE_TIMER0_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(0)
#else
  #define _ENABLE_TIMER0_COMPC_ISR
#endif

#if defined(TIMER1_COMPA_vect)
  #define _ENABLE_TIMER1_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(1)
#else
  #define _ENABLE_TIMER1_COMPA_ISR
#endif
#if defined(TIMER1_COMPB_vect)
  #define _ENABLE_TIMER1_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(1)
#else
  #define _ENABLE_TIMER1_COMPB_ISR
#endif
#if defined(TIMER1_COMPC_vect)
  #define _ENABLE_TIMER1_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(1)
#else
  #define _ENABLE_TIMER1_COMPC_ISR
#endif

#if defined(TIMER2_COMPA_vect)
  #define _ENABLE_TIMER2_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(2)
#else
  #define _ENABLE_TIMER2_COMPA_ISR
#endif
#if defined(TIMER2_COMPB_vect)
  #define _ENABLE_TIMER2_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(2)
#else
  #define _ENABLE_TIMER2_COMPB_ISR
#endif
#if defined(TIMER2_COMPC_vect)
  #define _ENABLE_TIMER2_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(2)
#else
  #define _ENABLE_TIMER2_COMPC_ISR
#endif

#if defined(TIMER3_COMPA_vect)
  #define _ENABLE_TIMER3_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(3)
#else
  #define _ENABLE_TIMER3_COMPA_ISR
#endif
#if defined(TIMER3_COMPB_vect)
  #define _ENABLE_TIMER3_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(3)
#else
  #define _ENABLE_TIMER3_COMPB_ISR
#endif
#if defined(TIMER3_COMPC_vect)
  #define _ENABLE_TIMER3_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(3)
#else
  #define _ENABLE_TIMER3_COMPC_ISR
#endif

#if defined(TIMER4_COMPA_vect)
  #define _ENABLE_TIMER4_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(4)
#else
  #define _ENABLE_TIMER4_COMPA_ISR
#endif
#if defined(TIMER4_COMPB_vect)
  #define _ENABLE_TIMER4_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(4)
#else
  #define _ENABLE_TIMER4_COMPB_ISR
#endif
#if defined(TIMER4_COMPC_vect)
  #define _ENABLE_TIMER4_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(4)
#else
  #define _ENABLE_TIMER4_COMPC_ISR
#endif

#if defined(TIMER5_COMPA_vect)
  #define _ENABLE_TIMER5_COMPA_ISR _ENABLE_TIMER_COMPA_ISR(5)
#else
  #define _ENABLE_TIMER5_COMPA_ISR
#endif
#if defined(TIMER5_COMPB_vect)
  #define _ENABLE_TIMER5_COMPB_ISR _ENABLE_TIMER_COMPB_ISR(5)
#else
  #define _ENABLE_TIMER5_COMPB_ISR
#endif
#if defined(TIMER5_COMPC_vect)
  #define _ENABLE_TIMER5_COMPC_ISR _ENABLE_TIMER_COMPC_ISR(5)
#else
  #define _ENABLE_TIMER5_COMPC_ISR
#endif

#if defined(TIMER0_CAPT_vect)
  #define _ENABLE_TIMER0_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(0)
#else
  #define _ENABLE_TIMER0_CAPTURE_ISR
#endif
#if defined(TIMER1_CAPT_vect)
  #define _ENABLE_TIMER1_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(1)
#else
  #define _ENABLE_TIMER1_CAPTURE_ISR
#endif
#if defined(TIMER2_CAPT_vect)
  #define _ENABLE_TIMER2_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(2)
#else
  #define _ENABLE_TIMER2_CAPTURE_ISR
#endif
#if defined(TIMER3_CAPT_vect)
  #define _ENABLE_TIMER3_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(3)
#else
  #define _ENABLE_TIMER3_CAPTURE_ISR
#endif
#if defined(TIMER4_CAPT_vect)
  #define _ENABLE_TIMER4_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(4)
#else
  #define _ENABLE_TIMER4_CAPTURE_ISR
#endif
#if defined(TIMER5_CAPT_vect)
  #define _ENABLE_TIMER5_CAPTURE_ISR _ENABLE_TIMER_CAPTURE_ISR(5)
#else
  #define _ENABLE_TIMER5_CAPTURE_ISR
#endif

#if defined(TIMER0_OVF_vect)
  #define _ENABLE_TIMER0_OVF_ISR _ENABLE_TIMER_OVF_ISR(0)
#else
  #define _ENABLE_TIMER0_OVF_ISR
#endif
#if defined(TIMER1_OVF_vect)
  #define _ENABLE_TIMER1_OVF_ISR _ENABLE_TIMER_OVF_ISR(1)
#else
  #define _ENABLE_TIMER1_OVF_ISR
#endif
#if defined(TIMER2_OVF_vect)
  #define _ENABLE_TIMER2_OVF_ISR _ENABLE_TIMER_OVF_ISR(2)
#else
  #define _ENABLE_TIMER2_OVF_ISR
#endif
#if defined(TIMER3_OVF_vect)
  #define _ENABLE_TIMER3_OVF_ISR _ENABLE_TIMER_OVF_ISR(3)
#else
  #define _ENABLE_TIMER3_OVF_ISR
#endif
#if defined(TIMER4_OVF_vect)
  #define _ENABLE_TIMER4_OVF_ISR _ENABLE_TIMER_OVF_ISR(4)
#else
  #define _ENABLE_TIMER4_OVF_ISR
#endif
#if defined(TIMER5_OVF_vect)
  #define _ENABLE_TIMER5_OVF_ISR _ENABLE_TIMER_OVF_ISR(5)
#else
  #define _ENABLE_TIMER5_OVF_ISR
#endif

#define _ENABLE_TIMER_COMPARE_ISR(N) \
  _ENABLE_TIMER##N##_COMPA_ISR       \
  _ENABLE_TIMER##N##_COMPB_ISR       \
  _ENABLE_TIMER##N##_COMPC_ISR
//------------------------------------------------------------------------------------------------
#endif

