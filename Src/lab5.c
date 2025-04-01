#include <stm32f0xx_hal.h>
#include <assert.h>

int lab5_main(void){
    HAL_Init();

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);

    My_HAL_I2C2_ALTERNATE_FUNCTION_CONFIG();
    My_HAL_I2C2_PERIPHERAL_CONFIG();

    My_HAL_RCC_GPIOB_CLK_ENABLE();
    My_HAL_RCC_GPIOC_CLK_ENABLE();

    while(1){
        My_HAL_I2C2_Read_WHO_AM_I();
    }
}