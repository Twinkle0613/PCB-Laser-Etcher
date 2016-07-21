#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "Timer_setting.h"
#include "peripherals.h"
#include "DMA_setting.h"
#include "Linklist.h"
#include "Timer.h"
#include "DMA.h"
#include "Registers.h"
#include "Host.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Motor.h"
#include "unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}



void func1(void){



}



void test_getCommond_(void){

  motorInfo motor1;

  motorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);;



  motorConfig->stepHighCommand = 0xFF;

  motorConfig->stepLowCommand = 0xF0;

  UnityAssertEqualNumber((_U_SINT)((0xF0)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(45), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(46), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(47), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(48), UNITY_DISPLAY_STYLE_INT);



}
