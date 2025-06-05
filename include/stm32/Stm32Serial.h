/**
 **************************************************************************************************
 *
 * @file    : Stm32Serial.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : STM32 Serial Implementation header file
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

#ifndef STM32_SERIAL_H 
#define STM32_SERIAL_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "ISerial.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class Stm32Serial : public ISerial {
 
public:
  Stm32Serial(unsigned long baudRate);
  bool setup() override;
  bool writeData(const uint8_t* data, size_t length, size_t& bytesWritten) override;
  bool readData(uint8_t* buffer, size_t length, size_t& bytesRead) override;
    
private:
  unsigned long baudRate;
};

#endif // STM32_SERIAL_H 