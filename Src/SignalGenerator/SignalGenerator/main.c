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

#include "i2c/i2c.h"

/** check my schematic on rotary encoder for A and B */
volatile uint8_t A_trace = 0;
/** check my schematic on rotary encoder for A and B */
volatile uint8_t B_trace = 0;

volatile uint8_t count = 0;

ISR(INT0_vect) 
{
	PORTD |= (0x01 << 7);	// set pin 8 high
	
	if (B_trace == 0x01)
	{
		count--;
		A_trace = 0;
		B_trace = 0;
	}
	else
	{
		A_trace = 0x01;	
	}
}

ISR(INT1_vect)
{
	PORTD &= ~(0x01 << 7);	// set pin 8 low
	
	if (A_trace == 0x01)
	{
		count++;
		A_trace = 0;
		B_trace = 0;
	}
	else
	{
		B_trace = 0x01;
	}
}


int main(void)
{	
	uint8_t status = 0;
	uint8_t *str = (uint8_t*)"Jocke";
	
	DDRD |= 0xff;
	PORTD = 0x00;
		
	_delay_ms(1);		// delay so the LCD can initialize
	
	I2C_Init();
	
	if ((status = I2C_WriteString(0x50, str, 0x05)) != 0)	// send an 'A' to LCD
	{
		PORTD = ~(status);	// invert output to leds so they are shown correctly.
	}
	else
		PORTD = 0xff;	// means all leds are off. status OK! ;)
		
	//PORTD = ~0x04;		

/*	
	DDRD |= 0b10000000;		// Set MSB to 1 to make it an output
	DDRD &= 0b11110011;		// clear bit 2 and 3 so they are inputs

	PORTD |= 0b10001100;		// enable pull up resistors on the inputs and on PD2,3 and 7.
		
	EICRA = 0b00001010;			// Set up external interrupt control register A to falling edge on of INT1 and INT0
	
	EIMSK = 0b00000011;		// enable the two interrupts
	
	sei();
	*/
    while (1) 
    {
//		PORTD &= 0b01111111;
//		_delay_ms(1000);
//		PORTD &= 0b11111111;
//		_delay_ms(1000);
    }
}

