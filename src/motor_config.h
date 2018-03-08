#ifndef MOTOR_CONFIG_H
#define MOTOR_CONFIG_H

#define NUMBER_OF_MOTORS 2

#define Motor1_StepPin D1
#define Motor1_DirPin  D0

#define Motor2_StepPin D3
#define Motor2_DirPin  D2

//#define Motor3_StepPin D5
//#define Motor3_DirPin  D4

//#define Motor4_StepPin D7
//#define Motor4_DirPin  D6

#define threadResolution 1 //thread delay in ms, this is the minimum time between signal pulses for a stepper motor
#endif
