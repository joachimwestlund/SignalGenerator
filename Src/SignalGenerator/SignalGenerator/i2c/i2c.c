/** \File */

/*
 * CFile1.c
 *
 * Created: 2022-02-27 14:24:38
 * Author: Joachim Westlund
 *
 * Based on this site:
 * https://embedds.com/programming-avr-i2c-interface/
 */ 

#include "i2c.h"


/**
*	Initialize I2C or as some call it TWI (Two Wire Interface)
*/
void I2C_Init(void)
{
	TWSR = I2C_Prescaler;
	TWBR = I2C_BitRate;
	TWCR = (1 << TWEN);	// enable TWI
}


/**
*	Send Start signal
*/
void I2C_Start(void) 
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	while ((TWCR & (1 << TWINT)) == 0)
	{
		
	}
}

/**
*	Send stop signal
*/
void I2C_Stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/**
*	Write a byte
*/
void I2C_Write(uint8_t u8data)
{
	TWDR = u8data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

/**	
*	Read byte with ACK
*/
uint8_t I2C_ReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

/**
*	Read byte with NACK
*/
uint8_t I2C_ReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

/**
*	Reading the status
*/
uint8_t I2C_GetStatus(void)
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

/**
*	7-bit addressing mode
*	Returns 0 on success and status code on failure
*/
uint8_t I2C_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t status = 0;
	
	I2C_Start();
	status = I2C_GetStatus();
	if (status != 0x08)
		return(status);
	
	addr &= 0b11111110;		// setting LSB to 0 Write mode.
	
	I2C_Write(addr);
	status = I2C_GetStatus();
	if (status != 0x18)
		return(status);	
		
	I2C_Write(data);
	status = I2C_GetStatus();
	if (status != 0x28)
		return(status);
	
	I2C_Stop();
	
	return(0);	
}

/**
*	7-bit addressing mode
*	Returns 0 on success and status code on failure
*/
uint8_t I2C_WriteString(uint8_t addr, uint8_t *data, uint8_t size)
{
	uint8_t status = 0;
	uint8_t i = 0;
	
	I2C_Start();
	status = I2C_GetStatus();
	if (status != 0x08)
		return(status);

	addr &= 0b11111110;		// write mode
	
	I2C_Write(addr);
	status = I2C_GetStatus();
	if (status != 0x18)
		return(status);
	
	for (i = 0; i < size; i++)
	{
		I2C_Write(*data++);
		if (status != 0x18)
			return(status);
	}
	
	I2C_Stop();
	
	return(0);
}