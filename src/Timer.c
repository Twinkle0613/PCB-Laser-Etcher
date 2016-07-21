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


void timerDelay(struct ListElement* timerElement,uint32_t period){
  updateCurrentTime;
  if(isTimerQueueEmpty){
    timerSetExpiry(period);
  }
   timerQueue(timerElement,period);
}

void timerSetExpiry(uint32_t period){
   TIM_SetAutoreload(TIM2,period);
   startTimer(TIM2);
}

void TIM2_IRQHandler(){
  struct ListElement *temp;
  stopTimer(TIM2);
  resetTimerCounter(TIM2);
  
  do{
   updateBaseTime; 
   temp = timerDequeue();
   callBackFunction(temp); 
  }while( !isTimerQueueEmpty && currActionTimeIsZero );

   clearUpdateFlag(TIM2);
   
   if(!isTimerQueueEmpty){
     timerSetExpiry(root->head->actionTime);
   }else{
   	 stopTimer(TIM2);
   }
}
