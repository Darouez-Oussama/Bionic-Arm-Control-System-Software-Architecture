/**
 **************************************************************************************************
 *
 * @file    : MotorDriver.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Motor Driver Implementation
 * 
 **************************************************************************************************
 */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "MotorDriver.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
MotorDriver::MotorDriver(uint8_t forwardPin, uint8_t backwardPin) {
  this->forwardPwm = PwmFactory::createPwm(forwardPin);
  this->backwardPwm = PwmFactory::createPwm(backwardPin);
}

MotorDriver::~MotorDriver() {
  if (this->forwardPwm != nullptr) {
    delete this->forwardPwm;
    this->forwardPwm = nullptr;
  }
  if (this->backwardPwm != nullptr) {
    delete this->backwardPwm;
    this->backwardPwm = nullptr;
  }
}

bool MotorDriver::setup() {
  return (this->forwardPwm != nullptr && this->forwardPwm->setup() &&
          this->backwardPwm != nullptr && this->backwardPwm->setup());
}

bool MotorDriver::forward(uint8_t speed) {
  return (this->forwardPwm != nullptr && this->backwardPwm != nullptr &&
          this->forwardPwm->write(speed) && this->backwardPwm->write(0));
}

bool MotorDriver::backward(uint8_t speed) {
  return (this->forwardPwm != nullptr && this->backwardPwm != nullptr &&
          this->forwardPwm->write(0) && this->backwardPwm->write(speed));
}

bool MotorDriver::stop() {
  return (this->forwardPwm != nullptr && this->backwardPwm != nullptr &&
          this->forwardPwm->write(0) && this->backwardPwm->write(0));
} 