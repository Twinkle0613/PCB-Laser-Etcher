//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM standard Library
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
//Own Library
#include "Timer.h"
#include "DMA.h"
#include "DMA_setting.h"
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"

Linkedlist *motorRoot;

void dmaQueue(ListElement *motorElement){
    addList(motorRoot,motorElement);
}


