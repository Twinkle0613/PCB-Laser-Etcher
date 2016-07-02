//Own Library
#include "SPI_setting.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "Coroutine.h"
#include "projectStruct.h"
//STM32F103 Standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
//General Library
#include <stdint.h>
#include <stdio.h>


void Tim2_init(void);
struct Linkedlist *root;
void delay(int counter);

int main(void)
{
	root = createLinkedList();
	motorInfo* Motor1 = motorInit();
	motorInfo* Motor2 = motorInit();
	motorInfo* Motor3 = motorInit();

	setCallBack(&(Motor1->timerElement),coroutine);
	setCallBack(&(Motor2->timerElement),coroutine);
	setCallBack(&(Motor3->timerElement),coroutine);

	Motor1->timerElement.callBack(Motor1);

	Tim2_init();

	while(1)
    {

    }
}


void Tim2_init(void){
    NVIC_EnableIRQ(TIM2_IRQn);  //TIM2 global Interrupt

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);

    Timer_conf(TIM2,0,TIM_CounterMode_Down,0xFFFF,TIM_CKD_DIV1);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    enableTimer(TIM2,ENABLE);
}


void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 100; i++) {}
}
