#ifndef RelativeTimeLinkList_H
#define RelativeTimeLinkList_H

//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM32F1XX standard Library
#include "stm32f10x_tim.h"
//Own Library
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"

#define diffBtwCurTimeAndBaseTime(x) (x->curTime - x->baseTime)
#define addTimeList(x,y) { addList(x,createLinkedElement(y)); }
#define insertNode(x,y) {                                     \
         ListElement * temp = createLinkedElement(y);  \
         temp->next = x->next;                                \
         x->next = temp;                                      \
}  
#define periodFromBase (period + receiveInstrTime)

#define findLastZeroNode(x) {                                       \
    while(x->next->actionTime== 0){                                 \
    x = x->next;                                                    \
   }                                                                \
} 

extern Linkedlist *root;
void findTheNodeNearPeriodForBase(ListElement **recordElement, uint32_t* collectActTime , uint32_t period);
void updateHead(Linkedlist *root);
ListElement* dequeue(Linkedlist *root);
void updateCurTime(Linkedlist *newList,uint32_t curTime);
void _updateBaseTime(Linkedlist *newList,uint32_t baseTime);
void updateActionTime(ListElement *timerElement, uint32_t newActTime);
void insertTimeElement(ListElement *recordElement, ListElement *timerElement);
void timerQueue(ListElement *timerElement, uint32_t period);
void timerListAdd(Linkedlist *newList, uint32_t period);



#endif // RelativeTimeLinkList_H
