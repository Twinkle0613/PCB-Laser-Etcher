//Own Library
#include "SPI_setting.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"
//STM32F103 Standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
//General Library
#include <stdint.h>

void TIM2_IRQHandler(){

  
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 100; i++) {}
}

int main(void)
{
    NVIC_EnableIRQ(TIM2_IRQn);  //TIM2 global Interrupt

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);
    
    Timer_conf(TIM2,0,TIM_CounterMode_Down,0xFFFF,TIM_CKD_DIV1);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    uint16_t time;
    enableTimer(TIM2,ENABLE);

    while(1)
    {
      time = getTime(TIM2);
    }
}
