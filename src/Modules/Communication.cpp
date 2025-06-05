/**
 **************************************************************************************************
 *
 * @file    : Communication.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Communication Implementation
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
#include "Communication.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Constructor for Communication
  * @return     Nothing
  ********************************************************************************************** */
Communication::Communication() {
  #ifdef WIFI_COMMUNICATION
    this->comm = WifiFactory::createWifi();
  #else
    this->comm = SerialFactory::createSerial(115200);
  #endif
}

/**************************************************************************************************
  * @brief      Destructor for Communication
  * @return     Nothing
  ********************************************************************************************** */
Communication::~Communication() {
  if (this->comm != nullptr) {
    delete this->comm;
    this->comm = nullptr;
  }
}

/**************************************************************************************************
  * @brief      Setup communication
  * @return     true if setup successful
  ********************************************************************************************** */
bool Communication::setup() {
  return (this->comm != nullptr && this->comm->setup());
}

/**************************************************************************************************
  * @brief      Write data to communication channel
  * @param      data Data buffer to write
  * @param      length Length of data
  * @param      bytesWritten Number of bytes written
  * @return     true if write successful
  ********************************************************************************************** */
bool Communication::writeData(const uint8_t* data, size_t length, size_t& bytesWritten) {
  if (this->comm == nullptr || data == nullptr || length == 0) {
    return false;
  }
  return this->comm->writeData(data, length, bytesWritten);
}

/**************************************************************************************************
  * @brief      Read data from communication channel
  * @param      buffer Buffer to store data
  * @param      length Maximum length to read
  * @param      bytesRead Number of bytes read
  * @return     true if read successful
  ********************************************************************************************** */
bool Communication::readData(uint8_t* buffer, size_t length, size_t& bytesRead) {
  if (this->comm == nullptr || buffer == nullptr || length == 0) {
    return false;
  }
  return this->comm->readData(buffer, length, bytesRead);
} 