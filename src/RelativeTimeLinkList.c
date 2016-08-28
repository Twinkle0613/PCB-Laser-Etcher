//General Library
#include <stdint.h>
//STM32F1XX standard Library
#include "stm32f10x_tim.h"
//Own Library
#include "Linklist.h"
#include "projectStruct.h"

#include "RelativeTimeLinkList.h"

Linkedlist *root;

/*
 The timerQueue function is used to sequence stepper motor action time.
*/
void timerQueue(ListElement *timerElement, uint32_t period){
    uint32_t wholeActTime = 0;     // To store the sum of timeELement value.
    uint32_t receiveInstrTime = 0; // To store the difference between currentTime and prevTime
    uint32_t timeInterval = 0;     // To store the difference between wholeActTime and receiveInstrTime
    uint32_t newActTime = 0;       // To store the new timeElement value.
    uint32_t collectActTime = 0;   // To store timElement value in searchTheNodeActionTimeNearbyPeriodFromBase(...) function.
    ListElement * recordElement;   // To record the timeElement address
    

    if(root->head == NULL){  // if the root is NULL, timeELement is pointed by root->head.

      updateActionTime(timerElement,period);
      addList(root,timerElement);
	  
    }else{

       wholeActTime = getTotalActionTime(root);   // To sum all timerElement value in link-list.
       receiveInstrTime = diffBtwCurTimeAndBaseTime(root); // To get the value between root->curTime and root->baseTime.
       timeInterval = wholeActTime - receiveInstrTime; 
       
       if( period > timeInterval){   //Condition: (period > timeInterval)       
         newActTime = period - timeInterval; // The different is the new timeElement value.
         updateActionTime(timerElement,newActTime); //update the actionTime of timerElement.
         addList(root,timerElement); // add the timerElement into link-list.

       }else if( period < timeInterval){  //Condition: ( period < timeInterval) 
         recordElement = root->head; //Before searching, the root->head is pointed by recordElement.
         searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase); // To find timeElement which the sum of timerElement 
                                                                                                     // from begin to destination is more than and near  
                                                                                                     // the value of periodFromBase.
         newActTime = collectActTime - periodFromBase; // The different is the new timeElement value.
         
         if(newActTime != 0){
          updateActionTime(timerElement, recordElement->actionTime - newActTime);  //Update the actionTime of timerElement.
          recordElement->actionTime = newActTime;
           if(recordElement == root->head){  // If recordElement is equal to root->head, 
               root->head = timerElement;    // timerElement that will add into link-list 
           }                                 // was pointed by root->head.
           insertTimeElementIntoBack(recordElement,timerElement); //Insert newTimerElement to the back of recordElement.
         }else{
           searchLastZeroTimerElement(&recordElement); //search the last of zero actionTime timerElement.
           updateActionTime(timerElement,0); //Update the actionTime of timerElement.
           insertTimeElementIntoFront(recordElement,timerElement);  //Insert newTimerElement to the front of recordElement.
         }
         
       }else{  //Condition: ( period == timeInterval )     
           
           recordElement = root->head; //Before searching, the root->head is pointed by recordElement.
           searchTheNodeActionTimeNearbyPeriodFromBase(&recordElement,&collectActTime,periodFromBase);
           //searchLastZeroTimerElement(&recordElement);
           updateActionTime(timerElement,0); //Change the actionTime of timerElement to 0.
           addList(root,timerElement);  //add the timerElement into link-list.
       }
    }
}

ListElement* dequeue(Linkedlist *root){
  ListElement *temp = root->head;
  updateHead(root);
  return temp;
}

void searchLastZeroTimerElement(ListElement **timerElement){
   while((*timerElement)->next->actionTime== 0){                                 
    (*timerElement) = (*timerElement)->next;                                                    
   }     
}

void searchTheNodeActionTimeNearbyPeriodFromBase(ListElement **recordElement, uint32_t* collectActTime , uint32_t periodFrombase){
    while( (*collectActTime) < periodFrombase ){
        (*collectActTime) += (*recordElement)->actionTime;
        if( (*collectActTime) < periodFrombase ){
          (*recordElement) = (*recordElement)->next;
        }
    }
      
}

void setCurrentTime(Linkedlist *newList,uint32_t curTime){
     newList->curTime = curTime;
}

void setBaseTime(Linkedlist *newList,uint32_t baseTime){
     newList->baseTime = baseTime;
}

void updateActionTime(ListElement *timerElement, uint32_t newActTime){
  timerElement->actionTime = newActTime;
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

void insertTimeElementIntoBack(ListElement *recordElement, ListElement *timerElement) {                                              
         timerElement->next = recordElement;
         timerElement->prev = recordElement->prev;
         recordElement->prev->next = timerElement;
         recordElement->prev = timerElement;                                  
                                         
}  

void insertTimeElementIntoFront(ListElement *recordElement, ListElement *timerElement) {                                              
           timerElement->next = recordElement->next;
           recordElement->next->prev = timerElement;  
           recordElement->next = timerElement;  
           timerElement->prev = recordElement;                              
                                         
} 


uint32_t getTotalActionTime(Linkedlist *newList){
  uint32_t storeActTime = 0;
  ListElement * recordElement;
  recordElement = newList->head;
     do{
         storeActTime += recordElement->actionTime;
         recordElement = recordElement->next;
        }while(recordElement != newList->head);
  return storeActTime;
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

       wholeActTime = getTotalActionTime(newList);
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
         searchLastZeroTimerElement(&recordElement);
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
           searchLastZeroTimerElement(&recordElement);
           if(recordElement->next == newList->head){
             addTimeList(newList,0);
           }else{ 
             insertNode(recordElement,0);
           }
       }
    }
}



