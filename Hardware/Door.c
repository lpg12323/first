#include "stm32f10x.h"
#include "Delay.h"

void Door_Init(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

// 获取门状态
// 返回值：0 = 门关着 (安全)
// 返回值：1 = 门开了 (危险)
uint8_t Door_GetState(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
	{
		Delay_ms(20);// 软件消抖：等20ms再确认
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
		{
			return 1;
		}
	}
	
	return 0;// 默认返回0 (门关着或只是抖动)
}
