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

void updateCurTime(Linkedlist *newList,uint32_t curTime){
     newList->curTime = curTime;
}

void _updateBaseTime(Linkedlist *newList,uint32_t baseTime){
     newList->baseTime = baseTime;
}

void findTheNodeNearPeriodForBase(ListElement **recordElement, uint32_t* collectActTime , uint32_t periodFrombase){
    while( (*collectActTime) < periodFrombase ){
        (*collectActTime) += (*recordElement)->actionTime;
        if( (*collectActTime) < periodFrombase ){
          (*recordElement) = (*recordElement)->next;
        }
    }
   findLastZeroNode((*recordElement));     
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

void insertTimeElement(ListElement *recordElement, ListElement *timerElement) {                                     
         timerElement->next = recordElement->next;                                
         recordElement->next = timerElement;                                      
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
        newActTime = period - timeInterval;
        addTimeList(newList,newActTime);
       }else if( period < timeInterval){  //Condition: ( period < timeInterval) 
         
         recordElement = newList->head;
         findTheNodeNearPeriodForBase(&recordElement,&collectActTime,periodFromBase);
         newActTime = collectActTime - periodFromBase;
         recordElement->actionTime = recordElement->actionTime - newActTime;
        
         if(recordElement->next == newList->head){
            addTimeList(newList,newActTime);
         }else{ 
           insertNode(recordElement,newActTime);
         }
         
       }else{  //Condition: ( period == timeInterval ) 
       
           recordElement = newList->head;
           findTheNodeNearPeriodForBase(&recordElement,&collectActTime,periodFromBase);
           
           if(recordElement->next == newList->head){
             addTimeList(newList,0);
           }else{ 
             insertNode(recordElement,0);
           }
       }
    }
}


/*
  timerListAdd() function Version 2  
*/
void timerQueue(ListElement *timerElement, uint32_t period){
    uint32_t wholeActTime = 0;   // To store the sum of timeELement value.
    uint32_t receiveInstrTime = 0;      // To store the difference between currentTime and prevTime
    uint32_t timeInterval = 0;      // To store the difference between wholeActTime and receiveInstrTime
    uint32_t newActTime = 0;     // To store the new timeElement value.
    uint32_t collectActTime = 0;
    ListElement * recordElement; // To record the timeElement address

    if(root->head == NULL){  // if the root is NULL, timeELement is connected the root->head.

      updateActionTime(timerElement,period);
      addList(root,timerElement);
	  
    }else{

       wholeActTime = getWholeActionTime(root);
       receiveInstrTime = diffBtwCurTimeAndBaseTime(root);
       timeInterval = wholeActTime - receiveInstrTime;

       if( period > timeInterval){   //Condition: (period > timeInterval)       
     
         newActTime = period - timeInterval;
         updateActionTime(timerElement,newActTime);
         addList(root,timerElement);

       }else if( period < timeInterval){  //Condition: ( period < timeInterval) 
     
         recordElement = root->head;
         findTheNodeNearPeriodForBase(&recordElement,&collectActTime,periodFromBase);
         newActTime = collectActTime - periodFromBase;
         recordElement->actionTime = recordElement->actionTime - newActTime;
        
          updateActionTime(timerElement,newActTime);
         if(recordElement->next == root->head){
               
         addList(root,timerElement);
         }else{ 
         
          insertTimeElement(recordElement,timerElement);
         }
         
       }else{  //Condition: ( period == timeInterval ) 
           recordElement = root->head;
           findTheNodeNearPeriodForBase(&recordElement,&collectActTime,periodFromBase);
           updateActionTime(timerElement,0);
           addList(root,timerElement);
           
       }
    }
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





