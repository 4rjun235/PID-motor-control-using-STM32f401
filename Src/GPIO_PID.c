#include "GPIO_PID.h"
#include <stdint.h>
#include "stm32f401xe.h"

void gpioPID(void){

	RCC -> AHB1ENR |= GPIOA_ENR;
	RCC -> AHB1ENR |= GPIOB_ENR;
	RCC -> AHB1ENR |= GPIOC_ENR;

	GPIOA -> MODER &= ~(0x03U << GPIO_A_PWM_SET);
	GPIOA -> MODER |= (GPIOAF << GPIO_A_PWM_SET);
	GPIOA -> AFR[0] &= ~(0x0F << (PIN6 * 4));
	GPIOA -> AFR[0] |= (0x02 << (PIN6 * 4));

	GPIOA -> MODER &= ~(0x03U << GPIO_A_ENCODER_A_SET);
	GPIOA -> MODER |= (GPIOAF << GPIO_A_ENCODER_A_SET);
	GPIOA -> AFR[0] &= ~(0x0F << (PIN0 * 4));
	GPIOA -> AFR[0] |= (0x01U << (PIN0 * 4));

	GPIOA -> MODER &= ~(0x03U << GPIO_A_ENCODER_B_SET);
	GPIOA -> MODER |= (GPIOAF << GPIO_A_ENCODER_B_SET);
	GPIOA -> AFR[0] &= ~(0x0F << (PIN1 * 4));
	GPIOA -> AFR[0] |= (0x01U << (PIN1 * 4));

	GPIOB -> MODER &= ~(0x03U << GPIO_B_DIR_A_SET);
	GPIOB -> MODER |= (GPIODEF_OUT << GPIO_B_DIR_A_SET);

	GPIOB -> MODER &= ~(0x03U << GPIO_B_DIR_B_SET);
	GPIOB -> MODER |= (GPIODEF_OUT << GPIO_B_DIR_B_SET);

	GPIOC -> MODER &= ~(0x03U << GPIO_C_INTERRUPT);
	GPIOC -> MODER |= (GPIODEF_IN << GPIO_C_INTERRUPT);

	GPIOA->PUPDR &= ~(0x03U << (PIN0 * 2));
	GPIOA->PUPDR |=  (0x01U << (PIN0 * 2));

	GPIOA->PUPDR &= ~(0x03U << (PIN1 * 2));
	GPIOA->PUPDR |=  (0x01U << (PIN1 * 2));

}


