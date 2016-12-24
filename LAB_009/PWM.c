#include "PWM.h"

void PWM_Init() {
	//Turn on PWM
	PCONP |= (1<<5);
	
	//Enable PWM output for corresponding pin.
	PWMX->PCR |= (1<<11);
	
	//PWM gives pulse every 20 ms.
	PWMX->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	PWMX->MR3 = 0;
	
	//Enable PWM Match Latch 0 and Latch 3.
	PWMX->LER |= (1<<0);
	PWMX->LER |= (1<<3);
	
	//Write the Correct Values to TCR for Enabling Counter and PWM
	PWMX->TCR |= (1<<0);
	PWMX->TCR |= (1<<3);
	PWM_Write(0);
}

void PWM_Write(uint32_t value) {
	uint32_t trueValue;
	
	if(value > 1000) {
		value = 1000;
	}
	
	trueValue = (uint32_t)(((PWMX->MR0) * value) / 1000);
	
	if (trueValue == PWMX->MR0) {
		trueValue++;
	}
	
	PWMX->MR3 = trueValue;
	
	PWMX->LER |= 1 << 3;
}
