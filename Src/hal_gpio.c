#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    GPIOx->MODER   |= (1 << 12) | (1 << 14) | (1 << 16) | (1 << 18);

    GPIOx->MODER   &= ~((1 << 1) | (1 << 13) | (1 << 15) | (1 << 17) | (1 << 19));

    GPIOx->OTYPER  &= ~((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9));

    GPIOx->OSPEEDR &= ~((1 << 12) | (1 << 14) | (1 << 16) | (1 << 18));

    GPIOx->PUPDR   &= ~((1 << 12) |  (1 << 13) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19));

    GPIOx->PUPDR   |= ~(1 << 1);

    GPIOA->MODER   &= ~((1 << 1) | (1 << 0));
    GPIOA->OSPEEDR &= ~(1 << 0);
    GPIOA->PUPDR   &= ~(1 << 0);
    GPIOA->PUPDR   |=  (1 << 1);

}

void My_HAL_LED_ALTERNATE_FUNCTION_ENABLE(void){
    GPIOC->AFR[0] &= ~(0xF << 28);
    GPIOC->AFR[0] &= ~(0xF << 24);

    GPIOC->MODER &= ~((3 << (6 * 2)) | (3 << (7 * 2))); 
    GPIOC->MODER |= (2 << (6 * 2)) | (2 << (7 * 2)); 
}

void My_HAL_USART_ALTERNATE_FUNCTION_ENABLE(void){
    GPIOA->AFR[1] &= ~(0xF << 4);
    GPIOA->AFR[1] &= ~(0xF << 8);

    GPIOA->AFR[1] |= (1 << 4);
    GPIOA->AFR[1] |= (1 << 8);
}
/*
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return GPIOx->IDR & GPIO_Pin;
}


void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if(PinState == GPIO_PIN_SET){
        GPIOx->BSRR = (uint32_t)GPIO_Pin;
    }
    else{
        GPIOx->BRR = (uint32_t)GPIO_Pin;
    }
}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if (GPIOx->ODR & GPIO_Pin){
        GPIOx->BSRR = GPIO_Pin << 16;
    }
    else {
    GPIOx->BSRR = GPIO_Pin;
   }
}

void My_HAL_EXTI_ENABLE(void){
    EXTI->IMR  |= (1 << 0);
    EXTI->RTSR |= (1 << 0);
}

void My_HAL_SYSCFG_PA0_ENABLE(void){
    SYSCFG->EXTICR[0] &= ~(1 << 0 ) | (1 << 1) | (1 << 2) | (1 << 3);
}