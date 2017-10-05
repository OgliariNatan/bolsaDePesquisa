/*
 * why_not.c
 *
 * Created: 14/09/2017 18:06:28
 * Author : Natan Ogliari
 */ 

#define F_CPU 8000000UL //CUIDADO COM O A biblioteca: globalDefine.h F_CPU

#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include "ATmega328.h"
#include "globalDefines.h"
#include <string.h>


nRF24L01 *setup_rf(void);
void process_message(char *message);
void usartSetup(void);

inline void prepare_led_pin(void);
inline void  set_led_high(void);
inline void  set_led_low(void);

volatile bool rf_interrupt = false;

int main(void) {
	uint8_t address[5] = { 0x01, 0x01, 0x01, 0x01, 0x01 };
	prepare_led_pin();
	usartSetup(); //Configura USART
	
	
	
	sei();
	nRF24L01 *rf = setup_rf();
	nRF24L01_listen(rf, 0, address);
	uint8_t addr[5];
	uint8_t	CONFIG =0;
	nRF24L01_read_register(rf, CONFIG, addr, 1);

	while (true) {
		if (rf_interrupt) {
			rf_interrupt = false;
			while (nRF24L01_data_received(rf)) {
				nRF24L01Message msg;
				nRF24L01_read_received_data(rf, &msg);
				process_message((char *)msg.data);
			}

			nRF24L01_listen(rf, 0, address);
		}
	}

	return 0;
}

nRF24L01 *setup_rf(void) {
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

void process_message(char *message) {
	if (strcmp(message, "ON") == 0)
	set_led_high();
	else if (strcmp(message, "OFF") == 0)
	set_led_low();
}

inline void prepare_led_pin(void) {
	setBit(DDRD,PB0); //configura como saida 
	setBit(PORTB, PB0);
	//DDRB |= _BV(PB0);
	//PORTB &= ~_BV(PB0);
}

inline void set_led_high(void) {
	setBit (PINB, PB0);
	//PORTB |= _BV(PB0);
}

inline void set_led_low(void) {
	clrBit (PINB, PB0);
	//PORTB &= ~_BV(PB0);
}

// nRF24L01 interrupt
ISR(INT0_vect) {
	rf_interrupt = true;
}

//Configuração da USART
void usartSetup(void){
	usartConfig(USART_MODE_ASYNCHRONOUS, USART_BAUD_115200, USART_DATA_BITS_8, USART_PARITY_NONE, USART_STOP_BIT_SINGLE);
	usartEnableTransmitter();
	usartEnableReceiver();
	usartClearReceptionBuffer();
	usartActivateReceptionCompleteInterrupt();
	usartStdio();
}