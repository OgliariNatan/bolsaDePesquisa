#include "usart.h"

void usart_init(void){
	//baud=57000
	UBRR0H=0x07;
	UBRR0L=0x00;
	
	//habilita a receiver, transmissor 
	UCSR0B= (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	//tamanho do caracter de 8bit e bit de parada
	UCSR0C= (0<<USBS0) | (1<<UCSZ00) | (1<<UCSZ01);
}

void usart_send_char(unsigned char *ch){
	UDR = ch;
	//espera enviar a mensagem
	while(!(UCSR0A & _BV(UDRE0)));
}

void usart_send_char(char *sr){
		unsigned uint8_t i=0;
		//while
}