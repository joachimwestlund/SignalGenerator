/*
 * main.c
 *
 * Created: 9/30/2022 12:36:23 PM
 *  Author: jocke
 */ 


#define F_CPU 16000000UL

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#include "AD9833.h"

int main(void)
{
	
	AD9833_Init();
	
	DDRB |= (1 << DDB0);
		
    while(1)
    {
        PORTB &= ~(1 << DDB0);

		AD9833_Reset(1);
		AD9833_SetFreq(1000);				// 1kHz
		AD9833_SetPhase(0);					// 0 phase shift
		AD9833_Reset(0);
	
		_delay_ms(500); 

		PORTB |= (1 << DDB0);
		

		_delay_ms(500);
    }
	return(0);
}