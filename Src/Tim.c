#include "Tim.h"
#include "stm32f401xe.h"


void PWM_TIM(void)
{

    RCC->APB1ENR |= TIM3_APB1_BIT;
    (void)RCC->APB1ENR;


    TIM3->PSC = TIM3_PSC_VAL;
    TIM3->ARR = TIM3_ARR_VAL;
    TIM3->CCMR1 &= ~(0xFFU << 0);
    TIM3->CCMR1 |=  TIM3_OC1M_PWM1;
    TIM3->CCMR1 |=  TIM3_OC1PE;


    TIM3->CCR1 = 0;     /*  Starting with 0% duty */

    TIM3->CCER &= ~(0x0FU << 0);
    TIM3->CCER |=  TIM3_CC1E;

    TIM3->CR1 |= (0x01U << 7);
    TIM3->CNT  = 0;
    TIM3->EGR |= TIM_EGR_UG;

    TIM3->CR1 |= TIM_CR1_CEN;
}


void ENCODER_TIM(void)
{

    RCC->APB1ENR |= TIM2_APB1_BIT;

    TIM2->PSC = 0;
    TIM2->ARR = 0xFFFFFFFFU;

    TIM2->SMCR &= ~(0x07U << 0);
    TIM2->SMCR |=  TIM2_SMS_ENC3;

    TIM2->CCMR1 = 0;
    TIM2->CCMR1 |= TIM2_CC1S_TI1;
    TIM2->CCMR1 |= TIM2_CC2S_TI2;

    TIM2->CCMR1 |= TIM2_IC1F_4SAMP;   /* 4-sample digital filter CH1    */
    TIM2->CCMR1 |= TIM2_IC2F_4SAMP;   /* 4-sample digital filter CH2    */
    TIM2->CCER &= ~(0x55U);
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;

}
