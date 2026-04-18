#include "interrupt_tim4.h"
#include "Tim.h"
#include "PID_Init.h"
#include "EXTI_PID.h"
#include "stm32f401xe.h"
#include <stdint.h>
#include <stdio.h>

extern volatile uint8_t motorRunning;
extern volatile int32_t speed_diff;
extern volatile float setpoint;
extern volatile uint32_t debounce_ticks;
void USART2_Init(void);
static int32_t prev_cnt = 0;

int __io_putchar(int ch)
{
	while (!(USART2->SR & USART_SR_TXE));
	USART2->DR = (ch & 0xFF);
	return ch;
}


void EXTI_TIM4_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	(void)RCC->APB1ENR;

	TIM4->PSC  = TIM4_PSC_VAL;
	TIM4->ARR  = TIM4_ARR_VAL;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->CNT  = 0;
	TIM4->EGR  |= TIM_EGR_UG;
	TIM4->SR   &= ~TIM_SR_UIF_BIT;
	TIM4->CR1  |= TIM_CR1_CEN;

	NVIC_SetPriority(TIM4_IRQn, 3);
	NVIC_EnableIRQ(TIM4_IRQn);

}


void TIM4_IRQHandler(void)
{
	if (!(TIM4->SR & TIM_SR_UIF_BIT))
		return;

	TIM4->SR &= ~TIM_SR_UIF_BIT;

	if (debounce_ticks > 0)
		debounce_ticks--;

	if (!motorRunning)
	{
		PID_reset();
		TIM3->CCR1 = 0;
		GPIOB->ODR &= ~(1U << 0);
		prev_cnt = (int32_t)TIM2->CNT;
		return;
	}

	int32_t curr_cnt = (int32_t)TIM2->CNT;
	int32_t counts = curr_cnt - prev_cnt;
	prev_cnt = curr_cnt;

	float rpm = (counts / 44.0f) * 12.0f;
	float error = setpoint - rpm;
	float ff = 1.65f * setpoint;

	float pid = PID_compute(error);
	if (pid > 150.0f)  pid = 150.0f;
	if (pid < -150.0f) pid = -150.0f;

	float output = ff + pid;


	GPIOB->ODR &= ~(1U << 0);

	if (output > 1000.0f) output = 1000.0f;
	if (output < 0.0f)    output = 0.0f;

	if (setpoint > 0 && output < 120.0f)
		output = 120.0f;

	TIM3->CCR1 = (uint32_t)output;

	static uint16_t log_counter = 0;
	if (++log_counter >= 10)
	{
		log_counter = 0;
		printf("RPM: %.2f, SP: %.2f, OUT: %.2f\r\n", rpm, setpoint, output);
	}
	}

void USART2_Init(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER &= ~(3U << 4);
	GPIOA->MODER |=  (2U << 4);

	GPIOA->AFR[0] &= ~(0xF << 8);
	GPIOA->AFR[0] |=  (7U << 8);

	GPIOA->OSPEEDR |= (3U << 4);
	GPIOA->OTYPER  &= ~(1U << 2);

	USART2->BRR = 0x008B;
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_UE;

}

