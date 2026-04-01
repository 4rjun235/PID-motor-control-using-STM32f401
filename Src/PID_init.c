#include "arm_math.h"
#include "PID_Init.h"

PID_t pid;

void PID_init(void){
    pid.Kp = 1.0f;
    pid.Ki = 0.0f;
    pid.Kd = 0.0f;
    pid.integral = 0.0f;
    pid.prev_error = 0.0f;
}

float PID_compute(float error){
    pid.integral += error;
    float derivative = error - pid.prev_error;
    pid.prev_error = error;
    return (pid.Kp * error) + (pid.Ki * pid.integral) + (pid.Kd * derivative);
}
