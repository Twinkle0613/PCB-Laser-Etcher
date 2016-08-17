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







void setUp(void)

{

  getFakeTick_StubWithCallback(fake_getFakeTick);

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



  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x80))), (_U_SINT)((whichMotor->direation)), (((void *)0)), (_U_UINT)(84), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x20))), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(86), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->microstep)), (((void *)0)), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->period)), (((void *)0)), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->state)), (((void *)0)), (_U_UINT)(89), UNITY_DISPLAY_STYLE_INT);



  if ((((whichMotor->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(91))));};

  if ((((whichMotor->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(92))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.callBack)), (((void *)0)), (_U_UINT)(93), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.args)), (((void *)0)), (_U_UINT)(94), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->timerElement.actionTime)), (((void *)0)), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->slot)), (((void *)0)), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(98), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

  if ((((whichMotor->motorConfiguration->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(100))));};

  if ((((whichMotor->motorConfiguration->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(101))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.callBack)), (((void *)0)), (_U_UINT)(102), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.args)), (((void *)0)), (_U_UINT)(103), UNITY_DISPLAY_STYLE_HEX32);



}



void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){

  printf("No 1.1");

  MotorInfo* whichMotor = motorInit(testMotor,0,FIRST_MOTOR);

  setCallBack(&whichMotor->timerElement,testMotor);

  whichMotor->timerElement.callBack(whichMotor);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_INT);

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

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

}





void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){

  printf("No 1.1");

  MotorInfo motor1;

  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(144), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(145), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(146), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);

}







