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
#include "DMA.h"
#include "Motor.h"
//#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"

#define motorMovementHandler DMA1_Channel3_IRQHandler

/*
  DMA_Channel is a marco that was defined in Config.h. 
*/

uint8_t motorDriveBuffer[3];
uint8_t txBuffer[3];
uint8_t txStorage[3];
Linkedlist *txRoot;

void motorController(MotorInfo* whichMotor){
   startCoroutine();


  while(1){

    recordCurrentTime(whichMotor->timeRecord1);
   	motorStep(whichMotor->motorConfiguration);
    yield();
    recordCurrentTime(whichMotor->timeRecord2);
    
    timerDelay(&(whichMotor->timerElement),whichMotor->period - interval );
    yield();
   }
   endCoroutine();
}


void motorStep(MotorConfigInfo* motorConfiguration){
  stopDMA(DMA_Channel);  // Before modified, the DMA must be stopped.
  
  dmaQueue(&motorConfiguration->txElement);  //Add the Element into DMA Queue.
  
  if( (Motor_Number - DMA_Channel->CNDTR) <= motorConfiguration->slot ){  
    updateSlotCommand(motorConfiguration->slot);  // update the command of slot
  }
  startDMA(DMA_Channel); // After modified, the DMA should be started.
}

uint8_t getMotorSetUp(MotorInfo* whichMotor){
  return (whichMotor->direation
         |whichMotor->microstep 
         |whichMotor->sleep
         |whichMotor->reset
         |whichMotor->motorState);
}

void setUpCommand(MotorInfo* whichMotor){
   uint8_t motorSetup;
   motorSetup = getMotorSetUp(whichMotor); // Extract the motor setting that has already set in whichMotor.
   whichMotor->motorConfiguration->stepHighCommand = motorSetup|Motor_Step_High;
   whichMotor->motorConfiguration->stepLowCommand = motorSetup&Motor_Step_Low;
}

void motorSet(MotorInfo* whichMotor, uint8_t direation, uint8_t microstep){
   whichMotor->direation = direation;
   whichMotor->microstep = microstep;
   whichMotor->sleep = Motor_Sleep_Mode_Disable;    
   whichMotor->reset = Motor_Sleep_Reset_Disable;
   whichMotor->motorState = Motor_Enable;
   setUpCommand(whichMotor);
}

void motorMovementHandler(void){
  stopDMA(DMA1_Channel3);
  outputData();
  int i;
  ListElement* cur;
  resetTCFlag;
  ListElement* temp;
  MotorConfigInfo* motorConfig = readMotorConfigInfo(txRoot->head->args);
  setDataNumber(DMA1_Channel3,3);

   while(!isDmaQueueEmpty && hasCompleteUpdate(motorConfig) ){ // need to change
     temp = dmaDequeue(txRoot);
     resetCommandCounter(readMotorConfigInfo(temp->args));
     callBackFunction(temp);
     if(!isDmaQueueEmpty){
       updateMotorConfigInfo(motorConfig);
     }
   }

   
  if(!isDmaQueueEmpty){
   updateMotorDriveBuffer();
   startDMA(DMA1_Channel3);
  }

}
   
   // printf("txRoot->count = %d\n",txRoot->count);
   // for(i = txRoot->count,cur = txRoot->head ; i > 0 ; --i,cur = cur->next ){
     // printf("hello2\n");
      // if( hasCompleteUpdate( motorConfig )){
           // printf("hello\n");
       // linkedListRemove(txRoot,cur);
       // cur->callBack(cur->args);
     // }
     // if(!isDmaQueueEmpty){
      // cur = cur->next;
      // resetCommandCounter(motorConfig);
      // linkedListRemove(txRoot,cur);
      
      // if(!isDmaQueueEmpty){
        // updateMotorConfigInfo(motorConfig);
       // }
     // }
   // }
   
   

void updateMotorDriveBuffer(void){
  ListElement* temp ;
  
  MotorConfigInfo* motorConfiguration;
  pointToHeadOfLinkedList(temp);
  do{
   motorConfiguration = readMotorConfigInfo(temp->args);
   updateSlotCommand(motorConfiguration->slot);
   pointToNext(temp);
  }while( !isEndOfQueue );
  
}

MotorConfigInfo* readMotorConfigInfo(void *args){
  MotorInfo* whichMotor = readMotorInfo(args);
  return (whichMotor->motorConfiguration);
}


