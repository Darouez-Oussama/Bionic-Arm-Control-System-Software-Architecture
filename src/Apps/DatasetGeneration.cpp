/**
 **************************************************************************************************
 *
 * @file    : DatasetGeneration.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Dataset Generation Application Implementation
 * 
 **************************************************************************************************
 */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "DatasetGeneration.h"

/*-----------------------------------------------------------------------------------------------*/
/* Constants                                                                                     */
/*-----------------------------------------------------------------------------------------------*/
const uint16_t numberOfSamples = 100 ; 

/*-----------------------------------------------------------------------------------------------*/
/* Static members                                                                                */
/*-----------------------------------------------------------------------------------------------*/
BionicArmApp* BionicArmApp::instance = nullptr;

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Get singleton instance
  * @return     Reference to singleton instance
  ********************************************************************************************** */
BionicArmApp& BionicArmApp::getInstance() {
  if (instance == nullptr) {
    instance = new BionicArmApp();
  }
  return *instance;
}

/**************************************************************************************************
  * @brief      Constructor
  * @return     Nothing
  ********************************************************************************************** */
BionicArmApp::BionicArmApp() : App() {
  emgSensor = new EmgSensor(34);
  communication = new Communication();
}

/**************************************************************************************************
  * @brief      Destructor
  * @return     Nothing
  ********************************************************************************************** */
BionicArmApp::~BionicArmApp() {
  delete emgSensor;
  delete communication;
  if (instance == this) {
    instance = nullptr;
  }
}

/*-----------------------------------------------------------------------------------------------*/
/* Protected methods                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/**************************************************************************************************
  * @brief      Start application
  * @return     Nothing
  ********************************************************************************************** */
void BionicArmApp::onStart() {
  emgSensor->setup();
  communication->setup();
  Serial.begin(115200);
  delay(1000);
  Serial.println("Dataset Generation Application Started");
  delay(100);
  
}

/**************************************************************************************************
  * @brief      Main application loop
  * @return     Nothing
  ********************************************************************************************** */
void BionicArmApp::onLoop() {
  uint8_t emgData[numberOfSamples * 2];
  uint8_t packet[numberOfSamples * 2 + 5];
  size_t bytesWritten;
  createSample(emgData);
  createPacket(packet, emgData, 1);
  communication->writeData(packet, numberOfSamples * 2 + 5, bytesWritten);
  delay(1000);
} 

/**************************************************************************************************
  * @brief      Convert a 16-bit value to two 8-bit values using decimal division
  * @param[in]  value: The 16-bit value to convert
  * @param[out] array: Array to store the two 8-bit values (array[0] = hundreds, array[1] = remainder)
  * @return     true if conversion successful
  ********************************************************************************************** */
bool BionicArmApp::toArray(uint16_t value, uint8_t* array) {
  array[0] = value / 100 ;  // High byte
  array[1] = value % 100;   // Low byte 
  return true;
}

/**************************************************************************************************
  * @brief      Create a sample by reading multiple EMG values and converting them to pairs of bytes
  * @param[out] emgData: Array to store the converted EMG samples (size = numberOfSamples * 2)
  * @return     true if all samples were read successfully, false otherwise
  ********************************************************************************************** */
bool BionicArmApp::createSample(uint8_t * emgData) {
  uint16_t emgValue;
  size_t bytesWritten;
  uint8_t array[2];
  for (uint16_t i = 0; i < numberOfSamples; i++) {
    if (emgSensor->read(emgValue)) {
      toArray(emgValue, array);
      emgData[i * 2] = array[0];
      emgData[i * 2 + 1] = array[1];
      delay(10);
    }
    else {
      return false;
    }
  }
  return true;
} 

/**************************************************************************************************
  * @brief      Create a data packet with label, EMG data and checksum
  * @param[out] packet: Array to store the complete packet (size = numberOfSamples * 2 + 5)
  * @param[in]  emgData: Array containing the EMG samples
  * @param[in]  label: Classification label for this data packet
  * @return     true if packet creation successful
  * @details    Packet format: [label][emg data][checksum]
  *             - label: 1 byte
  *             - emg data: numberOfSamples * 2 bytes
  *             - checksum: 4 bytes (split into thousands, hundreds, tens, ones)
  ********************************************************************************************** */
bool BionicArmApp::createPacket(uint8_t * packet, uint8_t * emgData, uint8_t label) {
  uint8_t checkSumArray[4];
  packet[0] = label;
  uint32_t checkSum = 0;
  for (uint16_t i = 1; i <= 2*numberOfSamples; i++) {
    packet[i] = emgData[i-1];
    checkSum += packet[i-1];
  }
  checkSum += packet[2*numberOfSamples];
  checkSumArray[0] = checkSum / 1000000;
  checkSumArray[1] = (checkSum%1000000)/10000;
  checkSumArray[2] = (checkSum%10000)/100;
  checkSumArray[3] = (checkSum%100);
  packet[2*numberOfSamples + 1] = checkSumArray[0];
  packet[2*numberOfSamples + 2] = checkSumArray[1];
  packet[2*numberOfSamples + 3] = checkSumArray[2];
  packet[2*numberOfSamples + 4] = checkSumArray[3];
 
  return true;
}