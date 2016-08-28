#include "mock_getTick.h"
#include "mock_MockFunction.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "Timer_setting.h"
#include "peripherals.h"
#include "Linklist.h"
#include "Timer.h"
#include "Dma.h"
#include "Registers.h"
#include "Host.h"
#include "Config.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Motor.h"
#include "unity.h"










void resetMotorDriveBuffer(void);

MotorInfo motor;



uint32_t* tickPointer = ((void *)0);

void setTickSequence(uint32_t tickTable[]){

  tickPointer = tickTable;

}





uint32_t fake_getTick(TIM_TypeDef* TIMx){

  uint32_t tick = *tickPointer;

  tickPointer++;

  return tick;

}





void setUp(void)

{



  getTick_StubWithCallback(fake_getTick);



  HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));

  HostDma1 = malloc((sizeof(DMA_TypeDef)));

  HostGpioA= malloc((sizeof(GPIO_TypeDef)));

  HostTim2= malloc((sizeof(TIM_TypeDef)));

  root = createLinkedList();

  motorRoot = createLinkedList();

  tickRecord1 = 0;

  tickRecord2 = 0;

  resetMotorDriveBuffer();

}



void tearDown(void)

{

  free(HostDma1_Channel3);

  free(HostDma1);

  free(HostGpioA);

  free(HostTim2);

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

  HostGpioA = ((void *)0);

  resetMotorDriveBuffer();

  motorRoot = ((void *)0);

  root = ((void *)0);

}





void func1(void){



}

void testMotor(MotorInfo* whichMotor){

  whichMotor->step = 1;

  whichMotor->sleep = 1;

}



void test_motorInit_the_configuration_was_set_by_motorInit_every_setting_should_pass_the_test_(void){

  printf("No 1.0");

  MotorInfo* whichMotor = motorInit(testMotor,0,0);



  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x80))), (_U_SINT)((whichMotor->direation)), (((void *)0)), (_U_UINT)(89), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(90), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x20))), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(91), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->microstep)), (((void *)0)), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->period)), (((void *)0)), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->state)), (((void *)0)), (_U_UINT)(94), UNITY_DISPLAY_STYLE_INT);



  if ((((whichMotor->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(96))));};

  if ((((whichMotor->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(97))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.callBack)), (((void *)0)), (_U_UINT)(98), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.args)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->timerElement.actionTime)), (((void *)0)), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->slot)), (((void *)0)), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(104), UNITY_DISPLAY_STYLE_INT);

  if ((((whichMotor->motorConfiguration->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(105))));};

  if ((((whichMotor->motorConfiguration->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(106))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.callBack)), (((void *)0)), (_U_UINT)(107), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.args)), (((void *)0)), (_U_UINT)(108), UNITY_DISPLAY_STYLE_HEX32);



}



void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){

  printf("No 1.1");

  MotorInfo* whichMotor = motorInit(testMotor,0,2);

  setCallBack(&whichMotor->timerElement,testMotor);

  whichMotor->timerElement.callBack(whichMotor);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(118), UNITY_DISPLAY_STYLE_INT);

}





void resetMotorDriveBuffer(void){

  motorDriveBuffer[0] = 0;

  motorDriveBuffer[1] = 0;

  motorDriveBuffer[2] = 0;

}



void initialStepCommand(MotorConfigInfo* motorConfiguration){

  motorConfiguration->stepLowCommand = 0xAA;

  motorConfiguration->stepHighCommand = 0x55;

}







void test_initialStepCommand_the_value_stepLowCommand_and_stepHighCommand_is_changed_to_0xAA_and_0x55(void){

  printf("No 1.0");

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(139), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

}





void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){

  printf("No 1.1");

  MotorInfo motor1;

  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,2);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

}







