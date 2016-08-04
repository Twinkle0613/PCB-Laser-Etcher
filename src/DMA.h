#ifndef DMA_H
#define DMA_H

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
#include "DMA_setting.h"
#include "Timer.h"
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"


#define startDMA(x) (DMA_Cmd(x,ENABLE))
#define stopDMA(x) (DMA_Cmd(x,DISABLE))
#define resetTCFlag ( DMA_ClearITPendingBit(DMA1_IT_TC3) )
#define dmaDequeue(x) dequeue(x)
void dmaQueue(ListElement *txElement);


#endif // DMA_H
