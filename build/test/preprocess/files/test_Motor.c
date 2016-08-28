#include "mock_getTick.h"
#include "mock_MockFunction.h"
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



uint32_t fake_getFakeTick(){

  uint32_t tick = *tickPointer;

  tickPointer++;

  return tick;

}



uint32_t fake_getTick(TIM_TypeDef* TIMx){

  uint32_t tick = *tickPointer;

  tickPointer++;

  return tick;

}





void setUp(void)

{

  getFakeTick_StubWithCallback(fake_getFakeTick);

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



  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x80))), (_U_SINT)((whichMotor->direation)), (((void *)0)), (_U_UINT)(94), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x20))), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->microstep)), (((void *)0)), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->period)), (((void *)0)), (_U_UINT)(98), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->state)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);



  if ((((whichMotor->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(101))));};

  if ((((whichMotor->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(102))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.callBack)), (((void *)0)), (_U_UINT)(103), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.args)), (((void *)0)), (_U_UINT)(104), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->timerElement.actionTime)), (((void *)0)), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->slot)), (((void *)0)), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(108), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);

  if ((((whichMotor->motorConfiguration->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(110))));};

  if ((((whichMotor->motorConfiguration->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(111))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.callBack)), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.args)), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_HEX32);



}



void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){

  printf("No 1.1");

  MotorInfo* whichMotor = motorInit(testMotor,0,FIRST_MOTOR);

  setCallBack(&whichMotor->timerElement,testMotor);

  whichMotor->timerElement.callBack(whichMotor);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

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

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(144), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(145), UNITY_DISPLAY_STYLE_INT);

}





void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){

  printf("No 1.1");

  MotorInfo motor1;

  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(157), UNITY_DISPLAY_STYLE_INT);

}







void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){

  printf("No 1.2");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(165), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(167), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){

  printf("No 2.0");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),4);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(194), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(195), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(197), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(198), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){

  printf("No 3.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(227), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(228), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(229), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(230), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(231), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(232), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(233), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){

  printf("No 4.0");



  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),4);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(260), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(261), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(262), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);

}

  void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){

    printf("No 5.0");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

    initialStepCommand(motorConfig);



    motorStep(motorConfig);



    UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(292), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(293), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(294), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(295), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(296), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(297), UNITY_DISPLAY_STYLE_INT);

  }

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){

  printf("No 6.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(328), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(329), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(330), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(331), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(332), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){

  printf("No 7.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(360), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(362), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(363), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(364), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(365), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){

  printf("No 8.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(389), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(390), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(391), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(392), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(393), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(394), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){

  printf("No 9.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(419), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(420), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(421), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(422), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(423), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(424), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){

  printf("No 10.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(449), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(450), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(451), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(452), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(453), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(454), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(486), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(487), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(488), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(490), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(491), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(492), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(493), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(494), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(495), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(528), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(529), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(530), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(531), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(532), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(534), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(535), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(536), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(579), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(580), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(581), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(582), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(584), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(585), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(586), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(588), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(589), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(590), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(591), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(627), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(628), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(629), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(631), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(632), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(633), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(634), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(636), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(637), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(638), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(673), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(674), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(675), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(677), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(678), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(679), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(681), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(682), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(683), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(684), UNITY_DISPLAY_STYLE_INT);



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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(718), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(719), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(720), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(722), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(723), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(724), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(726), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(727), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(728), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(729), UNITY_DISPLAY_STYLE_INT);

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



    MotorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);

    motorSet(Motor3,((uint8_t)0x80),((uint8_t)0x00));



    UnityAssertEqualNumber((_U_SINT)((tempHigh)), (_U_SINT)((Motor3->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(745), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((tempLow)), (_U_SINT)((Motor3->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(746), UNITY_DISPLAY_STYLE_INT);

}





void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){

      printf("No 14.0");

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(753), UNITY_DISPLAY_STYLE_INT);



}

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){

  printf("motorConfigInit\n");

  printf("No 1.0");

  MotorInfo motor0;

  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(771), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->slot)), (((void *)0)), (_U_UINT)(772), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepHighCommand)), (((void *)0)), (_U_UINT)(773), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepLowCommand)), (((void *)0)), (_U_UINT)(774), UNITY_DISPLAY_STYLE_INT);

  if ((((motorConfig0->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(775))));};

  if ((((motorConfig0->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(776))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((motorConfig0->motorElement.callBack)), (((void *)0)), (_U_UINT)(777), UNITY_DISPLAY_STYLE_HEX32);



}



void test_extractMotorConfigInfo_(void){

   printf("extractMotorConfigInfo\n");

   printf("No 2.0");

   MotorConfigInfo* motorConfig;

   MotorInfo* Motor0 = motorInit(func1,10000,0);

   motorConfig = extractMotorConfigInfo(Motor0->motorConfiguration->motorElement.args);

   UnityAssertEqualNumber((_U_SINT)((Motor0)), (_U_SINT)((motorConfig->motorElement.args)), (((void *)0)), (_U_UINT)(787), UNITY_DISPLAY_STYLE_INT);

}



void test_dmaQueue_add_one_motorElement_into_Queue(void){

    printf("dmaQueue\n");

    printf("No 3.0");

    motorRoot = createLinkedList();

    MotorInfo motor2;

    MotorConfigInfo* motorConfig2 = motorConfigInit(&motor2,func1,2);

    dmaQueue(&motorConfig2->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(797), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_motorElement_into_Queue(void){

    printf("No 3.1");

    motorRoot = createLinkedList();

    MotorInfo motor0;

    MotorInfo motor1;

    MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

    MotorConfigInfo* motorConfig1 = motorConfigInit(&motor1,func1,1);

    dmaQueue(&motorConfig0->motorElement);

    dmaQueue(&motorConfig1->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(809), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(810), UNITY_DISPLAY_STYLE_HEX32);

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



    dmaQueue(&motorConfig0->motorElement);

    dmaQueue(&motorConfig1->motorElement);



    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(828), UNITY_DISPLAY_STYLE_HEX32);

    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(830), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(831))));};



}

