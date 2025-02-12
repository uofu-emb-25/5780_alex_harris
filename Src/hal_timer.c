#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_TIMER_PERIPHERAL_ENABLE(void)
{
    RCC->APB1ENR|= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 8000;
    TIM2->ARR = 250;
    TIM2->DIER|= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;
}