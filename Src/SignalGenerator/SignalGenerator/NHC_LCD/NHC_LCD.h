/*
 * NHC_LCD.h
 *
 * Created: 2022-03-12 20:09:24
 *  Author: jocke
 */ 


#ifndef NHC_LCD_H_
#define NHC_LCD_H_


#include "../i2c/i2c.h"

uint8_t LCD_WriteCommand(uint8_t addr, uint8_t command);


#endif /* NHC_LCD_H_ */