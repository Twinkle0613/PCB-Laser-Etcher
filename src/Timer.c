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
#include "MockFunction.h"

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
  	if( root->head->actionTime != recordCurActTime && root->head->actionTime > getFakeTick() ){
	  	timerSetExpiry(root->head->actionTime);
    }
  }

}

void timerSetExpiry(uint16_t period){
   TIM_SetAutoreload(TIM2,period);
}

//#include "Motor.h"
void TIM2_IRQHandler(){

  ListElement *temp1 = root->head;
  stopTimer(TIM2);
  clearUpdateFlag(TIM2);
  if( root->head->next != root->head){
     for(temp1 = root->head->next; ((temp1->next != root->head) && temp1->actionTime == 0) ; temp1 = temp1->next);      
     if(temp1->actionTime != 0){
      timerSetExpiry(temp1->actionTime); 
      startTimer(TIM2);
     }
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
 /*
  *
  * 	 ITStatus checkIT = TIM_GetITStatus(TIM2,TIM_IT_Update);

	  uint16_t checkCNT = TIM2->CNT;
	  uint16_t checkCNT2 = TIM2->CNT;
	  uint16_t checkARR;
	  clearUpdateFlag(TIM2);
	  TIM_SetCounter(TIM2,0); // set CNT to 0
	  TIM2->ARR = 10000;
	  checkARR = TIM2->ARR;
	  TIM_Cmd(TIM2,ENABLE); // Disable Timer2
	  checkCNT = TIM2->CNT;
	  while(TIM2->CNT < 9000 ){
	   checkCNT = TIM2->CNT;
	   checkIT = TIM_GetITStatus(TIM2,TIM_IT_Update);
	  }
	  checkCNT = TIM2->CNT;
	  while(TIM2->CNT < 9000 ){
	   checkCNT = TIM2->CNT;
	   checkIT = TIM_GetITStatus(TIM2,TIM_IT_Update);
	  }
  *
  *
  *
  *
  * */

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
