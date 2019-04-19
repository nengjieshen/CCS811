
#include "Global.h"
u16 Sensor_Value;


void TIM3_IRQHandler(void) 											//TIME3中断服务函数  需要设定中断优先级  即NVIC配置
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)					//判断是否发生了更新(溢出)中断
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);					//清除溢出中断标志位
    }

    OLED_ShowString(0,0,"light: ",16);
    OLED_ShowNum(50,0,Sensor_Value,4,16);
    OLED_ShowString(90,0," Lux",16);
}



int main(void)
{
	SystemInit();
	delay_init();
	NVIC_Configuration();
	//OutputIOInit();
	//InputIOInit();
	OLED_Init();
	OLED_Clear();
	ADCIOInit();
	ADCInit();
	time3_init(7199,9999);
	NVIC_INIT();

	while(1)
	{
		Sensor_Value = GetADCValue();
	}
}
