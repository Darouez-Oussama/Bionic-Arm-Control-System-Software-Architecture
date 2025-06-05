/**
 **************************************************************************************************
 *
 * @file    : Stm32Serial.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : STM32 Serial Implementation
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

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "stm32/Stm32Serial.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Constructor for STM32 Serial
  * @return     Nothing
  ********************************************************************************************** */
Stm32Serial::Stm32Serial(unsigned long baudRate) {
  this->baudRate = baudRate;
}

/**************************************************************************************************
  * @brief      Setup Serial
  * @return     true if setup successful, false otherwise
  ********************************************************************************************** */
bool Stm32Serial::setup() {
  if (this->baudRate > 0) {
    Serial.begin(this->baudRate);
    return true;
  }
  return false;
}

/**************************************************************************************************
  * @brief      Write data to Serial
  * @param      data Data buffer to write
  * @param      length Length of data
  * @param      bytesWritten Reference to store number of bytes written
  * @return     true if write successful, false otherwise
  ********************************************************************************************** */
bool Stm32Serial::writeData(const uint8_t* data, size_t length, size_t& bytesWritten) {
  if (data != nullptr && length > 0) {
    bytesWritten = Serial.write(data, length);
    return bytesWritten == length;
  }
  return false;
}

/**************************************************************************************************
  * @brief      Read data from Serial
  * @param      buffer Buffer to store read data
  * @param      length Maximum length to read
  * @param      bytesRead Reference to store number of bytes read
  * @return     true if read successful, false otherwise
  ********************************************************************************************** */
bool Stm32Serial::readData(uint8_t* buffer, size_t length, size_t& bytesRead) {
  if (buffer != nullptr && length > 0 && Serial.available()) {
    bytesRead = Serial.readBytes(buffer, length);
    return bytesRead > 0;
  }
  return false;
} 