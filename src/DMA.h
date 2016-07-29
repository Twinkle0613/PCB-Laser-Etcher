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
#define cmarIsNotTXstorage DMA1_Channel3->CMAR != (uint32_t)txStorage
#define stepHigh 0x40
#define stepLow 0xBF

#define updateSlotCommand(x) (motorDriveBuffer[x] = getCommand(motorConfiguration))

#define pointToHeadOfLinkedList(x) (x = txRoot->head)
#define isEndOfQueue (temp == txRoot->head) 
#define pointToNext(x) (x = x->next)

#define resetTCFlag ( DMA_ClearITPendingBit(DMA1_IT_TC3) )
#define isCompleteUpdateCommand(x) (x->counter >= 2)
#define isDmaQueueEmpty (txRoot->head == NULL)
#define resetCount(x) (x->counter = 0)
#define readMotorInfo(x) ((motorInfo*)x)

#define resetCommandCounter(x) (x->counter = 0)
#define updateMotorConfigInfo(x) (x = readMotorConfigInfo(txRoot->head->args))





extern uint8_t motorDriveBuffer[];
extern uint8_t txBuffer[];
extern uint8_t txStorage[];
extern struct Linkedlist *txRoot;
uint8_t getCommand(motorConfigInfo* motorConfiguration);

motorConfigInfo* readMotorConfigInfo(void *args);
void copyWholeInform(uint8_t buffer[],uint8_t storetage[]);
motorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress),int slot);
void dmaQueue(struct ListElement *txElement);
struct ListElement* dmaDequeue(void);
void cleanUpListedList(void);
void updateMotorDriveBuffer(void);

#endif // DMA_H