void test_updateMotorDriveBuffer_the_linkedlist_only_contain_motor0Element_and_Update_the_triMotor_slot_buffer(void){

    printf("updateMotorDriveBuffer\n");

    printf("No 4.0");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);

    dmaQueue(&motor0->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(858), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(859), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(860), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_and_motor1Element_and_Update_the_triMotor_and_secMotor_slot_buffer(void){

    printf("No 4.1");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);



    dmaQueue(&motor0->motorConfiguration->motorElement);

    dmaQueue(&motor1->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(891), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(892), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(894), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(895), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(897), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(898), UNITY_DISPLAY_STYLE_INT);

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



    dmaQueue(&motor0->motorConfiguration->motorElement);

    dmaQueue(&motor1->motorConfiguration->motorElement);

    dmaQueue(&motor2->motorConfiguration->motorElement);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(934), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(936), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(938), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(939), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(940), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(941), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(942), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(943), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){

    printf("No 4.3");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(968), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(969), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(970), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(971), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(973), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1007), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1008), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1009), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1011), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1012), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1013), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1017), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1018), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1019), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1021), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1022), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1023), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1053), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1054), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1058), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1059), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1061), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1062), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1063), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1065), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1066), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1100), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1101), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1103), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1104), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1105), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1107), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1108), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1109), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1141), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1142), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1144), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1145), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1146), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1148), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1149), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1150), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1184), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1185), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1187), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1188), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1189), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1191), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1192), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1193), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1223), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1224), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1225), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1226), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1227), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1228), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1229), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1230), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1259), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1260), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1261), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1263))));};

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1264), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1265), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1267), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1268), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1269), UNITY_DISPLAY_STYLE_INT);

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1302), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1303), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1304), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1306), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1307), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1308), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1310), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1311), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1345), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1346), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1347), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1349), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1350), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1351), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1353))));};



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1355), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1356), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1357), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1358), UNITY_DISPLAY_STYLE_INT);

    if (((1) != (motor2->step))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1359)));};

    if (((1) != (motor2->sleep))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1360)));};



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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1396), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1397), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1398), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1400), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1401), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1402), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1404), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1405), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1406), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1407), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1408), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1409), UNITY_DISPLAY_STYLE_INT);



   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1411))));};

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1451), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1452), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1453), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1455), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1456), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1457), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1459), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1460), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1461), UNITY_DISPLAY_STYLE_HEX32);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1465), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1466), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1468), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1469), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1470), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1472), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1473), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1474), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1476), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1477), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1481))));};



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1483), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1484), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1485), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1487), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1488), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1490), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1491), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1492), UNITY_DISPLAY_STYLE_INT);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1529), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1530), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1531), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1533), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1534), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1535), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1537), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1538), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1539), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1540), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1542), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1543), UNITY_DISPLAY_STYLE_HEX32);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1579), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1580), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1581), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1583), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1584), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1585), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1587), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1588), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1589), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1590), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1592), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1593), UNITY_DISPLAY_STYLE_HEX32);

}





void test_getFakeTick(void){



  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1601), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1602), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1603), UNITY_DISPLAY_STYLE_INT);



}



