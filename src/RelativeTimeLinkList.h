#ifndef RelativeTimeLinkList_H
#define RelativeTimeLinkList_H

#include "Linklist.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>


typedef struct{
  uint32_t baseTime;
  uint32_t currentTime;
  uint32_t rate;
}timeRecordList;

timeRecordList *recordTime(uint32_t baseTime, uint32_t currentTime, uint32_t rate);
void AddTimeList(timeRecordList *record, struct Linkedlist *newList);
void timerListAdd(struct Linkedlist *newList, uint32_t period);
void timerListDelete(struct ListElement* Node);
void findTheNodeNearPeriodForBase(struct ListElement **recordElement, uint32_t* collectActTime , uint32_t period);
#endif // RelativeTimeLinkList_H