void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){

  printf("No 1.2");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){

  printf("No 2.0");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(189), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(190), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(191), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(192), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){

  printf("No 3.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(222), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(223), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(225), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(226), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(227), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(228), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){

  printf("No 4.0");



  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(255), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(256), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(257), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(258), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(259), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(260), UNITY_DISPLAY_STYLE_INT);

}

  void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){

    printf("No 5.0");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

    initialStepCommand(motorConfig);



    motorStep(motorConfig);



    UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(287), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(289), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(290), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(291), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(292), UNITY_DISPLAY_STYLE_INT);

  }

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){

  printf("No 6.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(323), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(324), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(325), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(326), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(327), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(328), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){

  printf("No 7.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(355), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(356), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(357), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(358), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(359), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(360), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){

  printf("No 8.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(384), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(385), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(386), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(387), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(388), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(389), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){

  printf("No 9.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(414), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(415), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(417), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(418), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(419), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){

  printf("No 10.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(444), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(445), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(446), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(447), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(448), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(449), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_the_firMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_firMotorElem(void){

  printf("NO 11.0");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig0);



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorStep(motorConfig2);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(481), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(482), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(483), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(485), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(486), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(487), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(488), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(489), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(490), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_the_secMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_secMotorElem(void){

  printf("No 12.0");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);



  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig1);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig0);

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig1);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(523), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(524), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(525), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(526), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(527), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(529), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(530), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(531), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_Motor0Element_Motor1Element_and_Motor2Element_was_added_into_linked_list_at_the_same_time(void){

  printf("No 12.1");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);



  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig1);

  initialStepCommand(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig0);

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig1);

  motorStep(motorConfig2);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(574), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(575), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(576), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(577), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(579), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(580), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(581), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(583), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(584), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(585), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(586), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_did_not_update_slot1_but_add_the_Motor2Element_into_linked_list(void){

  printf("NO 12.2");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);



  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig1);

  initialStepCommand(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig0);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorStep(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorStep(motorConfig1);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(622), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(623), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(624), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(626), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(627), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(628), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(629), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(631), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(632), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(633), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DataNumber_is_0_the_slot2_cant_be_update_but_the_Motor2Element_was_added_into_linked_list(void){

  printf("No 12.3");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);



  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig1);

  initialStepCommand(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorStep(motorConfig0);

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorStep(motorConfig1);

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),0);

  motorStep(motorConfig2);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(668), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(669), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(670), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(672), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(673), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(674), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(676), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(677), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(678), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(679), UNITY_DISPLAY_STYLE_INT);



}

void test_motorStep_when_DataNumber_is_0_the_all_of_slot_cant_be_update_but_the_all_MotorElement_were_added_into_linked_list(void){

  printf("No 12.4");



  motorRoot = createLinkedList();



  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);



  initialStepCommand(motorConfig0);

  initialStepCommand(motorConfig1);

  initialStepCommand(motorConfig2);



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),0);

  motorStep(motorConfig0);

  motorStep(motorConfig1);

  motorStep(motorConfig2);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(713), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(714), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(715), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(717), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(718), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(719), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(721), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(722), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(723), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(724), UNITY_DISPLAY_STYLE_INT);

}



void test_motorSet_the_motor_setting_was_set_by_using_motorSet_the_stepHighCommand_and_stepLowCommand_should_return_the_motor_setting(void){

    printf("No 13.0");

    uint8_t tempHigh = ((uint8_t)0x80)

                      |((uint8_t)0x40)

                      |((uint8_t)0x00)

                      |((uint8_t)0x20)

                      |((uint8_t)0x10)

                      |((uint8_t)0x00);

    uint8_t tempLow = tempHigh&((uint8_t)0xBF);



    MotorInfo* Motor3 = motorInit(func1,0,0);

    motorSet(Motor3,((uint8_t)0x80),((uint8_t)0x00));



    UnityAssertEqualNumber((_U_SINT)((tempHigh)), (_U_SINT)((Motor3->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(740), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((tempLow)), (_U_SINT)((Motor3->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(741), UNITY_DISPLAY_STYLE_INT);

}





void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){

      printf("No 14.0");

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(748), UNITY_DISPLAY_STYLE_INT);



}

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){

  printf("motorConfigInit\n");

  printf("No 1.0");

  MotorInfo motor0;

  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(766), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->slot)), (((void *)0)), (_U_UINT)(767), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepHighCommand)), (((void *)0)), (_U_UINT)(768), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepLowCommand)), (((void *)0)), (_U_UINT)(769), UNITY_DISPLAY_STYLE_INT);

  if ((((motorConfig0->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(770))));};

  if ((((motorConfig0->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(771))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((motorConfig0->motorElement.callBack)), (((void *)0)), (_U_UINT)(772), UNITY_DISPLAY_STYLE_HEX32);



}



void test_extractMotorConfigInfo_(void){

   printf("extractMotorConfigInfo\n");

   printf("No 2.0");

   MotorConfigInfo* motorConfig;

   MotorInfo* Motor0 = motorInit(func1,10000,0);

   motorConfig = extractMotorConfigInfo(Motor0->motorConfiguration->motorElement.args);

   UnityAssertEqualNumber((_U_SINT)((Motor0)), (_U_SINT)((motorConfig->motorElement.args)), (((void *)0)), (_U_UINT)(782), UNITY_DISPLAY_STYLE_INT);

}



void test_dmaQueue_add_one_motorElement_into_Queue(void){

    printf("dmaQueue\n");

    printf("No 3.0");

    motorRoot = createLinkedList();

    MotorInfo motor2;

    MotorConfigInfo* motorConfig2 = motorConfigInit(&motor2,func1,2);

    dmaQueue(motorRoot,&motorConfig2->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(792), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_motorElement_into_Queue(void){

    printf("No 3.1");

    motorRoot = createLinkedList();

    MotorInfo motor0;

    MotorInfo motor1;

    MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

    MotorConfigInfo* motorConfig1 = motorConfigInit(&motor1,func1,1);

    dmaQueue(motorRoot,&motorConfig0->motorElement);

    dmaQueue(motorRoot,&motorConfig1->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(804), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(805), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaDequeue_add_two_motorElement_into_Queue_and_deQueue(void){

    printf("dmaDequeue\n");

    printf("No 3.2");

    motorRoot = createLinkedList();

    ListElement *temp;

    MotorInfo motor0;

    MotorInfo motor1;



    MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

    MotorConfigInfo* motorConfig1 = motorConfigInit(&motor1,func1,1);



    dmaQueue(motorRoot,&motorConfig0->motorElement);

    dmaQueue(motorRoot,&motorConfig1->motorElement);



    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(823), UNITY_DISPLAY_STYLE_HEX32);

    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(825), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(826))));};



}

