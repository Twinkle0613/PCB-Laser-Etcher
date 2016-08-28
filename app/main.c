//General Library
#include <stdint.h>
#include <stdio.h>
//STM32F103 Standard Library
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
//Own Library
#include "Config.h"
#include "Motor.h"
#include "Dma.h"
#include "Timer.h"
#include "Spi.h"
#include "Gpio.h"
#include "RelativeTimeLinkList.h"


/*  Global Declaration
 *
 * "Motor.h"
 *extern uint8_t motorDriveBuffer[];
 *extern Linkedlist *motorRoot;
 *
 * "Timer.h"
 *extern uint32_t tickRecord1;
 *extern uint32_t tickRecord2;
 *
 * "RelativeTimeLinkList"
 *extern Linkedlist *root;
 *
 * */

void SPI1_DMA1_init(void);
void TIM_init(void);
void SPI_init(void);


// Buffer Size For Motor
uint8_t motorDriveBuffer[NumberOfMotor];

// Clear Record
uint32_t tickRecord1 = 0;
uint32_t tickRecord2 = 0;

//Declare Motor
MotorInfo* motor4;
MotorInfo* motor3;
MotorInfo* motor2;
MotorInfo* motor1;
MotorInfo* motor0;

int main(void)
{
  // Checking Element
  //uint16_t checkActionTime = 0;
 // uint32_t time = 0;
  //uint16_t timeInterval1 = 0;
  //uint16_t checkARR = 0;

  // Initialize Linked List
   motorRoot = createLinkedList();
   root = createLinkedList();

   // Initialize Motor
  //motor4 = motorInit(motorController,100,4);
  //motor3 = motorInit(motorController,100,3);
  motor2 = motorInit(motorController,2,2);
  motor1 = motorInit(motorController,10,1);
  motor0 = motorInit(motorController,100,0);

  // Initialize Peripherals
  SPI_init();
  SPI1_DMA1_init();
  TIM_init();
  resetMotorDrive();

  // Configure Motor
 // motorSet(motor4,Motor_Clockwise,Motor_Full_step);
  //motorSet(motor3,Motor_Clockwise,Motor_Full_step);
  motorSet(motor2,Motor_Clockwise,Motor_Full_step);
  motorSet(motor1,Motor_Anti_Clockwise,Motor_Full_step);
  motorSet(motor0,Motor_Clockwise,Motor_Full_step);

 // Start Execution
  //motor4->timerElement.callBack(motor4);
  //motor3->timerElement.callBack(motor3);
  motor2->timerElement.callBack(motor2);
  motor1->timerElement.callBack(motor1);
  motor0->timerElement.callBack(motor0);

	while(1)
    {
	// checkARR = TIM2->ARR;
	// checkActionTime = root->head->actionTime;
	// timeInterval1 = getTickInterval();
	 //time = getTick(TIM2);
    }
}

void SPI1_DMA1_init(void){
  SPI_I2S_DMACmd(SPI,SPI_I2S_DMAReq_Tx,ENABLE);
  NVIC_SetPriority(DMA1_Channel3_IRQn,0);
  NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  DMA_DeInit(DMA1_Channel3);
  DmaConfig(DMA1_Channel3,(uint32_t)&(SPI->DR),(uint32_t)&motorDriveBuffer,DMA_DIR_PeripheralDST,3,
	       DMA_PeripheralDataSize_Byte,DMA_MemoryDataSize_Byte,DMA_Mode_Normal);
  DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);
}

void TIM_init(void){
	NVIC_SetPriority(TIM2_IRQn,0);
	NVIC_EnableIRQ(TIM2_IRQn);  //TIM2 global Interrupt
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2 ,DISABLE);
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //Clear the update flag
    TIM_SetCounter(TIM2,0); // set CNT to 0
    TIM_UpdateRequestConfig(TIM2,TIM_UpdateSource_Regular);
    TIM_ARRPreloadConfig(TIM2,DISABLE);
    TimerConfig(TIM2,9000,TIM_CounterMode_Up,0xFFFF);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
   // TIM_Cmd(TIM2,ENABLE); // Disable Timer2
}

void SPI_init(void){
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
	  GpioConfig(GPIO,NSS_PIN,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);   //SPI1_NSS
	  GpioConfig(GPIO,SCLK_PIN,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_SCK
	  GpioConfig(GPIO,MISO_PIN,Input_Mode,GPIO_Mode_IPU);           //SPI1_MISO
	  GpioConfig(GPIO,MOSI_PIN,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_MOSI
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
	  SpiConfig(SPI,SPI_Mode_Master,SPI_DataSize_8b,SPI_BaudRatePrescaler_2,SPI_FirstBit_LSB,idle0_1Edge);
	  SPI_SSOutputCmd(SPI,ENABLE);
	  SPI_Cmd(SPI,ENABLE);
}


