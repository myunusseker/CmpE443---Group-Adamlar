#include "LPC407x_8x_177x_8x.h"

#include "Library/ADC.h"
#include "Library/ESP8266.h"
#include "Library/RGB_LED.h"
#include "Library/Serial.h"
#include "Library/Wait.h"

#include <stdio.h>

void init() {	
	Serial_Init();
	
	
	
	//RGB_LED_Init();
	
	//ADC_Init();
	//ADC_Start();
	
	//Connect the WiFi SSID = HWLAB  and Password = 12345678 (You can send AT Commands to ESP8266 with ESP8266_sendCommand)
	//Whenever you use ESP8266_sendCommand, wait until ESP8266 response end (You can use ESP8266_waitResponseEnd)
	//Whenever you use ESP8266_sendCommand, send the esp8266Response to PC via Serial Communication.
	
	//Get IP Address
	
	//Change WiFi Mode to Station Mode.
}

void update() {	
	//Connect 192.168.0.100 IP address and 8080 port via TCP.
	
	//Send "GET /HWLAB_IoT/GetColor HTTP/1.0\r\n\r\n" Packet. (Firstly, you should send the length of packet, after response return OK, you should send the packet.)
	
	//Change the RGB LED color according to response.
	
	if(ADC_New_Data_Available) {
		//Calculate temperature value.
		
		//Send temperature value to server.
		
		ADC_New_Data_Available = 0;
	}
}

int main() {
	init();
	serialTransmitData = "Hello World"; 
	Serial_WriteData(*serialTransmitData++); 
	while(!serialTransmitCompleted);

	while(1) {
		update();
	}
}

