#include "LPC407x_8x_177x_8x.h"

#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"
#include <stdio.h>

int distance = 0 ;
char l = 0;
int flag = 0,lapCounter = 0, carDistanceLimit = 10;
char stringValue [30];

// Task Initialization
void TI() 
{
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger_Timer();
	LCD_Init();
	LCD_clearDisplay();
	LCD_write("LAP: ");
	LCD_data('0');
	Serial_Init();
	sprintf(stringValue ,"SYSTEM DIAGNOSIS STARTED\r\n");
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);
}

// Task Display
void TDI()
{
	LCD_setCursorPositionFirstLine(5);
	LCD_clearDisplay();
	LCD_write("LAP: ");
	if(lapCounter > 9)
		LCD_data('0' + (lapCounter/10));
	LCD_data('0' + (lapCounter%10));
}

// Task Ultrasonic
void TU()
{
	if(ultrasonicSensorNewDataAvailable == 1)
	{
		distance = ultrasonicSensorDuration / 58;
		ultrasonicSensorNewDataAvailable = 0;
		return;
	}		
	distance = -1;
}

// Task Lap Counter
void TC()
{
		if(flag == 0 && distance < carDistanceLimit)
		{
			flag = 1;
			lapCounter++;
			if(lapCounter == 100) lapCounter = 0;
		}
		if(flag == 1 && distance >= carDistanceLimit) flag = 0;
}

// Task system diagnosis
void TSD()
{
	sprintf(stringValue ,"LAP:%d \t%f\r\n" , lapCounter, distance);
	serialTransmitData = stringValue;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
}

void update() {
	TU();
	if(distance == -1) return;
	TC();
	TDI();	
	TSD();
}

int main() {
	TI();
	__enable_irq();

	while(1) {
		update();
		__WFI();
	}
}
