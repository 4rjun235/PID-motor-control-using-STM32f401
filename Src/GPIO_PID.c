#include "GPIO_PID.h"
#include "stm32f401xe.h"

void gpioPID(void)
{
    /* ====================== Enable GPIO clocks ===================================*/
    RCC->AHB1ENR |= GPIOA_ENR | GPIOB_ENR | GPIOC_ENR;

    /*================== PA6: TIM3 CH1 — PWM output (AIN1)===========================*/
    GPIOA->MODER &= ~(0x03U << GPIO_A_PWM_SHIFT);
    GPIOA->MODER |=  (GPIO_MODE_AF << GPIO_A_PWM_SHIFT);
    GPIOA->OSPEEDR |= (0x03U << GPIO_A_PWM_SHIFT);
    GPIOA->AFR[0] &= ~(0x0FU << (PIN6 * 4));
    GPIOA->AFR[0] |=  (AF2_TIM3 << (PIN6 * 4));

    /* ================== PA0: TIM2 CH1 — Encoder A =============================== */
    GPIOA->MODER &= ~(0x03U << GPIO_A_ENCODER_A_SHIFT);
    GPIOA->MODER |=  (GPIO_MODE_AF << GPIO_A_ENCODER_A_SHIFT);
    GPIOA->AFR[0] &= ~(0x0FU << (PIN0 * 4));
    GPIOA->AFR[0] |=  (AF1_TIM2 << (PIN0 * 4));

    GPIOA->PUPDR &= ~(0x03U << (PIN0 * 2));
    GPIOA->PUPDR |=  (PUPDR_UP << (PIN0 * 2));

    /* ================== PA1: TIM2 CH2 — Encoder B =============================== */
    GPIOA->MODER &= ~(0x03U << GPIO_A_ENCODER_B_SHIFT);
    GPIOA->MODER |=  (GPIO_MODE_AF << GPIO_A_ENCODER_B_SHIFT);
    GPIOA->AFR[0] &= ~(0x0FU << (PIN1 * 4));
    GPIOA->AFR[0] |=  (AF1_TIM2 << (PIN1 * 4));
    GPIOA->PUPDR &= ~(0x03U << (PIN1 * 2));
    GPIOA->PUPDR |=  (PUPDR_UP << (PIN1 * 2));

    /*====================== PB0: GPIO output — AIN2 (direction) ================== */
    GPIOB->MODER &= ~(0x03U << GPIO_B_AIN2_SHIFT);
    GPIOB->MODER |=  (GPIO_MODE_OUT << GPIO_B_AIN2_SHIFT);
    GPIOB->OTYPER &= ~(0x01U << 0);                        /* Push-pull  */
    GPIOB->OSPEEDR |= (0x03U << GPIO_B_AIN2_SHIFT);        /* High speed */
    GPIOB->ODR &= ~(0x01U << 0);                           /* Start LOW  */

    /*===================== PC13: GPIO input — button ============================= */
    GPIOC->MODER &= ~(0x03U << GPIO_C_BTN_SHIFT);

}
