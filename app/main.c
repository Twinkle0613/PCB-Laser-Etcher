#include "SPI_setting.h"
#include "GPIO_setting.h"
#include "stm32f10x_rcc.h"
#include "stpMtr_drive.h"
#include "stm32f10x_spi.h"
#include <stdint.h>

void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 100; i++) {}
}

int main(void)
{
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,DISABLE);
   GPIO_conf(GPIOC,GPIO_Pin_13,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);
    while(1)
    {
      GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
      delay(100);
      GPIO_ResetBits(GPIOC, GPIO_Pin_13); // LED OFF
      delay(100);
    }
}
