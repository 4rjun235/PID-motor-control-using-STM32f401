#include "interrupt_tim4.h"
#include "stm32f401xe.h"
#include <stdint.h>
#include "arm_math.h"
#include "PID_Init.h"
extern volatile uint8_t motorRunning;


void EXIT_TIM4_init(void){

	RCC ->APB1ENR |= APB_ENR;

	TIM4 ->PSC = 84-1;
	TIM4 ->ARR = 10000-1;

	TIM4 -> DIER |= EXIT_UIE;

	TIM4 ->CNT =0;
	TIM4 ->CR1 |= CR1_ENR ;

	NVIC_SetPriority(TIM4_IRQn, 1);   // priority 1
	NVIC_EnableIRQ(TIM4_IRQn);        // enable
}

volatile int32_t prev_val = 0;
volatile float32_t setpoint = 50;

void TIM4_IRQHandler(void){
    if(TIM4->SR & TIM_SR_UIF){
        TIM4->SR &= ~TIM_SR_UIF;  // CLEAR UIF

        if(motorRunning){
        int32_t current = TIM2 ->CNT;
        int32_t speed_diff = current - prev_val;
        prev_val  = current;

        float32_t speed = (float32_t)speed_diff;
        float32_t error = setpoint - speed;
        float32_t output = PID_compute(error);

        if(output >= 0){
            GPIOB->ODR |=  (1U << 0);    // PB0 HIGH forward
            GPIOB->ODR &= ~(1U << 1);    // PB1 LOW
        } else {
            GPIOB->ODR &= ~(1U << 0);    // PB0 LOW backward
            GPIOB->ODR |=  (1U << 1);    // PB1 HIGH
            output = -output;             // make positive for CCR1
        }
        // Clamp output
        if(output > 99.0f) output = 99.0f;
        TIM3->CCR1 = (uint32_t)output;
        }

        else {
        TIM3->CCR1 = 0;       // motor off
        }
    }
}
