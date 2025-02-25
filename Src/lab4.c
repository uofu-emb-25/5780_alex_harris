#include <stm32f0xx_hal.h>
#include <assert.h>

void transmit_message(char *input){
    while(*input){
        while((USART1->ISR & USART_ISR_TXE) == 0){}
        USART1->TDR = *input++;
    }
}
volatile char receive = 0;
volatile int newData = 0;

void USART1_IRQHandler(void){
    if(USART1->ISR & USART_ISR_RXNE){
        receive = (char)(USART1->RDR & 0xFF);
        newData = 1;
        transmit_message(receive);
    }
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
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(USART1_IRQn,0);
    USART1->CR1 |= USART_CR1_RXNEIE;

    while(1){
        char led = 0;
        char funct = 0;
        uint16_t led_pin = 0;
        char *led_color = "";
        transmit_message("CMD? ");

        while(newData == 0){}
        led = receive;
        newData = 0;

        while(newData == 0){}
        funct = receive;
        newData = 0;
           
        switch (led) {
            case 'r': 
                led_pin = GPIO_PIN_6;
                transmit_message("red ");
                break;
            case 'b': 
                led_pin = GPIO_PIN_7;
                transmit_message("blue ") ;
                break;
            case 'o': 
                led_pin = GPIO_PIN_8;
                transmit_message("orange ") ;
                break;
            case 'g': 
                led_pin = GPIO_PIN_9;
                transmit_message("green ") ;
                break;
            default:
                transmit_message("Error\r\n");
                break;
        }
        switch (funct) {
            case '0':
                My_HAL_GPIO_WritePin(GPIOC, led_pin, GPIO_PIN_RESET);
                transmit_message(*led_color);
                transmit_message(" off\r\n");
                break;
            case '1':
                My_HAL_GPIO_WritePin(GPIOC, led_pin, GPIO_PIN_SET);
                transmit_message(*led_color);
                transmit_message(" on\r\n");
                break;
            case '2':
                HAL_GPIO_TogglePin(GPIOC, led_pin);
                transmit_message(*led_color);
                transmit_message(" toggle\r\n");
                break;
            default:
                transmit_message("Error\r\n");
                break;
        }
    }
}