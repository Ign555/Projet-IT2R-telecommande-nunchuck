#include "Board_LED.h" 
#include "Driver_USART.h"   
#include "Driver_I2C.h"  
#include "nunchuck.h"

void callback_UART(){
	
	
}
void Init_UART(){
	Driver_USART2.Initialize(callback_UART); //On utilise la fonction de callback définie plus haut
	Driver_USART2.PowerControl(ARM_POWER_FULL);
	Driver_USART2.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_FLOW_CONTROL_NONE   |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		,							
						115200);	// valeur à valider...
	Driver_USART2.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART2.Control(ARM_USART_CONTROL_RX,1);
}

int main(){
	int i;
	char RxChar, jx=0, jy=0, button=0, data;
	
	uint8_t askX[1] = {0x00};
	uint8_t askY[1] = {0x01};
	uint8_t askButton[1] = {0x05};
	//Initialisation UART
	Init_UART();
	
	Nunchuck_init();	
	
	//Initialiser les LEDs présentent sur la carte
	LED_Initialize();
	LED_On (1);
	LED_On (2);
	LED_On (3);
	
	while(1){
		//Driver_USART2.Receive(&RxChar,1);
		// à optimiser
		Driver_I2C1.MasterTransmit (0x52, askX, 1, false); // true = sans stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
		Driver_I2C1.MasterReceive (0x52, &jx, 1, false); // false = avec stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission*/
		
		Driver_I2C1.MasterTransmit (0x52, askY, 1, false); // true = sans stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
		Driver_I2C1.MasterReceive (0x52, &jy, 1, false); // false = avec stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission*/
		
		//Lecture des boutons
		Driver_I2C1.MasterTransmit (0x52, askButton, 1, false); // true = sans stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission
		Driver_I2C1.MasterReceive (0x52, &button, 1, false); // false = avec stop
		while (Driver_I2C1.GetStatus().busy == 1); // attente fin transmission*/
		button &= 0x03;
		
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send("x",1); // send the read characters
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send(&jx,1); // send the read characters
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send("y",1); // send the read characters
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send(&jy,1); // send the read characters
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send("b",1); // send the read characters
		while(Driver_USART2.GetStatus().tx_busy == 1);
		Driver_USART2.Send(&button,1); // send the read characters

	}
}