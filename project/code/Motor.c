
#include "bsp_system.h"
//Motor para Control Area//
#define MAX_DUTY            ( 50 )                                               // 最大 MAX_DUTY% 占空比


#define nSleep1             ( IO_P11 )
#define DIR_1               ( IO_P83 ) 
#define PWM_1               ( PWMD_CH2_P51 )
  
#define nSleep2             ( IO_P04 )  
#define DIR_2               ( IO_P00 ) 
#define PWM_2               ( PWMB_CH3_P02 )


#define LED_1				( IO_P85 ) 
#define LED_2				( IO_P87 ) 


// #define DIR_3               ( IO_P75 )
// #define PWM_3               ( PWMB_CH1_P74 )

int16 duty = 0;
int8 dir = 1;

// #define DIR_4               ( IO_P77 )
// #define PWM_4               ( PWMB_CH3_P76 )

//Motor para Control Area//
void Motor_Init(void)
	{


	//gpio_init(LED_1, GPO, GPIO_HIGH, GPO_OPEN_DTAIN); 
	gpio_init(DIR_1, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高
    gpio_init(nSleep1, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高

    pwm_init(PWM_1, 17000, 0);                         // PWM 通道初始化频率 17KHz 占空比初始为 0

	//gpio_init(LED_2, GPO, GPIO_HIGH, GPO_OPEN_DTAIN); 
    gpio_init(DIR_2, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高
	gpio_init(nSleep2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    pwm_init(PWM_2, 17000, 0);                         // PWM 通道初始化频率 17KHz 占空比初始为 0

    // gpio_init(DIR_3, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高
    // pwm_init(PWM_3, 17000, 0);                         // PWM 通道初始化频率 17KHz 占空比初始为 0

	}
	
void Motor_R(int16 duty)
{	
	
	
    if(duty>9900)
    {
        duty=9900;
    }
    if(duty<-9900)
    {
        duty=-9900;
    }
    if(duty>0)
    {
        dir = 1;
        pwm_set_duty(PWM_1,duty);
    }
    else
    {
        dir = 0;
        pwm_set_duty(PWM_1,-duty);
    }
}
 void Motor_L(int16 duty)
 {
    if(duty>9900)
    {
        duty=9900;
    }
    if(duty<-9900)
    {
        duty=-9900;
    }
    if(duty>0)
    {
        dir = 1;
        pwm_set_duty(PWM_2,duty);
    }
    else
    {
        dir = 0;
        pwm_set_duty(PWM_2,-duty);
    }
 }