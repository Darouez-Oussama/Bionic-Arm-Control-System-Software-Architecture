/**
 **************************************************************************************************
 *
 * @file    : BionicArm.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : BionicArm Implementation
 * 
 **************************************************************************************************
 */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "BionicArm.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
BionicArm::BionicArm(uint8_t emgPin, 
                     const uint8_t* motorPins,
                     const uint8_t* rowPins,
                     const uint8_t* colPins) {
  // Initialize EMG sensor
  this->emg = new EmgSensor(emgPin);
  
  // Initialize motors
  for (uint8_t i = 0; i < NUM_MOTORS; i++) {
    this->motors[i] = new MotorDriver(motorPins[i*2], motorPins[i*2 + 1]);
  }
  
  // Initialize button matrix
  this->buttonMatrix = new ButtonMatrix(rowPins, MATRIX_ROWS, colPins, MATRIX_COLS);
  
  // Initialize communication
  this->communication = new Communication();
}

BionicArm::~BionicArm() {
  // Cleanup EMG sensor
  if (this->emg != nullptr) {
    delete this->emg;
    this->emg = nullptr;
  }
  
  // Cleanup motors
  for (uint8_t i = 0; i < NUM_MOTORS; i++) {
    if (this->motors[i] != nullptr) {
      delete this->motors[i];
      this->motors[i] = nullptr;
    }
  }
  
  // Cleanup button matrix
  if (this->buttonMatrix != nullptr) {
    delete this->buttonMatrix;
    this->buttonMatrix = nullptr;
  }
  
  // Cleanup communication
  if (this->communication != nullptr) {
    delete this->communication;
    this->communication = nullptr;
  }
}

bool BionicArm::setup() {
  bool success = true;
  
  // Setup EMG sensor
  success &= (this->emg != nullptr && this->emg->setup());
  
  // Setup motors
  for (uint8_t i = 0; i < NUM_MOTORS; i++) {
    success &= (this->motors[i] != nullptr && this->motors[i]->setup());
  }
  
  // Setup button matrix
  success &= (this->buttonMatrix != nullptr && this->buttonMatrix->setup());
  
  // Setup communication
  success &= (this->communication != nullptr && this->communication->setup());
  
  return success;
}

bool BionicArm::doGesture() {
  uint16_t emgValue;
  uint8_t row, col;
  
  // Read EMG sensor
  if (!processEmgSignal(emgValue)) {
    return false;
  }
  
  // Check if EMG signal is above threshold
  if (emgValue > EMG_THRESHOLD) {
    // Read button matrix for gesture selection
    if (this->buttonMatrix->read(row, col)) {
      uint8_t gestureId = row * MATRIX_COLS + col;
      
      // Execute the gesture
      if (!executeGesture(gestureId)) {
        return false;
      }
      
      // Send gesture data
      if (!sendGestureData(gestureId, emgValue)) {
        return false;
      }
      
      return true;
    }
  }
  
  return false;
}

/*-----------------------------------------------------------------------------------------------*/
/* Private methods                                                                               */
/*-----------------------------------------------------------------------------------------------*/
bool BionicArm::processEmgSignal(uint16_t& emgValue) {
  return this->emg->read(emgValue);
}

bool BionicArm::executeGesture(uint8_t gestureId) {
  bool success = true;
  
  // Example gesture patterns (customize based on your needs)
  switch (gestureId) {
    case 0: // Fist
      success &= this->motors[0]->forward(255);  // Thumb
      success &= this->motors[1]->forward(255);  // Index
      success &= this->motors[2]->forward(255);  // Middle
      success &= this->motors[3]->forward(255);  // Ring
      success &= this->motors[4]->forward(255);  // Pinky
      break;
      
    case 1: // Peace sign
      success &= this->motors[0]->stop();        // Thumb
      success &= this->motors[1]->backward(255); // Index
      success &= this->motors[2]->backward(255); // Middle
      success &= this->motors[3]->forward(255);  // Ring
      success &= this->motors[4]->forward(255);  // Pinky
      break;
      
    // Add more gesture patterns here
      
    default:
      // Stop all motors
      for (uint8_t i = 0; i < NUM_MOTORS; i++) {
        success &= this->motors[i]->stop();
      }
      break;
  }
  
  return success;
}

bool BionicArm::sendGestureData(uint8_t gestureId, uint16_t emgValue) {
  // Prepare data packet
  uint8_t data[3] = {
    gestureId,
    (uint8_t)(emgValue >> 8),   // High byte
    (uint8_t)(emgValue & 0xFF)  // Low byte
  };
  
  size_t bytesWritten;
  return this->communication->writeData(data, sizeof(data), bytesWritten);
} 