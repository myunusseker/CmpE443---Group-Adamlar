#include "LPC407x_8x_177x_8x.h"

#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"
#include <stdio.h>

float distance = 0 ;
char l = 0;
int flag = 0,lapCounter = 0, carDistanceLimit = 10;
char stringValue [30];

void init() {
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger_Timer();
	LCD_Init();
	LCD_clearDisplay();
	LCD_write("LAP: ");
	LCD_data('0');
	Serial_Init();
}

void update() {
	if(ultrasonicSensorNewDataAvailable == 1)
	{
		distance = ultrasonicSensorDuration / 58.0;
		if(flag == 0 && distance < carDistanceLimit)
		{
			flag = 1;
			lapCounter++;
			if(lapCounter == 100) lapCounter = 0;
			LCD_setCursorPositionFirstLine(5);
			LCD_clearDisplay();
			LCD_write("LAP: ");
			if(lapCounter > 9)
				LCD_data('0' + (lapCounter/10));
			LCD_data('0' + (lapCounter%10));
			sprintf(stringValue ,"LAP:%d \t%f\r\n" , lapCounter, distance);
			serialTransmitData = stringValue;
			Serial_WriteData(*serialTransmitData++);
			while(!serialTransmitCompleted);
		}
		if(flag == 1 && distance >= carDistanceLimit) flag = 0;
		ultrasonicSensorNewDataAvailable = 0;
	}
}

int main() {
	init();
	__enable_irq();

	sprintf(stringValue ,"SYSTEM DIAGNOSIS STARTED\r\n");
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);

	while(1) {
		update();
		__WFI();
	}
}