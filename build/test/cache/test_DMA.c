#include "getTick.h"
#include "MockFunction.h"
#include "RelativeTimeLinkList.h"
#include "peripherals.h"
#include "Linklist.h"
#include "Registers.h"
#include "Host.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Dma.h"
#include "unity.h"


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



void test_foo_(void){



  uint8_t motorDriveBuffer[3];

  uint8_t spi = 0;

  printf("&motorDriveBuffer = %x\n",&motorDriveBuffer);

  printf("motorDriveBuffer = %x\n",motorDriveBuffer);



  DmaConfig(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),(uint32_t)&spi,(uint32_t)&motorDriveBuffer,((uint32_t)0x00000010),3,((uint32_t)0x00000000),((uint32_t)0x00000000),((uint32_t)0x00000000));



  UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(45), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((&spi)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CPAR)), (((void *)0)), (_U_UINT)(46), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((&motorDriveBuffer)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CMAR)), (((void *)0)), (_U_UINT)(47), UNITY_DISPLAY_STYLE_INT);



}
