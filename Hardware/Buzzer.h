#ifndef __BUZZER_H
#define __BUZZER_H

void Buzzer_Init(void); // 初始化函数
void Buzzer_ON(void);   // 开
void Buzzer_OFF(void);  // 关
void Buzzer_Turn(void); // 翻转状态（响变不响，不响变响）

#endif
