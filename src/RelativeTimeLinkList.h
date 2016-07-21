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
#define addTimeList(x,y) { addListInCycle(x,createLinkedElement(y)); }
#define insertNode(x,y) {                                     \
         struct ListElement * temp = createLinkedElement(y);  \
         temp->next = x->next;                                \
         x->next = temp;                                      \
}  
#define periodFromBase (period + receiveInstrTime)

#define findLastZeroNode(x) {                                       \
    while(x->next->actionTime== 0){                                 \
    x = x->next;                                                    \
   }                                                                \
} 

extern struct Linkedlist *root;

void findTheNodeNearPeriodForBase(struct ListElement **recordElement, uint32_t* collectActTime , uint32_t period);
void updateHead(struct Linkedlist *root);
struct ListElement* timerDequeue(void);
void updateCurTime(struct Linkedlist *newList,uint32_t curTime);
void _updateBaseTime(struct Linkedlist *newList,uint32_t baseTime);
void updateActionTime(struct ListElement *timerElement, uint32_t newActTime);
void insertTimeElement(struct ListElement *recordElement, struct ListElement *timerElement);
void timerQueue(struct ListElement *timerElement, uint32_t period);
void timerListAdd(struct Linkedlist *newList, uint32_t period);
void timerListDelete(struct ListElement* Node);


#endif // RelativeTimeLinkList_H
