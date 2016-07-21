#include "unity.h"
#include "Motor.h"
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
#include "Host.h"
#include "Registers.h"
#include "DMA.h"
#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "peripherals.h"
#include "Timer_setting.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void func1(void){
  
}

void test_getCommond_(void){
  motorInfo motor1; 
  motorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);;
  
  motorConfig->stepHighCommand = 0xFF;
  motorConfig->stepLowCommand = 0xF0;
  TEST_ASSERT_EQUAL(0xF0,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
  TEST_ASSERT_EQUAL(0xFF,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(0,motorConfig->counter);
  
}