#ifndef CARSPEEDOUTPUT_H
#define CARSPEEDOUTPUT_H

#include "LPC407x_8x_177x_8x.h"

/*extern uint8_t clapCount;
extern uint8_t clapCountRisingEdge;
extern uint8_t clapCountChanged;
*/
#define IOCON_CAR_OUTPUT_PIN_ADDRESS	0x4002C094
#define IOCON_CAR_OUTPUT_PIN	*((volatile uint32_t*)(IOCON_CAR_OUTPUT_PIN_ADDRESS))

void CarOutputInit(void);

#endif
