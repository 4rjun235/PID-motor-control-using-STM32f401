#ifndef GPIO_PID_H
#define GPIO_PID_H

#include <stdint.h>
#include "stm32f401xe.h"

void gpioPID(void);

/* ================== RCC AHB1 clock enables ============================ */
#define GPIOA_ENR       (0x01U << 0)
#define GPIOB_ENR       (0x01U << 1)
#define GPIOC_ENR       (0x01U << 2)

/* ================== GPIO MODER  =========================== */
#define GPIO_MODE_IN    0x00U
#define GPIO_MODE_OUT   0x01U
#define GPIO_MODE_AF    0x02U
#define GPIO_MODE_AN    0x03U

#define GPIO_A_PWM_SHIFT        12   /* PA6  : TIM3 CH1 PWM (AIN1) */
#define GPIO_A_ENCODER_A_SHIFT   0   /* PA0  : TIM2 CH1 Encoder A      */
#define GPIO_A_ENCODER_B_SHIFT   2   /* PA1  : TIM2 CH2 Encoder B      */
#define GPIO_B_AIN2_SHIFT        0   /* PB0  : direction output     */
#define GPIO_C_BTN_SHIFT        26   /* PC13 : button input         */

/*=========================== Pin numbers ======================= */
#define PIN0    0
#define PIN1    1
#define PIN6    6
#define PIN13   13

/* ================ Alternate function numbers ========================*/
#define AF1_TIM2    0x01U   /* PA0/PA1 : TIM2 */
#define AF2_TIM3    0x02U   /* PA6     : TIM3 */

/* ====================== Pull resistor values  ================================ */
#define PUPDR_NONE  0x00U
#define PUPDR_UP    0x01U
#define PUPDR_DOWN  0x02U

#endif /* GPIO_PID_H */
