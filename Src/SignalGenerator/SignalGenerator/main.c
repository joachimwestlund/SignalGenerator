/** \File */

/**
 * SignalGenerator.c
 *
 * Created: 2022-02-27 13:12:30
 * Author : Joachim Westlund
 */ 

/*

how to use interrupts

https://www.youtube.com/watch?v=eZH4B4PIIPU

Set bit 7 in SREG ... global interrupt flag

chapter 11 interrupts in datasheet

check jump vectors pysical places in flash

MCUCR used when using bootloaders but we don't so...

chapter 12 external interrupts

int0 and int1 are we using

vi ska använda falling edge för att så funkar rotoray encodern. den är hög och går låg när något händer.

EICRA - external interrups control register A set edge ISC11 and ISC01
EIMSK - External interrupt mask register enables the whole thing
EIFR - external intrerrupt flag register flags are automaticaly cleard when interrupts are done executing but may be checked



code below



*/


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>


int main(void)
{	
	DDRD &= 0b11110011		// clear bit 2 and 3 so they are inputs
	DDRD |= 0b11110011		// set all the others to outputs we could have done DDRD = 0b11110011
							// but i need a refresher on bitwise operations.
	
	PORTD = 0b00001100		// enable pullup resistors on the inputs or set them as high
	
	EICRA |= (0b10 << 2) | (0b10 << ISC00);
	
	EIMSK = 0b00000011;
	
	sei();
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD &= 0b01111111;
		_delay_ms(100);
		PORTD &= 0b11111111;
		_delay_ms(100);
    }
}

