#include <stm32f0xx_hal.h>
#include <assert.h>

int lab6_main(void){
    HAL_Init();

    My_HAL_RCC_GPIOA_CLK_ENABLE();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); 

    My_HAL_USART_ALTERNATE_FUNCTION_ENABLE();
    My_HAL_USART_CONFIGURE_PARAMS();

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);

    GPIO_InitTypeDef initStr = {GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL};

    HAL_GPIO_INIT(GPIOC, &initStr);
}