//Own Library
#include "SPI_setting.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "Coroutine.h"
#include "projectStruct.h"
//STM32F103 Standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
//General Library
#include <stdint.h>
#include <stdio.h>

void SPI1_DMA1_Channel_init(void);
void Tim2_init(void);
void SPI1_init(void);
struct Linkedlist *root;
void delay(int counter);
uint8_t txBuffer[];

int main(void)
{
  uint32_t time = 0;
  root = createLinkedList();
  motorInfo* motor1 = motorInit(motorControl);
  motorInfo* motor2 = motorInit(motorControl);
  motorInfo* motor3 = motorInit(motorControl);
  setPeriod(motor1,10000);
  setPeriod(motor2,10000);
  setPeriod(motor3,10000);

  SPI1_init();
  SPI1_DMA1_init();
  Tim2_init();

  //txBuffer[0] = 0x88; //Drive1&0xBF;
  //txBuffer[1] = 0x44; //Drive1|0x40;
  //txBuffer[2] = 0x22;

//  DMA_Cmd(DMA1_Channel3,ENABLE);


  //outputData();
  motor1->timerElement.callBack(motor1);
  motor2->timerElement.callBack(motor2);
  motor3->timerElement.callBack(motor3);
	//SPI1_init();
	//uint8_t Drive1 = stdMtr_drive_conf(StpMtr_Clockwise,StpMtr_Slp_Off,StpMtr_Full_step);
   // uint32_t checkDIER = TIM2->DIER;
   // uint32_t checkCR1 = TIM2->CR1;

	while(1)
    {
	 time = getTime(TIM2);
    }
}

void SPI1_DMA1_init(void){
  SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  DMA_conf(DMA1_Channel3,&(SPI1->DR),&txBuffer,DMA_DIR_PeripheralDST,3,
		   DMA_PeripheralDataSize_Byte,DMA_MemoryDataSize_Byte);
}

void Tim2_init(void){

    NVIC_EnableIRQ(TIM2_IRQn);  //TIM2 global Interrupt
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //Clear the update flag
    TIM_SetCounter(TIM2,0); // set CNT to 0
    TIM_UpdateRequestConfig(TIM2,TIM_UpdateSource_Regular);
    TIM_ARRPreloadConfig(TIM2,DISABLE);
    Timer_conf(TIM2,9000,TIM_CounterMode_Up,0xFFFF);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
   // TIM_Cmd(TIM2,ENABLE); // Disable Timer2
}

void SPI1_init(void){
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
	  GPIO_conf(GPIOA,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);   //SPI1_NSS
	  GPIO_conf(GPIOA,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_SCK
	  GPIO_conf(GPIOA,GPIO_Pin_6,Input_Mode,GPIO_Mode_IPU);           //SPI1_MISO
	  GPIO_conf(GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_MOSI
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
	  SPI_conf(SPI1,SPI_Mode_Master,SPI_DataSize_8b,SPI_BaudRatePrescaler_2,SPI_FirstBit_LSB,idle0_1Edge);
	  SPI_SSOutputCmd(SPI1,ENABLE);
	  enableSPI(SPI1,ENABLE);
}


void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 100; i++) {}
}


/*
 *DMA
 *uint32_t checkCCR = DMA1_Channel3->CCR;
  uint32_t checkCNDTR = DMA1_Channel3->CNDTR;
  uint32_t checkCPAR = DMA1_Channel3->CPAR;
  uint32_t checkCMAR = DMA1_Channel3->CMAR;
 *uint32_t checkTXbufferAdd = &txBuffer;
 *uint32_t   uint32_t checkISR = DMA1->ISR;
  //uint32_t checkSpiDR = SPI1->DR;
   *
 * */
