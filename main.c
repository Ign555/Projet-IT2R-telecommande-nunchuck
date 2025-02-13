#include "Board_LED.h" 
#include "Driver_USART.h"   

extern ARM_DRIVER_USART Driver_USART2;

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
						19200);	// valeur à valider...
	Driver_USART2.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART2.Control(ARM_USART_CONTROL_RX,1);
}
int main(){
	int i;
	char RxChar;
	//Initialisation UART
	Init_UART();
	//Initialiser les LEDs présentent sur la carte
	LED_Initialize();
	LED_On (1);
	LED_On (2);
	LED_On (3);
	
	while(1){
		//Driver_USART2.Receive(&RxChar,1);
		
		Driver_USART2.Send("f",1); // send the read characters
		for(i=0;i<10000;i++);
	}
}