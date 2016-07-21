//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM standard Library
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
//Own Library
#include "DMA.h"
#include "Motor.h"
#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#define isSlotNotEqualFirstMotor (motorConfiguration->slot != FIRST_MOTOR)
#define isSlotEqualThirdMotor (motorConfiguration->slot == THIRD_MOTOR)
#define motorPosition motorConfiguration->slot
#define isDMAstarted(x) (x->CCR & 0x01)

uint8_t getCommand(motorConfigInfo* motorConfiguration){
  uint8_t commond;
  if(motorConfiguration->counter == 0){
   commond = motorConfiguration->stepLowCommand;
   motorConfiguration->counter++;
  }else{
   commond = motorConfiguration->stepHighCommand;
   motorConfiguration->counter = 0;
  }
  return commond;
}


void motorStep(motorConfigInfo* motorConfiguration){

  dmaQueue(&motorConfiguration->txElement);  
  switch(getDataNumber()){
    case 3:
    if( !isDMAstarted(DMA1_Channel3) || isSlotNotEqualFirstMotor ){
     motorDriveBuffer[motorPosition] = getCommand(motorConfiguration);
    }    
    break;
    
    case 2:
    if(isSlotEqualThirdMotor){
     motorDriveBuffer[THIRD_MOTOR] = getCommand(motorConfiguration);
    }
    
    break;
    
    case 1:
    break;
    
    default:break;
  }
  setDataNumber(DMA1_Channel3,3);
  startDMA(DMA1_Channel3); 
}

