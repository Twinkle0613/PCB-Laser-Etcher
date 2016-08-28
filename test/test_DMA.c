#include "unity.h"
#include "Dma.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
//Own Library

//#include "Timer.h"
#include "Host.h"
#include "Registers.h"
#include "Linklist.h"
#include "peripherals.h"
#include "RelativeTimeLinkList.h"
#include "MockFunction.h"
#include "getTick.h"

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

void test_foo_(void){
    
  uint8_t motorDriveBuffer[3];
  uint8_t spi = 0;
  printf("&motorDriveBuffer = %x\n",&motorDriveBuffer);
  printf("motorDriveBuffer = %x\n",motorDriveBuffer);
  
  DmaConfig(DMA1_Channel3,(uint32_t)&spi,(uint32_t)&motorDriveBuffer,DMA_DIR_PeripheralDST,3,DMA_PeripheralDataSize_Byte,DMA_MemoryDataSize_Byte,DMA_Mode_Normal);
  //TEST_ASSERT_EQUAL(DMA_DIR_PeripheralDST|DMA_PeripheralDataSize_Byte|DMA_MemoryDataSize_Byte|DMA_Mode_Normal,DMA1_Channel3->CCR);
  TEST_ASSERT_EQUAL(3,DMA1_Channel3->CNDTR);
  TEST_ASSERT_EQUAL(&spi,DMA1_Channel3->CPAR);
  TEST_ASSERT_EQUAL(&motorDriveBuffer,DMA1_Channel3->CMAR);
  
}