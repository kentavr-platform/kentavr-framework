/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 * File: avr-mcu.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_MCU_H
#define AVR_MCU_H
#include <avr/io.h>
//------------------------------------------------------------------------------------------------
/**
 * @file avr-mcu.h
 * @brief MCU family classification.
 *
 * Exactly one family macro is defined for each MCU.
 */
//------------------------------------------------------------------------------------------------
#if defined(__AVR_AT90C8534__)             || \
      defined(__AVR_AT90CAN32__)           || \
      defined(__AVR_AT90CAN64__)           || \
      defined(__AVR_AT90CAN128__)          || \
      defined(__AVR_AT90PWM1__)            || \
      defined(__AVR_AT90PWM2__)            || \
      defined(__AVR_AT90PWM2B__)           || \
      defined(__AVR_AT90PWM3__)            || \
      defined(__AVR_AT90PWM3B__)           || \
      defined(__AVR_AT90PWM81__)           || \
      defined(__AVR_AT90PWM161__)          || \
      defined(__AVR_AT90PWM216__)          || \
      defined(__AVR_AT90PWM316__)          || \
      defined(__AVR_AT90S2313__)           || \
      defined(__AVR_AT90S2323__)           || \
      defined(__AVR_AT90S2333__)           || \
      defined(__AVR_AT90S2343__)           || \
      defined(__AVR_AT90S4414__)           || \
      defined(__AVR_AT90S4433__)           || \
      defined(__AVR_AT90S4434__)           || \
      defined(__AVR_AT90S8515__)           || \
      defined(__AVR_AT90S8535__)           || \
      defined(__AVR_AT90SCR100__)          || \
      defined(__AVR_AT90USB82__)           || \
      defined(__AVR_AT90USB162__)          || \
      defined(__AVR_AT90USB646__)          || \
      defined(__AVR_AT90USB647__)          || \
      defined(__AVR_AT90USB1286__)         || \
      defined(__AVR_AT90USB1287__)
  #define AVR_AT90_FAMILY   // classic AT90 series

#elif defined(__AVR_ATtiny13__)            || \
      defined(__AVR_ATtiny13A__)           || \
      defined(__AVR_ATtiny22__)            || \
      defined(__AVR_ATtiny24__)            || \
      defined(__AVR_ATtiny24A__)           || \
      defined(__AVR_ATtiny25__)            || \
      defined(__AVR_ATtiny26__)            || \
      defined(__AVR_ATtiny43U__)           || \
      defined(__AVR_ATtiny44__)            || \
      defined(__AVR_ATtiny44A__)           || \
      defined(__AVR_ATtiny45__)            || \
      defined(__AVR_ATtiny48__)            || \
      defined(__AVR_ATtiny84__)            || \
      defined(__AVR_ATtiny84A__)           || \
      defined(__AVR_ATtiny85__)            || \
      defined(__AVR_ATtiny87__)            || \
      defined(__AVR_ATtiny88__)            || \
      defined(__AVR_ATtiny167__)           || \
      defined(__AVR_ATtiny261__)           || \
      defined(__AVR_ATtiny261A__)          || \
      defined(__AVR_ATtiny441__)           || \
      defined(__AVR_ATtiny461__)           || \
      defined(__AVR_ATtiny461A__)          || \
      defined(__AVR_ATtiny828__)           || \
      defined(__AVR_ATtiny841__)           || \
      defined(__AVR_ATtiny861__)           || \
      defined(__AVR_ATtiny861A__)          || \
      defined(__AVR_ATtiny1634__)          || \
      defined(__AVR_ATtiny2313__)          || \
      defined(__AVR_ATtiny2313A__)         || \
      defined(__AVR_ATtiny4313__)
  #define AVR_TINY_FAMILY   // classic ATtiny with full AVR registers

#elif defined(__AVR_ATtiny4__)             || \
      defined(__AVR_ATtiny5__)             || \
      defined(__AVR_ATtiny9__)             || \
      defined(__AVR_ATtiny10__)            || \
      defined(__AVR_ATtiny20__)            || \
      defined(__AVR_ATtiny40__)            || \
      defined(__AVR_ATtiny102__)           || \
      defined(__AVR_ATtiny104__)
  #define AVR_RTINY_FAMILY  // reduced-core ATtiny (AVRrc)

