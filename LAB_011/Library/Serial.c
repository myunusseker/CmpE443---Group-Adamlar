#include "Serial.h"

char serialReceivedCharacter = 0;
char* serialTransmitData = 0;
uint8_t serialTransmitCompleted = 0;

void Serial_Init() {
	Serial_UART_TX_PIN |= 0x01;
	Serial_UART_RX_PIN |= 0x01;
	
	PCONP |= 1 <<  3;
	
	Serial_UART->FCR =	1 << 0
						 |	0 << 1
						 |	0 << 2
						 |	0 << 6;
	
	//In order to change the DLM, DLL and FDR values, Write correct code for enabling the access to Divisor Latches.
	Serial_UART->LCR |= 0x00;
	
	//Write correct DLM, DLL and FDR values for 9600 baudrate
	Serial_UART->DLM = 0x00;
	Serial_UART->DLL = 0x00;
	Serial_UART->FDR = 0x00 << 0 | 0x00 << 4;

	//Write correct code for disabling the access to Divisor Latches.
	Serial_UART->LCR &= 0x00;
	
	//Change LCR register value for 8-bit character transfer, 1 stop bits and Odd Parity.

							
	Serial_UART->IER |= 1 << 0 | 1 << 1;
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn,5);
}

void UART0_IRQHandler() {	
	uint32_t currentInterrupt = ((Serial_UART->IIR & (0x7 << 1)) >> 1);
	
	if(currentInterrupt == 0x02) {
		serialReceivedCharacter = Serial_ReadData();
	}
	else if(currentInterrupt == 0x01) {
		if(*serialTransmitData > 0) {
			Serial_WriteData(*serialTransmitData++);
		}
		else {
			serialTransmitCompleted = 1;
		}
	}
}

char Serial_ReadData() {
	return Serial_UART->RBR;
}

void Serial_WriteData(char data) {
	serialTransmitCompleted = 0;
	Serial_UART->THR = data;
}

