#include "DMA_setting.h"
#include "stdint.h"
#include "stm32f10x_dma.h"

void DMA_conf(DMA_Channel_TypeDef* DMAy_Channelx,
              uint32_t periAddress, 
              uint32_t memoryAddress,
              uint32_t dataDirection,
              uint32_t bufferSize,
              uint32_t periDataSize,
              uint32_t memoryDataSize
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
  dma.DMA_Mode = DMA_Mode_Normal;
  dma.DMA_Priority = DMA_Priority_Low;
  dma.DMA_M2M = DMA_M2M_Disable;
  
  DMA_Init(DMAy_Channelx,&dma);
}
