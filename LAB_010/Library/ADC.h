#ifndef ADC_H
#define ADC_H

#include "LPC407x_8x_177x_8x.h"

#include "SystemStructures.h"

typedef struct
{
  volatile	uint32_t CR;
  volatile	uint32_t GDR;
						uint32_t RESERVED0;
  volatile	uint32_t INTEN;
  volatile	uint32_t DR[8];
  volatile	uint32_t STAT;
  volatile	uint32_t TRM;
} ADC_TypeDef;

#define ADC_CLOCK_FREQUENCY 1000000

#define ADC_CLKDIV ((PERIPHERAL_CLOCK_FREQUENCY / ADC_CLOCK_FREQUENCY) -  1)

#define ADC_MAX_VALUE 0xFFF

#define ADC_BASE	0x40034000
#define ADC	((ADC_TypeDef*) ADC_BASE)

#define	ANALOG_PIN_IOCON_ADDRESS	0x4002C060
#define ANALOG_PIN_IOCON	*((volatile uint32_t*)(ANALOG_PIN_IOCON_ADDRESS))

extern uint32_t ADC_Last;
extern uint8_t ADC_New_Data_Available;

void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);


#endif
