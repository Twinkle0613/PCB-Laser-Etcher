//General Library
#include "unity.h"
#include <malloc.h>
#include <stdio.h>
//STM standard Library
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"
//Own Library
#include "DMA_setting.h"
// #include "DMA.h"
#include "Host.h"
#include "Timer.h"
#include "Linklist.h"
#include "Registers.h"
#include "stepperMotor.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "Motor.h"

void setUp(void)
{
  HostGpioA= malloc((sizeof(GPIO_TypeDef)));
}

void tearDown(void)
{
   free(HostGpioA);
   HostGpioA = NULL;
}

void testMotor(motorInfo* whichMotor){
  whichMotor->step = 1;
  whichMotor->sleep = 1;
}

void test_motorInit_the_configuration_was_set_by_motorInit_every_setting_should_pass_the_test_(void){
  printf("No 1.0");
  motorInfo* whichMotor = motorInit(testMotor,0,0);
  /* Initialzation Motor */
  TEST_ASSERT_EQUAL(StpMtr_Clockwise,whichMotor->direation);
  TEST_ASSERT_EQUAL(StpMtr_Low,whichMotor->step);
  TEST_ASSERT_EQUAL(StpMtr_Slp_Off,whichMotor->sleep);
  TEST_ASSERT_EQUAL(StpMtr_Full_step,whichMotor->microstep);
  TEST_ASSERT_EQUAL(0,whichMotor->period);
  TEST_ASSERT_EQUAL(0,whichMotor->state);
  /* Initialzation Timer Elemenet */
  TEST_ASSERT_NULL(whichMotor->timerElement.next);
  TEST_ASSERT_NULL(whichMotor->timerElement.prev);
  TEST_ASSERT_EQUAL_PTR(testMotor,whichMotor->timerElement.callBack);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->timerElement.args);
  TEST_ASSERT_EQUAL(0,whichMotor->timerElement.actionTime);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->counter);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->slot);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->stepHighCommand);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->stepLowCommand);
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->txElement.next);
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->txElement.prev);
  TEST_ASSERT_EQUAL_PTR(testMotor,whichMotor->motorConfiguration->txElement.callBack);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->motorConfiguration->txElement.args);
  
}

void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){
  printf("No 1.1");
  motorInfo* whichMotor = motorInit(testMotor,0,FIRST_MOTOR);
  setCallBack(&whichMotor->timerElement,testMotor);
  whichMotor->timerElement.callBack(whichMotor);
  TEST_ASSERT_EQUAL(1,whichMotor->step);
  TEST_ASSERT_EQUAL(1,whichMotor->sleep);
}