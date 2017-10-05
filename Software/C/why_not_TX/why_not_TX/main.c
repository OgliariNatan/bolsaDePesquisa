/*
 * why_not_TX.c
 *
 * Created: 04/10/2017 22:27:57
 * Author : Cliente
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include "ATmega328.h"
#include "globalDefines.h"
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include <string.h>

void setup_timer(void);
nRF24L01 *setup_rf(void);
void adcSetup(void);
void usartSetup(void);

volatile bool rf_interrupt = false;
volatile bool send_message = false;

int main(void) {
	uint8_t to_address[5] = { 0x01, 0x01, 0x01, 0x01, 0x01 };
	bool on = false;
	usartSetup();
	adcSetup();
	
	sei();
	nRF24L01 *rf = setup_rf();
	setup_timer();

	while (true) {
		if (rf_interrupt) {
			rf_interrupt = false;
			int success = nRF24L01_transmit_success(rf);
			if (success != 0)
			nRF24L01_flush_transmit_message(rf);
		}

		if (send_message) {
			send_message = false;
			on = !on;
			nRF24L01Message msg;
			if (on) memcpy(msg.data, "ON", 3);
			else memcpy(msg.data, "OFF", 4);
			msg.length = strlen((char *)msg.data) + 1;
			nRF24L01_transmit(rf, to_address, &msg);
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

// setup timer to trigger interrupt every second when at 1MHz
void setup_timer(void) {
	TCCR1B |= _BV(WGM12);
	TIMSK1 |= _BV(OCIE1A);
	OCR1A = 80;//15624 //REVER ESTE VALOR !!!
	TCCR1B |= _BV(CS10) | _BV(CS11);
}

// each one second interrupt
ISR(TIMER1_COMPA_vect) {
	send_message = true;
}

// nRF24L01 interrupt
ISR(INT0_vect) {
	rf_interrupt = true;
}

void adcSetup(void){
	adcConfig(	ADC_MODE_SINGLE_CONVERSION,
	ADC_REFERENCE_POWER_SUPPLY,
	ADC_PRESCALER_128	);
	adcSelectChannel(ADC_CHANNEL_0);	//
	adcClearInterruptRequest();			// clear adc interrupts
	adcActivateInterrupt();				// activate adc interrupts
	adcEnable();						//
	adcStartConversion();				// this first conversion takes 20 cycles
}

void usartSetup(void){
	usartConfig(USART_MODE_ASYNCHRONOUS,
	USART_BAUD_115200,
	USART_DATA_BITS_8,
	USART_PARITY_NONE,
	USART_STOP_BIT_SINGLE);
	usartEnableTransmitter();
	usartEnableReceiver();
	usartClearReceptionBuffer();
	usartActivateReceptionCompleteInterrupt();
	usartStdio();
}