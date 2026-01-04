#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "Door.h"

int main(void)
{
	Buzzer_Init();
	Door_Init();
	
	Buzzer_OFF();
	
	while(1)
	{
		if (Door_GetState() == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	}
}		
