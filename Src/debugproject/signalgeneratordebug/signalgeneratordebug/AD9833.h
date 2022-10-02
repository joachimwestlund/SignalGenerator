/*
 * AD9833.h
 *
 * Created: 2022-04-21 11:08:44
 *  Author: Joachim Westlund
 *
 */ 


#ifndef AD9833_H_
#define AD9833_H_

#include <avr/io.h>
#include <math.h>

#include "SPI.h"

unsigned long	mclk;

uint16_t		controlRegister;
uint16_t		freqRegister;
uint16_t		phaseRegister;
uint16_t		phase;
unsigned long	freq;				// output frequency

void AD9833_Init(void);
void AD9833_WriteData(uint16_t data);
void AD9833_Reset(uint8_t reset);
void AD9833_SetFreq(unsigned long _freq);
void AD9833_SetMode(int mode);
void AD9833_SetPhase(int _phase);
void AD9833_SetFreqPhasePRegister(int reg);


#endif /* AD9833_H_ */