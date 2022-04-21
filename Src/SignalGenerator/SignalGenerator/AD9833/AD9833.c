/*
 * AD9833.c
 *
 * Created: 2022-04-21 11:08:59
 *  Author: Joachim Westlund
 */ 

#include "AD9833.h"

void AD9833_Init(void)
{
	mclk = 25000000;	// 25Mhz external oscillator
	controlRegister = 0x2000;
	freqRegister = 0x4000;
	phaseRegister = 0xc000;
	freq = 1000;	// 1kHz
	phase = 0;
	
	SPI_Init();
}


void AD9833_WriteData(uint16_t data)
{
	uint8_t tmp;
	// get high byte of data
	tmp = (uint8_t)(data >> 8);
	SPI_Start_Transfer();
	SPI_Tranceiver(tmp);
	// get low byte of data
	tmp = (uint8_t)(data & 0x00ff);
	SPI_Tranceiver(tmp);
	SPI_End_Transfer();
}

/**
*	reset: 1 means set reset and 0 means not reset. or unreset.
*/
void AD9833_Reset(uint8_t reset)
{
	if (reset == 0)
	{
		controlRegister &= 0xFEFF;	// set D8 to 0
	}
	else if (reset == 1)
	{
		controlRegister |= 0x0100;	// set D8 to 1
	}
	AD9833_WriteData(controlRegister);
}

void AD9833_SetFreq(unsigned long _freq)
{
	unsigned long fRegister;
	uint16_t MSW;	// Most Significant Word
	uint16_t LSW;	// Least Significant Word
	
	if (_freq < 0)					// frequency cant be set to lower than 0 Hz
	{
		fRegister = 0;
		freq = 0;
	}
	else if(_freq > (mclk /2))		// frequency cant be set to higher than mclk/2
	{
		fRegister = pow(2,28) - 1;
		freq = mclk / 2;
	}
	else							// all good, then we set the new frequency.
	{
		freq = _freq;
		fRegister = (freq * pow(2,28)) / mclk;
	}
	
	MSW = ((uint16_t)(fRegister >> 14)) | freqRegister;
	LSW = ((uint16_t)(fRegister & 0x3FFF)) | freqRegister; 
	
	AD9833_WriteData(LSW);
	AD9833_WriteData(MSW);
}

void AD9833_SetMode(int mode) {
	switch (mode) {
		case 0: {
			controlRegister &= 0xFFDD; // Output sine: D5-0 and D1-0
		} break;
		case 1: {
			controlRegister &= 0xFFDF; // Output triangle: D5-0 and D1-1
			controlRegister |= 0x0002;
		} break;
		case 2: {
			controlRegister &= 0xFFFD; // Output clock (rectangle): D5-1 and D1-0
			controlRegister |= 0x0020;
		} break;
	}
	AD9833_WriteData(controlRegister);
}

void AD9833_SetPhase(int _phase) {
	
	uint16_t phaseData;
	uint16_t LSW;
	
	// Phase cannot be negative
	if (_phase < 0) {
		phase = 0;
	}
	// Phase maximum is 2^12
	else if (_phase >= 4096) {
		phase = 4096 - 1;
	}
	// If all is good, set the new phase value
	else {
		phase = _phase;
	}
	// Extract the 12 bits from the freqReg and set D15-1, D14-1, D13-0, D12-X to
	// put data in PHASE0/1 register
	
	phaseData = phase | phaseRegister;
	LSW = (phaseData & 0x3FFF) | phaseRegister;
	
	AD9833_WriteData(phaseData);			// This might be wrong
}

// reg0 or reg1
void AD9833_SetFreqPhasePRegister(int reg) {
	if (reg == 0) 
	{
		controlRegister &= 0xF3FF;			// Set D11 and D10 in control register to 0
		freqRegister = 0x4000;				// Set D15 to 0 and D14 to 1 in a variable that will
											// later choose the FREQ0 register
		phaseRegister =	0xC000;				// Set D15 to 1 and D14 to 1 and D13 to 0 for the PHASE register
		
	} 
	else if (reg == 1) 
	{
		controlRegister |= 0x0C00;			// Set D11 and D10 in control register to 1
		freqRegister = 0x8000;				// Set D15 to 1 and D14 to 0 in a variable that will
											// later choose the FREQ1 register
		phaseRegister =	0xD000;				// Set D15 to 1 and D14 to 1 and D13 to 1 for the PHASE register
	}
	AD9833_WriteData(controlRegister);
}