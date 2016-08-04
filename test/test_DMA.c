#include "unity.h"
#include "DMA.h"


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
#include "DMA_setting.h"
#include "Timer.h"
#include "Host.h"
#include "Registers.h"
#include "Linklist.h"
#include "peripherals.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "Motor.h"


motorInfo motor;

void resetMotorDriveBuffer(void);
void setUp(void)
{
 HostGpioA= malloc((sizeof(GPIO_TypeDef)));
 HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));
 HostDma1 = malloc((sizeof(DMA_TypeDef)));
}

void tearDown(void)
{
  free(HostDma1_Channel3);
  free(HostDma1);
  free(HostGpioA);
  HostGpioA = NULL;
  HostDma1_Channel3 = NULL;
  HostDma1 = NULL;
}


