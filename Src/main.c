#include "arm_math.h"
#include "stm32f401xe.h"
#include <stdint.h>

#include "GPIO_PID.h"
#include "Tim.h"
#include "interrupt_tim4.h"
#include "EXTI_PID.h"


volatile uint8_t motorRunning = 0;

int main(void){

    gpioPID();
    PWM_TIM();
    ENCODER_TIM();
    EXIT_TIM4_init();
    EXTI_INTRPT();
    PID_init();

    while(1){
    }
}