#elif defined(__AVR_ATtiny202__)           || \
      defined(__AVR_ATtiny204__)           || \
      defined(__AVR_ATtiny212__)           || \
      defined(__AVR_ATtiny214__)           || \
      defined(__AVR_ATtiny402__)           || \
      defined(__AVR_ATtiny404__)           || \
      defined(__AVR_ATtiny406__)           || \
      defined(__AVR_ATtiny412__)           || \
      defined(__AVR_ATtiny414__)           || \
      defined(__AVR_ATtiny416__)           || \
      defined(__AVR_ATtiny416AUTO__)       || \
      defined(__AVR_ATtiny417__)           || \
      defined(__AVR_ATtiny424__)           || \
      defined(__AVR_ATtiny426__)           || \
      defined(__AVR_ATtiny427__)           || \
      defined(__AVR_ATtiny804__)           || \
      defined(__AVR_ATtiny806__)           || \
      defined(__AVR_ATtiny807__)           || \
      defined(__AVR_ATtiny814__)           || \
      defined(__AVR_ATtiny816__)           || \
      defined(__AVR_ATtiny817__)           || \
      defined(__AVR_ATtiny824__)           || \
      defined(__AVR_ATtiny826__)           || \
      defined(__AVR_ATtiny827__)           || \
      defined(__AVR_ATtiny1604__)          || \
      defined(__AVR_ATtiny1606__)          || \
      defined(__AVR_ATtiny1607__)          || \
      defined(__AVR_ATtiny1614__)          || \
      defined(__AVR_ATtiny1616__)          || \
      defined(__AVR_ATtiny1617__)          || \
      defined(__AVR_ATtiny1624__)          || \
      defined(__AVR_ATtiny1626__)          || \
      defined(__AVR_ATtiny1627__)          || \
      defined(__AVR_ATtiny3214__)          || \
      defined(__AVR_ATtiny3216__)          || \
      defined(__AVR_ATtiny3217__)          || \
      defined(__AVR_ATtiny3224__)          || \
      defined(__AVR_ATtiny3226__)          || \
      defined(__AVR_ATtiny3227__)
  #define AVR_XTINY_FAMILY  // tinyAVR 0-series, 1-series and 2-series

