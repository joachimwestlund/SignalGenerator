/*
 * SPI.c
 *
 * Created: 2022-04-20 12:46:25
 * Author: Joachim Westlund
 */ 


#include "SPI.h"

void SPI_Init(void)
{
	// SS, MOSI and CLK as outputs
	DDRB |= (1 << PINB2) | (1 << PINB3) | (1 << PINB5);
	// MISO as input
	DDRB &= ~(1 << PINB4);
	SPI_End_Transfer();
	
	// SPCR |= ~(1 << SPIE) | (1 << SPE) | (1 << DORD) | (1 << MSTR) | ~(1 << CPOL) | ~(1 << CPHA) | ~(1 << SPR1) | ~(1 << SPR0);
	
	// Enable SPI 4Mhz clock no interrupt enable. LSB. 
	SPCR = 0b01010000;
	SPSR &= ~(1 << SPI2X);
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
	PORTB |= (1 << PINB2);
}

void SPI_Start_Transfer(void)
{
	// Set SS pin low
	PORTB &= ~(1 << PINB2);
}