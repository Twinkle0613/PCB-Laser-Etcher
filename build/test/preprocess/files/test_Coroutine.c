#include "RelativeTimeLinkList.h"
#include "mock_MockFunction.h"
#include "CustomAssertion.h"
#include "Timer_setting.h"
#include "stepperMotor.h"
#include "peripherals.h"
#include "Coroutine.h"
#include "Registers.h"
#include "Linklist.h"
#include "Timer.h"
#include "Host.h"
#include "DMA_setting.h"
#include "DMA.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "unity.h"
























void setUp(void)

{

  HostGpioA= malloc((sizeof(GPIO_TypeDef)));

  HostTim2= malloc((sizeof(TIM_TypeDef)));

}



void tearDown(void)

{

   free(HostGpioA);

   free(HostTim2);

   HostGpioA = ((void *)0);

   HostTim2 = ((void *)0);

}



void testMotor123(motorInfo* whichMotor){

  whichMotor->step = 1;

  whichMotor->sleep = 1;

}
