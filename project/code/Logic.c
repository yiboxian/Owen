#include "bsp_system.h"


//void Electromagnetic_Logic()
//{   

//    siai_adc_all_sample();
//    adc_normalizing();

//    LRM_fabs = |RM-LM|;
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

//}
