#include "PID_Init.h"

extern PID_t pid;


void PID_init(void)
{
    pid.Kp           = PID_KP_DEFAULT;
    pid.Ki           = PID_KI_DEFAULT;
    pid.Kd           = PID_KD_DEFAULT;
    pid.integral_max = PID_INTEGRAL_MAX;
    pid.integral     = 0.0f;
    pid.prev_error   = 0.0f;
}

/*
 * Clear integrator and derivative state only
 * */

void PID_reset(void)
{
    pid.integral   = 0.0f;
    pid.prev_error = 0.0f;
}

/*
 * Run one PID iteration
 *
 * Returns: raw control output (positive = forward, negative = reverse)
 * The caller scales this to CCR1 range and extracts direction.
 *
 * Anti-windup: clamp integral symmetrically at ±integral_max.
 * This prevents the integrator from charging up during saturation
 * and causing overshoot on recovery.
 * */
float PID_compute(float error)
{
    pid.integral += error;	    /* Integral with anti-windup clamp */
    if (pid.integral >  pid.integral_max) pid.integral =  pid.integral_max;
    if (pid.integral < -pid.integral_max) pid.integral = -pid.integral_max;
    float derivative   = error - pid.prev_error;
    pid.prev_error     = error;
    return (pid.Kp * error)
         + (pid.Ki * pid.integral)
         + (pid.Kd * derivative);
}
