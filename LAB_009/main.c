#include "LPC407x_8x_177x_8x.h"

#include "CarSpeedOutput.h"
#include "PWM.h"
#include "Wait.h"
#include "MMA7455.h"
#include "Serial.h"
#include <stdio.h>

char stringValue [30];
int x = 0, carOutput = 0;
int values[3] = {0,0,0};

void init() {
	MMA7455_Init();
	MMA7455_setMode(1);
	MMA7455_calibrate();
	CarOutputInit();
	PWM_Init();
	Serial_Init();
}

uint32_t mapAccValue(int acc){
	return (uint32_t)(acc/63.0*999);
}

void update() {

	MMA7455_read(&values[0], &values[1], &values[2]);
	x = values[0];
	if(x < 0) x = 0;
	else if(x > 63) x = 63;
	carOutput = mapAccValue(x);
	PWM_Write(carOutput);
	sprintf(stringValue ,"x, y, z, carOutput= \t%d, \t%d, \t%d \t%d\r\n" , values[0], values[1], values[2], carOutput);
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

