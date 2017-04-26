/*
 * bluetooth_Attiny85.c
 *
 * Created: 02/04/2017 04:37:20
 * Author : Natan Ogliari 
 */ 

#include <avr/io.h>
#include <avr/iotnx5.h>
#define F_CPU 8000000UL //8Mhz
#include <util/delay.h>
#include <avr/interrupt.h>

//#define DEBUG //!<Ativa a depuração

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(set_bit))//bit 
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


#define BAUD 9600
#define BRC        ((F_CPU/16/BAUD) - 1)
#define RX_BUFFER_SIZE 128
char rxBuffer[RX_BUFFER_SIZE];
volatile uint8_t rxReadPos = 0;
volatile uint8_t rxWritePos = 0;

char getChar(void);
char peekChar(void);

int main(void)
{
	 //volatile uint8_t UBRR0H;
	 //volatile uint8_t UBRR0L;
	 //UBRR0H = (BRC >> 8);    // set baud rate High
	 //UBRR0L = BRC;            // set baud rate Low
	 
	  // control & status register
	  //UCSR0B = (1 << RXEN0) | (1 << RXCIE0);    // enable USART receiver, enables interrupt on the RXCn Flag
	  //UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // set frame format, character size 5bit
	  
	  //DDRB = (1 << _BV(PB4));    // PORTB3 is OUTPUT
	  PORTB = 0x11;
	  
	  //sei();    // set interrupt
	CLKPR=_BV(CLKPCE);
	CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)
	
	sei();                   // Enable all interrupts


	//DDRB=_BV(PB4);		// Enable LED output pin


    /* Replace with your application code */
    while (1) 
    {
		set_bit( 1 |< 0x1f)
    }
}

char peekChar(void)
{
	char ret = '\0';
	
	if(rxReadPos != rxWritePos)
	{
		ret = rxBuffer[rxReadPos];
	}
	return ret;
}

char getChar(void)
{
	char ret = '\0';
	
	if(rxReadPos != rxWritePos)
	{
		ret = rxBuffer[rxReadPos];
		
		rxReadPos++;
		
		if(rxReadPos >= RX_BUFFER_SIZE)
		{
			rxReadPos = 0;
		}
	}
	return ret;
}

//ISR(USART_RX_vect)
//{
	//uint8_t UDR0;	// UDR0 == USIDR ??? VERIFICAR   problemas neste registrador, possivel que ñ seja este!!!!!!!!ATENÇÃO!!!!!!
	//rxBuffer[rxWritePos] = USIDR; //UDR0;
	
	//rxWritePos++;
	
	//if(rxWritePos >= RX_BUFFER_SIZE)
	//{
		//rxWritePos = 0;
	//}
//}


#ifdef DEBUG
 //Adicionar uma comunicação serial
#endif // DEBUG
ISR(PCINT0_vect)//PCINT0_vect
{
	//updateBlue(int *dados); //a implementar
	//uint8_t value;
	//value = 1;             // Increment volatile variable
}