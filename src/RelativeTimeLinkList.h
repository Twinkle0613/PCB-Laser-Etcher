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
//void AddTimeList(uint32_t baseTime, uint32_t currentTime, uint32_t rate, struct Linkedlist *newList)；

#endif // RelativeTimeLinkList_H
