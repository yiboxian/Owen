#ifndef __PID_H_
#define __PID_H_

extern struct PID
{
	float Kp;
	float Ki;
	float Kd;
	float Kp_gyro;
	float Ki_gyro;
	float Kd_gyro;
};


extern int16 err_speed;				//Îó²î
extern float out_L,out_R;			//Êä³ö



#endif