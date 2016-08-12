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
#include "Config.h"

#define timerDequeue(x) dequeue(x) //dequeue function can be found in RelativeTimeLinkList.c
#define nextActionTime ( getTime(TIM2) + root->head->actionTime)
#define newActionTime (root->head->actionTime + root->baseTime)
uint16_t timeRecord1;
uint16_t timeRecord2;
uint16_t timeRecord3;

void timerDelay(ListElement* timerElement,uint32_t period){

  updateCurrentTime;

  if(isTimerQueueEmpty){
	stopTimer(TIM2);
	TIM2->CNT = 0;
	timerSetExpiry(period);
	startTimer(TIM2);
	timerQueue(timerElement,period);
  }else{
    uint16_t recordCurActTime = root->head->actionTime;
	timerQueue(timerElement,period);
	if( root->head->actionTime != recordCurActTime && root->head->actionTime > getTime(TIM2) ){
		 timerSetExpiry( root->head->actionTime );
    }
  }


}

void timerSetExpiry(uint16_t period){
   TIM_SetAutoreload(TIM2,period);

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
	 stopTimer(TIM2);
	 timeRecord1 = getTime(TIM2) - timeRecord1;
	 timeRecord3 = getTime(TIM2);
     timerSetExpiry( root->head->actionTime - getTime(TIM2) );
     TIM2->CNT = 0;
     startTimer(TIM2);
   }else{
   	 //stopTimer(TIM2);
   }
}
