#include "zf_common_headfile.h"

//ADC para Control Area//

#define CHANNEL_NUMBER          (3)
#define ADC_CHANNEL1            ( ADC2_CH5_P05 )
#define ADC_CHANNEL2            ( ADC2_CH6_P06 )
#define ADC_CHANNEL3            ( ADC2_CH7_P07 )

//ADC para Control Area//
uint8 channel_index = 0;
adc_channel_enum channel_list[CHANNEL_NUMBER] =
{
    ADC_CHANNEL1, 
    ADC_CHANNEL2, 
    ADC_CHANNEL3, 
};
void ADC_Init(void)
{
    adc_init(ADC_CHANNEL1, ADC_12BIT);          // 初始化对应 ADC 通道为对应精度
    adc_init(ADC_CHANNEL2, ADC_12BIT);          // 初始化对应 ADC 通道为对应精度
    adc_init(ADC_CHANNEL3, ADC_12BIT);          // 初始化对应 ADC 通道为对应精度
}