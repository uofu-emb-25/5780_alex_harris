#include <stm32f0xx_hal.h>
#include <assert.h>

int lab1_main(void) {
    HAL_Init();
    
    SystemClock_Config();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    // Assert that GPIOC Clock is enabled
    assert(((RCC ->AHBENR & RCC_AHBENR_GPIOCEN_Msk) >> RCC_AHBENR_GPIOCEN_Pos) == 0x1);

    
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7, 
                                GPIO_MODE_OUTPUT_PP, 
                                GPIO_SPEED_FREQ_LOW, 
                                GPIO_NOPULL};
    
    My_HAL_GPIO_Init(GPIOC, &initStr);

    // Assert that GPIOC pins 8 and 9 are set to push pull output mode
    assert((GPIOC->OTYPER & GPIO_OTYPER_OT_6)  == 0);
    assert((GPIOC->OTYPER & GPIO_OTYPER_OT_7)  == 0);


    // Assert that GPIOC pins 8 and 9 are set to low freq mode
    assert(((GPIOC ->OSPEEDR & GPIO_OSPEEDR_OSPEEDR6_Msk) >> GPIO_OSPEEDR_OSPEEDR6_Pos) == 0x0);
    assert(((GPIOC ->OSPEEDR & GPIO_OSPEEDR_OSPEEDR7_Msk) >> GPIO_OSPEEDR_OSPEEDR7_Pos) == 0x0);

    // Assert that GPIOC pins 8 and 9 are set to no pull up or pull down activation
    assert(((GPIOC ->PUPDR & GPIO_PUPDR_PUPDR6_Msk) >> GPIO_PUPDR_PUPDR6_Pos) == 0x0);
    assert(((GPIOC ->PUPDR & GPIO_PUPDR_PUPDR7_Msk) >> GPIO_PUPDR_PUPDR7_Pos) == 0x0);


    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    // Assert that GPIOC 6 is set
    assert(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6) == GPIO_PIN_SET);

    while (1) {
        HAL_Delay(200);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
        //Assert that the GPIOC 6 and GPIO 7 are not in the same state.
        assert(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6) != HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7));
    }
}