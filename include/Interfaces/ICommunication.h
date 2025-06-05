/**
 **************************************************************************************************
 *
 * @file    : ICommunication.h
 * @author  : Oussama Darouez
 * @version : 1.0
 * @date    : February 2024
 * @brief   : Communication Interface header file
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

#ifndef ICOMMUNICATION_H
#define ICOMMUNICATION_H

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include <Arduino.h>

/*-----------------------------------------------------------------------------------------------*/
/* Classes                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
class ICommunication {
public:
    virtual ~ICommunication() = default;

    virtual bool setup() = 0;


    virtual int sendData(const uint8_t* data, size_t length) = 0;


    virtual int receiveData(uint8_t* buffer, size_t maxLength) = 0;
};

#endif // ICOMMUNICATION_H
