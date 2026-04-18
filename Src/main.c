#include "stm32f401xe.h"
#include <stdint.h>
#include "GPIO_PID.h"
#include "Tim.h"
#include "interrupt_tim4.h"
#include "EXTI_PID.h"
#include "PID_Init.h"


volatile uint8_t motorRunning = 1;
volatile int32_t speed_diff = 0;
volatile float setpoint = 300.0f;
volatile uint32_t debounce_ticks = 0;
PID_t pid;

void USART2_Init(void);

int main(void)
{
    SCB->CPACR |= (0xFU << 20);
    __DSB();
    __ISB();
    USART2_Init();
    gpioPID();
    PWM_TIM();
    ENCODER_TIM();
    PID_init();
    EXTI_INTRPT();
    EXTI_TIM4_init();


    while (1)
    { }

}

