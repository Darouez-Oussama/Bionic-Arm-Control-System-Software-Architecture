/**
 **************************************************************************************************
 *
 * @file    : Communication.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Communication class header file
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

#ifndef COMMUNICATION_H 
#define COMMUNICATION_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "ISerial.h"
#include "IWifi.h"
#include "SerialFactory.h"
// #include "Factories/WifiFactory.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class Communication {
 
public:
  Communication();
  ~Communication();
  bool setup();
  bool writeData(const uint8_t* data, size_t length, size_t& bytesWritten);
  bool readData(uint8_t* buffer, size_t length, size_t& bytesRead);
    
private:
  #ifdef WIFI_COMMUNICATION
    IWifi* comm;
  #else
    ISerial* comm;
  #endif
};

#endif // COMMUNICATION_H 