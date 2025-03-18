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

    GPIOA->MODER &= ~(0xF << 18); 
    GPIOA->MODER |= (0xA << 18); 
}

void My_HAL_USART_CONFIGURE_PARAMS(void){
    USART1->BRR = (uint16_t)(HAL_RCC_GetHCLKFreq() / 115200);
    USART1->ISR    |= USART_ISR_RXNE;
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEEDR9 | GPIO_OSPEEDR_OSPEEDR10);
    GPIOA->PUPDR   |= (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0);
    USART1->CR1    |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

void My_HAL_I2C1_ALTERNATE_FUNCTION_ENABLE(void){
    // clear alternate function registers for pb6 and pb7
    GPIOB->AFR[0] &= ~(0xF << 24);
    GPIOB->AFR[0] &= ~(0xF << 28);

    // set to af1
    GPIOB->AFR[0] |= (1 << 24);
    GPIOB->AFR[0] |= (1 << 28);

    // set gpio to alternate function mode
    GPIOB->MODER &= ~(0xF << 12); 
    GPIOB->MODER |= (0xA << 12); 
}

void My_HAL_I2C2_ALTERNATE_FUNCTION_CONFIG(void){
    // configure pb11
    // clear alternate function registers for pb11
    GPIOB->AFR[1] &= ~(0xF << 12);
    // set pb11 to af1
    GPIOB->AFR[1] |= (1 << 12);
    // set pb11 to alternate function mode
    GPIOB->MODER &= ~(0x3 << 22); 
    GPIOB->MODER |=  (0x2 << 22);
    // set pb11 to push pull
    GPIOB->OTYPER |= (1 << 11);

    //configure pb13
    GPIOB->AFR[1] &= ~(0xF << 20);
    // set pb13 to af4
    GPIOB->AFR[1] |= (0x4 << 20);
    // set pb13 to alternate function mode
    GPIOB->MODER &= ~(0x3 << 26); 
    GPIOB->MODER |= (0x2 << 26);
    // set pb13 to push pull
    GPIOB->OTYPER |= (1 << 13);

    //configure pb14
    // set pb14 to output mode
    GPIOB->MODER &= ~(0x3 << 28); 
    GPIOB->MODER |=  (0x1 << 28); 
    // set pb14 to push pull
    GPIOB->OTYPER &= ~(1 << 14);
    // set pb14 high
    GPIOB->ODR |= (1 << 14);

    // configure pc0
    // set pc0 to output mode
    GPIOC->MODER &= ~(0x3 << 0);
    GPIOC->MODER |=  (0x1 << 0);
    //set pc0 to push pull
    GPIOC->OTYPER &= ~(1 << 0);
    //set pc0 high
    GPIOC->ODR |= (1 << 0);
}

void My_HAL_I2C2_PERIPHERAL_CONFIG(void){
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    I2C2->TIMINGR |= ((1 << 28) | (4 << 28) | (2 << 16) | (6 << 8) | (9 << 0));
    I2C2->CR1 |= I2C_CR1_PE;
}

void My_HAL_I2C_CONFIGURE_PARAMS(void){
    // set pb6 and pb7 to output open drain
    GPIOB->OTYPER |= GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7;

    // configure i2c1 
    I2C1->TIMINGR |= I2C_TIMINGR_PRESC;
    I2C1->TIMINGR |= (0x13 << I2C_TIMINGR_SCLL);
    I2C1->TIMINGR |= (0xF << I2C_TIMINGR_SCLH);
    I2C1->TIMINGR |= (0x2 << I2C_TIMINGR_SDADEL);
    I2C1->TIMINGR |= (0x4 << I2C_TIMINGR_SCLDEL);
    I2C1->CR1 |= I2C_CR1_PE;
}

void My_HAL_I2C_WRITE_TRANSACTION_SETUP(void){
    I2C1->CR2 &= ~((0x7F << 16) | (0x3FF << 0));
    I2C1->CR2 |= (1 << 16 | 0x69 << 1);
    I2C1->CR2 &= ~(1 << 10);
    I2C1->CR2 |= (1 << 13);
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