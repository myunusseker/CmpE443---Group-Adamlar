#ifndef GPIO_H
#define GPIO_H

#include "LPC407x_8x_177x_8x.h"
#include "DataStructure.h"

void GPIO_PIN_Write(PORT_TypeDef* PORT,uint32_t MASK,uint8_t value);

#endif
