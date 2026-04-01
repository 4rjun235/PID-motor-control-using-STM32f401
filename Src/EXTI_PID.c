#include "stm32f401xe.h"
#include "EXTI_PID.h"
extern volatile uint8_t motorRunning;

void EXTI_INTRPT(void){

	RCC->APB2ENR |= SYSCFG_ENR;

	SYSCFG ->EXTICR[3] &= ~(0xF << 4);
	SYSCFG ->EXTICR[3] |= PCINT;

    EXTI->IMR  |= PC13CONFG;
    EXTI->FTSR |= PC13CONFG;

	NVIC_SetPriority(EXTI15_10_IRQn, 2);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void){
    if(EXTI->PR & (1 << 13)){
    	motorRunning ^= 1;
        EXTI->PR |= (1 << 13);  
    }
}
