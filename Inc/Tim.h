#ifndef TIM_H
#define TIM_H

#include "stdint.h"
/*==================PWM================================*/
#define PWMAPB_ENR  (0x01U << 1)
#define CCMR1_ENR  (0x00U << 0)
#define CCMR1_COMP1 (0x06U << 4)
#define UGENR (0x01U << 0)
#define OC1PE (0x01U << 3)

/*========================ENCODER===========================*/
#define TIM2_SMS	(0x03U<<0)
#define PWMAPB_ENCODER_ENR  (0x01U << 0)
#define TIM2_CCMR_CC1S (0x01U << 0)
#define TIM2_CCMR_CC2S (0x01U << 8)


/*===========================COMMON TO BOTH PWM AND ENCODER========================*/
#define CR1_ENR  (0x01U << 0)
#define CC1E_ENR  (0x01U << 0)

#endif
