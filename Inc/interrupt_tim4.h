#ifndef INTERRUPT_TIM4_H
#define INTERRUPT_TIM4_H
#include <stdint.h>
void EXTI_TIM4_init(void);



#define TIM4_PSC_VAL        (8400U - 1U)	/*Prescalar*/
#define TIM4_ARR_VAL        (1000U - 1U)	/*Auto reload register*/

extern volatile int32_t speed_diff;
extern volatile float   setpoint;

#endif /* INTERRUPT_TIM4_H */
