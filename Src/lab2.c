#include <stm32f0xx_hal.h>
#include <assert.h>

int lab2_main(void){
    HAL_Init();
    SystemClock_Config();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC   
    My_HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC   

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
                                GPIO_MODE_OUTPUT_PP, 
                                GPIO_SPEED_FREQ_LOW, 
                                GPIO_NOPULL};
    HAL_GPIO_Init(GPIOC, &initStr);

    GPIO_InitTypeDef initStr = {GPIO_PIN_0, 
                                GPIO_MODE_INPUT, 
                                GPIO_SPEED_FREQ_LOW, 
                                GPIO_PULLDOWN};
    HAL_GPIO_Init(GPIOA, &initStr);

    My_HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9, GPIO_PIN_SET);


    while(1){
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6);
        HAL_Delay(400);
    }
}