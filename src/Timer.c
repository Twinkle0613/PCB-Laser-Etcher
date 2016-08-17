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

uint32_t tickRecord1;
uint32_t tickRecord2;

void timerDelay(ListElement* timerElement,uint32_t period){
  uint16_t recordCurActTime;
  updateCurrentTime;

  if(isTimerQueueEmpty){
	 stopTimer(TIM2);
	 TIM_SetCounter(TIM2,0);
	 timerSetExpiry(period);
	 startTimer(TIM2);
	 timerQueue(timerElement,period);
  }else{
   recordCurActTime = root->head->actionTime;
   timerQueue(timerElement,period);
  	if( root->head->actionTime != recordCurActTime && root->head->actionTime > getTime(TIM2) ){
	  	timerSetExpiry(root->head->actionTime);
    }
  }
}

void timerSetExpiry(uint16_t period){
   TIM_SetAutoreload(TIM2,period);
}

#include "Motor.h"
void TIM2_IRQHandler(){
 
  ListElement *temp1 = root->head;
  stopTimer(TIM2);
  clearUpdateFlag(TIM2);
  if( temp1->next != root->head){
    // while( temp1->next->actionTime == 0){
     // temp1 = temp1->next; 
    // }
     
      timerSetExpiry(root->head->next->actionTime);
      startTimer(TIM2);
     // }else{
       
     // }
  
  }
     
     
  
  
  
  ListElement *temp2;
  
  do{
   updateBaseTime;
   temp2 = timerDequeue(root);
   callBackFunction(temp2); 
  }while( !isTimerQueueEmpty && currActionTimeIsZero );


}

   /*
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
   */ 

uint32_t getTick(TIM_TypeDef* TIMx){
   return (root->baseTime + (TIMx->CNT&0x0000FFFF) );
}

uint32_t getTickInterval(void){
  
  if(tickRecord2 - tickRecord1 < 0){
    tickRecord2 = tickRecord2;
  }else{
    return (tickRecord2 - tickRecord1);
  }
}
