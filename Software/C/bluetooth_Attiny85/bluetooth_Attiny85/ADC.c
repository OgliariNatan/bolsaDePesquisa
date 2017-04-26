/*
 * ADC.c
 *
 * Created: 02/04/2017 04:37:20
 * Author : Natan Ogliari 
 */

#include <avr/io.h>
#include <avr/iotnx5.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ADC.h"
//#define DEBUG

void adc_init()
{
	PRR&=~(1<<PRADC);
	DDRB&=~(1<<DDB0);
	
	//admux every bit is zero
	ADCSRA|= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRB|=(1<<ADLAR);
	DIDR0|=(1<<ADC0D);
	sei();
}
/*
ISR(ADC_vect)//ADC_ADC_vect
{
	unsigned int duty=0;
	unsigned int temp=0;
	char x;
	duty=0.15*ADCH;
	uint8_t y;
	y = ADCH;
	duty=(int)(y);
	OCR0B=duty;//output write
}

*/


#ifdef DEBUG
	//confserial();
    //Adicionar uma comunicação serial
#endif // DEBUG

