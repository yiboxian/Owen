/*********************************************************************************************************************
 * STC32G144K Opensourec Library 即（STC32G144K 开源库）是一个基于官方 SDK 接口的第三方开源库
 * Copyright (c) 2025 SEEKFREE 逐飞科技
 *
 * 本文件是STC32G144K开源库的一部分
 *
 * STC32G144K 开源库 是免费软件
 * 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
 * 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
 *
 * 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
 * 甚至没有隐含的适销性或适合特定用途的保证
 * 更多细节请参见 GPL
 *
 * 您应该在收到本开源库的同时收到一份 GPL 的副本
 * 如果没有，请参阅<https://www.gnu.org/licenses/>
 *
 * 额外注明：
 * 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
 * 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
 * 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
 * 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
 *
 * 文件名称
 * 公司名称          成都逐飞科技有限公司
 * 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
 * 开发环境          MDK FOR C251
 * 适用平台          STC32G144K
 * 店铺链接          https://seekfree.taobao.com/
 *
 * 修改记录
 * 日期              作者           备注
 * 2025-11-20        大W            first version
 ********************************************************************************************************************/
#include "bsp_system.h"
// #include "PD_ENC_SDI.h"
// #include "var.h"
// #include "Motor.h"
// #include "ADC.h"
void Pit_funciton(void);
void Pit_Steering_PD(void);
#define PIT_CH (TIM1_PIT)
#define LED1 IO_P52

// 陀螺仪型号为IMU963RA 因兼容性改为IMU660RB//

void main(void)
{

	clock_init(SYSTEM_CLOCK_96M); // 时钟配置及系统初始化<务必保留>
	debug_init();				  // 调试串口信息初始化
	Module_Init();
	// 设置DEBUG串口输出
	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
	gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	// 此处编写用户代码 例如外设初始化代码等
	pit_ms_init(TIM1_PIT, 5, Pit_Steering_PD);
	pit_ms_init(TIM2_PIT, 2, Pit_funciton);
	// pit_ms_init(TIM2_PIT, 5, gyroscope_get_gyro);

	// 此处编写用户代码 例如外设初始化代码等

	// 此处编写用户代码 例如d\n", duty);  // 输出编码器计数信息
		// printf("speed_R:%.2f,speed_L:%.2f,out_R:%.2f,out_L:%.2f\n", speed_R,speed_L, out_R,out_L); // 输出编码器计数信息
		//  printf("dec_speed_loop_R:%.2f\n",dec_speed_loop_R);8
		//  printf("err_speed_R:%d,err_speed_R_last:%d\n", err_speed_R,err_speed_R_last);
		// printf("Speed_loop_Kp:%.2f\n",pid_loop_speed.Kp);
		// printf("Speed_loop_Ki:%.2f\n",pid_loop_speed.Ki);
		// printf("test1:%d\n",test1);
		// printf("Raw_L:%.2f,Raw_LM:%.2f,Raw_RM:%.2f,Raw_R:%.2f\n", ADC_temp[0], ADC_temp[1], ADC_temp[2], ADC_temp[3]);
		//printf("Elec外设初始化代码等);

	while (1)
	{

		seekfree_assistant_data_analysis();

		TFT_Debug();

	
		printf("err_position:%.2f\n", err_position);
		printf("out_L:%.2f,out_R:%.2f\n", out_L,out_R);
		printf("expect_gyro:%.2f\n", expect_gyro);
		pid_motor_run.Kp = seekfree_assistant_parameter[2];
		pid_motor_run.Kd = seekfree_assistant_parameter[3];
		printf("place_Kp:%.2f, place_kd:%.2f\n", pid_motor_run.Kp, pid_motor_run.Kd);
		// 电磁初始化//

		// 电磁初始化//
		// printf("dec_speed_loop_R:%.2f, out_R:%.2f, Target_speed:%d\n",dec_speed_loop_R,out_R,target_R);
		// printf("gyro_z_data:%.2f\n", avl_gyro_z);
		gpio_toggle_level(LED1);
		// Motor_Control();
		system_delay_ms(100);
	}
	// 此处编写需要循环执行的代码
}
void Pit_funciton()
{
	encoder_update();
	Electromagnetic_Logic();
	// 0-获取数据
	// loop_speed_LR(20, 20);
	// loop_speed_LR(0, 0);
	Task_Run();

	// Motor_R(out_R);
	// Motor_L(out_L);
	Key_Case();
	Run_Out_Protect();
}
void Pit_Steering_PD(void)
{
	direction_return(err_position);

}