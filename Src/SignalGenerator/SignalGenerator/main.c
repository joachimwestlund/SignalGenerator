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

#include "i2c/i2c.h"
#include "NHC_LCD/NHC_LCD.h"

/** check my schematic on rotary encoder for A and B */
volatile uint8_t A_trace = 0;
/** check my schematic on rotary encoder for A and B */
volatile uint8_t B_trace = 0;

volatile uint8_t right = 0;
volatile uint8_t left = 0;

volatile uint8_t count = 3;
char count_buf[9] = {0};

volatile uint8_t updateLCD = 1;



int main(void)
{	
	uint8_t status = 0;
	uint8_t *str = (uint8_t*)"Jocke";
	uint8_t *str1 = (uint8_t*)"rules";
	
	DDRD |= 0xff;
	PORTD = 0x00;
		
	_delay_ms(100);		// delay so the LCD can initialize
	
	I2C_Init();
	
	if ((status = I2C_WriteString(0x50, str, 0x05)) != 0)	// send an 'A' to LCD
	{
		PORTD = ~(status);									// invert output to LEDS so they are shown correctly.
		while(1) {}											// Halt program
	}
	else
		PORTD = 0xff;										// means all leds are off. status OK! ;)
		

//	DDRD |= 0b00000000;										// Set all pins to 1 to make it outputs
//	DDRD &= 0b10011111;										// clear bit 5 and 6 so they are inputs for rotary encoder

	PORTD = 0x02;									
	
	_delay_ms(2);
	LCD_WriteCommand(0x50, 0x46);
	_delay_ms(2);
	I2C_WriteString(0x50, str1, 0x05);	



    while (1) 
    {
		/*
		if ((PIND & (1 << PIND5)) == (1 << PIND5)) 
		{
			// pin is high, do nothing
		} 
		else
		{
			if (left == 0)
			{
				right = 1;
				A_trace = 1;
			}
		}
		if ((PIND & (1 << PIND6)) == (1 << PIND6))
		{
			// pin high, do nothing
		}
		else
		{
			if (right == 0)
			{
				left = 1;
				B_trace = 1;
			}
		}
		
		if (A_trace == 1 && B_trace == 1)
		{
			if (right == 1)
			{
				count++;
				updateLCD = 1;
			}
			if (left == 1)
			{
				count--;
				updateLCD = 1;
			}
			A_trace = 0;
			B_trace = 0;
			right = 0;
			left = 0;
		}
		*/
		if (updateLCD == 1)
		{
			snprintf(count_buf, 0x09, "%08d", count);
			I2C_WriteString(0x50, (uint8_t *)count_buf, 0x08);
			updateLCD = 0;
		}
		
    }
}

