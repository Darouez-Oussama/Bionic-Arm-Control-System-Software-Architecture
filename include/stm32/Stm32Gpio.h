/**
 **************************************************************************************************
 *
 * @file    : Stm32Gpio.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : STM32 GPIO Implementation header file
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

#ifndef STM32_GPIO_H 
#define STM32_GPIO_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "IGpio.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class Stm32Gpio : public IGpio {
 
public:
  Stm32Gpio(uint8_t pin, uint8_t mode);
  bool setup() override;
  bool write(uint8_t state) override;
  bool read(uint8_t& state) override;
    
private:
  uint8_t pin;
  uint8_t mode;
};

#endif // STM32_GPIO_H 