#include <stm32f0xx_hal.h>
#include <assert.h>

int lab4_main(void){
    HAL_Init();
    My_HAL_RCC_GPIOA_CLK_ENABLE();
    My_HAL_USART_ALTERNATE_FUNCTION_ENABLE();
}