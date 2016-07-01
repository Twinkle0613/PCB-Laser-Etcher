#ifndef RelativeTimeLinkList_H
#define RelativeTimeLinkList_H

#include "Linklist.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

extern struct Linkedlist *root;

typedef struct{
  uint32_t baseTime;
  uint32_t currentTime;
  uint32_t rate;
}timeRecordList;

void updateActionTime(struct ListElement *timerElement, uint32_t newActTime);
void insertTimeElement(struct ListElement *recordElement, struct ListElement *timerElement);
timeRecordList *recordTime(uint32_t baseTime, uint32_t currentTime, uint32_t rate);
void newTimerListAdd(struct ListElement *timerElement, uint32_t period);
void AddTimeList(timeRecordList *record, struct Linkedlist *newList);
void timerListAdd(struct Linkedlist *newList, uint32_t period);
void timerListDelete(struct ListElement* Node);
void findTheNodeNearPeriodForBase(struct ListElement **recordElement, uint32_t* collectActTime , uint32_t period);


#endif // RelativeTimeLinkList_H
