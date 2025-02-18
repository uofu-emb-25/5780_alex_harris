#include <stm32f0xx_hal.h>
#include <assert.h>

void TIM2_IRQHandler(void){
    
    if(TIM2->SR &= TIM_SR_UIF){
        TIM2->SR &= ~TIM_SR_UIF; 

        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
    }
    
}

int lab3_main(void){
    HAL_Init();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC   
    My_HAL_TIMER_PERIPHERAL_ENABLE(); // Enables the TIM2 and TIM3 peripheral
    My_HAL_LED_ALTERNATE_FUNCTION_ENABLE();

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};
    HAL_GPIO_Init(GPIOC, &initStr);
    My_HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);


    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn,1);
    HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6);
    HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
}