#ifndef peripherals_H
#define peripherals_H
#include "Registers.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE_ADDRESS)
#define assert_param(expr) ((void)0);

#endif // peripherals_H
