#ifndef Dma_H
#define Dma_H


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
#include "Linklist.h"
#include "RelativeTimeLinkList.h"
#include "MockFunction.h"

#define startDMA(x) (DMA_Cmd(x,ENABLE))
#define stopDMA(x) (DMA_Cmd(x,DISABLE))
#define resetTCFlag ( DMA_ClearITPendingBit(DMA1_IT_TC3) )
#define dmaDequeue(x) dequeue(x)

void setDataNumber(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t dataNumber);
uint32_t getDataNumber(DMA_Channel_TypeDef* DMAy_Channelx);
void DmaConfig(DMA_Channel_TypeDef* DMAy_Channelx,
              uint32_t periAddress,
              uint32_t memoryAddress,
              uint32_t dataDirection,
              uint32_t bufferSize,
              uint32_t periDataSize,
              uint32_t memoryDataSize,
              uint32_t dmaMode
              );


void dmaQueue(Linkedlist *motorRoot,ListElement *motorElement);
#endif // Dma_H
