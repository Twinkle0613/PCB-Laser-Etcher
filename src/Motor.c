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
#include "Dma.h"
#include "Motor.h"
#include "Timer.h"
#include "Linklist.h"
//#include "DMA_setting.h"
#include "stepperMotor.h"
#include "projectStruct.h"

#include "RelativeTimeLinkList.h"
#include "Config.h"
#include "MockFunction.h"
#include "getTick.h"
uint8_t motorDriveBuffer[NumberOfMotor];
Linkedlist *motorRoot;

/*
  DMA_Channel is a marco that was defined in Config.h. 
*/


/*
  "motorMovementHandler" is instead of the name of "DMA1_Channel3_IRQHandler"
  to verify clearly the purpose of the Handler is used for motor movement.
  
  The function is used to serve the motor movement in order.
*/
void motorMovementHandler(void){
  ListElement* temp;
  int i;
  ListElement* cur;
  stopDMA(DMA1_Channel3);
  triggerOutputData();  
  resetTCFlag;
  setDataNumber(DMA1_Channel3,3);

  for(i = motorRoot->count,cur = motorRoot->head ; i > 0 ; --i, cur = temp){
       temp = cur->next;
    if( hasCompleteUpdate( extractMotorConfigInfo(cur->args) ) ){
       linkedListRemove(motorRoot,cur);
       cur->callBack(cur->args);
       resetCommandCounter( extractMotorConfigInfo(cur->args) );
     }
  }
    
  if(!isDmaQueueEmpty){
   updateMotorDriveBuffer();
   startDMA(DMA1_Channel3);
  }

}

/*
  The function is used to set the instruction of motor movement.
*/
void motorController(MotorInfo* whichMotor){
   startCoroutine();
  while(1){
    recordCurrentTick(tickRecord1);
   	motorStep(whichMotor->motorConfiguration);
    yield();
    recordCurrentTick(tickRecord2);
    timerDelay(&(whichMotor->timerElement),getNewPeriod(whichMotor->period));
    yield();
   }
   endCoroutine();
}

/*
  The function is used to drive the motor in one step.
  Note: The function is only used in motorController.
*/
void motorStep(MotorConfigInfo* motorConfiguration){
  stopDMA(DMA_Channel);  // Before modified, the DMA must be stopped.
  
  dmaQueue(motorRoot,&motorConfiguration->motorElement);  //Add the Element into DMA Queue.
  
  if( DMA_Channel->CNDTR >= NumberOfMotor - motorConfiguration->slot ){  
    updateSlotCommand(motorConfiguration->slot);  // update the command of slot
  }
  
  startDMA(DMA_Channel); // After modified, the DMA should be started.
}

void motorSet(MotorInfo* whichMotor, uint8_t direation, uint8_t microstep){
   whichMotor->direation = direation;
   whichMotor->microstep = microstep;
   whichMotor->sleep = Motor_Sleep_Mode_Disable;    
   whichMotor->reset = Motor_Sleep_Reset_Disable;
   whichMotor->motorState = Motor_Enable;
   setUpCommand(whichMotor);
}

/*
  The function is used to initialize the "MotorConfigInfo" data type variable.
*/
MotorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot){
  MotorConfigInfo* detail = malloc(sizeof(MotorConfigInfo));
  detail->counter = 0;
  detail->slot = slot;
  detail->stepHighCommand = 0;
  detail->stepLowCommand = 0;
  detail->motorElement.next = NULL;
  detail->motorElement.prev = NULL;
  detail->motorElement.callBack = funcAddress;
  detail->motorElement.args = motorAddress;
  return detail;
}


/*
  The function is used to initialize the "MotorInfo" data type variable.
*/
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

/*

*/
void resetMotorDrive(void){
 uint8_t reset = StpMtr_Clockwise
		         |StpMtr_Low
		         |StpMtr_Slp_Off
		         |StpMtr_Rst_On
		         |StpMtr_Full_step
		         |StpMtr_Enable;
 SPI_I2S_SendData(SPI1,reset);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  triggerOutputData();
}

/*

*/
uint8_t getMotorSetUp(MotorInfo* whichMotor){
  return (whichMotor->direation
         |whichMotor->microstep 
         |whichMotor->sleep
         |whichMotor->reset
         |whichMotor->motorState);
}

/*

*/
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

/*

*/
uint8_t getMotorSetting(MotorInfo* whichMotor){
 return(whichMotor->direation
	    |whichMotor->sleep
    	|whichMotor->microstep
		|StpMtr_Rst_Off
		|StpMtr_Enable);
}

/*

*/
uint32_t getNewPeriod(uint32_t period){
  int32_t tick = period - getTickInterval();
  if( tick < 0 || tick == 0){
	  return 1;
  }else{
	  return tick;
  }
}

/*
  The Function is used to extract the data of variable 
  that data type is "motorConfigInfo". 

*/
MotorConfigInfo* extractMotorConfigInfo(void *args){
  MotorInfo* whichMotor = readMotorInfo(args);
  return (whichMotor->motorConfiguration);
}

/*
  The Function is used to set a varible which is 
  "MotorInfo" data type into timerElement.args.
*/
void setArgs(MotorInfo* whichMotor){
  whichMotor->timerElement.args = whichMotor;
}

/*

*/
void setPeriod(MotorInfo* whichMotor,int period){
	whichMotor->period = period;
}

/*
  The Function is used to set a function address into "whichMotorElement->callBack".
*/
void setCallBack(ListElement* whichMotorElement, void (*funcAddress) ){
   whichMotorElement->callBack = funcAddress;
}

/*

*/
void setUpCommand(MotorInfo* whichMotor){
   uint8_t motorSetup;
   motorSetup = getMotorSetUp(whichMotor); // Extract the motor setting that has already set in whichMotor.
   whichMotor->motorConfiguration->stepHighCommand = motorSetup|Motor_Step_High;
   whichMotor->motorConfiguration->stepLowCommand = motorSetup&Motor_Step_Low;
}

/*
  The Function is used to update the motorDriveBuffer 
  when the motor linked-list contained elements.
*/
void updateMotorDriveBuffer(void){
  ListElement* temp ;
  
  MotorConfigInfo* motorConfiguration;
  pointToHeadOfLinkedList(temp);
  do{
   motorConfiguration = extractMotorConfigInfo(temp->args);
   updateSlotCommand(motorConfiguration->slot);
   pointToNext(temp);
  }while( !isEndOfQueue );
  
}

/*

*/
void triggerOutputData(){
     GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Clock Low
     GPIO_SetBits(GPIOA, GPIO_Pin_4);   // Clock High
}






