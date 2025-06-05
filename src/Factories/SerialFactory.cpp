/**
 **************************************************************************************************
 *
 * @file    : SerialFactory.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Serial Factory Implementation
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
#include "SerialFactory.h"
#include "Stm32Serial.h"
#include "Esp32Serial.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Create Serial instance based on architecture
  * @return     Serial instance pointer
  ********************************************************************************************** */
ISerial* SerialFactory::createSerial(unsigned long baudRate) {
  #ifdef ARDUINO_ARCH_STM32
    return new Stm32Serial(baudRate);
  #elif defined(ARDUINO_ARCH_ESP32)
    return new Esp32Serial(baudRate);
  #else
    return nullptr;
  #endif
} 