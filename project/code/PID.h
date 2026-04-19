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
void loop_speed_LR(int16 speed_L_t,int16 speed_R_t);

extern float place_errorplace;
extern float place_last_errorplace;
extern float place_outplace;
extern float place_last_outplace;
extern float place_kpplace;
extern float place_kdplace;
extern float place_out;
extern uint16 target_R;
extern uint16 target_L;

#endif