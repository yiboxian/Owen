#include "bsp_system.h"
void TFT_Debug(void)
{
    //		tft180_clear(RGB565_WHITE);							//清屏
    tft180_show_string(0, 16 * 0, "SDI_L:");      // 显示字符串
    tft180_show_float(60, 16 * 0, speed_L, 3, 2); // 显示一个16位无符号整数
    tft180_show_string(0, 16 * 1, "SDI_R:");      // 显示字符串
    tft180_show_float(60, 16 * 1, speed_R, 3, 2); // 显示一个16位无符号整数
    // 电磁传感器显示//
    tft180_show_string(0, 16 * 2, "expect_gyro:");  // 显示字符串
    tft180_show_float(60, 16 * 2, expect_gyro, 3, 2);     // 显示一个16位无符号整数
    tft180_show_string(0, 16 * 3, "out_L:");  // 显示字符串
    tft180_show_float(60, 16 * 3, out_L, 4, 0);     // 显示一个16位无符号整数
    tft180_show_string(0, 16 * 4, "out_R:");  // 显示字符串
    tft180_show_float(60, 16 * 4, out_R, 4, 0);     // 显示一个16位无符号整数
    tft180_show_string(0, 16 * 5, "Kp:");  // 显示字符串    
    tft180_show_float(60, 16 * 5, pid_motor_run.Kp, 3, 2);     // 显示一个16位无符号整数
    tft180_show_string(0, 16 * 6, "Kd:");  // 显示字符串
    tft180_show_float(60, 16 * 6, pid_motor_run.Kd, 3, 2);     // 显示一个16位无符号整数
    // tft180_show_string(0, 16 * 2, "L:");  // 显示字符串
    // tft180_show_float(60, 16 * 2, L, 3, 2);     // 显示一个16位无符号整数
    // tft180_show_string(0, 16 * 3, "LM:"); // 显示字符串
    // tft180_show_float(60, 16 * 3, LM, 3, 2);    // 显示一个16位无符号整数
    // tft180_show_string(0, 16 * 4, "RM:"); // 显示字符串
    // tft180_show_float(60, 16 * 4, RM, 3, 2);    // 显示一个16位无符号整数
    // tft180_show_string(0, 16 * 5, "R:");  // 显示字符串
    // tft180_show_float(60, 16 * 5, R, 3, 2);     // 显示电磁传感器各路数据
    // tft180_show_uint16(0, 16*1, 111);                	//显示一个16位无符号整数
    // tft180_show_int32(0, 16 * 2, 222, 3);      // 显示一个32位有符号数  并去除无效0
    // tft180_show_int32(0, 16 * 3, -333, 3);     // 显示一个32位有符号数  并去除无效0
    // tft180_show_float(0, 16 * 4, 56.35, 3, 1); // 显示一个浮点数        并去除整数部分无效0
    // 以上函数x坐标设置是以像素为单位   y坐标是以字符为单位

    // 以下为色彩测试，红绿蓝全屏各显示一秒。
    //		system_delay_ms(2000);								//延时1秒
    //		tft180_clear(RGB565_RED);
    //		system_delay_ms(1000);								//延时1秒
    //		tft180_clear(RGB565_GREEN);
    //		system_delay_ms(1000);								//延时1秒
    //		tft180_clear(RGB565_BLUE);
    //		system_delay_ms(1000);								//延时1秒
    // 此处编写需要循环执行的代码
}