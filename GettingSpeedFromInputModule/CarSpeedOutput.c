#include "CarSpeedOutput.h"

/*uint8_t clapCount = 0;
uint8_t clapCountRisingEdge = 0;
uint8_t clapCountChanged = 0;
*/
void CarOutputInit() {
	IOCON_CAR_OUTPUT_PIN |= (1 << 0);
	IOCON_CAR_OUTPUT_PIN |= (1 << 1);
	IOCON_CAR_OUTPUT_PIN &= ~(1 << 2);
}
