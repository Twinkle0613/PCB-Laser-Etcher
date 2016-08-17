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
#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "Config.h"
/*
  DMA_Channel is a marco that was defined in Config.h. 
*/
#define interval1 (whichMotor->timeRecord2 + whichMotor->timeRecord3)
uint8_t motorDriveBuffer[3];
Linkedlist *motorRoot;

/*
  The function is used to set the instruction of motor movement.
*/

uint16_t getInterval(uint16_t timeRecord1, uint16_t timeRecord2){
	if( timeRecord1 > timeRecord2 ){
	  return (timeRecord1 + timeRecord2);
	}else if( timeRecord1 < timeRecord2 ){
	  return (timeRecord2 - timeRecord1);
	}else{
	  return 0;
	}
}

void motorController(MotorInfo* whichMotor){
   startCoroutine();
  while(1){
	  //recordCurrentTime(timeRecord1);
    recordCurrentTick(tickRecord1);
   	motorStep(whichMotor->motorConfiguration);
    yield();
    //recordCurrentTime(timeRecord2);
    recordCurrentTick(tickRecord2);
    //getTickInterval();
    //getInterval(timeRecord1,timeRecord2);
    timerDelay(&(whichMotor->timerElement),whichMotor->period - getInterval(timeRecord1,timeRecord2) );
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
  
  dmaQueue(&motorConfiguration->motorElement);  //Add the Element into DMA Queue.
  
  if( DMA_Channel->CNDTR >= Motor_Number - motorConfiguration->slot ){  
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

/*
  "motorMovementHandler" is instead of the name of "DMA1_Channel3_IRQHandler"
  to verify clearly the purpose of the Handler is used for motor movement.
  
  The function is used to serve the motor movement in order.
  
  "Personal reference"
     while(!isDmaQueueEmpty && hasCompleteUpdate(motorConfig) ){ 
     temp = dmaDequeue(motorRoot);
     resetCommandCounter(readMotorConfigInfo(temp->args));
     callBackFunction(temp);
     if(!isDmaQueueEmpty){
       updateMotorConfigInfo(motorConfig);
     }
   }
  
*/
void motorMovementHandler(void){
  MotorConfigInfo* motorConfig = extractMotorConfigInfo(motorRoot->head->args);
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
 *
 *   uint16_t checkCNT;
  uint16_t checkARR;
  TIM_SetCounter(TIM2,0); // set CNT to 0
  TIM2->ARR = 20000;
  checkARR = TIM2->ARR;
  TIM_Cmd(TIM2,ENABLE); // Disable Timer2
  checkCNT = TIM2->CNT;
  while(TIM2->CNT < 19000 ){
   checkCNT = TIM2->CNT;
  }
  checkCNT = TIM2->CNT;
 *
 * */

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
  The Function is used to extract the data of variable 
  that data type is "motorConfigInfo". 

*/
MotorConfigInfo* extractMotorConfigInfo(void *args){
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
  The Function is used to set a varible which is 
  "MotorInfo" data type into timerElement.args.
*/
void setArgs(MotorInfo* whichMotor){
  whichMotor->timerElement.args = whichMotor;
}

/*
  The Function is used to set a function address into "whichMotorElement->callBack".
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


void triggerOutputData(){
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
  triggerOutputData();
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
