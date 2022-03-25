/** \File */

/*
 * NHC_LCD.c
 *
 * Created: 2022-03-12 20:09:44
 *  Author: Joachim Westlund
 */ 

#include "NHC_LCD.h"

uint8_t LCD_WriteCommand(uint8_t addr, uint8_t command, uint8_t data)
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
	
	I2C_Write(0xfe);
	status = I2C_GetStatus();
	if (status != 0x28)
		return(status);
	
	I2C_Write(command);
	status = I2C_GetStatus();
	if (status != 0x28)
		return(status);
	
	if (data != 0)
	{
		I2C_Write(data);
		status = I2C_GetStatus();
		if (status != 0x28)
			return(status);
	}
	
	I2C_Stop();
	
	return(0);
}