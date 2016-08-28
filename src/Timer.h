#ifndef Timer_H
#define Timer_H

//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM standard Library
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
//Own Library
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "MockFunction.h"
#include "getTick.h"

#define stopTimer(x) (TIM_Cmd(x,DISABLE))
#define startTimer(x) (TIM_Cmd(x,ENABLE))
#define isTimerQueueEmpty (root->head == NULL)
#define callBackFunction(x) x->callBack(x->args)
#define resetTimerCounter(x) (TIM_SetCounter(x,0))
#define currActionTimeIsZero root->head->actionTime == 0
#define updateBaseTime  root->baseTime += root->head->actionTime
#define clearUpdateFlag(x) (TIM_ClearITPendingBit(x,TIM_IT_Update))
#define recordCurrentTime(x) (x = getTime(TIM2))



#define interval (whichMotor->timeRecord2 - whichMotor->timeRecord1)


#define updateCurrentTime root->curTime = root->baseTime + getTime(TIM2)

//#define recordCurrentTick(x) (x = getFakeTick() + root->baseTime )
#define recordCurrentTick(x) (x = getTick(TIM2) + root->baseTime )

extern uint16_t timeInterval;
extern uint16_t timeRecord1;
extern uint16_t timeRecord2;
extern uint16_t timeRecord3;



extern uint32_t tickRecord1;
extern uint32_t tickRecord2; 


void timerDelay(ListElement* timerElement,uint32_t period);
void timerSetExpiry(uint16_t period);
void _timerDelay(ListElement* timerElement,uint32_t period);

typedef struct{
   ListElement *next;
   ListElement *prev;
   void (*callBack)(void* unknown);
   void *args;
   uint16_t actionTime;
}TimerElement;

#endif // Timer_H
