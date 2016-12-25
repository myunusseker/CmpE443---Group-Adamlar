#include "Ultrasonic.h"

uint32_t ultrasonicSensorDuration = 0;
uint32_t ultrasonicSensorDistance = 0;
uint8_t ultrasonicSensorNewDataAvailable = 0;

uint8_t ultrasonicSensorTriggerStart = 0;
uint8_t ultrasonicSensorCaptureRisingEdge = 0;

void Ultrasonic_Init() {	
	//Give the Correct Function Values to IOCON_TRIGGER and IOCON_ECHO
	IOCON_TRIGGER &= ~(1 << 2); IOCON_TRIGGER |= (1 << 1); IOCON_TRIGGER |= (1 << 0);
	
	IOCON_ECHO &= ~(1 << 2); IOCON_ECHO |= (1 << 1); IOCON_ECHO |= (1 << 0);
}

void Ultrasonic_Trigger_Timer_Init() {
	//Enable Timer2.
	PCONP |= (1 << 22);
	
	//Change the mode of Timer2 to Timer Mode.
	TIMER2 -> CTCR &= ~(1 << 0);
	TIMER2 -> CTCR &= ~(1 << 1);
	
	//Disable Timer Counter and Prescale Counter for Timer2.
	TIMER2 -> TCR &= ~(1 << 0);
	
	//Reset Timer Counter and Prescale Counter for Timer2.
	TIMER2 -> TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER2 -> PR = 59;
	
	//Write the Correct Configuration for EMR (Toggle Output Value and Initial value is HIGH)
	TIMER2 -> EMR |= (1 << 3);
	TIMER2 -> EMR |= (1 << 10);
	TIMER2 -> EMR |= (1 << 11);
	
	//Enable TIMER2_IRQn (Interrupt Request).
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	//Set Priority Timer2 IRQ as 5.
	NVIC_SetPriority(TIMER2_IRQn, 5);
	
	//Clear pendings for Timer2.
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
}

void Ultrasonic_Start_Trigger_Timer() {
	//Give correct value to MR3 Register for 10 microsecond
	TIMER2 -> MR3 = 10;
	
	//Enable interrupt for MR3 register, if MR3 register matches the TC.
	TIMER2 -> MCR |= (1 << 9);
	
	//Remove the reset on counters of Timer2.
	TIMER2 -> TCR &= ~(1 << 1);
	
	//Enable Timer Counter and Prescale Counter for counting.
	TIMER2 -> TCR |= (1 << 0);
}

void ISR_ultrasonicTriggerToggler() {
	if(ultrasonicSensorTriggerStart == 0) {
		//Change MR3 Register Value for Suggested Waiting
		TIMER2->MR3 = 59990;
		ultrasonicSensorTriggerStart = 1;
	}
	else {
		TIMER2->MR3 = 10;
		ultrasonicSensorTriggerStart = 0;
	}
	
	//Write HIGH bit value to IR Register for Corresponding Interrupt
	TIMER2->IR |= (1 << 3);
	TIMER2->TC = 0;
}

