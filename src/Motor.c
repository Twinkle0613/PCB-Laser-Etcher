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

#define allowThirdMotorUpdate (motorConfiguration->slot == THIRD_MOTOR)
#define allowSecondMotorUpdate (motorConfiguration->slot == SECOND_MOTOR)
#define allowFirstMotorUpdate (motorConfiguration->slot == FIRST_MOTOR)
#define OneCommandTransmitted 2
#define noCommandTransmitted  3
#define transmittedStatus getDataNumber(DMA_Channel)
#define motorPosition motorConfiguration->slot
#define isDMAstarted(x) ( (x->CCR & 0x01) == 1)

/*
  DMA_Channel is a marco that was defined in Config.h. 

*/

void motorController(motorInfo* whichMotor){
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


void motorStep(motorConfigInfo* motorConfiguration){
  stopDMA(DMA_Channel);  // Before modified, the DMA must be stopped.
  
  dmaQueue(&motorConfiguration->txElement);  //Add the Element into DMA Queue.
  
  if( (Motor_Number - DMA_Channel->CNDTR) <= motorConfiguration->slot ){  
    updateSlotCommand(motorConfiguration->slot);  // update the command of slot
  }
  startDMA(DMA_Channel); // After modified, the DMA should be started.
}

uint8_t getMotorSetUp(motorInfo* whichMotor){
  return (whichMotor->direation
         |whichMotor->microstep 
         |whichMotor->sleep
         |whichMotor->reset
         |whichMotor->motorState);
}

void setUpCommand(motorInfo* whichMotor){
   uint8_t motorSetup;
   motorSetup = getMotorSetUp(whichMotor); // Extract the motor setting that has already set in whichMotor.
   whichMotor->motorConfiguration->stepHighCommand = motorSetup|Motor_Step_High;
   whichMotor->motorConfiguration->stepLowCommand = motorSetup&Motor_Step_Low;
}

void motorSet(motorInfo* whichMotor, uint8_t direation, uint8_t microstep){

   whichMotor->direation = direation;
   whichMotor->microstep = microstep;
   whichMotor->sleep = Motor_Sleep_Mode_Disable;    
   whichMotor->reset = Motor_Sleep_Reset_Disable;
   whichMotor->motorState = Motor_Enable;
   setUpCommand(whichMotor);

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
