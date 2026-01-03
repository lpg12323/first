#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define BUZZER_ON GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define BUZZER_OFF GPIO_SetBits(GPIOB, GPIO_Pin_12)

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
	BUZZER_OFF;
	
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			Delay_ms(20);
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
				BUZZER_OFF;
			}
		}
		else 
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			BUZZER_ON;
		}
	}
}		
