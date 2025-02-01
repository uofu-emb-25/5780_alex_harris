#include <stm32f0xx_hal.h>
#include <assert.h>

int lab1_main(void) {
    HAL_Init();
    
    SystemClock_Config();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    // Assert that GPIOC Clock is enabled
    assert(((RCC ->AHBENR & RCC_AHBENR_GPIOCEN_Msk) >> RCC_AHBENR_GPIOCEN_Pos) == 0x1);

    
    GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_9, 
                                GPIO_MODE_OUTPUT_PP, 
                                GPIO_SPEED_FREQ_LOW, 
                                GPIO_NOPULL};
    
    HAL_GPIO_Init(GPIOC, &initStr);

    // Assert that GPIO pins 8 and 9 are set to push pull output mode
    // assert(GPIOC->OTYPER & GPIO_OTYPER_OT_8  == 0);
    // assert(GPIO_OTYPER_OT_9  == 0);

    // Assert that GPIO pins 8 and 9 are set to low freq mode
    assert(((GPIOC ->OSPEEDR & GPIO_OSPEEDR_OSPEEDR8_Msk) >> GPIO_OSPEEDR_OSPEEDR8_Pos) == 0x0);
    assert(((GPIOC ->OSPEEDR & GPIO_OSPEEDR_OSPEEDR9_Msk) >> GPIO_OSPEEDR_OSPEEDR9_Pos) == 0x0);

    // Assert that GPIO pins 8 and 9 are set to no pull up or pull down activation
    assert(((GPIOC ->PUPDR & GPIO_PUPDR_PUPDR8_Msk) >> GPIO_PUPDR_PUPDR8_Pos) == 0x0);
    assert(((GPIOC ->PUPDR & GPIO_PUPDR_PUPDR9_Msk) >> GPIO_PUPDR_PUPDR9_Pos) == 0x0);


    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    // assert(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8) == GPIO_PIN_SET);

    // GPIOC->MODER |= (1 << 12) | (1 << 14) | (1 << 16);

    // GPIOC->MODER &= ~((1 << 0) | (1 << 1) | (1 << 13) | (1 << 15) | (1 << 17));
    

    while (1) {
        HAL_Delay(200);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
    }
}