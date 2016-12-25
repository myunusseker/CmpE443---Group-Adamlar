#include "ADC.h"

uint32_t ADC_Last = 0;
uint8_t ADC_New_Data_Available = 0;

void ADC_Init() {
	ANALOG_PIN_IOCON |= 0x01;
	
	ANALOG_PIN_IOCON &= ~(1 << 3 | 1 << 4);
	
	ANALOG_PIN_IOCON &= ~(1 << 7);
	
	PCONP |= (1 << 12);
	
	ADC->CR = 	(1 << 1)
							|	(ADC_CLKDIV << 8)
							| (0 << 16)
							| (1 << 21)
							| (0 << 24);
	
	ADC->INTEN |= 1 << 1;
	
	NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_Start () {
	ADC->CR |= (1 << 24);
}

void ADC_Stop() {
	ADC->CR &= ~(7 << 24);
}

void ADC_IRQHandler() {
	ADC_Stop();
	
	ADC_Last = ADC->DR[1];
	
	ADC_Last = ((ADC_Last >> 4) & ADC_MAX_VALUE);
	
	ADC_New_Data_Available = 1;
	
	ADC_Start();
}
