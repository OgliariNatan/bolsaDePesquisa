/*
 * gateway_i2cLCD.c
 *
 * Created: 26/11/2017 18:56:26
 * Author : cliente
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "ATmega328.h"


int main(void)
{
	usartConfig(USART_MODE_ASYNCHRONOUS, USART_BAUD_57600, USART_DATA_BITS_8, USART_PARITY_NONE, USART_STOP_BIT_SINGLE);
	usartEnableReceiver();
	usartEnableTransmitter();
	printf("teste");
	
    globalInterruptEnable();
    while (1)  {
		//usartTransmit("NATAN\n");
		printf("NATAN\n");
		_delay_ms(500);
		
		//usartEnableReceiver();
    }
}

