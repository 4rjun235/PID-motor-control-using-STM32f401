## PID-motor-control-using-STM32f401
Closed loop DC Motor control using PID in STM32 (Encoder Feedback, CMSIS)


## Core idea:
measure motor speed using an encoder, compare it with a desired value, and adjust the PWM using a PID controller so the motor maintains that speed.

# What it does
* Uses TIM3 to generate PWM for motor control
* Uses TIM2 to read encoder signals
* Uses TIM4 interrupt to run the control loop
* Adjusts motor speed using a PID algorithm
* Supports forward and reverse direction
* Start/stop using a button interrupt


## How it works

* Encoder gives position -> difference gives speed
* Error = setpoint - speed
* PID processes the error
* Output is converted to PWM duty cycle
* Motor speed adjusts continuously

## Hardware

* STM32F401 (Nucleo board)
* DC motor
* Motor driver (L298N)
* Encoder


## Notes

* CMSIS and DSP files are included inside the project
* Include paths need to be set in STM32CubeIDE (see chip_header/README.md)




---

## License

MIT
