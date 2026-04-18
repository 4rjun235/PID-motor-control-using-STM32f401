#include "EXTI_PID.h"
#include "stm32f401xe.h"
#include <stdint.h>

extern volatile uint8_t motorRunning;


void EXTI_INTRPT(void)
{
    RCC->APB2ENR |= SYSCFG_APB2_BIT;
    (void)RCC->APB2ENR;

    SYSCFG->EXTICR[3] &= ~EXTI13_MASK;
    SYSCFG->EXTICR[3] |=  EXTI13_PORTC;

    EXTI->IMR  |= EXTI_LINE13;
    EXTI->FTSR |= EXTI_LINE13;
    EXTI->RTSR &= ~EXTI_LINE13;
    EXTI->PR    = EXTI_LINE13;

    NVIC_SetPriority(EXTI15_10_IRQn, 2);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void)
{
    if (!(EXTI->PR & EXTI_LINE13))
        return;

    EXTI->PR = EXTI_LINE13;

    if (debounce_ticks == 0)
    {
        motorRunning   ^= 1U;
        debounce_ticks  = BTN_DEBOUNCE_TICKS;
    }

}
