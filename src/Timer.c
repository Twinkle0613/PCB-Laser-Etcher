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

#include "RelativeTimeLinkList.h"
#include "Config.h"
#include "MockFunction.h"


uint32_t tickRecord1;
uint32_t tickRecord2;

void timerDelay(ListElement* timerElement,uint32_t period){
    int recordTick;
  if(period != 0){  
    if(isTimerQueueEmpty){
      stopTimer(TIM2);
	    TIM_SetCounter(TIM2,0);
	    timerSetExpiry(period);
	    startTimer(TIM2);
      timerQueue(timerElement,period);
    }else{
      
      if(root->head->actionTime > period){ 
       stopTimer(TIM2);
       recordTick = getTick(TIM2);   //This command is used for real execution
       
       root->curTime = recordTick + root->baseTime; //update currrent time
       root->baseTime += recordTick;   // Update baseTime
       root->head->actionTime -= recordTick;
       
       timerQueue(timerElement,period);   
       TIM_SetCounter(TIM2,0);
       timerSetExpiry(root->head->actionTime);
       startTimer(TIM2);

      }else{
       root->curTime = getTick(TIM2) + root->baseTime;
       timerQueue(timerElement,period);   
      }
      
    }
  }else{
    
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
  if( root->head->next != root->head){
     for(temp1 = root->head->next; ((temp1->next != root->head) && temp1->actionTime == 0) ; temp1 = temp1->next);      
     if(temp1->actionTime != 0){
      TIM_SetCounter(TIM2,0);
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

uint32_t getTickInterval(void){
  if(tickRecord2 - tickRecord1 < 0){
	  tickRecord2 = tickRecord2;
  }else{
    return (tickRecord2 - tickRecord1);
  }
}

void TimerConfig(TIM_TypeDef* TIMx,
                uint16_t Prescaler,
                uint16_t CounterMode,
                uint16_t Period
              ){
  TIM_TimeBaseInitTypeDef timer;
  timer.TIM_Prescaler = Prescaler;
  timer.TIM_CounterMode = CounterMode;
  timer.TIM_Period = Period;
  timer.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIMx,&timer);
}
