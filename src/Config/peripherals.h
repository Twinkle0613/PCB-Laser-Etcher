#ifndef peripherals_H
#define peripherals_H
#include "Registers.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE_ADDRESS)
#define TIM2 ((TIM_TypeDef*) TIM2_BASE_ADDRESS)

#endif // peripherals_H
