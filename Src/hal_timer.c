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
    TIM3->ARR = 101;

    TIM2->DIER|= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S);
    TIM3->CCMR1 &= ~(TIM_CCMR1_CC2S);
    TIM3->CCMR1 |= (1 << 4) | (1 << 5) | (1 << 6);
    TIM3->CCMR1 |= (1 << 14) | (1 << 13);
    TIM3->CCMR1 &= ~(1 << 12);
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;
    TIM3->CCER  |= TIM_CCER_CC1E | TIM_CCER_CC2E;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3-> CCR1 = 100;
    TIM3-> CCR2 = 60;
    TIM3->CR1 |= TIM_CR1_CEN;

}

