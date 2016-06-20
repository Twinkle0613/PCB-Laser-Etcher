#include "RelativeTimeLinkList.h"
#include "Linklist.h"
#include <stdint.h>


timeRecordList *recordTime(uint32_t baseTime, uint32_t currentTime, uint32_t rate){
  timeRecordList *record = malloc(sizeof(timeRecordList));
  record->baseTime = baseTime;
  record->currentTime =currentTime;
  record->rate = rate;
  return record;
}

// void AddTimeList(timeRecordList *record, struct ListElement *newElement){
  
// }



void AddTimeList(timeRecordList *record, struct Linkedlist *newList){
    uint32_t storeActTime = 0;
    
    if(newList->head == NULL){
      
      addList(newList,createLinkedElement(record->rate));
      
	  }else{
       
       if(newList->head->next == NULL){
         storeActTime = newList->head->actionTime;
         printf("storeActTime = %d\n",storeActTime);
       }else{
         for(newList->tail = newList->head; newList->tail != NULL ; newList->tail = newList->tail->next ){
         storeActTime += newList->tail->actionTime;
         printf("storeActTime = %d\n",storeActTime);
         }
       } 
         
        
       
      uint32_t interval1 = record->currentTime - record->baseTime;
      printf("interval1 = record->currentTime - record->baseTime = %d\n",interval1);
      uint32_t interval2 =  storeActTime - interval1;
      printf("interval2 =  storeActTime - interval1 = %d\n",interval2);
       
      if(record->rate > interval2){
       uint32_t nextActTime = record->rate - interval2;
        printf("nextActTime = record->rate - interval2 = %d\n",nextActTime);
       addList(newList,createLinkedElement(nextActTime));
      }
      
      
      
    }
    
}

