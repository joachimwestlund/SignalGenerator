/*
 * SPI.c
 *
 * Created: 2022-04-20 12:46:25
 * Author: Joachim Westlund
 */ 


#include "SPI.h"

void SPI_Init(void)
{
	
	PORTB |= (1 << DDB3);
	PORTB |= (1 << DDB5);
	PORTB |= (1 << DDB2);
	
	// SS, MOSI and CLK as outputs
	DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
	
	// MISO as input
	DDRB &= ~(1 << DDB4);

	
	// SPCR |= ~(1 << SPIE) | (1 << SPE) | (1 << DORD) | (1 << MSTR) | ~(1 << CPOL) | ~(1 << CPHA) | ~(1 << SPR1) | ~(1 << SPR0);
	
	SPSR &= ~(1 << SPI2X);
	// Enable SPI 4Mhz clock no interrupt enable. LSB. CPOL=1, CPHA=0
	SPCR = 0b01011000;
	
}

uint8_t SPI_Tranceiver(uint8_t data)
{
	SPDR = (unsigned char)data;
	while (!(SPSR & (1 << SPIF)));
	
	return((uint8_t)SPDR);
}

void SPI_End_Transfer(void)
{
	// Set SS pin high
	PORTB |= (1 << DDB2);
}

void SPI_Start_Transfer(void)
{
	// Set SS pin low
	PORTB &= ~(1 << DDB2);
	
}