#include "bsp_system.h"

// ADC para Control Area//

#define CHANNEL_NUMBER (4)
#define ADC_CHANNEL1 (ADC2_CH3_P03)
#define ADC_CHANNEL2 (ADC2_CH6_P06)
#define ADC_CHANNEL3 (ADC2_CH7_P07)
#define ADC_CHANNEL4 (ADC2_CH5_P05)

float adc_data_buffer[CHANNEL_NUMBER][ADC_Sample_Num];
float filtered_results[CHANNEL_NUMBER];
float L = 0, LM = 0, RM = 0, R = 0;
float ADC_temp[4]={0};
// ADC para Control Area//
uint8 channel_index = 0;
adc_channel_enum channel_list[CHANNEL_NUMBER] =
	{
		ADC_CHANNEL1,
		ADC_CHANNEL2,
		ADC_CHANNEL3,
		ADC_CHANNEL4};
void my_ADC_Init(void)
{
	adc_init(ADC_CHANNEL1, ADC_10BIT); // 初始化对应 ADC 通道为对应精度
	adc_init(ADC_CHANNEL2, ADC_10BIT); // 初始化对应 ADC 通道为对应精度
	adc_init(ADC_CHANNEL3, ADC_10BIT); // 初始化对应 ADC 通道为对应精度
	adc_init(ADC_CHANNEL4, ADC_10BIT); // 初始化对应 ADC 通道为对应精度
}
void Update_All_Inductors(float* final_values)
{	
	int i = 0;
		int ch = 0;
    // 遍历 4 个通道
    for (ch = 0; ch < CHANNEL_NUMBER; ch++)
    {
        // 每个通道连续采集 ADC_Sample_Num 次数据
        for (i = 0; i < ADC_Sample_Num; i++)
        {
            // 这里的 adc_convert 需要传入你实际的通道枚举或 ID
            adc_data_buffer[ch][i] = (float)adc_convert(ch); 
        }

        // 调用滤波函数，将结果存入输出数组
        final_values[ch] = Median_Average_Filter(adc_data_buffer[ch], ADC_Sample_Num);
    }
}
/************电磁采样************/
// 以下代码均为ADC采样滤波算法//
uint16 adc_sample(adc_channel_enum ch)
{
	uint16 temp, sum = 0;
	uint16 max, min;
	uint8 i;

	temp = adc_convert(ch);
	max = temp;
	min = temp;
	sum += temp;

	for (i = 0; i < 10; i++)
	{
		temp = adc_convert(ch);
		if (max < temp)
		{
			max = temp;
		}
		if (min > temp)
		{
			min = temp;
		}
		sum += temp;
	}

	temp = (sum - max - min) / (11 - 2);

	return temp;
}

uint16 adc_sample_b(adc_channel_enum ch)
{
	uint16 temp, sum = 0;
	uint16 max, min;
	uint8 i;

	temp = adc_mid_sample(ch);
	max = temp;
	min = temp;
	sum += temp;

	for (i = 1; i <= 7; i++)
	{
		temp = adc_mid_sample(ch);
		if (max < temp)
		{
			max = temp;
		}
		if (min > temp)
		{
			min = temp;
		}
		sum += temp;
	}

	temp = (sum - max - min) / (8 - 2);

	return temp;
}

uint16 adc_sample_a(adc_channel_enum ch)
{
	uint8 i;
	uint16 arr[7];

	for (i = 0; i < ADC_Sample_Num; i++)
	{
		arr[i] = adc_convert(ch);
	}

	arr[0] = sort_seven(arr);
	return arr[0];
}
/**
* @brief 中位值平均滤波函数
* @param arr 输入数据数组
* @param times 数据采样次数
* @return int 滤波后的平均值
*/
/**
* @brief 中位值平均滤波函数
* @param arr 输入数据数组
* @param times 数据采样次数
* @return int 滤波后的平均值
*/
int Median_Average_Filter(float* arr, int times)
{
		int min = arr[0], max = arr[0], sum = 0;
		int i = 0;
		
		// 遍历数组，找出最大值、最小值并求和
		for (i = 0; i < times; i++)
		{
				if (arr[i] < min) min = arr[i];
				if (arr[i] > max) max = arr[i];
				sum += arr[i];
		}
		
		// 计算去掉最大值和最小值后的平均值
		return (sum - min - max) / (times - 2);
}