uint8_t getCommand(MotorConfigInfo* motorConfiguration){
  uint8_t commond;
  if(motorConfiguration->counter == 0){ // If the function was called by first times, the stepLowCommand will be return out.
   commond = motorConfiguration->stepLowCommand;
  }else{
   commond = motorConfiguration->stepHighCommand;
  }
   motorConfiguration->counter++; // Once the function was called, the Counter will be recorded.
                                  // Once the counter reached 2, it is mean the command update is completed.
  return commond;
}

//stepperMotor

MotorInfo* motorInit( void (*funcAddress),int period, int slot ){
   MotorInfo* whichMotor = malloc(sizeof(MotorInfo));  
   
   whichMotor->direation = StpMtr_Clockwise;
   whichMotor->step = StpMtr_Low;
   whichMotor->sleep = StpMtr_Slp_Off; 
   whichMotor->microstep = StpMtr_Full_step;
   whichMotor->reset = StpMtr_Rst_Off;
   whichMotor->motorState = StpMtr_Enable;
   
   whichMotor->period = period;
   whichMotor->state = 0;
   
   whichMotor->timerElement.next = NULL;
   whichMotor->timerElement.prev = NULL;
   whichMotor->timerElement.actionTime = 0;
   whichMotor->timerElement.callBack = funcAddress;
   whichMotor->timerElement.args = whichMotor;
   whichMotor->motorConfiguration = motorConfigInit(whichMotor,funcAddress,slot);
   return whichMotor;
}

MotorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot){
  MotorConfigInfo* detail = malloc(sizeof(MotorConfigInfo));
  detail->counter = 0;
  detail->slot = slot;
  detail->stepHighCommand = 0;
  detail->stepLowCommand = 0;
  detail->txElement.next = NULL;
  detail->txElement.prev = NULL;
  detail->txElement.callBack = funcAddress;
  detail->txElement.args = motorAddress;
  return detail;
}

/**
 * Set own address to args that was created in motorInfo struct.
*/
void setArgs(MotorInfo* whichMotor){
  whichMotor->timerElement.args = whichMotor;
}
/**
 * Set some function address to callBack that was created in motorInfo struct.
*/
void setCallBack(ListElement* whichMotorElement, void (*funcAddress) ){
   whichMotorElement->callBack = funcAddress;
}

void setPeriod(MotorInfo* whichMotor,int period){
	whichMotor->period = period;
}


uint8_t stdMtr_drive_conf(uint8_t dir, uint8_t slp_mode,uint8_t microstep){
  return (dir | StpMtr_Low |slp_mode | StpMtr_Rst_Off | microstep | StpMtr_Enable);
}


void sendConfToShiftReg(SPI_TypeDef* SPIx,uint16_t driver_conf){
  if(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) ){ // if TXE is 1, the while loop will stop
  SPIx->DR = driver_conf;
  }
}

void outputData(){
      GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Clock Low
      GPIO_SetBits(GPIOA, GPIO_Pin_4);   // Clock High
}

uint8_t getMotorSetting(MotorInfo* whichMotor){
 return(whichMotor->direation
	    |whichMotor->sleep
    	|whichMotor->microstep
		|StpMtr_Rst_Off
		|StpMtr_Enable);
}

void resetMotorDrive(void){
 uint8_t reset = StpMtr_Clockwise
		         |StpMtr_Low
		         |StpMtr_Slp_Off
		         |StpMtr_Rst_On
		         |StpMtr_Full_step
		         |StpMtr_Enable;
 SPI_I2S_SendData(SPI1,reset);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  outputData();
}


/*

void motorStep(motorConfigInfo* motorConfiguration){
  dmaQueue(&motorConfiguration->txElement);  
  uint32_t checkDataNumber = getDataNumber(DMA_Channel);

  switch( transmittedStatus ){

    case noCommandTransmitted:
    if( !isDMAstarted(DMA_Channel) || !allowThirdMotorUpdate ){
     updateSlotCommand(motorConfiguration->slot);
    }
    break;
    
    case OneCommandTransmitted:
    if( allowFirstMotorUpdate ){
     updateSlotCommand(motorConfiguration->slot);
    }
    break;
    
    default:break;
  }

  startDMA(DMA_Channel); 
}


*/
