#include "Tim.h"
#include "GPIO_PID.h"
#include "stm32f401xe.h"
void PWM_TIM(void){

	RCC ->APB1ENR |= PWMAPB_ENR;

	TIM3 ->PSC = 84-1;
	TIM3 ->ARR = 100-1;

	TIM3 ->CCMR1 &= ~(0xFF << 0);
	TIM3->CCMR1 |= CCMR1_ENR;

	TIM3->CCMR1 &= ~(0x07 << 4);
	TIM3 ->CCMR1 |= CCMR1_COMP1;
	TIM3->CCMR1 |= OC1PE;

	TIM3 ->CCR1 = 0;

	TIM3 ->CCER |= CC1E_ENR;
	TIM3 ->CNT =0;
	TIM3->EGR |= UGENR;
	TIM3 ->CR1 |= CR1_ENR ;

}

void ENCODER_TIM(void){

	RCC ->APB1ENR |= PWMAPB_ENCODER_ENR;
	TIM2 ->PSC = 0;
	TIM2 ->ARR = 0XFFFFFFFF;

	TIM2->SMCR &= ~(0x07U << 0);
	TIM2 ->SMCR |= TIM2_SMS;

    TIM2->CCMR1 &= ~(0xFFFF);
	TIM2->CCMR1 |= (0x03 << 4);  // IC1F
	TIM2->CCMR1 |= (0x03 << 12); // IC2F

    TIM2->CCMR1 |=  TIM2_CCMR_CC1S;         // CC1S = TI1 input
    TIM2->CCMR1 |=  TIM2_CCMR_CC2S;         // CC2S = TI2 input

    TIM2 ->CNT =0;
	TIM2 ->CR1 |= CR1_ENR;
}
