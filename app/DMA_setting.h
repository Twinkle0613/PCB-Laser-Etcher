#ifndef __DMA_setting_H__
#define __DMA_setting_H__
#include <stdint.h>
#include "stm32f10x_dma.h"
void DMA_conf(DMA_Channel_TypeDef* DMAy_Channelx,
              uint32_t periAddress,
              uint32_t memoryAddress,
              uint32_t dataDirection,
              uint32_t bufferSize,
              uint32_t periDataSize,
              uint32_t memoryDataSize,
              uint32_t dmaMode
              );
void setDataNumber(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t dataNumber);
void setMemoryAddress(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t address);

#endif //__DMA_setting_H__
