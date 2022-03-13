/** \File */

/*
 * i2c.h
 *
 * Created: 2022-02-27 14:24:28
 * Author: Joachim Westlund
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_SDL				PORTC4
#define I2C_SCL				PORTC5
#define I2C_Port			PORTC
#define I2C_DataDirection	DDRC

#define I2C_BitRate			0x98	// This sets 50kHz. For 400kHz use 0x0c.     
									// formula: SCL_freq = CPU_freq / (16 + (2*TWBR*TWSR))
									// TWBR = bitrate register
									// TWBS = PrescaleValue 2,4,8,16,32,64
#define I2C_Prescaler		0x00

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t);
uint8_t I2C_ReadACK(void);
uint8_t I2C_ReadNACK(void);

uint8_t I2C_WriteByte(uint8_t, uint8_t);
uint8_t I2C_WriteString(uint8_t, uint8_t*, uint8_t);


#endif /* I2C_H_ */