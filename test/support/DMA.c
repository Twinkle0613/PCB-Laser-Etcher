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

void dmaQueue(ListElement *txElement){
    addList(motorRoot,txElement);
}

// uint8_t motorDriveBuffer[3];
// uint8_t txBuffer[3];
// uint8_t txStorage[3];
// struct Linkedlist *txRoot;



// void updateMotorDriveBuffer(void){
  // struct ListElement* temp ;
  
  // motorConfigInfo* motorConfiguration;
  // pointToHeadOfLinkedList(temp);
  // do{
   // motorConfiguration = readMotorConfigInfo(temp->args);
   // updateSlotCommand(motorConfiguration->slot);
   // pointToNext(temp);
  // }while( !isEndOfQueue );
  
// }

// motorConfigInfo* readMotorConfigInfo(void *args){
  // motorInfo* whichMotor = readMotorInfo(args);
  // return (whichMotor->motorConfiguration);
// }

// struct ListElement* dmaDequeue(void){   //Need to change
  // struct ListElement *temp = txRoot->head;
  // updateHead(txRoot);
  // return temp;
// }

// void dmaQueue(struct ListElement *txElement){
    // addListInCycle(txRoot,txElement);
// }


// uint8_t getCommand(motorConfigInfo* motorConfiguration){
  // uint8_t commond;
  // if(motorConfiguration->counter == 0){ // If the function was called by first times, the stepLowCommand will be return out.
   // commond = motorConfiguration->stepLowCommand;
  // }else{
   // commond = motorConfiguration->stepHighCommand;
  // }
   // motorConfiguration->counter++; // Once the function was called, the Counter will be recorded.
                              ////    Once the counter reached 2, it is mean the command update is completed.
  // return commond;
// }





/*
void copyWholeInform(uint8_t buffer[],uint8_t storetage[]){
 int i; 
 for(i = 0; i<3 ; i++){
    buffer[i] = storetage[i];
  }
}


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

void cleanUpListedList(void){
  struct ListElement* temp ;
  motorConfigInfo* motorConfiguration = readMotorConfigInfo(txRoot->head->args);
  while( !isDmaQueueEmpty && isCompleteUpdateCommand(motorConfiguration) ){
       temp = dmaDequeue();
       if(!isDmaQueueEmpty){
         motorConfiguration = readMotorConfigInfo(txRoot->head->args);
       }
  }     
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


/*
  struct ListElement* temp = dmaDequeue();
  struct ListElement* temp2;
  motorConfigInfo* motorConfiguration = (motorConfigInfo*)temp->args;
  motorDriveBuffer[motorConfiguration->slot] = getCommand(motorConfiguration);
  while( txRoot->head != NULL ){
    
    
  }

*/
