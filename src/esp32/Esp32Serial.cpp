/**
 **************************************************************************************************
 *
 * @file    : Esp32Serial.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : ESP32 Serial Implementation
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
#include "esp32/Esp32Serial.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Constructor for ESP32 Serial
  * @return     Nothing
  ********************************************************************************************** */
Esp32Serial::Esp32Serial(unsigned long baudRate) {
  this->baudRate = baudRate;
}

/**************************************************************************************************
  * @brief      Setup Serial communication
  * @return     true if setup successful
  ********************************************************************************************** */
bool Esp32Serial::setup() {
  if (this->baudRate > 0) {
    Serial.begin(this->baudRate);
    return Serial;  // Returns true if Serial is available
  }
  Serial.println("Serial setup");
  return false;
}

/**************************************************************************************************
  * @brief      Write data to Serial
  * @return     Number of bytes written
  ********************************************************************************************** */
bool Esp32Serial::writeData(const uint8_t* data, size_t length, size_t& bytesWritten) {
  if (data != nullptr && length > 0) {
    bytesWritten = Serial.write(data, length);
    return bytesWritten == length;
  }
  return false;
}

/**************************************************************************************************
  * @brief      Read data from Serial
  * @return     Number of bytes read
  ********************************************************************************************** */
bool Esp32Serial::readData(uint8_t* buffer, size_t length, size_t& bytesRead) {
  if (buffer != nullptr && length > 0) {
    if (Serial.available()) {
      bytesRead = Serial.readBytes(buffer, length);
      return bytesRead > 0;
    }
  }
  return false;
} 