/*
 * ADC.c
 *
 * Created: 02/04/2017 04:37:20
 * Author : Natan Ogliari 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"



void adc_init()
{
	PRR&=~(1<<PRADC);
	DDRA&=~(1<<DDA0);
	
	//admux every bit is zero
	ADCSRA|= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRB|=(1<<ADLAR);
	DIDR0|=(1<<ADC0D);
}

ISR(ADC_ADC_vect)
{
	unsigned int duty=0;
	unsigned int temp=0;
	char x;
	//duty=0.15*ADCH;
	float y=0.153;
	y=(float)(ADCH*y);
	duty=(int)(y);
	OCR0B=duty;
}