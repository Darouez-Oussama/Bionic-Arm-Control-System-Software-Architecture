/**
 **************************************************************************************************
 *
 * @file    : ButtonMatrix.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Button Matrix class header file
 * 
 **************************************************************************************************
 */

#ifndef BUTTON_MATRIX_H 
#define BUTTON_MATRIX_H 

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "IGpio.h"
#include "GpioFactory.h"

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class ButtonMatrix {
 
public:
  ButtonMatrix(const uint8_t* rowPins, uint8_t rowCount, 
               const uint8_t* colPins, uint8_t colCount);
  ~ButtonMatrix();
  bool setup();
  bool read(uint8_t& row, uint8_t& col);
    
private:
  IGpio** rowGpios;
  IGpio** colGpios;
  uint8_t rowCount;
  uint8_t colCount;
};

#endif // BUTTON_MATRIX_H 