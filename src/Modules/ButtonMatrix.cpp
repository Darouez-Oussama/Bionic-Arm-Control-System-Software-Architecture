/**
 **************************************************************************************************
 *
 * @file    : ButtonMatrix.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Button Matrix Implementation
 * 
 **************************************************************************************************
 */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "ButtonMatrix.h"

/*-----------------------------------------------------------------------------------------------*/
/* Public methods                                                                                */
/*-----------------------------------------------------------------------------------------------*/
ButtonMatrix::ButtonMatrix(const uint8_t* rowPins, uint8_t rowCount, 
                         const uint8_t* colPins, uint8_t colCount) {
  this->rowCount = rowCount;
  this->colCount = colCount;
  
  // Create GPIO arrays
  this->rowGpios = new IGpio*[rowCount];
  this->colGpios = new IGpio*[colCount];
  
  // Initialize row GPIOs
  for (uint8_t i = 0; i < rowCount; i++) {
    this->rowGpios[i] = GpioFactory::createGpio(rowPins[i], OUTPUT);
  }
  
  // Initialize column GPIOs
  for (uint8_t i = 0; i < colCount; i++) {
    this->colGpios[i] = GpioFactory::createGpio(colPins[i], INPUT_PULLUP);
  }
}

ButtonMatrix::~ButtonMatrix() {
  // Clean up row GPIOs
  for (uint8_t i = 0; i < rowCount; i++) {
    if (this->rowGpios[i] != nullptr) {
      delete this->rowGpios[i];
    }
  }
  delete[] this->rowGpios;
  
  // Clean up column GPIOs
  for (uint8_t i = 0; i < colCount; i++) {
    if (this->colGpios[i] != nullptr) {
      delete this->colGpios[i];
    }
  }
  delete[] this->colGpios;
}

bool ButtonMatrix::setup() {
  bool success = true;
  
  // Setup rows
  for (uint8_t i = 0; i < rowCount; i++) {
    if (this->rowGpios[i] != nullptr) {
      success &= this->rowGpios[i]->setup();
    }
  }
  
  // Setup columns
  for (uint8_t i = 0; i < colCount; i++) {
    if (this->colGpios[i] != nullptr) {
      success &= this->colGpios[i]->setup();
    }
  }
  
  return success;
}

bool ButtonMatrix::read(uint8_t& row, uint8_t& col) {
  // Scan matrix
  for (uint8_t r = 0; r < rowCount; r++) {
    // Set current row low
    if (this->rowGpios[r] != nullptr) {
      this->rowGpios[r]->write(LOW);
      
      // Check all columns
      for (uint8_t c = 0; c < colCount; c++) {
        if (this->colGpios[c] != nullptr) {
          uint8_t state;
          if (this->colGpios[c]->read(state) && state == LOW) {
            row = r;
            col = c;
            this->rowGpios[r]->write(HIGH);
            return true;
          }
        }
      }
      
      // Reset row to high
      this->rowGpios[r]->write(HIGH);
    }
  }
  
  return false;
} 