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

NEW: https://www.youtube.com/watch?v=ZDtRWmBMCmw

*/


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "i2c/i2c.h"
#include "NHC_LCD/NHC_LCD.h"

volatile uint8_t count = 0;
volatile uint8_t set_count = 0;
char count_buf[4] = {0};
char set_count_buf[4] = {0};

volatile uint8_t updateLCD = 1;

ISR (PCINT2_vect)
{
	if ((PIND & (1 << PIND5)) != (1 << PIND5))				// if interrupt pin is low
	{
		if ((PIND & (1 << PIND6)) != (1 << PIND6))			// and if the pd6 pin is low then the direction is left
		{
			count--;	
		}
		else
		{
			count++;										// if pd6 is high then the direction is right
		}
		updateLCD = 1;
	}
}

int main(void)
{	
	uint8_t status = 0;
	uint8_t *str = (uint8_t*)"Rotary Encoder";
	
	_delay_ms(100);		// delay so the LCD can initialize
	
	I2C_Init();
	
	LCD_WriteCommand(0x50, 0x51, 0x00);
	_delay_ms(2);
	if ((status = I2C_WriteString(0x50, str, strlen((char *)str))) != 0)	// send an 'A' to LCD
	{
		PORTD = ~(status);									// invert output to LEDS so they are shown correctly.
		while(1) {}											// Halt program
	}
	else
		PORTD = 0xff;										// means all leds are off. status OK! ;)
		
	DDRD &= 0b01111111;										// pin7 as input
	PORTD |= 0b10000000;									// enable pull-up on pin7

	// Lets enable PCINT21 on pin PD5
	DDRD &= 0b11011111;										// pin5 port d are input
	PORTD |= 0b00100000;									// enable pull-ups on pin
	PCICR = (1 << PCIE2);
	PCMSK2 |= 0b00100000;									// pin pd5 enabled for interrupt. pcint21 as interrupt.
	sei();
	
    while (1) 
    {
		if ((PIND & (1 << PIND7)) != (1 << PIND7))			// is pin7 low?
		{
				set_count = count;
				updateLCD = 1;
		}
		
		if (updateLCD == 1)
		{
			_delay_ms(2);
			LCD_WriteCommand(0x50, 0x45, 0x40);
			snprintf(count_buf, 0x04, "%03d", count);
			_delay_ms(2);
			I2C_WriteString(0x50, (uint8_t *)count_buf, 0x03);
			
			_delay_ms(2);
			LCD_WriteCommand(0x50, 0x45, 0x4a);
			snprintf(set_count_buf, 0x04, "%03d", set_count);
			_delay_ms(2);
			I2C_WriteString(0x50, (uint8_t *)set_count_buf, 0x03);

			updateLCD = 0;
		}
		
    }
}

