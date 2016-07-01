#include "unity.h"
#include "ShiftReg.h"
#include "Registers.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "peripherals.h"
#include "Host.h"
#include <malloc.h>
#include <stdint.h>



void setUp(void)
{
  HostGpioA= malloc((sizeof(GPIO_TypeDef)));
}

void tearDown(void)
{
   free(HostGpioA);
   HostGpioA = NULL;
}

void test_GPIO_conf1(void){
  GPIOA->CRL = 0x0; //reset
  GPIO_conf1(GPIOA,GPIO_Pin_1,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
  GPIO_conf1(GPIOA,GPIO_Pin_0,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
  GPIO_conf1(GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);
  TEST_ASSERT_EQUAL_INT32(0x30000011,GPIOA->CRL);
}