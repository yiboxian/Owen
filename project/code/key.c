#include "bsp_system.h"
#define KEY1_PIN        IO_P93
//#define KEY2_PIN        IO_PB3
//#define KEY3_PIN        IO_PB4
//#define KEY4_PIN        IO_P32

//#define SWITCH1_PIN     IO_PB0
//#define SWITCH2_PIN     IO_PB1
int8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

// 上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

// 开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 test1=0;

void Key_Init(void)
{
	gpio_init(KEY1_PIN,GPI,1,GPI_PULL_UP);
	
}
void Key_Case(void)
{
	key1_last_status = key1_status;
	key1_status = gpio_get_level(KEY1_PIN);
	if(key1_status && !key1_last_status)    
	{
		key1_flag = 1;
	}
	if(key1_flag)   
        {	
			
			
			//Motor_R(1000);
            key1_flag = 0;//使用按键之后，应该清除标志位
			test1++;
        }


}
