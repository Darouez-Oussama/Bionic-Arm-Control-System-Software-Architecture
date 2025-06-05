/**
 **************************************************************************************************
 *
 * @file    : FullArm.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Full Arm Application header file
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

#ifndef FULL_ARM_H
#define FULL_ARM_H

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "App.h"
#include "BionicArm.h"

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
  
  // Full functionality with BionicArm
  BionicArm* bionicArm;
};

#endif // FULL_ARM_H 