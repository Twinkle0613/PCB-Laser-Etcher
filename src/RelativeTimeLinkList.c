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


void AddTimeList(timeRecordList *record, struct Linkedlist *newList){
    uint32_t storeActTime = 0;   // To store the sum of timeELement value.
    uint32_t interval1 = 0;      // To store the difference between currentTime and prevTime
    uint32_t interval2 = 0;      // To store the difference between storeActTime and interval1
    uint32_t newActTime = 0;     // To store the new timeElement value.
    struct ListElement * recordElement; // To record the timeElement address

    if(newList->head == NULL){  // if the newList is NULL, timeELement is connected the newList->head.
      addList(newList,createLinkedElement(record->rate));  //Added timeELement to newList
	  }else{

       if(newList->head->next == NULL){ //if the newList got only one timeELement, storeActTime is stored that timeELement value.
         storeActTime = newList->head->actionTime;
       }else{
         for(newList->tail = newList->head; newList->tail != NULL ; newList->tail = newList->tail->next ){
         storeActTime += newList->tail->actionTime;
         }
       } 
       
       
      interval1 = record->currentTime - record->baseTime;
     
     if(interval1 == newList->head->actionTime){ // the interval1 is equal to the value of first timeELement of newList.
      interval2 = storeActTime;
      }else{
      interval2 = storeActTime - interval1;
      }
      
      if(record->rate > interval2){   //Condition: ( new timeELement rate > interval2)
       newActTime = record->rate - interval2;
       addList(newList,createLinkedElement(newActTime));
      }else if(record->rate < interval2){  //Condition: (new timeELement rate < interval2) 
        
        if(newList->head->next == NULL){  
          newActTime = newList->head->actionTime - (record->rate + interval1);
          newList->head->actionTime = newList->head->actionTime - newActTime;
          addList(newList,createLinkedElement(newActTime));
        }else{
           recordElement = newList->head;
           storeActTime = 0;
         while( storeActTime < (record->rate + interval1) && recordElement != NULL ){
            storeActTime += recordElement->actionTime;
            if(storeActTime < (record->rate + interval1) ){
                recordElement = recordElement->next;
            }
         }
           newActTime = storeActTime - (record->rate + interval1);
           recordElement->actionTime = recordElement->actionTime - newActTime;
           if(recordElement->next == NULL){
             addList(newList,createLinkedElement(newActTime));
           }else{ 
             struct ListElement * temp = createLinkedElement(newActTime);
             temp->next = recordElement->next;
             recordElement->next = temp;
           }
        }
      }
    }
}

