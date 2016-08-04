//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM32F1XX standard Library
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
//Own Library
#include "Timer.h"
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"

#define timerDequeue(x) dequeue(x) //dequeue function can be found in RelativeTimeLinkList.c
#define nextActionTime ( getTime(TIM2) + root->head->actionTime)
#define newActionTime (root->head->actionTime + root->baseTime)

void timerDelay(ListElement* timerElement,uint32_t period){
  updateCurrentTime;
  if(isTimerQueueEmpty){
    timerSetExpiry(period);
  }
   timerQueue(timerElement,period);
}

void timerSetExpiry(uint16_t period){
   TIM_SetAutoreload(TIM2,period);
   startTimer(TIM2);
}

void TIM2_IRQHandler(){
  clearUpdateFlag(TIM2);
  ListElement *temp;

  do{
   updateBaseTime; 
   temp = timerDequeue(root);
   callBackFunction(temp); 
  }while( !isTimerQueueEmpty && currActionTimeIsZero );


   if(!isTimerQueueEmpty){

     timerSetExpiry(root->head->actionTime  );
   }else{
   	// stopTimer(TIM2);
   }
}
