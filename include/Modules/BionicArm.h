/**
 **************************************************************************************************
 *
 * @file    : BionicArm.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : BionicArm class header file
 * 
 **************************************************************************************************
 */

#ifndef BIONIC_ARM_H 
#define BIONIC_ARM_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "EmgSensor.h"
#include "MotorDriver.h"
#include "ButtonMatrix.h"
#include "Communication.h"

/*-----------------------------------------------------------------------------------------------*/
/* Constants                                                                                     */
/*-----------------------------------------------------------------------------------------------*/
#define NUM_MOTORS 5
#define EMG_THRESHOLD 2048  // Adjust based on your EMG sensor
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class BionicArm {
 
public:
  BionicArm(uint8_t emgPin, 
            const uint8_t* motorPins,  // Array of 10 pins (5 motors x 2 pins each)
            const uint8_t* rowPins,    // Array of row pins for button matrix
            const uint8_t* colPins);   // Array of column pins for button matrix
  ~BionicArm();
  bool setup();
  bool doGesture();
  
private:
  // Components
  EmgSensor* emg;
  MotorDriver* motors[NUM_MOTORS];
  ButtonMatrix* buttonMatrix;
  Communication* communication;

  // Helper functions
  bool processEmgSignal(uint16_t& emgValue);
  bool executeGesture(uint8_t gestureId);
  bool sendGestureData(uint8_t gestureId, uint16_t emgValue);
};

#endif // BIONIC_ARM_H 