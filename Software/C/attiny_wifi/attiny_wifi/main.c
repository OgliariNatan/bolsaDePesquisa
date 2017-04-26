/*
 * attiny_wifi.c
 *
 * Created: 26/04/2017 18:45:56
 * Author : Cliente
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "nrf24l01.h"
#define F_CPU 16000000UL

nRF24L01 *setup_rf(void);
void process_message (char *message);

volatile bool rf_interrupt = false;
uint8_t CONFIG = 0x00; //REVER AQUIIIIIIIIII

int main(void)
{
    uint8_t address[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
	sei();
	nRF24L01 *rf = setup_rf();
	nRF24L01_listen(rf, 0, address);
	uint8_t addr[5];
	nRF24L01_read_register(rf, CONFIG, addr, 1);
	
	
	
    while (1) {
		if (rf_interrupt){
			rf_interrupt = false;
			while(nRF24L01_data_received(rf)){
				nRF24L01Message msg;
				nRF24L01_read_received_data(rf, &msg);
				process_message((char *) msg.data);
			}
			nRF24L01_listen(rf, 0, address);
		}
    }
}

nRF24L01 *setup_rf(void){
	nRF24L01 *rf = nRF24L01_init();
	rf->ss.port = &PORTB;
	rf->ss.pin = PB2;
	rf->ce.port = &PORTB;
	rf->ce.pin = PB1;
	rf->sck.port = &PORTB;
	rf->sck.pin = PB5;
	rf->mosi.port = &PORTB;
	rf->mosi.pin = PB3;
	rf->miso.port = &PORTB;
	rf->miso.pin = PB4;
	// interrupt on falling edge of INT0 (PD2)
	EICRA |= _BV(ISC01);
	EIMSK |= _BV(INT0);
	nRF24L01_begin(rf);
	return rf;
}
void process_message (char *message){
	if (strcmp(message, "ON") == 0){}//quando a mensagem foi "ON" faz algo
		//função a ser implemantada
	else if (strcmp(message, "OFF") == 0){//quando a mensagem foi "OFF" faz algo
		//Função a ser implemantada 
	}
} 

ISR(INT0_vect){
	rf_interrupt = true;
}