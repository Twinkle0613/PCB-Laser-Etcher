#include "unity.h"
#include "stepperMotor.h"
#include "Host.h"
#include "Registers.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include <malloc.h>
#include <stdio.h>
#include "projectStruct.h"


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

void test_motorInit_the_configuration_was_set_by_motorInit(void){
  motorInfo* whichMotor = motorInit(testMotor);
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
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->timerElement.motorID);
  TEST_ASSERT_EQUAL(0,whichMotor->timerElement.actionTime);
}

void test_setMotorID_(void){
  motorInfo* whichMotor = motorInit(testMotor);
  setMotorID(whichMotor);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->timerElement.motorID);
}

void test_setCallBack_(void){
  motorInfo* whichMotor = motorInit(testMotor);
  setCallBack(&whichMotor->timerElement,testMotor);
  whichMotor->timerElement.callBack(whichMotor);
  TEST_ASSERT_EQUAL(1,whichMotor->step);
  TEST_ASSERT_EQUAL(1,whichMotor->sleep);
}