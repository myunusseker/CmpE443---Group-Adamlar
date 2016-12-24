#include "LPC407x_8x_177x_8x.h"

#include "CarSpeedOutput.h"
#include "PWM.h"
#include "Wait.h"

int x = 500;

void init() {
	//MMA7455_Init();
	//MMA7455_setMode(0);
	//MMA7455_calibrate();
	CarOutputInit();
	PWM_Init();
}
void update() {

	//MMA7455_read(&values[0], &values[1], &values[2]);
	//Angle a gore bir takim sihirli islemler oran orantilar.. BUMM
	PWM_Write(x);

}

int main() {
	init();
	
	while(1) {
		update();
	}
}

