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

#define stopTimer(x) (TIM_Cmd(x,DISABLE))
#define startTimer(x) (TIM_Cmd(x,ENABLE))
#define isTimerQueueEmpty (root->head == NULL)
#define callBackFunction(x) x->callBack(x->args)
#define resetTimerCounter(x) (TIM_SetCounter(x,0))
#define currActionTimeIsZero root->head->actionTime == 0
#define updateBaseTime  root->baseTime += root->head->actionTime
#define clearUpdateFlag(x) (TIM_ClearITPendingBit(x,TIM_IT_Update))
#define updateCurrentTime root->curTime = root->baseTime + getTime(TIM2)


void timerDelay(struct ListElement* timerElement,uint32_t period);
void timerSetExpiry(uint32_t period);

#endif // Timer_H