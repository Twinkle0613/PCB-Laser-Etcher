#include "SPI_setting.h"
#include <stdint.h>
#include "stm32f10x_spi.h"


void enableSPI(SPI_TypeDef* SPIx,FunctionalState NewState){
  if (NewState != DISABLE)
  {
    SPIx->CR1 |= SPI_Enable;
  }
  else
  {
    SPIx->CR1 &= SPI_Disable;
  }
}


void SPI_conf(SPI_TypeDef* SPIx,
              uint16_t Mode,
              uint16_t DataSize,
              uint16_t BaudRatePrescaler,
              uint16_t FirstBit,
              uint16_t spi_clock
              ){
                
  SPI_InitTypeDef spi;
  spi.SPI_Mode = Mode;
  spi.SPI_DataSize = DataSize;
  spi.SPI_BaudRatePrescaler = BaudRatePrescaler;
  spi.SPI_FirstBit = FirstBit;
  switch(spi_clock){
    case 0:
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    break;
    case 1:
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_2Edge;
    break;
    case 2:
    spi.SPI_CPOL = SPI_CPOL_High;
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    break;
    case 3:
    spi.SPI_CPOL = SPI_CPOL_High;
    spi.SPI_CPHA = SPI_CPHA_2Edge;
    break;
    default:break;
  }

  spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  spi.SPI_NSS = SPI_NSS_Hard;
  spi.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx,&spi);
}
