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
#include "SPI_setting.h"

void TIM2_IRQHandler(){
  struct ListElement *temp;
  TIM_Cmd(TIM2,DISABLE);
  TIM_SetCounter(TIM2,0); // set CNT to 0

  do{
   temp = root->head;
   root->baseTime += root->head->actionTime; // record the previous time of node
   headPointToNext(root); // the Head point to next node
   temp->callBack(temp->motorID); // call the function of previous node
  }while(root->head != NULL && root->head->actionTime == 0);

   if(root->head == NULL)
	   TIM_Cmd(TIM2,DISABLE);
   else 
     TIM_SetAutoreload(TIM2,root->head->actionTime);

   TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
   TIM_Cmd(TIM2,ENABLE);
}

void motorControl(motorInfo* whichMotor){
   startCoroutine();
  while(1){

    timerDelay(&(whichMotor->timerElement),whichMotor->period);
    yield();

   }
   endCoroutine();
}

void timerDelay(struct ListElement* timerElement,uint32_t period){

 if(root->head != NULL){
   root->curTime = root->baseTime + getTime(TIM2);
 }

 newTimerListAdd(timerElement,period);

 if(root->head->next == root->head && root->callBackState == IS_FIRST_CALL){
  TIM_SetAutoreload(TIM2,period);
  TIM_Cmd(TIM2,ENABLE);
  root->callBackState = NOT_FIRST_CALL;
 }

}

void headPointToNext(struct Linkedlist *root){
  
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

uint8_t getMotorSetting(motorInfo* whichMotor){
 return( whichMotor->direation| \
		 whichMotor->sleep| \
		 whichMotor->microstep| \
		 StpMtr_Rst_Off | \
		 StpMtr_Enable );
}


      
      

    
    


