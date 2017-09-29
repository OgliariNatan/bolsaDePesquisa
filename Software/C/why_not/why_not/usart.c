#include "usart.h"
#include "usart.h"

void usart_init(){
	//baud=57000
	UBRR0H=0x07;
	UBRR0L=0x00;
	
	//habilita a receiver, transmissor 
	UCSR0B= (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	//tamanho do caracter de 8bit e bit de parada
	UCSR0C= (0<<USBS0) | (1<<UCSZ00) | (1<<UCSZ01);
}

void usart_send_char(unsigned char *ch){
	
	UDRE0 = ch;
	//espera enviar a mensagem
	while(!(UCSR0A & _BV(UDRE0)));
}

void usart_sendstring(char *sr){
		uint8_t i=0;
		
		
		while(s[i] != '\x0'){
			usart_send_char(s[i++]);
		}
}

void usart_send_hex(unsigned char *ch){
	unsigned char i, temp;
	for (i=0; i<2; i++)	{
		temp = (ch & 0xF0)>>4;
		if (temp <= 9){
			usart_send_char('0'+temp);
		} 
		else{
			usart_send_char('A'+temp-10);
		}
		ch=ch<<4;
	}
}

//interup��o USART
ISR(USART_RX_vect){
	char status, ch;
	status = UCSR0A;
	ch = UDRE0;
	
	//verifica ERRO
	if((status &(_BV(FE) | _BV(DOR))) !=0)
		return;
	
	if (ch>='a' && ch<='z') {
		ch=ch-'a'+'A';
	} 
	else if (ch>='A' && ch<='z'){
		ch=ch-'A'+'a';
	}
	usart_send_char(ch);
}
	
	