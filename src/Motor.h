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
#include "DMA.h"
#include "Motor.h"
#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "stepperMotor.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"

typedef struct{
  int slot;
  int counter;
  ListElement txElement;
  uint8_t stepHighCommand;
  uint8_t stepLowCommand;
}MotorConfigInfo;

typedef enum{
  THIRD_MOTOR,
  SECOND_MOTOR,
  FIRST_MOTOR
}MotorIdentify;

typedef enum{
  SLOT_0,
  SLOT_1,
  SLOT_2,
}MotorSlot;

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
  MotorConfigInfo* motorConfiguration;
}MotorInfo;   

typedef struct {
   ListElement *next;
   ListElement *prev;
   void (*callBack)(void* unknown);
   void *args;
}MotorElement;

void motorController(MotorInfo* whichMotor);
uint8_t getCommand(MotorConfigInfo* motorConfiguration);
void motorStep(MotorConfigInfo* motorConfiguration);
uint8_t getMotorSetUp(MotorInfo* whichMotor);
void setUpCommand(MotorInfo* whichMotor);
void motorSet(MotorInfo* whichMotor, uint8_t direation, uint8_t microstep);

/*
  The macros as shown at bottom are used to configure Motor Drive.
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


//DMA

#define cmarIsNotTXstorage DMA1_Channel3->CMAR != (uint32_t)txStorage
#define stepHigh 0x40
#define stepLow 0xBF
#define updateSlotCommand(x) (motorDriveBuffer[x] = getCommand(motorConfiguration))
#define pointToHeadOfLinkedList(x) (x = txRoot->head)
#define isEndOfQueue (temp == txRoot->head) 
#define pointToNext(x) (x = x->next)

#define hasCompleteUpdate(x) (x->counter >= 2)
#define isDmaQueueEmpty (txRoot->head == NULL)
#define resetCount(x) (x->counter = 0)
#define readMotorInfo(x) ((MotorInfo*)x)
#define resetCommandCounter(x) (x->counter = 0)
#define updateMotorConfigInfo(x) (x = readMotorConfigInfo(txRoot->head->args))
//motor
#define allowThirdMotorUpdate (motorConfiguration->slot == THIRD_MOTOR)
#define allowSecondMotorUpdate (motorConfiguration->slot == SECOND_MOTOR)
#define allowFirstMotorUpdate (motorConfiguration->slot == FIRST_MOTOR)
#define OneCommandTransmitted 2
#define noCommandTransmitted  3
#define transmittedStatus getDataNumber(DMA_Channel)
#define motorPosition motorConfiguration->slot
#define isDMAstarted(x) ( (x->CCR & 0x01) == 1)
// #define dmaQueue(x) (addList(txRoot,x))
extern uint8_t motorDriveBuffer[];
extern uint8_t txBuffer[];
extern uint8_t txStorage[];
extern Linkedlist *txRoot;

uint8_t getCommand(MotorConfigInfo* motorConfiguration);
MotorConfigInfo* readMotorConfigInfo(void *args);
void copyWholeInform(uint8_t buffer[],uint8_t storetage[]);
MotorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress),int slot);
// void dmaQueue(struct ListElement *txElement);

void cleanUpListedList(void);
void updateMotorDriveBuffer(void);
//stepperMotor
MotorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot);
uint8_t getMotorSetting(MotorInfo* whichMotor);
void outputData();
//DMA
MotorInfo* motorInit(void (*funcAddress),int period,int identity);
void setArgs(MotorInfo* whichMotor);
void setPeriod(MotorInfo* whichMotor,int period);
void setCallBack(ListElement* whichMotorElement, void (*funcAddress));
void sendConfToShiftReg(SPI_TypeDef* SPIx,uint16_t driver_conf);
uint8_t stdMtr_drive_conf(uint8_t dir, uint8_t slp_mode,uint8_t microstep);
void resetMotorDrive(void);


#endif //Motor_H
