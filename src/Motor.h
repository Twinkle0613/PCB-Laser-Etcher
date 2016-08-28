#ifndef Motor_H
#define Motor_H

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
#include "Config.h"
#include "Dma.h"
#include "Motor.h"
#include "Timer.h"
#include "Linklist.h"

#include "stepperMotor.h"

#include "RelativeTimeLinkList.h"
#include "MockFunction.h"
#include "getTick.h"

typedef struct {
   ListElement *next;
   ListElement *prev;
   void (*callBack)(void* unknown);
   void *args;
}MotorElement;

typedef struct{
  int slot;
  int counter;
  ListElement motorElement;
  uint8_t stepHighCommand;
  uint8_t stepLowCommand;
}MotorConfigInfo;

typedef struct{
  int state;
  ListElement timerElement;
  uint32_t period;
  uint8_t direation;         
  uint8_t step;     
  uint8_t sleep;
  uint8_t reset;
  uint8_t motorState;
  uint8_t microstep;
  uint16_t timeRecord1;
  uint16_t timeRecord2;
  uint16_t timeRecord3;
  MotorConfigInfo* motorConfiguration;
}MotorInfo;   

/*
  The macros as shown at bottom are used to configure motorSet(...) function.
*/
#define Motor_Step_High  ((uint8_t)0x40)
#define Motor_Step_Low   ((uint8_t)0xBF)

#define Motor_Clockwise       ((uint8_t)0x80)
#define Motor_Anti_Clockwise  ((uint8_t)0x00)

#define Motor_Sleep_Mode_Enable   ((uint8_t)0x00)
#define Motor_Sleep_Mode_Disable  ((uint8_t)0x20)

#define Motor_Sleep_Reset_Enable  ((uint8_t)0x00)
#define Motor_Sleep_Reset_Disable ((uint8_t)0x10)

#define Motor_Full_step      ((uint8_t)0x00)
#define Motor_Half_step      ((uint8_t)0x08)
#define Motor_Quater_step    ((uint8_t)0x04)
#define Motor_Eighth_step    ((uint8_t)0x0C)
#define Motor_Sixteenth_step ((uint8_t)0x0E)

#define Motor_Enable   ((uint8_t)0x00)
#define Motor_Disable  ((uint8_t)0x01)


#define stepHigh 0x40
#define stepLow 0xBF
#define updateSlotCommand(x) (motorDriveBuffer[x] = getCommand(motorConfiguration))
#define pointToHeadOfLinkedList(x) (x = motorRoot->head)
#define isEndOfQueue (temp == motorRoot->head) 
#define pointToNext(x) (x = x->next)
#define hasCompleteUpdate(x) (x->counter >= 2)
#define isDmaQueueEmpty (motorRoot->head == NULL)
#define resetCount(x) (x->counter = 0)
#define readMotorInfo(x) ((MotorInfo*)x)
#define resetCommandCounter(x) (x->counter = 0)
#define updateMotorConfigInfo(x) (x = extractMotorConfigInfo(motorRoot->head->args))
#define motorMovementHandler DMA1_Channel3_IRQHandler

//Global Declaration
extern uint8_t motorDriveBuffer[];
extern Linkedlist *motorRoot;


//Execution
void motorController(MotorInfo* whichMotor);
void motorStep(MotorConfigInfo* motorConfiguration);
void motorSet(MotorInfo* whichMotor, uint8_t direation, uint8_t microstep);

//Initialization
MotorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot);
MotorInfo* motorInit(void (*funcAddress),int period,int identity);
void resetMotorDrive(void);

//Get Information
uint8_t getMotorSetUp(MotorInfo* whichMotor);
uint8_t getCommand(MotorConfigInfo* motorConfiguration);
uint8_t getMotorSetting(MotorInfo* whichMotor);
uint32_t getNewPeriod(uint32_t period);
MotorConfigInfo* extractMotorConfigInfo(void *args);

//Setting
void setArgs(MotorInfo* whichMotor);
void setPeriod(MotorInfo* whichMotor,int period);
void setCallBack(ListElement* whichMotorElement, void (*funcAddress));
void setUpCommand(MotorInfo* whichMotor);

//Others
void updateMotorDriveBuffer(void);
void triggerOutputData();



#endif //Motor_H
