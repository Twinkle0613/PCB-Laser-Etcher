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
void motorController(motorInfo* whichMotor);
uint8_t getCommand(motorConfigInfo* motorConfiguration);
void motorStep(motorConfigInfo* motorConfiguration);
uint8_t getMotorSetUp(motorInfo* whichMotor);
void setUpCommand(motorInfo* whichMotor);
void motorSet(motorInfo* whichMotor, uint8_t direation, uint8_t microstep);

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

#endif //Motor_H
