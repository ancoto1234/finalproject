#include "MKL46Z4.h"

void InitRedLED(void) {
	// Configure Red Led - PORTE29
	// Enable Clock for PTE
	SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;
	// Connect GPIO to PTE29
	PORTE -> PCR[29] = PORT_PCR_MUX(1);
	// Configure PTE29 output
	PTE -> PDDR |= (1 << 29);
	PTE -> PSOR = (1 << 29);
}

void InitGreenLED(void) {
	// Configure Greed Led - PORTD5
	// Enable Clock for PTD
	SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK;
	// Connect GPIO to PTD5
	PORTD -> PCR[5] = PORT_PCR_MUX(1);
	// Configure PTD5 output
	PTD	-> PDDR |= (1 << 5);
	PTD -> PSOR = (1 << 5);
}

void InitSwitch(void) {
	SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	//Sw1
	PTC -> PDDR &= ~((uint32_t)(1 << 3));
	PORTC -> PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	//Sw3
	PTC -> PDDR &= ~((uint32_t)(1 << 12));
	PORTC -> PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	
	
	// Enable interrupt on falling edge of PTC3
	PORTC -> PCR[3] &= ~0x0F0000; // clear D19 -> D16
	PORTC -> PCR[3] |= 0x0A0000; // Set D19 -> D16 = "1010" = 0xA
	
	PORTC -> PCR[12] &= ~0x0F0000; // clear D19 -> D16
	PORTC -> PCR[12] |= 0x0A0000; // Set D19 -> D16 = "1010" = 0xA
	// Clear pending interrupt on PTC_PTD
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	// Enable PTC_PTD interruptin NVIC
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);

	

}

void InitSysTick(void) {
	// configure Systick_Timer
	SysTick -> LOAD = (SystemCoreClock / 1000) - 1; //timer counts to 0 in 1ms
	// SysTick -> CTRL = 5; // Enable SysTick, Clock source = Processor clock, disable interrupt
	SysTick -> CTRL = 7; // Enable SysTick, Clock source = Processor clock, enable interrupt
}



	