void test_updateMotorDriveBuffer_the_linkedlist_only_contain_motor0Element_and_Update_the_triMotor_slot_buffer(void){

    printf("updateMotorDriveBuffer\n");

    printf("No 4.0");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);

    dmaQueue(motorRoot,&motor0->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(853), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(854), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(855), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_and_motor1Element_and_Update_the_triMotor_and_secMotor_slot_buffer(void){

    printf("No 4.1");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);



    dmaQueue(motorRoot,&motor0->motorConfiguration->motorElement);

    dmaQueue(motorRoot,&motor1->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(886), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(887), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(889), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(890), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(892), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(893), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_motor1Element_and_motor2Elementent_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){

    printf("No 4.2");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    dmaQueue(motorRoot,&motor0->motorConfiguration->motorElement);

    dmaQueue(motorRoot,&motor1->motorConfiguration->motorElement);

    dmaQueue(motorRoot,&motor2->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(929), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(930), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(931), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(933), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(934), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(936), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(937), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(938), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){

    printf("No 4.3");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(963), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(964), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(965), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(966), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(968), UNITY_DISPLAY_STYLE_INT);



}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_motor1Element_and_motor2Element_after_function_they_should_dequeue(void){

    printf("No 4.4");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1002), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1003), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1004), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1006), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1007), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1008), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1012), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1013), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1014), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1016), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1017), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1018), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_they_should_dequeue(void){

    printf("No 4.5");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1048), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1049), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1053), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1054), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1056), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1057), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1058), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1060), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1061), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_linkedList_contain_motor2Element(void){

    printf("No 4.6");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor2->motorConfiguration);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

    motorStep(motor1->motorConfiguration);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1095), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1096), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1098), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1099), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1100), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1102), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1103), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1104), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_is_emply(void){

    printf("No 4.7");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1136), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1137), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1139), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1140), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1141), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1143), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1144), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1145), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_only_contain_motor1Element(void){

    printf("No 4.8");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor1->motorConfiguration);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    motorStep(motor0->motorConfiguration);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1179), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1180), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1182), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1183), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1184), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1186), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1187), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1188), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_the_DMA_IRQ_function_will_update_motor0Element_Command(void){

    printf("No 5.0");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    motorStep(motor0->motorConfiguration);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1218), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1219), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1220), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1221), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1222), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1223), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1224), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1225), UNITY_DISPLAY_STYLE_INT);



}

void test_motorMovementHandler_the_DMA_IRQ_function_was_called_in_2_times_and_the_head_of_queue_is_point_to_null(void){

    printf("No 5.1");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    motorStep(motor0->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1254), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1255), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1256), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1258))));};

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1259), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1260), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1262), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1263), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1264), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_the_DMA_IRQ_function_will_update_triMotorSlot_and_secMotorSlot_Command(void){

    printf("No 5.2");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1297), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1298), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1299), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1301), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1302), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1303), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1305), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1306), UNITY_DISPLAY_STYLE_HEX32);

}

void test_motorMovementHandler_motor0Element_and_motor1Element_that_updated_completely_should_be_dequeue(void){

    printf("No 5.3");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1340), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1341), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1342), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1344), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1345), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1346), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1348))));};



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1350), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1351), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1352), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1353), UNITY_DISPLAY_STYLE_INT);

    if (((1) != (motor2->step))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1354)));};

    if (((1) != (motor2->sleep))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1355)));};



}

