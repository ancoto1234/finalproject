#include "project.h"
#include "MKL46Z4.h"

int led_check = 0;
int32_t volatile msTime = 0;
uint32_t const timeToDelay = 3000; // 3s

void SysTick_Handler(void) {
	if (led_check == 1) {
		msTime++;
		if (msTime >= timeToDelay) {
			PTE -> PTOR = (1 << 29);
			msTime = timeToDelay - 1000;
		}
	} else {
		msTime = 0;
	}
	
}

void PORTC_PORTD_IRQHandler(void) {
	
	int hasPerson = ((PTC -> PDIR & (1 << 3)) == 0);
	int seatbelt = ((PTC -> PDIR & (1 << 12)) == 0);
	
	
	
	if (!hasPerson) {
		// chua co nguoi
		led_check = 0;
		PTE -> PSOR = (1 << 29);
		PTD -> PSOR = (1 << 5);
		PORTC -> ISFR = (1 << 3 ) | (1 << 12);
	} else if (hasPerson && !seatbelt) {
		// co nguoi nhung chua that day
		led_check = 1;
		// Delay(1000);
		// PTE -> PTOR = (1 << 29);
		PTD -> PSOR = (1 << 5);
	} else if (hasPerson && seatbelt) {
		// co nguoi va da that day
		led_check = 0;
		PTD -> PCOR = (1 << 5);
		PTE -> PSOR = (1 << 29);
	}
	
}

int main(void) {
	InitGreenLED();
	InitRedLED();
	InitSwitch();
	InitSysTick();
	
	while (1) {
		
	}
	
}