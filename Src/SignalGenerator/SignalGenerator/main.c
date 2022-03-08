/** \File */

/**
 * SignalGenerator.c
 *
 * Created: 2022-02-27 13:12:30
 * Author : Joachim Westlund
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0b00000100;
	PORTD = 0b0000000;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b00000100;
		_delay_ms(100);
		PORTD = 0b00000000;
		_delay_ms(100);
    }
}