void test_motorMovementHandler_motor0Element__motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){

       printf("No 5.31");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1391), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1392), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1393), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1395), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1396), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1397), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1399), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1400), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1401), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1402), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1403), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1404), UNITY_DISPLAY_STYLE_INT);



   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1406))));};

}

void test_motorMovementHandler_motor0ment_and_motor1Element_(void){

    printf("No 5.4");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor2->motorConfiguration);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

    motorStep(motor0->motorConfiguration);





    DMA1_Channel3_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1446), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1447), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1448), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1450), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1451), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1452), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1454), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1455), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1456), UNITY_DISPLAY_STYLE_HEX32);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1460), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1461), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1463), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1464), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1465), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1467), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1468), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1469), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1471), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1472), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1476))));};



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1478), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1479), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1480), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1482), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1483), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1485), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1486), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1487), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_motor0Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){

    printf("No 5.5");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    DMA1_Channel3_IRQHandler();



    motor1->motorConfiguration->counter = 1;

    motorDriveBuffer[1] = motor0->motorConfiguration->stepLowCommand;



    DMA1_Channel3_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1524), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1525), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1526), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1528), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1529), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1530), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1532), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1533), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1534), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1535), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1537), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1538), UNITY_DISPLAY_STYLE_HEX32);

}

void test_motorMovementHandler_motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){

       printf("No 5.6");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(testMotor,1000,0);

    MotorInfo* motor1 = motorInit(testMotor,1000,1);

    MotorInfo* motor2 = motorInit(testMotor,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    motor0->motorConfiguration->counter = 1;

    motorDriveBuffer[0] = motor0->motorConfiguration->stepLowCommand;

    DMA1_Channel3_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1574), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1575), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1576), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1578), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1579), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1580), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1582), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1583), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1584), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1585), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1587), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1588), UNITY_DISPLAY_STYLE_HEX32);

}



void test_getTick_the_function_should_return_1000_2000_3000(void){

  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1594), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1595), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1596), UNITY_DISPLAY_STYLE_INT);



}

void test_motorMovementHandler_the_DMA_interrupt_has_occured_two_time_the_timer_link_list_have_contained_two_element(void){

   printf("No 6.0");

   MotorInfo* motor0 = motorInit(motorController,2000,0);

   MotorInfo* motor1 = motorInit(motorController,6000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,100,200,300,400};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,2000);

   timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1630), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1631), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1632), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1633), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1634), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1638), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1639), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1640), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1641), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1642), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1643), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1644), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1646), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1647), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1648), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1649), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1650), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1651), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1652), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1653), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1654), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1657), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1658), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1659), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1660), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1661), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1662), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1663), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1664), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1665), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1668), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1669), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1670))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1671), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1672), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1673), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1674), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1675), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1676), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1678), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1679), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1680), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1681), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1682), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1683), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1684), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1685), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_the1(void){

   printf("No 6.1");

   MotorInfo* motor0 = motorInit(motorController,2000,0);

   MotorInfo* motor1 = motorInit(motorController,6000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,100,200,300};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,2000);

   timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1725), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1726), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1727), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1728), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1729), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1733), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1734), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1735), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1736), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1737), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1738), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1739), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1741), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1742), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1743), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1744), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1745), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1746), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1747), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1748), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1749), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1752), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1753), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1754), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1755), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1756), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1757), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1758), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1759), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1760), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1763), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1764), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1765))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1766), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1767), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1768), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1769), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1770), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1771), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1773), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1774), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1775), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1776), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1777), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1778), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1779), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1780), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_the_timer_link_list_has_contain_two_element_such_as_3000_and_6000(void){

   printf("No 6.2");

   MotorInfo* motor0 = motorInit(motorController,3000,0);

   MotorInfo* motor1 = motorInit(motorController,6000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,100,200,300};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,3000);

   timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1822), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1823), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1824), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1825), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1826), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1830), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1831), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1832), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1833), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1834), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1835), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1836), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1838), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1839), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1840), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1841), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1842), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1843), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1844), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1845), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1846), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1849), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1850), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1851), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1852), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1853), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1854), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1855), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1856), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1857), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1860), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1861), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1862))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1863), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1864), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1865), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1866), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1867), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1868), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1870), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1871), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1872), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1873), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1874), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(1875), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2700)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1876), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((200)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1877), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2700)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1878), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_with_3000_and_6000_elem_in_link_list(void){

   printf("No 6.3");

   MotorInfo* motor0 = motorInit(motorController,3000,0);

   MotorInfo* motor1 = motorInit(motorController,6000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,0,0,300};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,3000);

   timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1920), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1921), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1922), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1923), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1924), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1928), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1929), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1930), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1931), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1932), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1933), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1934), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1936), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1937), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1938), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1939), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1940), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1941), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1942), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1943), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1944), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1947), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1948), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1949), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1950), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1951), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1952), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1953), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1954), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1955), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1958), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1959), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1960))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1961), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1962), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1963), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1964), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1965), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1966), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1968), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1969), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1971), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1972), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(1973), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1974), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((300)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1975), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1976), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_with_1000_2000_and_4000_elem_in_timer_link_list(void){

   printf("No 6.4");

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,3000,1);

   MotorInfo* motor2 = motorInit(motorController,7000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,0,100,200,300,400,500};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,1000);

   timerDelay(&motor1->timerElement,3000);

   timerDelay(&motor2->timerElement,7000);



   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2021), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2022), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2023), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2025), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2026), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2027), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2028), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2032), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2033), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2034), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2035), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2036), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2037), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2038), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2039), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2041), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2042), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2043), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2044), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2045), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2046), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2047), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2048), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2049), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2052), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2053), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2054), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2055), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2056), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2057), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2058), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2059), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2060), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2063), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2064), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2065))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2066), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2067), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2068), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2069), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2070), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2071), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2073), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2074), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2075), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2076), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2078), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2079), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2080), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2081), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2083), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2084), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2085), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_with_900_800_and_4000_elem_in_timer_link_list(void){

   printf("No 6.5");

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,3000,1);

   MotorInfo* motor2 = motorInit(motorController,7000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,0,400,500,600};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,900);

   timerDelay(&motor1->timerElement,1700);

   timerDelay(&motor2->timerElement,5700);



   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2130), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2131), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2132), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2134), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2135), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2136), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2137), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2141), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2142), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2143), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2144), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2145), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2146), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2147), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2148), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2150), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2151), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2152), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2153), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2154), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2155), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2156), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2157), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2158), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2161), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2162), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2163), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2164), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2165), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2166), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2167), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2168), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2169), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2172), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1400)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2173), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2174))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2175), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2176), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2177), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2178), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2179), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2180), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2183), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2184), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2185), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2186), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1500)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2188), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2189), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2190), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2191), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2193), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((700)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2194), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2195), UNITY_DISPLAY_STYLE_INT);

}