#elif defined(__AVR_ATmega8__)             || \
      defined(__AVR_ATmega8A__)            || \
      defined(__AVR_ATmega8HVA__)          || \
      defined(__AVR_ATmega8U2__)           || \
      defined(__AVR_ATmega16__)            || \
      defined(__AVR_ATmega16A__)           || \
      defined(__AVR_ATmega16HVA2__)        || \
      defined(__AVR_ATmega16HVA__)         || \
      defined(__AVR_ATmega16HVB__)         || \
      defined(__AVR_ATmega16HVBREVB__)     || \
      defined(__AVR_ATmega16M1__)          || \
      defined(__AVR_ATmega16U2__)          || \
      defined(__AVR_ATmega16U4__)          || \
      defined(__AVR_ATmega32__)            || \
      defined(__AVR_ATmega32A__)           || \
      defined(__AVR_ATmega32C1__)          || \
      defined(__AVR_ATmega32HVB__)         || \
      defined(__AVR_ATmega32HVBREVB__)     || \
      defined(__AVR_ATmega32M1__)          || \
      defined(__AVR_ATmega32U2__)          || \
      defined(__AVR_ATmega32U4__)          || \
      defined(__AVR_ATmega32U6__)          || \
      defined(__AVR_ATmega48__)            || \
      defined(__AVR_ATmega48A__)           || \
      defined(__AVR_ATmega48P__)           || \
      defined(__AVR_ATmega48PA__)          || \
      defined(__AVR_ATmega48PB__)          || \
      defined(__AVR_ATmega64__)            || \
      defined(__AVR_ATmega64A__)           || \
      defined(__AVR_ATmega64C1__)          || \
      defined(__AVR_ATmega64HVE2__)        || \
      defined(__AVR_ATmega64HVE__)         || \
      defined(__AVR_ATmega64M1__)          || \
      defined(__AVR_ATmega64RFR2__)        || \
      defined(__AVR_ATmega88__)            || \
      defined(__AVR_ATmega88A__)           || \
      defined(__AVR_ATmega88P__)           || \
      defined(__AVR_ATmega88PA__)          || \
      defined(__AVR_ATmega88PB__)          || \
      defined(__AVR_ATmega103__)           || \
      defined(__AVR_ATmega128__)           || \
      defined(__AVR_ATmega128A__)          || \
      defined(__AVR_ATmega128RFA1__)       || \
      defined(__AVR_ATmega128RFR2__)       || \
      defined(__AVR_ATmega161__)           || \
      defined(__AVR_ATmega162__)           || \
      defined(__AVR_ATmega163__)           || \
      defined(__AVR_ATmega164A__)          || \
      defined(__AVR_ATmega164P__)          || \
      defined(__AVR_ATmega164PA__)         || \
      defined(__AVR_ATmega165__)           || \
      defined(__AVR_ATmega165A__)          || \
      defined(__AVR_ATmega165P__)          || \
      defined(__AVR_ATmega165PA__)         || \
      defined(__AVR_ATmega168__)           || \
      defined(__AVR_ATmega168A__)          || \
      defined(__AVR_ATmega168P__)          || \
      defined(__AVR_ATmega168PA__)         || \
      defined(__AVR_ATmega168PB__)         || \
      defined(__AVR_ATmega169__)           || \
      defined(__AVR_ATmega169A__)          || \
      defined(__AVR_ATmega169P__)          || \
      defined(__AVR_ATmega169PA__)         || \
      defined(__AVR_ATmega256RFR2__)       || \
      defined(__AVR_ATmega323__)           || \
      defined(__AVR_ATmega324A__)          || \
      defined(__AVR_ATmega324P__)          || \
      defined(__AVR_ATmega324PA__)         || \
      defined(__AVR_ATmega324PB__)         || \
      defined(__AVR_ATmega325__)           || \
      defined(__AVR_ATmega325A__)          || \
      defined(__AVR_ATmega325P__)          || \
      defined(__AVR_ATmega325PA__)         || \
      defined(__AVR_ATmega328__)           || \
      defined(__AVR_ATmega328P__)          || \
      defined(__AVR_ATmega328PB__)         || \
      defined(__AVR_ATmega329__)           || \
      defined(__AVR_ATmega329A__)          || \
      defined(__AVR_ATmega329P__)          || \
      defined(__AVR_ATmega329PA__)         || \
      defined(__AVR_ATmega406__)           || \
      defined(__AVR_ATmega640__)           || \
      defined(__AVR_ATmega644__)           || \
      defined(__AVR_ATmega644A__)          || \
      defined(__AVR_ATmega644P__)          || \
      defined(__AVR_ATmega644PA__)         || \
      defined(__AVR_ATmega644RFR2__)       || \
      defined(__AVR_ATmega645__)           || \
      defined(__AVR_ATmega645A__)          || \
      defined(__AVR_ATmega645P__)          || \
      defined(__AVR_ATmega649__)           || \
      defined(__AVR_ATmega649A__)          || \
      defined(__AVR_ATmega649P__)          || \
      defined(__AVR_ATmega1280__)          || \
      defined(__AVR_ATmega1281__)          || \
      defined(__AVR_ATmega1284__)          || \
      defined(__AVR_ATmega1284P__)         || \
      defined(__AVR_ATmega1284RFR2__)      || \
      defined(__AVR_ATmega2560__)          || \
      defined(__AVR_ATmega2561__)          || \
      defined(__AVR_ATmega2564RFR2__)      || \
      defined(__AVR_ATmega3250__)          || \
      defined(__AVR_ATmega3250A__)         || \
      defined(__AVR_ATmega3250P__)         || \
      defined(__AVR_ATmega3250PA__)        || \
      defined(__AVR_ATmega3290__)          || \
      defined(__AVR_ATmega3290A__)         || \
      defined(__AVR_ATmega3290P__)         || \
      defined(__AVR_ATmega3290PA__)        || \
      defined(__AVR_ATmega6450__)          || \
      defined(__AVR_ATmega6450A__)         || \
      defined(__AVR_ATmega6450P__)         || \
      defined(__AVR_ATmega6490__)          || \
      defined(__AVR_ATmega6490A__)         || \
      defined(__AVR_ATmega6490P__)         || \
      defined(__AVR_ATmega8515__)          || \
      defined(__AVR_ATmega8535__)
  #define AVR_MEGA_FAMILY   // classic mega series

