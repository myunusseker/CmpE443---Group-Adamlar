#include "LPC407x_8x_177x_8x.h"

#include <stdio.h>

#include "Library/MMA7455.h"
#include "Library/Serial.h"
	char stringValue [30];
	int values[3] = {0,0,0};

void init() {
	MMA7455_Init();
	//Write to Correct Mode to MMA7455
	MMA7455_setMode(0);//???????????????????????????? bu ne
	MMA7455_calibrate();
	
	//Serial_Init();
}

void update() {

	
	MMA7455_read(&values[0], &values[1], &values[2]);
	
	sprintf(stringValue ,"x, y, z = %d, %d, %d\r\n" , values[0], values[1], values[2]);
	
	/*
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
	*/
	
	wait(100);
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

