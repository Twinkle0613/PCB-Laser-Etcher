#ifndef __SPI_setting_H__
#define __SPI_setting_H__
#include <stdint.h>
#include "stm32f10x_spi.h"
#define Input_Mode 0x0

#define  idle0_1Edge  0
#define  idle0_2Edge  1
#define  idle1_1Edge  2
#define  idle1_2Edge  3


#define SPI_Enable ((uint16_t)0x0040)
#define SPI_Disable ((uint16_t)0xFFBF)

#define SPI_RXonlyMode_Enable ((uint16_t)0x0400)
#define SPI_RXonlyMode_Disable ((uint16_t)0xFBFF)

void enableSPI(SPI_TypeDef* SPIx,FunctionalState NewState);
void SPI_conf(SPI_TypeDef* SPIx,
              uint16_t Mode,
              uint16_t DataSize,
              uint16_t BaudRatePrescaler,
              uint16_t FirstBit,
              uint16_t spi_clock
              );

#endif //__SPI_setting_H__


/*
  GPIO setting for SPI1
  GPIO_conf(GPIOA,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_NSS
  GPIO_conf(GPIOA,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_SCK
  GPIO_conf(GPIOA,GPIO_Pin_6,Input_Mode,GPIO_Mode_IPU);           //SPI1_MISO
  GPIO_conf(GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_MOSI
*/
