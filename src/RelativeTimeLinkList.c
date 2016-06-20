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
    uint32_t storeActTime = 0;
    uint32_t interval1 = 0;
    uint32_t interval2 = 0;
    uint32_t newActTime = 0;
    uint32_t store = 0;
    struct ListElement * element;
    
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
         
        
       
      interval1 = record->currentTime - record->baseTime;
      printf("interval1 = record->currentTime - record->baseTime = %d\n",interval1);
      
      if(interval1 == newList->head->actionTime){
      interval2 = storeActTime;
      }else{
      interval2 = storeActTime - interval1;
      printf("interval2 =  storeActTime - interval1 = %d\n",interval2);
      }
    
      
      if(record->rate > interval2){
       newActTime = record->rate - interval2;
       printf("newActTime = record->rate - interval2 = %d\n",newActTime);
       addList(newList,createLinkedElement(newActTime));
      }else if(record->rate < interval2){
        printf("Hello World\n");
        if(newList->head->next == NULL){
          newActTime = newList->head->actionTime - (record->rate + interval1);
          printf("newActTime = %d\n",newActTime);
          newList->head->actionTime = newList->head->actionTime - newActTime;
          addList(newList,createLinkedElement(newActTime));
          printf("newList->head->actionTime = %d\n",newList->head->actionTime);
        }else{
           element = newList->head;
           store = 0;
            printf("store = %d\n",store);
         while( store < (record->rate + interval1) && element != NULL ){
            store += element->actionTime;
            printf("element->actionTime = %d\n",element->actionTime);
            printf("store = %d\n",store);
            if(store < (record->rate + interval1) ){
                element = element->next;
            }
         }
           newActTime = store - (record->rate + interval1);
           printf("newActTime = store - (record->rate + interval1) = %d - %d = %d\n",storeActTime,(record->rate + interval1),newActTime);
           element->actionTime = element->actionTime - newActTime;
           
           if(element->next == NULL){
             addList(newList,createLinkedElement(newActTime));
             printf("element->actionTime = %d\n",element->actionTime);
           }else{
             struct ListElement * temp = createLinkedElement(newActTime);
             temp->next = element->next;
             element->next = temp;
           }
         
        }
        
        
        
      }
      
      
      
    }
    
}

