#include "Coroutine.h"
#include <malloc.h>
#include <stdint.h>
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"


void TIM2_IRQHandler(){
  updateHead(root);
  if(root->head != NULL){
   root->head->callBack(root->head->motorID);
  }
  
  
  
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void coroutine(motorInfo* whichMotor){
   startCoroutine();
  while(1){

    timerDelay(&(whichMotor->timerElement),10);
    yield();


   }
   endCoroutine();
}

void updateHead(struct Linkedlist *root){
  
  struct ListElement *temp = root->head;
  
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


void timerDelay(struct ListElement* timerElement,uint32_t period){
  //updateBaseTime(root,10);
  //updateCurTime(root,20);
  newTimerListAdd(timerElement,period);
  
  // yield();
}
      
      

    
    


