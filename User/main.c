#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "Door.h"
#include "Key.h"

//定义三个状态：撤防（安全）、布防（警戒）、报警（抓人）
typedef enum {
	STATE_DISARMED = 0,
	STATE_ARMED,
	STATE_ALAREMING
} SecurityState_t;

SecurityState_t CurrentState = STATE_DISARMED;

int main(void)
{
	Buzzer_Init();
	Door_Init();
	Key_Init();
	
	Buzzer_OFF();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{
        // ================= PART 1: 处理按键 (切换模式) =================
		if (Key_GetNum() == 1)
		{
			if (CurrentState == STATE_DISARMED)
			{
				CurrentState = STATE_ARMED;
				// 响两声短的，提示布防
				Buzzer_ON(); Delay_ms(100); Buzzer_OFF(); Delay_ms(100);
				Buzzer_ON(); Delay_ms(100); Buzzer_OFF();
			}
			else
			{
				CurrentState = STATE_DISARMED;
				// 响一声长，提示撤防
				Buzzer_ON(); Delay_ms(500); Buzzer_OFF();
			}
		}
		
		// ================= PART 2: 根据状态干活 (状态机) =================
		switch (CurrentState)
		{
			case STATE_DISARMED: //【在家模式】
				Buzzer_OFF();
				GPIO_SetBits(GPIOC, GPIO_Pin_13); // 灯灭 (PC13高电平灭)
				break; 
			
			case STATE_ARMED:    //【警戒模式】
				GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 灯亮 (PC13低电平亮)
				
				if (Door_GetState() == 1) // 如果门开了
				{
					CurrentState = STATE_ALAREMING; // 切换状态
				}
				break; 
				
			case STATE_ALAREMING: //【报警模式】
				// 狂闪灯 + 狂叫
				Buzzer_Turn();
				
				// 翻转 LED 灯状态 (闪烁)
				if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) == 0)
					GPIO_SetBits(GPIOC, GPIO_Pin_13);
				else
					GPIO_ResetBits(GPIOC, GPIO_Pin_13);
				
				Delay_ms(100); // 闪烁频率
				break;
		}
	}
}		
