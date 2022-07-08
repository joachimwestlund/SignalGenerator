/*
 * SPI.h
 *
 * Created: 2022-04-20 12:46:15
 * Author: Joachim Westlund
 *
 * Based on https://maxembedded.com/2013/11/the-spi-of-the-avr/
 *
 */ 


//	Registers:
//	SPCR - SPI Control Register
//	SPSR - SPI Status Register
//	SPDR - SPI Data Register

#ifndef SPI_H_
#define SPI_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void SPI_Init(void);
uint8_t SPI_Tranceiver(uint8_t data);
void SPI_End_Transfer(void);
void SPI_Start_Transfer(void);

#endif /* SPI_H_ */