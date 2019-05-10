
#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__
#include "stm32f0xx.h"


#define TIM2_PRESCALER          479
#define TIM2_PERIOD             625


void TIM2_Init(void);
void SystemClock_Config(void);
void General_GPIO_Init(void);
extern TIM_HandleTypeDef htim2;
#endif
