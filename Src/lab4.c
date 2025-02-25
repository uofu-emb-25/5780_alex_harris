#include <stm32f0xx_hal.h>
#include <assert.h>

void transmit_message(char input){
    while((USART1->ISR & USART_ISR_TXE) == 0){}
    USART1->TDR = input;
}
int lab4_main(void){
    HAL_Init();

    My_HAL_RCC_GPIOA_CLK_ENABLE();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); 
    My_HAL_RCC_USART_CLK_ENABLE();

    My_HAL_USART_ALTERNATE_FUNCTION_ENABLE();
    My_HAL_USART_CONFIGURE_PARAMS();

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);

    while(1){
        transmit_message('h');
        HAL_Delay(1000);
    }
}