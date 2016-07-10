#include "projectStruct.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Registers.h"
#include "Host.h"
#include "stepperMotor.h"
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



void testMotor(motorInfo* whichMotor){

  whichMotor->step = 1;

  whichMotor->sleep = 1;

}



void test_motorInit_the_configuration_was_set_by_motorInit(void){

  motorInfo* whichMotor = motorInit(testMotor);



  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x80))), (_U_SINT)((whichMotor->direation)), (((void *)0)), (_U_UINT)(33), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(34), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x20))), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(35), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->microstep)), (((void *)0)), (_U_UINT)(36), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->period)), (((void *)0)), (_U_UINT)(37), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->state)), (((void *)0)), (_U_UINT)(38), UNITY_DISPLAY_STYLE_INT);



  if ((((whichMotor->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(40))));};

  if ((((whichMotor->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(41))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.callBack)), (((void *)0)), (_U_UINT)(42), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.motorID)), (((void *)0)), (_U_UINT)(43), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->timerElement.actionTime)), (((void *)0)), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);

}



void test_setMotorID_(void){

  motorInfo* whichMotor = motorInit(testMotor);

  setMotorID(whichMotor);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.motorID)), (((void *)0)), (_U_UINT)(50), UNITY_DISPLAY_STYLE_HEX32);

}



void test_setCallBack_(void){

  motorInfo* whichMotor = motorInit(testMotor);

  setCallBack(&whichMotor->timerElement,testMotor);

  whichMotor->timerElement.callBack(whichMotor);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(57), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);

}
