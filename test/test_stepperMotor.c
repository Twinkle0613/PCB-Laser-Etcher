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

void setUp(void)
{
  HostGpioA= malloc((sizeof(GPIO_TypeDef)));
}

void tearDown(void)
{
   free(HostGpioA);
   HostGpioA = NULL;
}

void test_motorInit_the_configuration_was_set_by_motorInit(void){
  
  motorInfo* whichMotor = motorInit();
  TEST_ASSERT_EQUAL(StpMtr_Clockwise,whichMotor->direation);
  TEST_ASSERT_EQUAL(StpMtr_Low,whichMotor->step);
  TEST_ASSERT_EQUAL(StpMtr_Slp_Off,whichMotor->sleep);
  TEST_ASSERT_EQUAL(StpMtr_Full_step,whichMotor->microstep);
  TEST_ASSERT_EQUAL(0,whichMotor->period);
  TEST_ASSERT_EQUAL(0,whichMotor->state);
  
  TEST_ASSERT_NULL(whichMotor->timerElement.next);
  TEST_ASSERT_NULL(whichMotor->timerElement.prev);
  TEST_ASSERT_NULL(whichMotor->timerElement.callBack);
  TEST_ASSERT_NULL(whichMotor->timerElement.motorID);
  TEST_ASSERT_EQUAL(0,whichMotor->timerElement.actionTime);
   
}

