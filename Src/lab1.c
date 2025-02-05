#include <stm32f0xx_hal.h>
#include <assert.h>

int lab1_main(void) {
    HAL_Init();
    
    SystemClock_Config();
    My_HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC   
    My_HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the GPIOA clock in the RCC   
    // Assert that GPIOC Clock is enabled
    assert(((RCC ->AHBENR & RCC_AHBENR_GPIOCEN_Msk) >> RCC_AHBENR_GPIOCEN_Pos) == 0x1);

    
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
                                GPIO_MODE_OUTPUT_PP, 
                                GPIO_SPEED_FREQ_LOW, 
                                GPIO_NOPULL};
    
    My_HAL_GPIO_Init(GPIOC, &initStr);

    // Assert that GPIOC pins 6 and 7 are set to push pull output mode
    assert((GPIOC->OTYPER & GPIO_OTYPER_OT_6)  == 0);
    assert((GPIOC->OTYPER & GPIO_OTYPER_OT_7)  == 0);

    // Assert that GPIOC pins 6 and 7 are set to low freq mode
    assert(((GPIOC->OSPEEDR & GPIO_OSPEEDR_OSPEEDR6_Msk) >> GPIO_OSPEEDR_OSPEEDR6_Pos) == 0x0);
    assert(((GPIOC->OSPEEDR & GPIO_OSPEEDR_OSPEEDR7_Msk) >> GPIO_OSPEEDR_OSPEEDR7_Pos) == 0x0);

    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

    // Assert that GPIOC 6 is set
    assert(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) == GPIO_PIN_SET);

    uint32_t debouncer = 0;
    while (1) {
    debouncer = (debouncer << 1);

    if(My_HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){
       debouncer |= 0x01;
    }

    if(debouncer == 0xFFFFFFFF){

    }

    if(debouncer == 0x00000000){

    }

    if(debouncer == 0x7FFFFFFF){
        My_HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
    }
        //Assert that the GPIOC 6 and GPIO 7 are not in the same state.
        assert(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6) != HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7));
    }
    HAL_Delay(10);
}