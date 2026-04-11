#ifndef __MOTOR_H_
#define __MOTOR_H_

extern int16 duty;


void Motor_Init(void);
void Motor_Control(void);
void Motor_R(int16 duty);
void Motor_L(int16 duty);
#endif