#include "nunchuck.h"
void Init_I2C(){
	
	Driver_I2C1.Initialize(NULL); // début initialisation (on fera mieux bientôt!)
	Driver_I2C1.PowerControl(ARM_POWER_FULL); // alimentation périphérique
	Driver_I2C1.Control( ARM_I2C_BUS_SPEED, // 2nd argument = débit
ARM_I2C_BUS_SPEED_STANDARD ); // =100 kHz

	
}
void Nunchuck_init(){
	
	uint8_t handshake1[2] = {0xF0, 0x55};
	uint8_t handshake2[2] = {0xFB, 0x00};
	
	Init_I2C();
	
	//Envoyer le handshake
	Driver_I2C1.MasterTransmit (0x52, handshake1, 2, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
	Driver_I2C1.MasterTransmit (0x52, handshake2, 2, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
	
}
uint8_t Nunchuck_joystick_x(){
	
	uint8_t jx;
	
	//Lecture de la position X du joystick
	Driver_I2C1.MasterTransmit (0x52, (uint8_t)ASK_JX, 1, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
	Driver_I2C1.MasterReceive (0x52, &jx, 1, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission*/
	
	return jx;
}/*
uint8_t Nunchuck_joystick_y(){
	
	uint8_t jy;
	
	//Lecture de la position Y du joystick
	Driver_I2C1.MasterTransmit (0x52, (uint8_t)ASK_JY, 1, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
	Driver_I2C1.MasterReceive (0x52, &jy, 1, false); 
	while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission*/
	
//return jy;
//}