void test_motorMovementHandler_with_1_9_and_90_elem_in_timer_link_list(void){

   printf("No 6.5");

   MotorInfo* motor0 = motorInit(motorController,1,0);

   MotorInfo* motor1 = motorInit(motorController,10,1);

   MotorInfo* motor2 = motorInit(motorController,100,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {0,0,0,0,0,0,0,0,0,0,0,0};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,1);

   timerDelay(&motor1->timerElement,2);

   timerDelay(&motor2->timerElement,12);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2240), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2241), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2242), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2244), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2245), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2246), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2247), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2251), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2252), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2253), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2254), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2255), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2256), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2257), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2258), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2260), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2261), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2262), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2263), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2264), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2265), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2266), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2267), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2268), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2271), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2272), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2273), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2274), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2275), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2276), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2277), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2278), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2279), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2282), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2283), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2284))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2285), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2286), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2287), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2288), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2289), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2290), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2293), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2294), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2295), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2296), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2298), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2299), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2300), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2301), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2303), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2304), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2305), UNITY_DISPLAY_STYLE_INT);





    TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2310), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2311), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2312), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2313), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2314), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2315), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2316), UNITY_DISPLAY_STYLE_HEX32);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2319), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2320), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(2321), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2323), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2324), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2325), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2326), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2327), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2328), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2329), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2332), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2333), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2334), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2335), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2336), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2337), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2338), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2339), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2340), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2341), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2342), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2345), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2346), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2347))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2348), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2349), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2350), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2351), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2352), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2353), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2356), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2357), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2358), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2359), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2361), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2362), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2363), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2364), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2366), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2367), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2368), UNITY_DISPLAY_STYLE_INT);





}







void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_20_the_function_should_return_10(void){

  printf("No 7.0");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((getNewPeriod(20))), (((void *)0)), (_U_UINT)(2380), UNITY_DISPLAY_STYLE_INT);





}



void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_5_the_function_should_return_1(void){

  printf("No 7.1");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getNewPeriod(5))), (((void *)0)), (_U_UINT)(2390), UNITY_DISPLAY_STYLE_INT);





}



void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_10_the_function_should_return_1(void){

  printf("No 7.2");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getNewPeriod(10))), (((void *)0)), (_U_UINT)(2400), UNITY_DISPLAY_STYLE_INT);





}



void test_DmaConfig_(void){













}