void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){

  printf("No 1.2");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(157), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){

  printf("No 2.0");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),4);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(184), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(185), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(186), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(187), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(188), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(189), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(190), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){

  printf("No 3.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(217), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(218), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(219), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(220), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){

  printf("No 4.0");



  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),4);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(250), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(251), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(252), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(253), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(254), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(255), UNITY_DISPLAY_STYLE_INT);

}

  void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){

    printf("No 5.0");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

    initialStepCommand(motorConfig);



    motorStep(motorConfig);



    UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(282), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(283), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  }

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){

  printf("No 6.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(318), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(319), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(320), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(321), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(322), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(323), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){

  printf("No 7.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(350), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(351), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(352), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(353), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(354), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(355), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){

  printf("No 8.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(379), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(380), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(381), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(382), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(383), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(384), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){

  printf("No 9.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(409), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(411), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(412), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(413), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(414), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){

  printf("No 10.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(439), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(440), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(441), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(442), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(443), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(444), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(476), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(477), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(478), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(480), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(481), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(482), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(483), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(484), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(485), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(518), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(519), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(520), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(521), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(522), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(524), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(525), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(526), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(569), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(570), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(571), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(572), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(574), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(575), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(576), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(578), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(579), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(580), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(581), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(617), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(618), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(619), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(621), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(622), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(623), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(624), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(626), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(627), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(628), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(663), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(664), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(665), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(667), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(668), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(669), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(671), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(672), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(673), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(674), UNITY_DISPLAY_STYLE_INT);



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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(708), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(709), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(710), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(712), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(713), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(714), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(716), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(717), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(718), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(719), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((tempHigh)), (_U_SINT)((Motor3->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(735), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((tempLow)), (_U_SINT)((Motor3->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(736), UNITY_DISPLAY_STYLE_INT);

}





void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){

      printf("No 14.0");

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(743), UNITY_DISPLAY_STYLE_INT);



}

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){

  printf("motorConfigInit\n");

  printf("No 1.0");

  MotorInfo motor0;

  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(761), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->slot)), (((void *)0)), (_U_UINT)(762), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepHighCommand)), (((void *)0)), (_U_UINT)(763), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepLowCommand)), (((void *)0)), (_U_UINT)(764), UNITY_DISPLAY_STYLE_INT);

  if ((((motorConfig0->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(765))));};

  if ((((motorConfig0->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(766))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((motorConfig0->motorElement.callBack)), (((void *)0)), (_U_UINT)(767), UNITY_DISPLAY_STYLE_HEX32);



}



void test_extractMotorConfigInfo_(void){

   printf("extractMotorConfigInfo\n");

   printf("No 2.0");

   MotorConfigInfo* motorConfig;

   MotorInfo* Motor0 = motorInit(func1,10000,0);

   motorConfig = extractMotorConfigInfo(Motor0->motorConfiguration->motorElement.args);

   UnityAssertEqualNumber((_U_SINT)((Motor0)), (_U_SINT)((motorConfig->motorElement.args)), (((void *)0)), (_U_UINT)(777), UNITY_DISPLAY_STYLE_INT);

}



void test_dmaQueue_add_one_motorElement_into_Queue(void){

    printf("dmaQueue\n");

    printf("No 3.0");

    motorRoot = createLinkedList();

    MotorInfo motor2;

    MotorConfigInfo* motorConfig2 = motorConfigInit(&motor2,func1,2);

    dmaQueue(&motorConfig2->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(787), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(799), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(800), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(818), UNITY_DISPLAY_STYLE_HEX32);

    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(820), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(821))));};



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(848), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(849), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(850), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(881), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(882), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(884), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(885), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(887), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(888), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(924), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(925), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(926), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(928), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(929), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(930), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(931), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(932), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(933), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){

    printf("No 4.3");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(958), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(959), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(960), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(961), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(963), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(997), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(998), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(999), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1001), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1002), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1003), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1007), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1008), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1009), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1011), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1012), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1013), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1043), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1044), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1048), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1049), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1051), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1052), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1053), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1055), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1056), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1090), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1091), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1093), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1094), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1095), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1097), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1098), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1099), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1131), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1132), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1134), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1135), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1136), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1138), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1139), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1140), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1174), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1175), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1177), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1178), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1179), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1181), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1182), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1183), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1213), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1214), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1215), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1216), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1217), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1218), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1219), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1220), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1249), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1250), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1251), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1253))));};

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1254), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1255), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1257), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1258), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1259), UNITY_DISPLAY_STYLE_INT);

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1292), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1293), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1294), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1296), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1297), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1298), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1300), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1301), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1335), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1336), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1337), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1339), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1340), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1341), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1343))));};



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1345), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1346), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1347), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1348), UNITY_DISPLAY_STYLE_INT);

    if (((1) != (motor2->step))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1349)));};

    if (((1) != (motor2->sleep))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1350)));};



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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1386), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1387), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1388), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1390), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1391), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1392), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1394), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1395), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1396), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1397), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1398), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1399), UNITY_DISPLAY_STYLE_INT);



   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1401))));};

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1441), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1442), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1443), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1445), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1446), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1447), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1449), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1450), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1451), UNITY_DISPLAY_STYLE_HEX32);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1455), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1456), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1458), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1459), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1460), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1462), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1463), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1464), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1466), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1467), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1471))));};



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1473), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1474), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1475), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1477), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1478), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1480), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1481), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1482), UNITY_DISPLAY_STYLE_INT);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1519), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1520), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1521), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1523), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1524), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1525), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1527), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1528), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1529), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1530), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1532), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1533), UNITY_DISPLAY_STYLE_HEX32);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1569), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1570), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1571), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1573), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1574), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1575), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1577), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1578), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1579), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1580), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1582), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1583), UNITY_DISPLAY_STYLE_HEX32);

}





void test_getFakeTick(void){



  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1591), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1592), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(1593), UNITY_DISPLAY_STYLE_INT);



}

void test_motorMovementHandler_233(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);

   uint32_t stickTable[] = {1000,2000,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,2000);

   timerDelay(&motor1->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1624), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1625), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1626), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1627), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1628), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1632), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1633), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1634), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1635), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1636), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1637), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(1638), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1640), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1641), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1642), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1643), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1644), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1645), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1646), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1647), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1648), UNITY_DISPLAY_STYLE_INT);



   DMA1_Channel3_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((getDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))))), (((void *)0)), (_U_UINT)(1651), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(1652), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DMA_GetITStatus(((uint32_t)0x00000002)))), (((void *)0)), (_U_UINT)(1653), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1654), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1655), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1656), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(1658), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(1659), UNITY_DISPLAY_STYLE_INT);



}
