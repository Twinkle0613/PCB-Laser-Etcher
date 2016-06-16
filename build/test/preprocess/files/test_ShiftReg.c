#include "Host.h"
#include "peripherals.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Registers.h"
#include "ShiftReg.h"
#include "unity.h"


















void setUp(void)

{

  HostGpioA= malloc((sizeof(GPIO_TypeDef)));

}



void tearDown(void)

{

   free(HostGpioA);

   HostGpioA = ((void *)0);

}



void test_GPIO_conf1(void){

  ((GPIO_TypeDef *) ((uint32_t)HostGpioA))->CRL = 0x0;

  GPIO_conf1(((GPIO_TypeDef *) ((uint32_t)HostGpioA)),((uint16_t)0x0002),GPIO_Speed_10MHz,GPIO_Mode_Out_PP);

  GPIO_conf1(((GPIO_TypeDef *) ((uint32_t)HostGpioA)),((uint16_t)0x0001),GPIO_Speed_10MHz,GPIO_Mode_Out_PP);

  GPIO_conf1(((GPIO_TypeDef *) ((uint32_t)HostGpioA)),((uint16_t)0x0080),GPIO_Speed_50MHz,GPIO_Mode_Out_PP);

  UnityAssertEqualNumber((_U_SINT)(_US32)((0x30000011)), (_U_SINT)(_US32)((((GPIO_TypeDef *) ((uint32_t)HostGpioA))->CRL)), (((void *)0)), (_U_UINT)(30), UNITY_DISPLAY_STYLE_INT32);

}
