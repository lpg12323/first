#include "stm32f10x.h"                  // Device header

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
		// 笨蛋延时 (随便空跑一会)
        int i; // 这一行如果报错，也要提到 while(1) 外面去定义
        for(i=0; i<1000000; i++);
        
        // 灭灯
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        
        // 再延时
        for(i=0; i<1000000; i++);
	}
}		
