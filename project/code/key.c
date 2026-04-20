#include "bsp_system.h"
#define KEY1_PIN IO_P93
#define KEY2_PIN IO_P92
#define KEY3_PIN IO_P91
#define KEY4_PIN IO_P90

// #define SWITCH1_PIN     IO_PB0
// #define SWITCH2_PIN     IO_PB1
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

uint8 test1 = 0;

void Key_Init(void)
{
	gpio_init(KEY1_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY2_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY3_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY4_PIN, GPI, 1, GPI_PULL_UP);
}
void Key_Case(void)
{
	key1_last_status = key1_status;
	key1_status = gpio_get_level(KEY1_PIN);
	key2_last_status = key2_status;
	key2_status = gpio_get_level(KEY2_PIN);
	key3_last_status = key3_status;
	key3_status = gpio_get_level(KEY3_PIN);
	key4_last_status = key4_status;
	key4_status = gpio_get_level(KEY4_PIN);
	if (key1_status && !key1_last_status)
	{
		key1_flag = 1;
	}
	if (key1_flag)
	{
		key1_flag = 0; // 使用按键之后，应该清除标志位
	}
	if (key2_status && !key2_last_status)
	{
		key2_flag = 1;
	}
	if (key2_flag)
	{	
		target_L = 0;
		target_R = 0;
		// Handle key2 press event
		key2_flag = 0;
	}
	if (key3_status && !key3_last_status)
	{
		key3_flag = 1;
	}
	if (key3_flag)
	{
		// Handle key3 press event
		key3_flag = 0;
	}
	if (key4_status && !key4_last_status)
	{
		key4_flag = 1;
	}
	if (key4_flag)
	{
		// Handle key4 press event
		key4_flag = 0;
	}
}
