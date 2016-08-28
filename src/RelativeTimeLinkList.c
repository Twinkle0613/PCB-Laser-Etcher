//General Library
#include <stdint.h>
//STM32F1XX standard Library
#include "stm32f10x_tim.h"
//Own Library
#include "Linklist.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"

Linkedlist *root;


void timerQueue(ListElement *timerElement, uint32_t period){
    uint32_t wholeActTime = 0;   // To store the sum of timeELement value.
    uint32_t receiveInstrTime = 0;      // To store the difference between currentTime and prevTime
    uint32_t timeInterval = 0;      // To store the difference between wholeActTime and receiveInstrTime
    uint32_t newActTime = 0;     // To store the new timeElement value.
    uint32_t collectActTime = 0;
    ListElement* temp = 0;
    ListElement * recordElement; // To record the timeElement address
    
    if(root->head == NULL){  // if the root is NULL, timeELement is connected the root->head.

      updateActionTime(timerElement,period);
      addList(root,timerElement);
	  
    }else{

       wholeActTime = getWholeActionTime(root);
       receiveInstrTime = diffBtwCurTimeAndBaseTime(root);
       printf("receiveInstrTime = %d\n",receiveInstrTime);
       timeInterval = wholeActTime - receiveInstrTime;
       printf("timeInterval = %d\n",timeInterval);
       
       if( period > timeInterval){   //Condition: (period > timeInterval)       
         newActTime = period - timeInterval;
         updateActionTime(timerElement,newActTime);
         addList(root,timerElement);

       }else if( period < timeInterval){  //Condition: ( period < timeInterval) 
         recordElement = root->head;
         searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase);
         temp = recordElement;
         findLastZeroNode(recordElement); 
         
         newActTime = collectActTime - periodFromBase;
         printf("newActTime = %d\n",newActTime);
         
         if(newActTime != 0){
          updateActionTime(timerElement, temp->actionTime - newActTime);
          temp->actionTime = newActTime;
           if(temp == root->head){
               root->head = timerElement;
           }
          insertTimeElementIntoLeft(temp,timerElement);
         }else{
           updateActionTime(timerElement,newActTime);
            printf("recordElement->actionTime = %d\n",recordElement->actionTime);
           insertTimeElementIntoRight(recordElement,timerElement);
         }
         
       }else{  //Condition: ( period == timeInterval )     
           recordElement = root->head;
           searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase);
           findLastZeroNode(recordElement); 
           updateActionTime(timerElement,0);
           addList(root,timerElement);    
           
       }
    }
}



void updateCurTime(Linkedlist *newList,uint32_t curTime){
     newList->curTime = curTime;
}

void _updateBaseTime(Linkedlist *newList,uint32_t baseTime){
     newList->baseTime = baseTime;
}

void searchTheNodeActionTimeNearbyPeriodFromBase(ListElement **recordElement, uint32_t* collectActTime , uint32_t periodFrombase){
    while( (*collectActTime) < periodFrombase ){
        (*collectActTime) += (*recordElement)->actionTime;
        if( (*collectActTime) < periodFrombase ){
          (*recordElement) = (*recordElement)->next;
        }
    }
      
}

/*
 The AddTimeList function is used to manage stepper motor action time.
*/
uint32_t getWholeActionTime(Linkedlist *newList){
  uint32_t storeActTime = 0;
  ListElement * recordElement;
  recordElement = newList->head;
     do{
         storeActTime += recordElement->actionTime;
         recordElement = recordElement->next;
        }while(recordElement != newList->head);
  return storeActTime;
}


void updateActionTime(ListElement *timerElement, uint32_t newActTime){
  timerElement->actionTime = newActTime;
}

void insertTimeElementIntoLeft(ListElement *recordElement, ListElement *timerElement) {                                              
         timerElement->next = recordElement;
         timerElement->prev = recordElement->prev;
         recordElement->prev->next = timerElement;
         recordElement->prev = timerElement;                                  
                                         
}  

void insertTimeElementIntoRight(ListElement *recordElement, ListElement *timerElement) {                                              
           timerElement->next = recordElement->next;
           recordElement->next->prev = timerElement;  
           recordElement->next = timerElement;  
           timerElement->prev = recordElement;                              
                                         
} 

ListElement* dequeue(Linkedlist *root){
  ListElement *temp = root->head;
  updateHead(root);
  return temp;
}

void updateHead(Linkedlist *root){
  ListElement *temp = root->head;
  if(root->head->next == root->head){
	 root->head = NULL;
  }else{
	 root->head = root->head->next;
	 root->head->prev = temp->prev;
	 temp->prev->next = root->head;
  }
  temp->next = NULL;
  temp->prev = NULL;
}

/*
  timerListAdd() function Version 1  
*/
void timerListAdd(Linkedlist *newList, uint32_t period){
    uint32_t wholeActTime = 0;   // To store the sum of timeELement value.
    uint32_t receiveInstrTime = 0;      // To store the difference between currentTime and prevTime
    uint32_t timeInterval = 0;      // To store the difference between wholeActTime and receiveInstrTime
    uint32_t newActTime = 0;     // To store the new timeElement value.
    uint32_t collectActTime = 0;
    ListElement * recordElement; // To record the timeElement address

    if(newList->head == NULL){  // if the newList is NULL, timeELement is connected the newList->head.
      addTimeList(newList,period);  //Added timeELement to newList
	  }else{

       wholeActTime = getWholeActionTime(newList);
       receiveInstrTime = diffBtwCurTimeAndBaseTime(newList);
       timeInterval = wholeActTime - receiveInstrTime;

       if( period > timeInterval){   //Condition: (period > timeInterval)       
        printf("period > timeInterval\n");
        newActTime = period - timeInterval;
        addTimeList(newList,newActTime);
       }else if( period < timeInterval){  //Condition: ( period < timeInterval) 
         printf("period < timeInterval\n");
         recordElement = newList->head;
         searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase);
         findLastZeroNode(recordElement); 
         newActTime = collectActTime - periodFromBase;
         recordElement->actionTime = recordElement->actionTime - newActTime;
        
         if(recordElement->next == newList->head){
            addTimeList(newList,newActTime);
         }else{ 
           insertNode(recordElement,newActTime);
         }
         
       }else{  //Condition: ( period == timeInterval ) 
       
           recordElement = newList->head;
           searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase);
           findLastZeroNode(recordElement); 
           if(recordElement->next == newList->head){
             addTimeList(newList,0);
           }else{ 
             insertNode(recordElement,0);
           }
       }
    }
}



