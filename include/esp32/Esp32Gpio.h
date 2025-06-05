/**
 **************************************************************************************************
 *
 * @file    : Esp32Gpio.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : ESP32 GPIO Implementation header file
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

#ifndef ESP32_GPIO_H 
#define ESP32_GPIO_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "IGpio.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class Esp32Gpio : public IGpio {
 
public:
  Esp32Gpio(uint8_t pin, uint8_t mode);
  bool setup() override;
  bool write(uint8_t state) override;
  bool read(uint8_t& state) override;
    
private:
  uint8_t pin;
  uint8_t mode;
};

#endif // ESP32_GPIO_H 