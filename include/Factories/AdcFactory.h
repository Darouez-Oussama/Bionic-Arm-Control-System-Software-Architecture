/**
 **************************************************************************************************
 *
 * @file    : AdcFactory.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : ADC Factory header file
 * 
 **************************************************************************************************
 * 
 * @project  : {BionicArm}
 * @board    : {esp32dev}
 * @compiler : {gcc-arm-none-eabi}
 * 
 **************************************************************************************************
 *
 */

#ifndef ADC_FACTORY_H 
#define ADC_FACTORY_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "IAdc.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class AdcFactory {
 
public:
  static IAdc* createAdc(uint8_t pin);
};

#endif // ADC_FACTORY_H