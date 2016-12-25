#include "LPC407x_8x_177x_8x.h"

#include "CarSpeedOutput.h"
#include "PWM.h"
#include "Wait.h"
#include "MMA7455.h"
#include "Serial.h"
#include <stdio.h>

char stringValue [30];
int angleX = 0, carOutput = 0;
int values[3] = {0,0,0};

void TI() {
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

// Task Get Acceleration
void TGA()
{
	MMA7455_read(&values[0], &values[1], &values[2]);
	angleX = values[0];
	if(angleX < 0) angleX = 0;
	else if(angleX > 63) angleX = 63;
}

//Task Set Speed
void TSS()
{
	carOutput = mapAccValue(angleX);
	PWM_Write(carOutput);
}

// Task System Diagnosis
void TSD()
{
	sprintf(stringValue ,"x, y, z, carOutput= \t%d, \t%d, \t%d \t%d\r\n" , values[0], values[1], values[2], carOutput);
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
}

void update() {
	TGA();
	TSS();
	TSD();
}

int main() {
	TI();
	while(1) {
		update();
	}
}

