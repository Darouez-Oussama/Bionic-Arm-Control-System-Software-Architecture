/**
 **************************************************************************************************
 *
 * @file    : App.cpp
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Implementation of the App base class
 * 
 **************************************************************************************************
 */

#include "App.h"

App::App() :  isRunning(false) {
}

App::~App() {
  if (isRunning) {
    stop();
  }
}

bool App::run() {
  if (!isRunning) {
    onStart();
    isRunning = true;
    while (isRunning) {
    onLoop();
  }
  return false;
}
}

bool App::stop() {
  if (isRunning) {
    isRunning = false;
    return true;
  }
  return false;
} 