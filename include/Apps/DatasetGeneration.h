/**
 **************************************************************************************************
 *
 * @file    : DatasetGeneration.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Dataset Generation Application header file
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

#ifndef DATASET_GENERATION_H
#define DATASET_GENERATION_H

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "App.h"
#include "EmgSensor.h"
#include "Communication.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class BionicArmApp : public App {
public:
  static BionicArmApp& getInstance();
  
protected:
  void onStart() override;
  void onLoop() override;

private:
  BionicArmApp();
  ~BionicArmApp();
  
  static BionicArmApp* instance;
  
  // Only EMG and Communication for dataset generation
  EmgSensor* emgSensor;
  Communication* communication;

  static bool toArray(uint16_t value, uint8_t* array);
  bool createSample(uint8_t * emgData);
  bool createPacket(uint8_t * packet, uint8_t * emgData, uint8_t  label);
};

#endif // DATASET_GENERATION_H 