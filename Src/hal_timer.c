#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_TIMER_PERIPHERAL_ENABLE(void)
{
    RCC->APB1ENR|= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR|= RCC_APB1ENR_TIM3EN;

    TIM2->PSC = 7999;
    TIM2->ARR = 250;
    TIM3->PSC = 99;
    TIM3->ARR = 99;

    TIM2->DIER|= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    

    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
    TIM3->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);
    TIM3->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);
    TIM3->CCER  |= TIM_CCER_CC1E | TIM_CCER_CC2E;

    TIM3->CR1 |= TIM_CR1_CEN;

    TIM3-> CCR1 = 20;
    TIM3-> CCR2 = 50;

}

