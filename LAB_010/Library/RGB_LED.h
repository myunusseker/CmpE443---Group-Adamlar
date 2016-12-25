#ifndef RGB_LED_H
#define RGB_LED_H

#include "GPIO.h"

#define RGB_LED_Color_NUMBER 8

typedef enum {
	RED = 1,
	GREEN = 2,
	BLUE = 3,
	MAGENTA = 4,
	CYAN = 5,
	YELLOW = 6,
	WHITE = 7,
	BLACK = 0
} RGB_LED_Colors;

#define RED_LED_PORT			PORT1
#define RED_LED_MASK			((uint32_t) 1 << 11)

#define GREEN_LED_PORT			PORT1
#define GREEN_LED_MASK			((uint32_t) 1 << 5)

#define BLUE_LED_PORT			PORT1
#define BLUE_LED_MASK			((uint32_t) 1 << 7)

void RGB_LED_Init(void);
void RGB_LED_setColor(RGB_LED_Colors color);

#endif
