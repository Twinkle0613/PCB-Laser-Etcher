#include "ShiftReg.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "peripherals.h"


#define LOW 0
#define HIGH 1

void sendOnebit(FunctionalState NewState){
   if( NewState == ENABLE)    
      GPIO_SetBits(GPIOA, GPIO_Pin_7);   // send High
   else 
      GPIO_ResetBits(GPIOA, GPIO_Pin_7); // send Low
      
      GPIO_ResetBits(GPIOA, GPIO_Pin_5); // Clock Low
      GPIO_SetBits(GPIOA, GPIO_Pin_5);   // Clock High
}


void outData(){
      GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Clock Low
      GPIO_SetBits(GPIOA, GPIO_Pin_4);   // Clock High
}

void GPIO_conf1(GPIO_TypeDef* GPIOx, uint16_t Pin, int Speed, int Mode){
    GPIO_InitTypeDef  gpio;
    gpio.GPIO_Pin = Pin;
    gpio.GPIO_Speed = Speed;
    gpio.GPIO_Mode = Mode;
    GPIO_Init(GPIOx,&gpio);
}