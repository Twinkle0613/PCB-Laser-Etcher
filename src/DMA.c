#include "Dma.h"


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



void setDataNumber(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t dataNumber){
	DMAy_Channelx->CNDTR = dataNumber;
}

uint32_t getDataNumber(DMA_Channel_TypeDef* DMAy_Channelx){
	return DMAy_Channelx->CNDTR;
}

void DmaConfig(DMA_Channel_TypeDef* DMAy_Channelx,
              uint32_t periAddress,
              uint32_t memoryAddress,
              uint32_t dataDirection,
              uint32_t bufferSize,
              uint32_t periDataSize,
              uint32_t memoryDataSize,
              uint32_t dmaMode
              ){
  DMA_InitTypeDef dma;
  dma.DMA_PeripheralBaseAddr = periAddress;
  dma.DMA_MemoryBaseAddr = memoryAddress;
  dma.DMA_DIR = dataDirection;
  dma.DMA_BufferSize = bufferSize;
  dma.DMA_PeripheralDataSize = periDataSize;
  dma.DMA_MemoryDataSize = memoryDataSize;

  dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma.DMA_Mode = dmaMode;
  dma.DMA_Priority = DMA_Priority_High;
  dma.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMAy_Channelx,&dma);
}


void dmaQueue(Linkedlist *motorRoot,ListElement *motorElement){
    addList(motorRoot,motorElement);
}
