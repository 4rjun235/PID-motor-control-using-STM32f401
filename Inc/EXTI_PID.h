#ifndef EXTI_PID_H
#define EXTI_PID_H

#include <stdint.h>

void EXTI_INTRPT(void);

#define SYSCFG_APB2_BIT     (0x01U << 14)
#define EXTI13_PORTC        (0x02U << 4)
#define EXTI13_MASK         (0x0FU << 4)
#define EXTI_LINE13         (0x01U << 13)
#define BTN_DEBOUNCE_TICKS  3U

extern volatile uint32_t debounce_ticks;

#endif /* EXTI_PID_H */
