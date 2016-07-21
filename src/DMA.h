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


#define startDMA(x) (DMA_Cmd(x,ENABLE))
#define stopDMA(x) (DMA_Cmd(x,DISABLE))
#define cmarIsNotTXstorage DMA1_Channel3->CMAR != (uint32_t)txStorage
#define stepHigh 0x40
#define stepLow 0xBF

typedef struct{
  int slot;
  int counter;
  struct ListElement txElement;
  uint8_t stepHighCommand;
  uint8_t stepLowCommand;
}motorConfigInfo;
extern uint8_t motorDriveBuffer[];
extern uint8_t txBuffer[];
extern uint8_t txStorage[];
extern struct Linkedlist *txRoot;

void copyWholeInform(uint8_t buffer[],uint8_t storetage[]);
motorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress),int slot);
void dmaQueue(struct ListElement *txElement);
struct ListElement* dmaDequeue(void);



#endif // DMA_H
