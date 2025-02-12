#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_TIMER_PERIPHERAL_ENABLE(void)
{
    RCC->APB1ENR|= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR|= RCC_APB1ENR_TIM3EN;

    TIM2->PSC = 8000;
    TIM2->ARR = 250;
    TIM3->PSC = 25599;
    TIM3->ARR = 250000;

    TIM2->DIER|= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    TIM3->CR1 |= TIM_CR1_CEN;
}