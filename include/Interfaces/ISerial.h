/**
 **************************************************************************************************
 *
 * @file    : ISerial.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Serial Interface header file
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

#ifndef ISERIAL_H 
#define ISERIAL_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include <Arduino.h>

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class ISerial {
 
public:
  virtual ~ISerial() = default;
  virtual bool setup() = 0;
  virtual bool writeData(const uint8_t* data, size_t length, size_t& bytesWritten) = 0;
  virtual bool readData(uint8_t* buffer, size_t length, size_t& bytesRead) = 0;
};

#endif // ISERIAL_H 