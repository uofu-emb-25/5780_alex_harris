#include <stm32f0xx_hal.h>
#include <assert.h>

int lab6_main(void){
    HAL_Init();
    My_HAL_RCC_GPIOA_CLK_ENABLE();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); 
    My_HAL_RCC_ADC_CLK_ENABLE();

    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
        GPIO_MODE_OUTPUT_PP, 
        GPIO_SPEED_FREQ_LOW, 
        GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);

    My_HAL_GPIO_ConfigADC();

    uint8_t adcVal;
    while(1){
        ADC1->CR |= ADC_CR_ADSTART;
        while(!(ADC1->ISR & ADC_ISR_EOC)){}
        adcVal = (uint8_t)ADC1->DR;


        if(adcVal >= 60){
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);
        }
        else{
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
        }

        if(adcVal >= 120){
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);
        }
        else{
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);
        }

        if(adcVal >= 180){
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
        }
        else{
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
        }

        if(adcVal >= 240){
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);
        }
        else{
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET);
        }
    }

    
}