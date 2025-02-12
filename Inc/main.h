#pragma once
#include <stdint.h>

void SystemClock_Config(void);
void My_HAL_RCC_GPIOC_CLK_ENABLE(void);
void My_HAL_EXTI_ENABLE(void);
void My_HAL_SYSCFG_PA0_ENABLE(void);
void My_HAL_TIMER_PERIPHERAL_ENABLE(void);