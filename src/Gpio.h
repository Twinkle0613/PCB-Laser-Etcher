#ifndef Gpio_H
#define Gpio_H

#include <stdint.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"

void GpioConfig(GPIO_TypeDef* GPIOx, uint16_t Pin, int Speed, int Mode);
  
#endif // Gpio_H
