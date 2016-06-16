#include "GPIO_setting.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"



void GPIO_conf(GPIO_TypeDef* GPIOx, uint16_t Pin, int Speed, int Mode){
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = Pin;
    gpio.GPIO_Speed = Speed;
    gpio.GPIO_Mode = Mode;
    GPIO_Init(GPIOx,&gpio);
}


