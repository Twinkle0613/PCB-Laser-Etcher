#include "stepperMotor.h"
#include "Linklist.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"

#include "projectStruct.h"
/**
 * Initialize the motor infomation.
*/
motorInfo* motorInit(void){
   motorInfo* whichMotor = malloc(sizeof(motorInfo));  
   whichMotor->direation = StpMtr_Clockwise;
   whichMotor->step = StpMtr_Low;
   whichMotor->sleep = StpMtr_Slp_Off; 
   whichMotor->microstep = StpMtr_Full_step;
   whichMotor->period = 0;
   whichMotor->state = 0;
   whichMotor->timerElement.next = NULL;
   whichMotor->timerElement.prev = NULL;
   whichMotor->timerElement.actionTime = 0;
   whichMotor->timerElement.callBack = NULL;
   setMotorID(whichMotor);
   return whichMotor;
}

/**
 * Set own address to MotorID that was created in motorInfo struct.
*/
void setMotorID(motorInfo* whichMotor){
  whichMotor->timerElement.motorID = whichMotor;
}

/**
 * Set some function address to callBack that was created in motorInfo struct.
*/
void setCallBack(struct ListElement* whichMotorElement, void (*funcAddress) ){
   whichMotorElement->callBack = funcAddress;
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


