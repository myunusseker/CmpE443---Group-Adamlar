#include "LPC407x_8x_177x_8x.h"

#include "CarSpeedOutput.h"
#include "PWM.h"
#include "Wait.h"

int x = 500;

void init() {
	CarOutputInit();
	PWM_Init();
}
void update() {
//	x++;
//	if(x == 1000) x = 500;
	PWM_Write(x);
//	wait(50);
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

