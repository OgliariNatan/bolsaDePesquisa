/*
 * rotaryEncoder.c
 *
 * Created: 25/01/2017 12:58:39
 * Author : cliente
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include "ATmega328.h"
#include "globalDefines.h"
#define F_CPU 16000000UL

#define max_encoders 8
#define pin_a PD2
#define pin_b PD4


struct encoder{
	int pin_a;
	int pin_b;
	volatile long value;
	volatile int lastEncoded;
};


struct encoder encoders[max_encoders];
struct encoder *setupencoder(int pin_a, int pin_b);

//int encoder;
int numberofencoders = 0;

int main(void)
{
    
	DDRD &= ~(1 << PD2);	//encoder A
	DDRD &= ~(1 << PD4);	//encoder B
	PORTD |= (1 << PD2);    //Pull-UP R
	PORTD |= (1 << PD4);    //Pull-UP R
	
	MCUCR|=(1<<ISC01)|(1<<ISC00);   //Set INT0 na "rising" signal on pin PD2
	//GICR |=(1<<INT0 );				//set interrupt INT0
	sei();    //sei global interrupt
	
	
	void updateEncoders(){
		struct encoder *encoder = encoders;
		for (; encoder < (encoders + numberofencoders); encoder++)		{
			int MSB = setBit(DDRD, pin_a);
			int LSB = setBit(DDRD, pin_b);

			int encoded = (MSB << 1) | LSB;
			int sum = (encoder->lastEncoded << 2) | encoded;

			if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder->value++;
			if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder->value--;

			encoder->lastEncoded = encoded;
		}
	}

	struct encoder *setupencoder(int pin_a, int pin_b){
		if (numberofencoders > max_encoders)
		{
			printf("Maximum number of encodered exceded: %i\n", max_encoders);
			return NULL;
		}

		struct encoder *newencoder = encoders + numberofencoders++;
		newencoder->pin_a = pin_a;
		newencoder->pin_b = pin_b;
		newencoder->value = 0;
		newencoder->lastEncoded = 0;

		//pinMode(pin_a, INPUT);
		//pinMode(pin_b, INPUT);
		//pullUpDnControl(pin_a, PUD_UP);
		//pullUpDnControl(pin_b, PUD_UP);
		//wiringPiISR(pin_a,INT_EDGE_BOTH, updateEncoders);
		//wiringPiISR(pin_b,INT_EDGE_BOTH, updateEncoders);

		return newencoder;
	}

	
	
    while (1) 
    {
		
    }
}

