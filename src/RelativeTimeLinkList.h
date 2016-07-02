#ifndef RelativeTimeLinkList_H
#define RelativeTimeLinkList_H

#include "Linklist.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "projectStruct.h"



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


void updateCurTime(struct Linkedlist *newList,uint32_t curTime);
void updateBaseTime(struct Linkedlist *newList,uint32_t baseTime);
void updateActionTime(struct ListElement *timerElement, uint32_t newActTime);
void insertTimeElement(struct ListElement *recordElement, struct ListElement *timerElement);
void newTimerListAdd(struct ListElement *timerElement, uint32_t period);
void timerListAdd(struct Linkedlist *newList, uint32_t period);
void timerListDelete(struct ListElement* Node);
void findTheNodeNearPeriodForBase(struct ListElement **recordElement, uint32_t* collectActTime , uint32_t period);


#endif // RelativeTimeLinkList_H
