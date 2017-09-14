/*
 * why_not.c
 *
 * Created: 14/09/2017 18:06:28
 * Author : Cliente
 */ 
#define F_CPU 800000UL

#include <avr/io.h>
#include "nrf24l01.h"
//#include "ATmega328.h"
#include "globalDefines.h"



// Configura��o do nrf24l01
nRF24L01 *setup_rf(void);
void process_message(char *message);
//FIM configura��o nrf24
//inline void prepare_led_pin(void);
//inline void  set_led_high(void);
//inline void  set_led_low(void);
volatile bool rf_interrupt = false;
volatile bool send_message = false;


int main(void)
{
	uint8_t address[5] = { 0x01, 0x01, 0x01, 0x01, 0x01 };
    sei();
    nRF24L01 *rf = setup_rf(); //configura os pinos do modulo nrf24l01
    nRF24L01_listen(rf, 0, address); //configura o modulo para leitura com endere�os pr� estabelecidos
    uint8_t addr[5];
	uint8_t CONFIG = 0; //VERIFICAR APAGAR
    nRF24L01_read_register(rf, CONFIG, addr, 1);//configura a verifica��o das mensagem
	
    while (1) {
		
    }
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
	OCR1A = 15624;
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




/*Help

https://br-arduino.org/2015/05/arduino-bootloader-atmega-standalone.html
https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard

*/