uint16 adc_mid_sample(adc_channel_enum ch) // 三次中值滤波函数
{
	uint16 i, j, k, tmp;
	// sample 3 times
	i = adc_convert(ch);
	j = adc_convert(ch);
	k = adc_convert(ch);
	//  select mid value
	if (i > j)
	{
		tmp = i;
		i = j;
		j = tmp;
	}
	if (k > j)
	{
		tmp = j;
	}
	else if (k > i)
	{
		tmp = k;
	}
	else
	{
		tmp = i;
	}
	return tmp;
}

// void siai_adc_all_sample(void)
// {
// 	ADC_temp[0] = adc_sample(ADC_CHANNEL1);
// 	ADC_temp[1] = adc_sample(ADC_CHANNEL2);
// 	ADC_temp[2] = adc_sample(ADC_CHANNEL3);
// 	ADC_temp[3] = adc_sample(ADC_CHANNEL4);
// }

// 归一化
void adc_normalizing(void)
{	
	Update_All_Inductors(filtered_results);
	// 归一化
	//	L  = 100*(ADC_temp[0]-0)/(600-0);
	//  LM = 100*(ADC_temp[1]-0)/(600-0);
	//	M  = 100*(ADC_temp[2]-0)/(600-0);
	//  RM = 100*(ADC_temp[3]-0)/(600-0);
	//	R  = 100*(ADC_temp[4]-0)/(600-0);
	
	L = Adc_Normalize(filtered_results[0], 46, 470);
	LM = Adc_Normalize(filtered_results[1], 46, 270);

	RM = Adc_Normalize(filtered_results[2], 46, 270);
	R = Adc_Normalize(filtered_results[3], 150, 994);

// 	// 输入限幅
// 	if (L > 100)
// 	{
// 		L = 100;
// 	}
// 	if (LM > 100)
// 	{
// 		LM = 100;
// 	}
// 	// if (M > 100)
// 	// {
// 	// M = 100;
// 	// }
// 	if (RM > 100)
// 	{
// 		RM = 100;
// 	}
// 	if (R > 100)
// 	{
// 		R = 100;
// 	}
 }
// 电压采集//
// 以下电压采集权重需要根据实际情况进行评估//
float adc_v_sample(float v_next)
{
	static float v, last_v = 0;
	v = v_next;
	v = v * 0.014648 * 4;

	v = 0.1 * v + 0.90 * last_v;
	last_v = v;

	return v;
}

float adc_v_sample_2(float v_next)
{
	static float v, last_v = 0;
	v = v_next;
	v = v * 0.038671;

	v = 0.5 * v + 0.5 * last_v;
	last_v = v;

	return v;
}

float adc_v_sample_3(float v_next)
{
	static float v, last_v = 0;
	v = v_next;
	v = v * 0.038671;

	v = 0.1 * v + 0.9 * last_v;
	last_v = v;

	return v;
}

float adc_v_sample_4(float v_next)
{
	static float v, last_v = 0;

	v = v_next;

	v = v * 0.038671;

	v = 0.05 * v + 0.95 * last_v;
	last_v = v;

	return v;
}
void debug_adc(void)
{
	for (channel_index = 0; channel_index < CHANNEL_NUMBER; channel_index++)
	{
		printf(
			"ADC channel %d convert data is %d.\r\n",
			channel_index + 1,
			adc_convert(channel_list[channel_index])); // 循环输出单次转换结果
	}
	system_delay_ms(500);

	for (channel_index = 0; channel_index < CHANNEL_NUMBER; channel_index++)
	{
		printf(
			"ADC channel %d mean filter convert data is %d.\r\n",
			channel_index + 1,
			adc_mean_filter_convert(channel_list[channel_index], 10)); // 循环输出 10 次均值滤波转换结果
	}
	system_delay_ms(500);
}