#ifndef PID_INIT_H
#define PID_INIT_H

#include <stdint.h>

/*  =================================PID structure===================================  */
typedef struct {
    float Kp;           /* Proportional gain                  */
    float Ki;           /* Integral gain                      */
    float Kd;           /* Derivative gain                    */
    float integral;     /* Accumulated integral term          */
    float prev_error;   /* Previous error             	      */
    float integral_max; /* Anti-windup clamp (positive limit) */
} PID_t;


extern PID_t pid;
void  PID_init(void);
float PID_compute(float error);
void  PID_reset(void);   /* Reset */

#define PID_KP_DEFAULT          2.0f
#define PID_KI_DEFAULT          0.4f
#define PID_KD_DEFAULT          0.0f
#define PID_INTEGRAL_MAX        600.0f

#endif /* PID_INIT_H */
