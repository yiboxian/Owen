#include "bsp_system.h"

float err_position = 0;
// 转向系数//
float Small_t = 0.8;
float Large_t = 1;
float angle_L_t = 1.2;
// 转向系数//

//
float deviation = 0;
float A_Deviation = 1;
float B_Deviation = 1;
float C_Deviation = 1;
//
uint8 standby = 0;
void Electromagnetic_Logic()
{

    siai_adc_all_sample();
    adc_normalizing();
    deviation_calculation();
    err_position = L - R;
    //     // 动态权重系数k（基于中间传感器M的值）
    //    if(M>b){k=0.8;}// 强信号区域，重视中间传感器
    //    else if(M<a){k=0.2;}// 弱信号区域，重视两侧传感器
    //    else{k = c*M+d+0.2;}// 线性过渡区域，动态调整权重

    //    A_Electro = K_*(R-L);// 基础差分项
    //    B_Electro = (1-k)*B_*(RM - LM);// 根据k调整RM和LM的权重
    //    C_Electro = (1-k)*C_*LRM_fabs;//对称性调整
    //    all_Electro = (L+R) + D_*M + C_Electro;// 综合考虑总信号强度和差分调整
    //    if(all_Electro<250){all_Electro=250;} // 防止除数

    //    err_Electro = A_ * ( A_Electro + B_Electro ) / (all_Electro);// 最终误差计算
}
void Module_Init()
{
    // 此处编写模块初始化代码 例如外设初始化代码等
    seekfree_assistant_init(); // 初始化逐飞助手上位机
    // Wifi_Init();
    tft180_init(); // 初始化 TFT180 液晶显示屏
    Motor_Init();  // 初始化电机控制模块
    Key_Init();    // 初始化按键输入模块
    ENC_Init();    // 初始化编码器模块
    IMU_Init();    // 初始化陀螺仪模块
    my_ADC_Init();

    // 此处编写其他需要初始化的模块代码
}
/**
 * @brief 限幅保护函数
 */
double range_protect(double duty, double min, double max)
{
    return duty >= max ? max : (duty <= min ? min : duty);
}

/**
 * @brief 归一化函数，将输入值映射到 1 ~ 100 范围
 * @param value 输入初始电感值（此时为整型）
 * @return double 归一化后的值（1 ~ 100）
 */
double Adc_Normalize(int value, double min, double max)
{
    double normalized = 0;

    // 计算归一化值
    normalized = (double)(value - min) / (max - min) * 100.0f;
    // 限幅保护，确保返回值在 1 ~ 100 范围内
    normalized = range_protect(normalized, 1.0, 100.0);

    return normalized;
}
void deviation_calculation()
{
    deviation = (A_Deviation * (L - R) + B_Deviation * (RM - LM)) / (A_Deviation * (L + R) + C_Deviation * fabs(LM - RM)) * 100;
    // 此处编写偏差计算代码 例如循迹误差计算等
}
void Task_Run()
{

    // 此处编写需要循环执行的代码 例如任务调度等
    switch (standby)
    {
    case 0:
        standby = null_drift_calculate(); // 零漂解算
        break;
    case 1: // 循迹运行//
        speed_target = 10;
        // if (deviation < -25)
        // {
        //     standby = 2;
        // }
        // else
        {
            if (expect_gyro > 0)
            {

                // loop_speed_LR( (Small_t * expect_gyro)/2, (Large_t * expect_gyro)/2);
                loop_speed_LR(expect_gyro, -expect_gyro);
                // Motor_L(expect_gyro* Large_t);
                // Motor_R(expect_gyro*Small_t);
            }
            else
            {

                loop_speed_LR(-expect_gyro, expect_gyro);
                // loop_speed_LR((Large_t * -expect_gyro)/2, (Small_t * -expect_gyro)/2);

                // Motor_R(expect_gyro* Large_t);
            }
        }

        Motor_L(out_L);
        Motor_R(out_R);
        break;
    case 2: // 直角转弯//

        loop_speed_LR((Small_t * expect_gyro) / 2, (angle_L_t * expect_gyro));

        if (deviation > 20)
        {
            standby = 1;
        }
        Motor_L(out_L);
        Motor_R(out_R);
        break;
    // 此处编写其他需要循环执行的代码 例如任务调度等
    default:
        break;
    }

    // 此处编写其他需要循环执行的代码
}

// 跑出赛道保护//
void Run_Out_Protect()
{
    if (L + LM + RM + R < 20)
    {
        Motor_R(0);
        Motor_L(0);
    }
}
// 跑出赛道保护//