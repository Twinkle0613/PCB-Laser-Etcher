#include "getTick.h"
#include "MockFunction.h"
#include "Motor.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "Timer_setting.h"
#include "projectStruct.h"
#include "peripherals.h"
#include "Linklist.h"
#include "Registers.h"
#include "Host.h"
#include "Timer.h"
#include "DMA_setting.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "DMA.h"
#include "unity.h"








MotorInfo motor;



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

  HostGpioA = ((void *)0);

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

}
