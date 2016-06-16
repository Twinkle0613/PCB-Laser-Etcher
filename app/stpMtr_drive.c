#include "stpMtr_drive.h"
#include <stdint.h>
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"


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




