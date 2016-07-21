//General Library
#include <malloc.h>
#include <stdint.h>
//STM standard Library
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
//Own Library
#include "Timer.h"
#include "DMA_setting.h"
#include "Coroutine.h"
#include "SPI_setting.h"
#include "stepperMotor.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"
#include "projectStruct.h"
#include "RelativeTimeLinkList.h"
#include "DMA.h"


// void motorControl(motorInfo* whichMotor){
   // startCoroutine();
  // while(1){

    // _timerDelay(&(whichMotor->timerElement),whichMotor->period);
    // yield();

   // }
   // endCoroutine();
// }

// void _timerDelay(struct ListElement* timerElement,uint32_t period){

 // if(root->head != NULL){
   // root->curTime = root->baseTime + getTime(TIM2);
 // }

 // timerQueue(timerElement,period);

 // if(root->head->next == root->head && root->callBackState == IS_FIRST_CALL){
  // TIM_SetAutoreload(TIM2,period);
  // TIM_Cmd(TIM2,ENABLE);
  // root->callBackState = NOT_FIRST_CALL;
 // }

// }

// void headPointToNext(struct Linkedlist *root){
  
  // struct ListElement *temp = root->head;
  
  // if(root->head->next == root->head){
	 // root->head = NULL;
  // }else{
	 // root->head = root->head->next;
	 // root->head->prev = temp->prev;
	 // temp->prev->next = root->head;
  // }
  // temp->next = NULL;
  // temp->prev = NULL;
// }




      
      

    
    


