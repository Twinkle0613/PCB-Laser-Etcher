#ifndef __Registers_H__
#define __Registers_H__
#include <stdint.h>

#include "Host.h"

#define RCC_BASE_ADDRESS   ((uint32_t)HostRcc)
#define GPIOG_BASE_ADDRESS ((uint32_t)HostGpioG)
#define GPIOA_BASE_ADDRESS ((uint32_t)HostGpioA)
#define TIM2_BASE_ADDRESS  ((uint32_t)HostTim2)

#endif //__Registers_H__