#elif defined(__AVR_ATmega808__)           || \
      defined(__AVR_ATmega809__)           || \
      defined(__AVR_ATmega1608__)          || \
      defined(__AVR_ATmega1609__)          || \
      defined(__AVR_ATmega3208__)          || \
      defined(__AVR_ATmega3209__)          || \
      defined(__AVR_ATmega4808__)          || \
      defined(__AVR_ATmega4809__)
  #define AVR_MEGA0_FAMILY  // megaAVR 0-series

#elif defined(__AVR_ATxmega8E5__)          || \
      defined(__AVR_ATxmega16A4__)         || \
      defined(__AVR_ATxmega16A4U__)        || \
      defined(__AVR_ATxmega16C4__)         || \
      defined(__AVR_ATxmega16D4__)         || \
      defined(__AVR_ATxmega16E5__)         || \
      defined(__AVR_ATxmega32A4__)         || \
      defined(__AVR_ATxmega32A4U__)        || \
      defined(__AVR_ATxmega32C3__)         || \
      defined(__AVR_ATxmega32C4__)         || \
      defined(__AVR_ATxmega32D3__)         || \
      defined(__AVR_ATxmega32D4__)         || \
      defined(__AVR_ATxmega32E5__)         || \
      defined(__AVR_ATxmega64A1__)         || \
      defined(__AVR_ATxmega64A1U__)        || \
      defined(__AVR_ATxmega64A3__)         || \
      defined(__AVR_ATxmega64A3U__)        || \
      defined(__AVR_ATxmega64A4U__)        || \
      defined(__AVR_ATxmega64B1__)         || \
      defined(__AVR_ATxmega64B3__)         || \
      defined(__AVR_ATxmega64C3__)         || \
      defined(__AVR_ATxmega64D3__)         || \
      defined(__AVR_ATxmega64D4__)         || \
      defined(__AVR_ATxmega128A1__)        || \
      defined(__AVR_ATxmega128A1U__)       || \
      defined(__AVR_ATxmega128A3__)        || \
      defined(__AVR_ATxmega128A3U__)       || \
      defined(__AVR_ATxmega128A4U__)       || \
      defined(__AVR_ATxmega128B1__)        || \
      defined(__AVR_ATxmega128B3__)        || \
      defined(__AVR_ATxmega128C3__)        || \
      defined(__AVR_ATxmega128D3__)        || \
      defined(__AVR_ATxmega128D4__)        || \
      defined(__AVR_ATxmega192A3__)        || \
      defined(__AVR_ATxmega192A3U__)       || \
      defined(__AVR_ATxmega192C3__)        || \
      defined(__AVR_ATxmega192D3__)        || \
      defined(__AVR_ATxmega256A3__)        || \
      defined(__AVR_ATxmega256A3B__)       || \
      defined(__AVR_ATxmega256A3BU__)      || \
      defined(__AVR_ATxmega256A3U__)       || \
      defined(__AVR_ATxmega256C3__)        || \
      defined(__AVR_ATxmega256D3__)        || \
      defined(__AVR_ATxmega384C3__)        || \
      defined(__AVR_ATxmega384D3__)
  #define AVR_XMEGA_FAMILY  // xmega series

