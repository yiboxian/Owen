#ifndef __LOGIC_H_
#define __LOGIC_H_
void Module_Init(void);
double Adc_Normalize(int value, double min, double max);
double range_protect(double duty, double min, double max);
void Task_Run(void);
#endif