void test_getTick(void){

  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1610), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1611), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(1612), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2000);

   _timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1646), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1647), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1648), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1649), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1650), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1654), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1655), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1656), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1657), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1658), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1659), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1660), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1662), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1663), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1664), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1665), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1666), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1667), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1668), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1669), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1670), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1673), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1674), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1675), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1676), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1677), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1678), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1679), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1680), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1681), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1684), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1685), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1686))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1687), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1688), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1689), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1690), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1691), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1692), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1694), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1695), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1696), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1697), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1698), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1699), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1700), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1701), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,2000);

   _timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1741), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1742), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1743), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1744), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1745), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1749), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1750), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1751), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1752), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1753), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1754), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1755), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1757), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1758), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1759), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1760), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1761), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1762), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1763), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1764), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1765), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1768), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1769), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1770), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1771), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1772), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1773), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1774), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1775), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1776), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1779), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1780), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1781))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1782), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1783), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1784), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1785), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1786), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1787), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1789), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1790), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1791), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1792), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1793), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1794), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1795), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1796), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,3000);

   _timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1838), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1839), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1840), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1841), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1842), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1846), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1847), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1848), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1849), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1850), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1851), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1852), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1854), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1855), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1856), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1857), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1858), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1859), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1860), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1861), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1862), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1865), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1866), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1867), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1868), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1869), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1870), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1871), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1872), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1873), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1876), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1877), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1878))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1879), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1880), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1881), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1882), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1883), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1884), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1886), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1887), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1888), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1889), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1890), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(1891), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2700)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1892), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((200)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1893), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2700)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1894), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,3000);

   _timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1936), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1937), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1938), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1939), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1940), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1944), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1945), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1946), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1947), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1948), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1949), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1950), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1952), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1953), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1954), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1955), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1956), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1957), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1958), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1959), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1960), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1963), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1964), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1965), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1966), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1967), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1968), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1969), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1970), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1971), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1974), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1975), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1976))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1977), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1978), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1979), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1980), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1981), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1982), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1984), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1985), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1987), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(1988), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(1989), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1990), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((300)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1991), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1992), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,1000);

   _timerDelay(&motor1->timerElement,3000);

   _timerDelay(&motor2->timerElement,7000);



   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2037), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2038), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2039), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2041), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2042), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2043), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2044), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2048), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2049), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2050), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2051), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2052), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2053), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2054), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2055), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2057), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2058), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2059), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2060), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2061), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2062), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2063), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2064), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2065), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2068), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2069), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2070), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2071), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2072), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2073), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2074), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2075), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2076), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1100)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2079), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1200)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2080), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2081))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2082), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2083), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2084), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2085), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2086), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2087), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2089), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2090), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2091), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2092), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2094), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2095), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2096), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2097), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2099), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2100), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2101), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,900);

   _timerDelay(&motor1->timerElement,1700);

   _timerDelay(&motor2->timerElement,5700);



   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2146), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2147), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2148), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2150), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2151), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2152), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2153), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2157), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2158), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2159), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2160), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2161), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2162), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2163), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2164), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2166), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2167), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2168), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2169), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2170), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2171), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2172), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2173), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2174), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2177), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2178), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2179), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2180), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2181), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2182), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2183), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2184), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2185), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1300)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2188), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1400)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2189), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2190))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2191), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2192), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2193), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2194), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2195), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2196), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2199), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2200), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2201), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2202), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1500)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2204), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((900)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2205), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2206), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2207), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((800)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2209), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((700)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2210), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3300)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2211), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,1);

   _timerDelay(&motor1->timerElement,2);

   _timerDelay(&motor2->timerElement,12);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2256), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2257), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2258), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2260), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2261), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2262), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2263), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2267), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2268), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2269), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2270), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2271), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2272), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2273), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2274), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2276), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2277), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2278), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2279), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2280), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2281), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2282), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2283), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2284), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2287), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2288), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2289), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2290), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2291), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2292), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2293), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2294), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2295), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2298), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2299), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2300))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2301), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2302), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2303), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2304), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2305), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2306), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2309), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2310), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2311), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2312), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2314), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2315), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2316), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2317), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2319), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2320), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2321), UNITY_DISPLAY_STYLE_INT);





    TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2326), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2327), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2328), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(2329), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(2330), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2331), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2332), UNITY_DISPLAY_STYLE_HEX32);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(2335), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(2336), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(2337), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2339), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2340), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2341), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2342), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2343), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2344), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2345), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(2348), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(2349), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(2350), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2351), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2352), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2353), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2354), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2355), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2356), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2357), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2358), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(2361), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(2362), UNITY_DISPLAY_STYLE_INT);

   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(2363))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2364), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2365), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(2366), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(2367), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(2368), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(2369), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(2372), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(2373), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(2374), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(2375), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(2377), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(2378), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(2379), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(2380), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2382), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2383), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(2384), UNITY_DISPLAY_STYLE_INT);





}







void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_20_the_function_should_return_10(void){

  printf("No 7.0");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((getNewPeriod(20))), (((void *)0)), (_U_UINT)(2396), UNITY_DISPLAY_STYLE_INT);





}



void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_5_the_function_should_return_1(void){

  printf("No 7.1");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getNewPeriod(5))), (((void *)0)), (_U_UINT)(2406), UNITY_DISPLAY_STYLE_INT);





}



void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_10_the_function_should_return_1(void){

  printf("No 7.2");

  tickRecord1 = 10;

  tickRecord2 = 20;



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getNewPeriod(10))), (((void *)0)), (_U_UINT)(2416), UNITY_DISPLAY_STYLE_INT);





}
