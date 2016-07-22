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

#define allowThirdMotorUpdate (motorConfiguration->slot == THIRD_MOTOR)
#define allowSecondMotorUpdate (motorConfiguration->slot == SECOND_MOTOR)
#define allowFirstMotorUpdate (motorConfiguration->slot == FIRST_MOTOR)
#define OneCommandTransmitted 2
#define noCommandTransmitted  3
#define transmittedStatus getDataNumber(DMA1_Channel3)
#define motorPosition motorConfiguration->slot
#define isDMAstarted(x) ( (x->CCR & 0x01) == 1)

uint8_t getCommand(motorConfigInfo* motorConfiguration){
  uint8_t commond;
  if(motorConfiguration->counter == 0){
   commond = motorConfiguration->stepLowCommand;
  }else{
   commond = motorConfiguration->stepHighCommand;
  }
   motorConfiguration->counter++;
  return commond;
}

void motorStep(motorConfigInfo* motorConfiguration){
  dmaQueue(&motorConfiguration->txElement);  
 switch( transmittedStatus ){

    case noCommandTransmitted:
    if( !isDMAstarted(DMA1_Channel3) || !allowThirdMotorUpdate ){
     updateSlotCommand(motorConfiguration->slot);
    }
    break;
    
    case OneCommandTransmitted:
    if( allowFirstMotorUpdate ){
     updateSlotCommand(motorConfiguration->slot);
    }
    break;
    
    default:break;
  }
  startDMA(DMA1_Channel3); 
}

