//General Library
#include <stdint.h>
#include <stdio.h>
//STM32F103 Standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
//Own Library
#include "Config.h"
#include "Motor.h"
#include "DMA.h"
#include "Timer.h"
#include "SPI_setting.h"
#include "stepperMotor.h"
#include "GPIO_setting.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "projectStruct.h"

void SPI1_DMA1_init(void);
void TIM_init(void);
void SPI_init(void);
Linkedlist *root;
void delay(int counter);
uint8_t motorDriveBuffer[Motor_Number];
uint8_t txBuffer[Motor_Number];
uint16_t timeInterval;
uint16_t timeRecord2 = 0;
uint16_t timeRecord1 = 0;
uint16_t timeRecord3 = 0;

void initializeTxBuffer(void);

int main(void)
{
  uint16_t checkActionTime = 0;
  uint16_t checkNextActionTime = 0;
  uint32_t time = 0;
  uint16_t timeInterval1 = 0;
  uint16_t checkTimeRecord1 = 0;
  uint16_t checkTimeRecord2 = 0;
  uint16_t checkTimeRecord3 = 0;
  uint16_t checkARR = 0;

  motorRoot = createLinkedList();
  root = createLinkedList();
  MotorInfo* motor1 = motorInit(motorController,6000,2);
  MotorInfo* motor2 = motorInit(motorController,2000,1);
  //MotorInfo* motor3 = motorInit(motorController,1000,0);
  initializeTxBuffer();
  SPI_init();
  SPI1_DMA1_init();
  TIM_init();
  resetMotorDrive();
  motorSet(motor1,Motor_Clockwise,Motor_Full_step);  
  motorSet(motor2,Motor_Clockwise,Motor_Full_step);
//  motorSet(motor3,Motor_Clockwise,Motor_Full_step);

  motor1->timerElement.callBack(motor1);
  motor2->timerElement.callBack(motor2);
  //motor3->timerElement.callBack(motor3);


	while(1)
    {
        checkTimeRecord1 = timeRecord1;
        checkTimeRecord2 = timeRecord2;
        checkTimeRecord3 = timeRecord3;
		timeInterval1 = getInterval(timeRecord1,timeRecord2);
		checkARR = TIM2->ARR;
		checkActionTime = root->head->actionTime;
		checkNextActionTime = root->head->next->actionTime;
	    time = getTime(TIM2);
    }
}

void SPI1_DMA1_init(void){
  SPI_I2S_DMACmd(SPI,SPI_I2S_DMAReq_Tx,ENABLE);
  NVIC_SetPriority(DMA1_Channel3_IRQn,0);
  uint32_t checkIntPriority = NVIC_GetPriority(DMA1_Channel3_IRQn);
  NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  DMA_DeInit(DMA1_Channel3);
  DMA_conf(DMA1_Channel3,&(SPI->DR),&motorDriveBuffer,DMA_DIR_PeripheralDST,3,
	       DMA_PeripheralDataSize_Byte,DMA_MemoryDataSize_Byte,DMA_Mode_Normal);
  DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);
}

void TIM_init(void){
	NVIC_SetPriority(TIM2_IRQn,0);
	uint32_t checkIntPriority = NVIC_GetPriority(TIM2_IRQn);
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

void SPI_init(void){

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
	  GPIO_conf(GPIO,NSS_PIN,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);   //SPI1_NSS
	  GPIO_conf(GPIO,SCLK_PIN,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_SCK
	  GPIO_conf(GPIO,MISO_PIN,Input_Mode,GPIO_Mode_IPU);           //SPI1_MISO
	  GPIO_conf(GPIO,MOSI_PIN,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_MOSI
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
	  SPI_conf(SPI,SPI_Mode_Master,SPI_DataSize_8b,SPI_BaudRatePrescaler_2,SPI_FirstBit_LSB,idle0_1Edge);
	  SPI_SSOutputCmd(SPI,ENABLE);
	  enableSPI(SPI,ENABLE);
}

void initializeTxBuffer(void){
  int i;
  for(i=0;i<3;i++){
  txBuffer[i] = StpMtr_Clockwise
		        |StpMtr_High
		        |StpMtr_Slp_Off
		        |StpMtr_Rst_Off
		        |StpMtr_Full_step
		        |StpMtr_Enable;
  }
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

/*
  // txBuffer[0] = 0x88; //Drive1&0xBF;
  // txBuffer[1] = 0x44; //Drive1|0x40;
  // txBuffer[2] = 0x22;
  // DMA_Cmd(DMA1_Channel3,ENABLE);
  // outputData();

  // uint32_t checkCCR = DMA1_Channel3->CCR;
 //  DMA_Cmd(DMA1_Channel3,DISABLE);

   uint32_t checkCNDTR = DMA1_Channel3->CNDTR;
   txBuffer[0] = 0xFF;
   txBuffer[1] = 0xAA;
   txBuffer[2] = 0xBB;
   uint32_t checkISR = DMA1->ISR;
   DMA_Cmd(DMA1_Channel3,ENABLE);
//   outputData();

   checkISR = DMA1->ISR;
   checkCNDTR = DMA1_Channel3->CNDTR;
   uint32_t checkCCR = DMA1_Channel3->CCR;
   DMA_Cmd(DMA1_Channel3,DISABLE);
   txBuffer[0] = 0x01; //Drive1&0xBF;
   txBuffer[1] = 0x10; //Drive1|0x40;
   txBuffer[2] = 0x20;
   setDataNumber(DMA1_Channel3,3);
   checkCNDTR = DMA1_Channel3->CNDTR;
   DMA_Cmd(DMA1_Channel3,ENABLE);
  // outputData();
 //  checkCNDTR = DMA1_Channel3->CNDTR;

*/