#elif defined(__AVR_AVR16DD14__)           || \
      defined(__AVR_AVR16DD20__)           || \
      defined(__AVR_AVR16DD28__)           || \
      defined(__AVR_AVR16DD32__)           || \
      defined(__AVR_AVR16DU14__)           || \
      defined(__AVR_AVR16DU20__)           || \
      defined(__AVR_AVR16DU28__)           || \
      defined(__AVR_AVR16DU32__)           || \
      defined(__AVR_AVR32DA28__)           || \
      defined(__AVR_AVR32DA28S__)          || \
      defined(__AVR_AVR32DA32__)           || \
      defined(__AVR_AVR32DA32S__)          || \
      defined(__AVR_AVR32DA48__)           || \
      defined(__AVR_AVR32DA48S__)          || \
      defined(__AVR_AVR32DB28__)           || \
      defined(__AVR_AVR32DB32__)           || \
      defined(__AVR_AVR32DB48__)           || \
      defined(__AVR_AVR32DD14__)           || \
      defined(__AVR_AVR32DD20__)           || \
      defined(__AVR_AVR32DD28__)           || \
      defined(__AVR_AVR32DD32__)           || \
      defined(__AVR_AVR32DU14__)           || \
      defined(__AVR_AVR32DU20__)           || \
      defined(__AVR_AVR32DU28__)           || \
      defined(__AVR_AVR32DU32__)           || \
      defined(__AVR_AVR64DA28__)           || \
      defined(__AVR_AVR64DA28S__)          || \
      defined(__AVR_AVR64DA32__)           || \
      defined(__AVR_AVR64DA32S__)          || \
      defined(__AVR_AVR64DA48__)           || \
      defined(__AVR_AVR64DA48S__)          || \
      defined(__AVR_AVR64DA64__)           || \
      defined(__AVR_AVR64DA64S__)          || \
      defined(__AVR_AVR64DB28__)           || \
      defined(__AVR_AVR64DB32__)           || \
      defined(__AVR_AVR64DB48__)           || \
      defined(__AVR_AVR64DB64__)           || \
      defined(__AVR_AVR64DD14__)           || \
      defined(__AVR_AVR64DD20__)           || \
      defined(__AVR_AVR64DD28__)           || \
      defined(__AVR_AVR64DD32__)           || \
      defined(__AVR_AVR64DU28__)           || \
      defined(__AVR_AVR64DU32__)           || \
      defined(__AVR_AVR128DA28__)          || \
      defined(__AVR_AVR128DA28S__)         || \
      defined(__AVR_AVR128DA32__)          || \
      defined(__AVR_AVR128DA32S__)         || \
      defined(__AVR_AVR128DA48__)          || \
      defined(__AVR_AVR128DA48S__)         || \
      defined(__AVR_AVR128DA64__)          || \
      defined(__AVR_AVR128DA64S__)         || \
      defined(__AVR_AVR128DB28__)          || \
      defined(__AVR_AVR128DB32__)          || \
      defined(__AVR_AVR128DB48__)          || \
      defined(__AVR_AVR128DB64__)
  #define AVR_DX_FAMILY     // AVR Dx series

#elif defined(__AVR_AVR16EA28__)           || \
      defined(__AVR_AVR16EA32__)           || \
      defined(__AVR_AVR16EA48__)           || \
      defined(__AVR_AVR16EB14__)           || \
      defined(__AVR_AVR16EB20__)           || \
      defined(__AVR_AVR16EB28__)           || \
      defined(__AVR_AVR16EB32__)           || \
      defined(__AVR_AVR32EA28__)           || \
      defined(__AVR_AVR32EA32__)           || \
      defined(__AVR_AVR32EA48__)           || \
      defined(__AVR_AVR32EB14__)           || \
      defined(__AVR_AVR32EB20__)           || \
      defined(__AVR_AVR32EB28__)           || \
      defined(__AVR_AVR32EB32__)           || \
      defined(__AVR_AVR64EA28__)           || \
      defined(__AVR_AVR64EA32__)           || \
      defined(__AVR_AVR64EA48__)
  #define AVR_EX_FAMILY     // AVR Ex series
#else
  #error "MCU is not listed in AVR/avr-mcu.h"
#endif
//------------------------------------------------------------------------------------------------
#endif // AVR_MCU_H
