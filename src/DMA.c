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



uint8_t motorDriveBuffer[3];
uint8_t txBuffer[3];
uint8_t txStorage[3];
struct Linkedlist *txRoot;

void DMA1_Channel3_IRQHandler(void){
  stopDMA(DMA1_Channel3);
  outputData();
  DMA_ClearITPendingBit(DMA1_IT_TC3);
  struct ListElement* temp = dmaDequeue();
  motorConfigInfo* motorConfiguration = (motorConfigInfo*)temp->args;
  



   
   setDataNumber(DMA1_Channel3,3);
   startDMA(DMA1_Channel3);
}

void copyWholeInform(uint8_t buffer[],uint8_t storetage[]){
 int i; 
 for(i = 0; i<3 ; i++){
    buffer[i] = storetage[i];
  }
}

struct ListElement* dmaDequeue(void){
  struct ListElement *temp = txRoot->head;
  updateHead(txRoot);
  return temp;
}

void dmaQueue(struct ListElement *txElement){
    addListInCycle(txRoot,txElement);
}

motorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot){
  motorConfigInfo* detail = malloc(sizeof(motorConfigInfo));
  detail->counter = 0;
  detail->slot = slot;
  detail->stepHighCommand = 0;
  detail->stepLowCommand = 0;
  detail->txElement.next = NULL;
  detail->txElement.prev = NULL;
  detail->txElement.callBack = funcAddress;
  detail->txElement.args = detail;
  return detail;
}





/*
void dmaDriveMotor(motorInfo* whichMotor, uint8_t motorDir, uint8_t microStep){
  whichMotor->direation = motorDir;
  whichMotor->microstep = microStep;
  txBuffer[whichMotor->identity] = getMotorSetting(whichMotor)&stepLow;
  txStorage[whichMotor->identity] = getMotorSetting(whichMotor)|stepHigh;
  copyInformFromBufferToStorageExcept(whichMotor->identity);
  setMemoryAddress(DMA1_Channel3,(uint32_t)txBuffer);
  setDataNumber(DMA1_Channel3,3);
  startDMA(DMA1_Channel3);
}
*/

// void copyInformFromBufferToStorageExcept(motorID identity){
  // switch(identity){
     // case FIRST_MOTOR:
	   // txStorage[SECOND_MOTOR] = txBuffer[SECOND_MOTOR];
	   // txStorage[THIRD_MOTOR] = txBuffer[THIRD_MOTOR];
	 // break;
   	 // case SECOND_MOTOR:
	   // txStorage[FIRST_MOTOR] = txBuffer[FIRST_MOTOR];
	   // txStorage[THIRD_MOTOR] = txBuffer[THIRD_MOTOR];
	 // break;
	   // case THIRD_MOTOR:
	   // txStorage[FIRST_MOTOR] = txBuffer[FIRST_MOTOR];
	   // txStorage[SECOND_MOTOR] = txBuffer[SECOND_MOTOR];
	 // break;
   // default:break;
	// }
// }
