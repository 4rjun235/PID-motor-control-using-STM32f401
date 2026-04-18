#ifndef TIM_H
#define TIM_H

#include <stdint.h>

void PWM_TIM(void);
void ENCODER_TIM(void);


#define TIM3_APB1_BIT       (0x01U << 1)
#define TIM3_PSC_VAL        (84U - 1U)
#define TIM3_ARR_VAL        (1000U - 1U)


#define TIM3_OC1M_PWM1      (0x06U << 4)
#define TIM3_OC1PE          (0x01U << 3)

#define TIM3_CC1E           (0x01U << 0)


#define TIM2_APB1_BIT       (0x01U << 0)
#define TIM2_SMS_ENC3       (0x03U << 0)
#define TIM2_CC1S_TI1       (0x01U << 0)
#define TIM2_CC2S_TI2       (0x01U << 8)
#define TIM2_IC1F_4SAMP     (0x04U << 4)   /* IC1 filter: 4 samples     */
#define TIM2_IC2F_4SAMP     (0x04U << 12)  /* IC2 filter: 4 samples     */


#define TIM_SR_UIF_BIT      (0x01U << 0)

#define PWM_MAX             99U
#define PWM_MIN             0U

#endif /* TIM_H */
