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
 * @brief MCU family and subfamily classification.
 *
 * Exactly one broad family and one subfamily macro are defined for each MCU.
 * For example, ATtiny85 defines AVR_TINY_FAMILY and AVR_TINY_X5_FAMILY;
 * ATmega1284P defines AVR_MEGA_FAMILY and AVR_MEGA_X4_FAMILY.
 * Subfamilies identify product lines; memory sizes, register availability and
 * peripheral capabilities still depend on the specific MCU.
 */
//------------------------------------------------------------------------------------------------
// classic AT90 series
#if defined(__AVR_AT90C8534__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_C8534_FAMILY

#elif defined(__AVR_AT90CAN32__)               || \
      defined(__AVR_AT90CAN64__)               || \
      defined(__AVR_AT90CAN128__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_CAN_FAMILY

#elif defined(__AVR_AT90PWM1__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM1_FAMILY

#elif defined(__AVR_AT90PWM2__)                || \
      defined(__AVR_AT90PWM3__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM2_3_FAMILY

#elif defined(__AVR_AT90PWM2B__)               || \
      defined(__AVR_AT90PWM3B__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM2B_3B_FAMILY

#elif defined(__AVR_AT90PWM81__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM81_FAMILY

#elif defined(__AVR_AT90PWM161__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM161_FAMILY

#elif defined(__AVR_AT90PWM216__)              || \
      defined(__AVR_AT90PWM316__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_PWM216_316_FAMILY

#elif defined(__AVR_AT90S2313__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S2313_FAMILY

#elif defined(__AVR_AT90S2323__)               || \
      defined(__AVR_AT90S2343__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S2323_2343_FAMILY

#elif defined(__AVR_AT90S2333__)               || \
      defined(__AVR_AT90S4433__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S2333_4433_FAMILY

#elif defined(__AVR_AT90S4414__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S4414_FAMILY

#elif defined(__AVR_AT90S4434__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S4434_FAMILY

#elif defined(__AVR_AT90S8515__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S8515_FAMILY

#elif defined(__AVR_AT90S8535__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_S8535_FAMILY

#elif defined(__AVR_AT90SCR100__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_SCR100_FAMILY

#elif defined(__AVR_AT90USB82__)               || \
      defined(__AVR_AT90USB162__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_USB_X2_FAMILY

#elif defined(__AVR_AT90USB646__)              || \
      defined(__AVR_AT90USB647__)              || \
      defined(__AVR_AT90USB1286__)             || \
      defined(__AVR_AT90USB1287__)
  #define AVR_AT90_FAMILY
  #define AVR_AT90_USB_X6_X7_FAMILY

//------------------------------------------------------------------------------------------------
// classic ATtiny with full AVR registers
#elif defined(__AVR_ATtiny13__)                || \
      defined(__AVR_ATtiny13A__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_13_FAMILY

#elif defined(__AVR_ATtiny22__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_22_FAMILY

#elif defined(__AVR_ATtiny24__)                || \
      defined(__AVR_ATtiny24A__)               || \
      defined(__AVR_ATtiny44__)                || \
      defined(__AVR_ATtiny44A__)               || \
      defined(__AVR_ATtiny84__)                || \
      defined(__AVR_ATtiny84A__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X4_FAMILY

#elif defined(__AVR_ATtiny25__)                || \
      defined(__AVR_ATtiny45__)                || \
      defined(__AVR_ATtiny85__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X5_FAMILY

#elif defined(__AVR_ATtiny26__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_26_FAMILY

#elif defined(__AVR_ATtiny43U__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_43U_FAMILY

#elif defined(__AVR_ATtiny48__)                || \
      defined(__AVR_ATtiny88__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X8_FAMILY

#elif defined(__AVR_ATtiny87__)                || \
      defined(__AVR_ATtiny167__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X7_FAMILY

#elif defined(__AVR_ATtiny261__)               || \
      defined(__AVR_ATtiny261A__)              || \
      defined(__AVR_ATtiny461__)               || \
      defined(__AVR_ATtiny461A__)              || \
      defined(__AVR_ATtiny861__)               || \
      defined(__AVR_ATtiny861A__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X61_FAMILY

#elif defined(__AVR_ATtiny441__)               || \
      defined(__AVR_ATtiny841__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X41_FAMILY

#elif defined(__AVR_ATtiny828__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_828_FAMILY

#elif defined(__AVR_ATtiny1634__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_1634_FAMILY

#elif defined(__AVR_ATtiny2313__)              || \
      defined(__AVR_ATtiny2313A__)             || \
      defined(__AVR_ATtiny4313__)
  #define AVR_TINY_FAMILY
  #define AVR_TINY_X313_FAMILY

//------------------------------------------------------------------------------------------------
// reduced-core ATtiny (AVRrc)
#elif defined(__AVR_ATtiny4__)                 || \
      defined(__AVR_ATtiny5__)                 || \
      defined(__AVR_ATtiny9__)                 || \
      defined(__AVR_ATtiny10__)
  #define AVR_RTINY_FAMILY
  #define AVR_RTINY_4_5_9_10_FAMILY

#elif defined(__AVR_ATtiny20__)
  #define AVR_RTINY_FAMILY
  #define AVR_RTINY_20_FAMILY

#elif defined(__AVR_ATtiny40__)
  #define AVR_RTINY_FAMILY
  #define AVR_RTINY_40_FAMILY

#elif defined(__AVR_ATtiny102__)               || \
      defined(__AVR_ATtiny104__)
  #define AVR_RTINY_FAMILY
  #define AVR_RTINY_102_104_FAMILY

//------------------------------------------------------------------------------------------------
// tinyAVR 0-series, 1-series and 2-series
#elif defined(__AVR_ATtiny202__)               || \
      defined(__AVR_ATtiny204__)               || \
      defined(__AVR_ATtiny402__)               || \
      defined(__AVR_ATtiny404__)               || \
      defined(__AVR_ATtiny406__)               || \
      defined(__AVR_ATtiny804__)               || \
      defined(__AVR_ATtiny806__)               || \
      defined(__AVR_ATtiny807__)               || \
      defined(__AVR_ATtiny1604__)              || \
      defined(__AVR_ATtiny1606__)              || \
      defined(__AVR_ATtiny1607__)
  #define AVR_XTINY_FAMILY
  #define AVR_XTINY_0_FAMILY

#elif defined(__AVR_ATtiny212__)               || \
      defined(__AVR_ATtiny214__)               || \
      defined(__AVR_ATtiny412__)               || \
      defined(__AVR_ATtiny414__)               || \
      defined(__AVR_ATtiny416__)               || \
      defined(__AVR_ATtiny416AUTO__)           || \
      defined(__AVR_ATtiny417__)               || \
      defined(__AVR_ATtiny814__)               || \
      defined(__AVR_ATtiny816__)               || \
      defined(__AVR_ATtiny817__)               || \
      defined(__AVR_ATtiny1614__)              || \
      defined(__AVR_ATtiny1616__)              || \
      defined(__AVR_ATtiny1617__)              || \
      defined(__AVR_ATtiny3214__)              || \
      defined(__AVR_ATtiny3216__)              || \
      defined(__AVR_ATtiny3217__)
  #define AVR_XTINY_FAMILY
  #define AVR_XTINY_1_FAMILY

#elif defined(__AVR_ATtiny424__)               || \
      defined(__AVR_ATtiny426__)               || \
      defined(__AVR_ATtiny427__)               || \
      defined(__AVR_ATtiny824__)               || \
      defined(__AVR_ATtiny826__)               || \
      defined(__AVR_ATtiny827__)               || \
      defined(__AVR_ATtiny1624__)              || \
      defined(__AVR_ATtiny1626__)              || \
      defined(__AVR_ATtiny1627__)              || \
      defined(__AVR_ATtiny3224__)              || \
      defined(__AVR_ATtiny3226__)              || \
      defined(__AVR_ATtiny3227__)
  #define AVR_XTINY_FAMILY
  #define AVR_XTINY_2_FAMILY

//------------------------------------------------------------------------------------------------
// classic mega series
#elif defined(__AVR_ATmega8__)                 || \
      defined(__AVR_ATmega8A__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_8_FAMILY

#elif defined(__AVR_ATmega16__)                || \
      defined(__AVR_ATmega16A__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_16_FAMILY

#elif defined(__AVR_ATmega32__)                || \
      defined(__AVR_ATmega32A__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_32_FAMILY

#elif defined(__AVR_ATmega64__)                || \
      defined(__AVR_ATmega64A__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_64_FAMILY

#elif defined(__AVR_ATmega128__)               || \
      defined(__AVR_ATmega128A__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_128_FAMILY

#elif defined(__AVR_ATmega103__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_103_FAMILY

#elif defined(__AVR_ATmega161__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_161_FAMILY

#elif defined(__AVR_ATmega162__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_162_FAMILY

#elif defined(__AVR_ATmega163__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_163_FAMILY

#elif defined(__AVR_ATmega323__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_323_FAMILY

#elif defined(__AVR_ATmega8515__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_8515_FAMILY

#elif defined(__AVR_ATmega8535__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_8535_FAMILY

#elif defined(__AVR_ATmega48__)                || \
      defined(__AVR_ATmega48A__)               || \
      defined(__AVR_ATmega48P__)               || \
      defined(__AVR_ATmega48PA__)              || \
      defined(__AVR_ATmega88__)                || \
      defined(__AVR_ATmega88A__)               || \
      defined(__AVR_ATmega88P__)               || \
      defined(__AVR_ATmega88PA__)              || \
      defined(__AVR_ATmega168__)               || \
      defined(__AVR_ATmega168A__)              || \
      defined(__AVR_ATmega168P__)              || \
      defined(__AVR_ATmega168PA__)             || \
      defined(__AVR_ATmega328__)               || \
      defined(__AVR_ATmega328P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X8_FAMILY

#elif defined(__AVR_ATmega48PB__)              || \
      defined(__AVR_ATmega88PB__)              || \
      defined(__AVR_ATmega168PB__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X8PB_FAMILY

#elif defined(__AVR_ATmega328PB__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_328PB_FAMILY

#elif defined(__AVR_ATmega164A__)              || \
      defined(__AVR_ATmega164P__)              || \
      defined(__AVR_ATmega164PA__)             || \
      defined(__AVR_ATmega324A__)              || \
      defined(__AVR_ATmega324P__)              || \
      defined(__AVR_ATmega324PA__)             || \
      defined(__AVR_ATmega644__)               || \
      defined(__AVR_ATmega644A__)              || \
      defined(__AVR_ATmega644P__)              || \
      defined(__AVR_ATmega644PA__)             || \
      defined(__AVR_ATmega1284__)              || \
      defined(__AVR_ATmega1284P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X4_FAMILY

#elif defined(__AVR_ATmega324PB__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_324PB_FAMILY

#elif defined(__AVR_ATmega165__)               || \
      defined(__AVR_ATmega165A__)              || \
      defined(__AVR_ATmega165P__)              || \
      defined(__AVR_ATmega165PA__)             || \
      defined(__AVR_ATmega325__)               || \
      defined(__AVR_ATmega325A__)              || \
      defined(__AVR_ATmega325P__)              || \
      defined(__AVR_ATmega325PA__)             || \
      defined(__AVR_ATmega645__)               || \
      defined(__AVR_ATmega645A__)              || \
      defined(__AVR_ATmega645P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X5_FAMILY

#elif defined(__AVR_ATmega3250__)              || \
      defined(__AVR_ATmega3250A__)             || \
      defined(__AVR_ATmega3250P__)             || \
      defined(__AVR_ATmega3250PA__)            || \
      defined(__AVR_ATmega6450__)              || \
      defined(__AVR_ATmega6450A__)             || \
      defined(__AVR_ATmega6450P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X50_FAMILY

#elif defined(__AVR_ATmega169__)               || \
      defined(__AVR_ATmega169A__)              || \
      defined(__AVR_ATmega169P__)              || \
      defined(__AVR_ATmega169PA__)             || \
      defined(__AVR_ATmega329__)               || \
      defined(__AVR_ATmega329A__)              || \
      defined(__AVR_ATmega329P__)              || \
      defined(__AVR_ATmega329PA__)             || \
      defined(__AVR_ATmega649__)               || \
      defined(__AVR_ATmega649A__)              || \
      defined(__AVR_ATmega649P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X9_FAMILY

#elif defined(__AVR_ATmega3290__)              || \
      defined(__AVR_ATmega3290A__)             || \
      defined(__AVR_ATmega3290P__)             || \
      defined(__AVR_ATmega3290PA__)            || \
      defined(__AVR_ATmega6490__)              || \
      defined(__AVR_ATmega6490A__)             || \
      defined(__AVR_ATmega6490P__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X90_FAMILY

#elif defined(__AVR_ATmega640__)               || \
      defined(__AVR_ATmega1280__)              || \
      defined(__AVR_ATmega2560__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X0_FAMILY

#elif defined(__AVR_ATmega1281__)              || \
      defined(__AVR_ATmega2561__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X1_FAMILY

#elif defined(__AVR_ATmega8U2__)               || \
      defined(__AVR_ATmega16U2__)              || \
      defined(__AVR_ATmega32U2__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_U2_FAMILY

#elif defined(__AVR_ATmega16U4__)              || \
      defined(__AVR_ATmega32U4__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_U4_FAMILY

#elif defined(__AVR_ATmega32U6__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_32U6_FAMILY

#elif defined(__AVR_ATmega16M1__)              || \
      defined(__AVR_ATmega32M1__)              || \
      defined(__AVR_ATmega64M1__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_M1_FAMILY

#elif defined(__AVR_ATmega32C1__)              || \
      defined(__AVR_ATmega64C1__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_C1_FAMILY

#elif defined(__AVR_ATmega8HVA__)              || \
      defined(__AVR_ATmega16HVA__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_HVA_FAMILY

#elif defined(__AVR_ATmega16HVA2__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_16HVA2_FAMILY

#elif defined(__AVR_ATmega16HVB__)             || \
      defined(__AVR_ATmega32HVB__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_HVB_FAMILY

#elif defined(__AVR_ATmega16HVBREVB__)         || \
      defined(__AVR_ATmega32HVBREVB__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_HVB_REVB_FAMILY

#elif defined(__AVR_ATmega64HVE__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_64HVE_FAMILY

#elif defined(__AVR_ATmega64HVE2__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_64HVE2_FAMILY

#elif defined(__AVR_ATmega406__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_406_FAMILY

#elif defined(__AVR_ATmega128RFA1__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_RFA1_FAMILY

#elif defined(__AVR_ATmega64RFR2__)            || \
      defined(__AVR_ATmega128RFR2__)           || \
      defined(__AVR_ATmega256RFR2__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_RFR2_FAMILY

#elif defined(__AVR_ATmega644RFR2__)           || \
      defined(__AVR_ATmega1284RFR2__)          || \
      defined(__AVR_ATmega2564RFR2__)
  #define AVR_MEGA_FAMILY
  #define AVR_MEGA_X4RFR2_FAMILY

//------------------------------------------------------------------------------------------------
// megaAVR 0-series
#elif defined(__AVR_ATmega808__)               || \
      defined(__AVR_ATmega1608__)              || \
      defined(__AVR_ATmega3208__)              || \
      defined(__AVR_ATmega4808__)
  #define AVR_MEGA0_FAMILY
  #define AVR_MEGA0_X08_FAMILY

#elif defined(__AVR_ATmega809__)               || \
      defined(__AVR_ATmega1609__)              || \
      defined(__AVR_ATmega3209__)              || \
      defined(__AVR_ATmega4809__)
  #define AVR_MEGA0_FAMILY
  #define AVR_MEGA0_X09_FAMILY

//------------------------------------------------------------------------------------------------
// xmega series
#elif defined(__AVR_ATxmega64A1__)             || \
      defined(__AVR_ATxmega128A1__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A1_FAMILY

#elif defined(__AVR_ATxmega64A1U__)            || \
      defined(__AVR_ATxmega128A1U__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A1U_FAMILY

#elif defined(__AVR_ATxmega64A3__)             || \
      defined(__AVR_ATxmega128A3__)            || \
      defined(__AVR_ATxmega192A3__)            || \
      defined(__AVR_ATxmega256A3__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A3_FAMILY

#elif defined(__AVR_ATxmega256A3B__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A3B_FAMILY

#elif defined(__AVR_ATxmega256A3BU__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A3BU_FAMILY

#elif defined(__AVR_ATxmega64A3U__)            || \
      defined(__AVR_ATxmega128A3U__)           || \
      defined(__AVR_ATxmega192A3U__)           || \
      defined(__AVR_ATxmega256A3U__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A3U_FAMILY

#elif defined(__AVR_ATxmega16A4__)             || \
      defined(__AVR_ATxmega32A4__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A4_FAMILY

#elif defined(__AVR_ATxmega16A4U__)            || \
      defined(__AVR_ATxmega32A4U__)            || \
      defined(__AVR_ATxmega64A4U__)            || \
      defined(__AVR_ATxmega128A4U__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_A4U_FAMILY

#elif defined(__AVR_ATxmega64B1__)             || \
      defined(__AVR_ATxmega128B1__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_B1_FAMILY

#elif defined(__AVR_ATxmega64B3__)             || \
      defined(__AVR_ATxmega128B3__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_B3_FAMILY

#elif defined(__AVR_ATxmega32C3__)             || \
      defined(__AVR_ATxmega64C3__)             || \
      defined(__AVR_ATxmega128C3__)            || \
      defined(__AVR_ATxmega192C3__)            || \
      defined(__AVR_ATxmega256C3__)            || \
      defined(__AVR_ATxmega384C3__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_C3_FAMILY

#elif defined(__AVR_ATxmega16C4__)             || \
      defined(__AVR_ATxmega32C4__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_C4_FAMILY

#elif defined(__AVR_ATxmega32D3__)             || \
      defined(__AVR_ATxmega64D3__)             || \
      defined(__AVR_ATxmega128D3__)            || \
      defined(__AVR_ATxmega192D3__)            || \
      defined(__AVR_ATxmega256D3__)            || \
      defined(__AVR_ATxmega384D3__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_D3_FAMILY

#elif defined(__AVR_ATxmega16D4__)             || \
      defined(__AVR_ATxmega32D4__)             || \
      defined(__AVR_ATxmega64D4__)             || \
      defined(__AVR_ATxmega128D4__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_D4_FAMILY

#elif defined(__AVR_ATxmega8E5__)              || \
      defined(__AVR_ATxmega16E5__)             || \
      defined(__AVR_ATxmega32E5__)
  #define AVR_XMEGA_FAMILY
  #define AVR_XMEGA_E5_FAMILY

//------------------------------------------------------------------------------------------------
// AVR Dx series
#elif defined(__AVR_AVR32DA28__)               || \
      defined(__AVR_AVR32DA28S__)              || \
      defined(__AVR_AVR32DA32__)               || \
      defined(__AVR_AVR32DA32S__)              || \
      defined(__AVR_AVR32DA48__)               || \
      defined(__AVR_AVR32DA48S__)              || \
      defined(__AVR_AVR64DA28__)               || \
      defined(__AVR_AVR64DA28S__)              || \
      defined(__AVR_AVR64DA32__)               || \
      defined(__AVR_AVR64DA32S__)              || \
      defined(__AVR_AVR64DA48__)               || \
      defined(__AVR_AVR64DA48S__)              || \
      defined(__AVR_AVR64DA64__)               || \
      defined(__AVR_AVR64DA64S__)              || \
      defined(__AVR_AVR128DA28__)              || \
      defined(__AVR_AVR128DA28S__)             || \
      defined(__AVR_AVR128DA32__)              || \
      defined(__AVR_AVR128DA32S__)             || \
      defined(__AVR_AVR128DA48__)              || \
      defined(__AVR_AVR128DA48S__)             || \
      defined(__AVR_AVR128DA64__)              || \
      defined(__AVR_AVR128DA64S__)
  #define AVR_DX_FAMILY
  #define AVR_DA_FAMILY

#elif defined(__AVR_AVR32DB28__)               || \
      defined(__AVR_AVR32DB32__)               || \
      defined(__AVR_AVR32DB48__)               || \
      defined(__AVR_AVR64DB28__)               || \
      defined(__AVR_AVR64DB32__)               || \
      defined(__AVR_AVR64DB48__)               || \
      defined(__AVR_AVR64DB64__)               || \
      defined(__AVR_AVR128DB28__)              || \
      defined(__AVR_AVR128DB32__)              || \
      defined(__AVR_AVR128DB48__)              || \
      defined(__AVR_AVR128DB64__)
  #define AVR_DX_FAMILY
  #define AVR_DB_FAMILY

#elif defined(__AVR_AVR16DD14__)               || \
      defined(__AVR_AVR16DD20__)               || \
      defined(__AVR_AVR16DD28__)               || \
      defined(__AVR_AVR16DD32__)               || \
      defined(__AVR_AVR32DD14__)               || \
      defined(__AVR_AVR32DD20__)               || \
      defined(__AVR_AVR32DD28__)               || \
      defined(__AVR_AVR32DD32__)               || \
      defined(__AVR_AVR64DD14__)               || \
      defined(__AVR_AVR64DD20__)               || \
      defined(__AVR_AVR64DD28__)               || \
      defined(__AVR_AVR64DD32__)
  #define AVR_DX_FAMILY
  #define AVR_DD_FAMILY

#elif defined(__AVR_AVR16DU14__)               || \
      defined(__AVR_AVR16DU20__)               || \
      defined(__AVR_AVR16DU28__)               || \
      defined(__AVR_AVR16DU32__)               || \
      defined(__AVR_AVR32DU14__)               || \
      defined(__AVR_AVR32DU20__)               || \
      defined(__AVR_AVR32DU28__)               || \
      defined(__AVR_AVR32DU32__)               || \
      defined(__AVR_AVR64DU28__)               || \
      defined(__AVR_AVR64DU32__)
  #define AVR_DX_FAMILY
  #define AVR_DU_FAMILY

//------------------------------------------------------------------------------------------------
// AVR Ex series
#elif defined(__AVR_AVR16EA28__)               || \
      defined(__AVR_AVR16EA32__)               || \
      defined(__AVR_AVR16EA48__)               || \
      defined(__AVR_AVR32EA28__)               || \
      defined(__AVR_AVR32EA32__)               || \
      defined(__AVR_AVR32EA48__)               || \
      defined(__AVR_AVR64EA28__)               || \
      defined(__AVR_AVR64EA32__)               || \
      defined(__AVR_AVR64EA48__)
  #define AVR_EX_FAMILY
  #define AVR_EA_FAMILY

#elif defined(__AVR_AVR16EB14__)               || \
      defined(__AVR_AVR16EB20__)               || \
      defined(__AVR_AVR16EB28__)               || \
      defined(__AVR_AVR16EB32__)               || \
      defined(__AVR_AVR32EB14__)               || \
      defined(__AVR_AVR32EB20__)               || \
      defined(__AVR_AVR32EB28__)               || \
      defined(__AVR_AVR32EB32__)
  #define AVR_EX_FAMILY
  #define AVR_EB_FAMILY

#else
  #error "MCU is not listed in AVR/avr-mcu.h"
#endif
//------------------------------------------------------------------------------------------------
#endif // AVR_MCU_H
