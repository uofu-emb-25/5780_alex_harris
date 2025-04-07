#include <stm32f0xx_hal.h>
#include <assert.h>

int lab6_main(void){
    HAL_Init();
    SystemClock_Config();
    My_HAL_RCC_GPIOA_CLK_ENABLE();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); 
    My_HAL_RCC_ADC_CLK_ENABLE();
    My_HAL_RCC_DAC_CLK_ENABLE();


    const uint8_t sine_wave[32] = {
        128, 152, 176, 198, 218, 234, 246, 253,
        255, 253, 246, 234, 218, 198, 176, 152,
        128, 103, 79, 57, 37, 21, 9, 2,
        0, 2, 9, 21, 37, 57, 79, 103
    };
    
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);

    My_HAL_GPIO_ConfigADC();
    My_HAL_GPIO_ConfigDAC();
    uint8_t adcVal;
    uint8_t index = 0;

    while(1) {
        DAC->DHR8R1 = sine_wave[index];
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;

        index = (index + 1) % 32;

        HAL_Delay(1);
    }
}