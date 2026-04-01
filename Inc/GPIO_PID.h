#ifndef GPIO_PID_H
#define GPIO_PID_H

#include<stdint.h>
#include "stm32f401xe.h"
//*=====================GPIO MODES====================*//
#define GPIOA_ENR	(0x01U<<0)
#define GPIOB_ENR   (0x01U<<1)
#define GPIOC_ENR   (0x01U<<2)
#define GPIOAF			0x02U
#define GPIODEF_OUT		0x01U
#define GPIODEF_IN		0x00U
/*=============functions================================*/

#define GPIO_A_PWM_SET    	  	12	//PIN6
#define GPIO_A_ENCODER_A_SET  	0 	//PIN0
#define GPIO_A_ENCODER_B_SET	2	//PIN1
#define GPIO_B_DIR_A_SET		0	//PIN0
#define GPIO_B_DIR_B_SET		2	//PIN1
#define	GPIO_C_INTERRUPT	    26	//PIN6


/*=============functions================================*/
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN6	6
#define PIN13	13

#endif
