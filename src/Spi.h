#ifndef Spi_H
#define Spi_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"

#define Input_Mode 0x0

#define  idle0_1Edge  0
#define  idle0_2Edge  1
#define  idle1_1Edge  2
#define  idle1_2Edge  3


#define SPI_Enable ((uint16_t)0x0040)
#define SPI_Disable ((uint16_t)0xFFBF)

#define SPI_RXonlyMode_Enable ((uint16_t)0x0400)
#define SPI_RXonlyMode_Disable ((uint16_t)0xFBFF)

void SpiConfig(SPI_TypeDef* SPIx,
              uint16_t Mode,
              uint16_t DataSize,
              uint16_t BaudRatePrescaler,
              uint16_t FirstBit,
              uint16_t spi_clock
              );
              
              
#endif // Spi_H
