#include "stepperMotor.h"
#include "Linklist.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

//STM standard Library
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
//Own Library
#include "RelativeTimeLinkList.h"
#include "projectStruct.h"
#include "Timer.h"





/**
 * Initialize the motor infomation.
*/

motorInfo* motorInit( void (*funcAddress),int period, int slot ){
   motorInfo* whichMotor = malloc(sizeof(motorInfo));  
   
   whichMotor->direation = StpMtr_Clockwise;
   whichMotor->step = StpMtr_Low;
   whichMotor->sleep = StpMtr_Slp_Off; 
   whichMotor->microstep = StpMtr_Full_step;
   whichMotor->reset = StpMtr_Rst_Off;
   whichMotor->motorState = StpMtr_Enable;
   
   whichMotor->period = period;
   whichMotor->state = 0;
   
   whichMotor->timerElement.next = NULL;
   whichMotor->timerElement.prev = NULL;
   whichMotor->timerElement.actionTime = 0;
   whichMotor->timerElement.callBack = funcAddress;
   whichMotor->timerElement.args = whichMotor;
   whichMotor->motorConfiguration = motorConfigInit(whichMotor,funcAddress,slot);
   return whichMotor;
}

motorConfigInfo* motorConfigInit(void* motorAddress, void (*funcAddress) ,int slot){
  motorConfigInfo* detail = malloc(sizeof(motorConfigInfo));
  detail->counter = 0;
  detail->slot = slot;
  detail->stepHighCommand = 0;
  detail->stepLowCommand = 0;
  detail->txElement.next = NULL;
  detail->txElement.prev = NULL;
  detail->txElement.callBack = funcAddress;
  detail->txElement.args = motorAddress;
  return detail;
}

/**
 * Set own address to args that was created in motorInfo struct.
*/
void setArgs(motorInfo* whichMotor){
  whichMotor->timerElement.args = whichMotor;
}
/**
 * Set some function address to callBack that was created in motorInfo struct.
*/
void setCallBack(struct ListElement* whichMotorElement, void (*funcAddress) ){
   whichMotorElement->callBack = funcAddress;
}

void setPeriod(motorInfo* whichMotor,int period){
	whichMotor->period = period;
}


uint8_t stdMtr_drive_conf(uint8_t dir, uint8_t slp_mode,uint8_t microstep){
  return (dir | StpMtr_Low |slp_mode | StpMtr_Rst_Off | microstep | StpMtr_Enable);
}


void sendConfToShiftReg(SPI_TypeDef* SPIx,uint16_t driver_conf){
  if(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) ){ // if TXE is 1, the while loop will stop
  SPIx->DR = driver_conf;
  }
}

void outputData(){
      GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Clock Low
      GPIO_SetBits(GPIOA, GPIO_Pin_4);   // Clock High
}

uint8_t getMotorSetting(motorInfo* whichMotor){
 return(whichMotor->direation
	    |whichMotor->sleep
    	|whichMotor->microstep
		|StpMtr_Rst_Off
		|StpMtr_Enable);
}

void resetMotorDrive(void){
 uint8_t reset = StpMtr_Clockwise
		         |StpMtr_Low
		         |StpMtr_Slp_Off
		         |StpMtr_Rst_On
		         |StpMtr_Full_step
		         |StpMtr_Enable;
 SPI_I2S_SendData(SPI1,reset);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  outputData();
}

