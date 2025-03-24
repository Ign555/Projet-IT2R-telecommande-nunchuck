#include "Board_LED.h" 
#include "Driver_USART.h"   
#include "Driver_I2C.h"  

#ifndef __NUNCHUCK_H__
#define __NUNCHUCK_H__

#define ASK_JX 0x00
#define ASK_JY 0x01
#define ASK_BUTTON 0x05

extern ARM_DRIVER_USART Driver_USART2;
extern ARM_DRIVER_I2C Driver_I2C1; 

void Nunchuck_init();
uint8_t Nunchuck_joystick_x();
uint8_t Nunchuck_joystick_y();

#endif