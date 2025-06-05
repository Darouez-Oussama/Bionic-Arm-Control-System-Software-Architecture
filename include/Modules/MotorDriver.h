/**
 **************************************************************************************************
 *
 * @file    : MotorDriver.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Motor Driver class header file
 * 
 **************************************************************************************************
 */

#ifndef MOTOR_DRIVER_H 
#define MOTOR_DRIVER_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "IPwm.h"
#include "PwmFactory.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class MotorDriver {
 
public:
  MotorDriver(uint8_t forwardPin, uint8_t backwardPin);
  ~MotorDriver();
  bool setup();
  bool forward(uint8_t speed);
  bool backward(uint8_t speed);
  bool stop();
    
private:
  IPwm* forwardPwm;
  IPwm* backwardPwm;
};

#endif // MOTOR_DRIVER_H 