/*
 * why_not.c
 *
 * Created: 14/09/2017 18:06:28
 * Author : Natan Ogliari
 */ 

#include "nrf24l01.h"
//#include "ATmega328.h"
#include "globalDefines.h"
#include "usart.h"




// Configuração do nrf24l01
nRF24L01 *setup_rf(void);
void process_message(char *message);
//FIM configuração nrf24
//inline void prepare_led_pin(void);
//inline void  set_led_high(void);
//inline void  set_led_low(void);
void initIO(void);
void initADC(void);
int readADC(uint8_t val);
volatile bool rf_interrupt = false;
volatile bool send_message = false;


int main(void)
{
	uint8_t address[5] = { 0x01, 0x01, 0x01, 0x01, 0x01 };
	uint8_t val = 0;
	initIO();
    sei();
    
	nRF24L01 *rf = setup_rf(); //configura os pinos do modulo nrf24l01
    nRF24L01_listen(rf, 0, address); //configura o modulo para leitura com endereços pré estabelecidos
    uint8_t addr[5];
	usart_init();
	
	uint8_t CONFIG = 0; //VERIFICAR APAGAR
    nRF24L01_read_register(rf, CONFIG, addr, 1);//configura a verificação das mensagem
	
		
    while (1) {
		val = readADC(0); //pino 0 das ADC
		
		
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

void initIO(){//Configuração de I/O
	DDRC = 0x00;
	PORTC = 0xFF;
}

void initADC() {//Conf ADC
	ADMUX = (1 << REFS0); // Aref = AVcc
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0); //prescaler 128
	
	
	DDRC &= ~_BV(2); //INPUT
	PORTC |= _BV(2); //pull high
	//...
	};
	
int readADC(uint8_t val){
	ADMUX = (1 << REFS0) | (val & 0x0f);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return ADCW;
}

/*Help

https://br-arduino.org/2015/05/arduino-bootloader-atmega-standalone.html
https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard

*/

