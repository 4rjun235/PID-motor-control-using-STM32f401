#ifndef PID_INIT_H_
#define PID_INIT_H_

typedef struct {
    float Kp, Ki, Kd;
    float integral;
    float prev_error;
} PID_t;

extern PID_t pid;
void PID_init(void);
float PID_compute(float error);

#endif /* PID_INIT_H_ */
