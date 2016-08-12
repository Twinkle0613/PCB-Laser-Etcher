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







void setUp(void)

{

  HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));

  HostDma1 = malloc((sizeof(DMA_TypeDef)));

  HostGpioA= malloc((sizeof(GPIO_TypeDef)));

}



void tearDown(void)

{

  free(HostDma1_Channel3);

  free(HostDma1);

  free(HostGpioA);

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

  HostGpioA = ((void *)0);

  resetMotorDriveBuffer();

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



  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x80))), (_U_SINT)((whichMotor->direation)), (((void *)0)), (_U_UINT)(63), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(64), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x20))), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(65), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((uint8_t)0x00))), (_U_SINT)((whichMotor->microstep)), (((void *)0)), (_U_UINT)(66), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->period)), (((void *)0)), (_U_UINT)(67), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->state)), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_INT);



  if ((((whichMotor->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(70))));};

  if ((((whichMotor->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(71))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.callBack)), (((void *)0)), (_U_UINT)(72), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->timerElement.args)), (((void *)0)), (_U_UINT)(73), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->timerElement.actionTime)), (((void *)0)), (_U_UINT)(74), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(75), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->slot)), (((void *)0)), (_U_UINT)(76), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(77), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((whichMotor->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(78), UNITY_DISPLAY_STYLE_INT);

  if ((((whichMotor->motorConfiguration->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(79))));};

  if ((((whichMotor->motorConfiguration->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(80))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.callBack)), (((void *)0)), (_U_UINT)(81), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->motorElement.args)), (((void *)0)), (_U_UINT)(82), UNITY_DISPLAY_STYLE_HEX32);



}



void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){

  printf("No 1.1");

  MotorInfo* whichMotor = motorInit(testMotor,0,FIRST_MOTOR);

  setCallBack(&whichMotor->timerElement,testMotor);

  whichMotor->timerElement.callBack(whichMotor);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->step)), (((void *)0)), (_U_UINT)(91), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((whichMotor->sleep)), (((void *)0)), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);

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

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);

}





void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){

  printf("No 1.1");

  MotorInfo motor1;

  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);

}







void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){

  printf("No 1.2");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(136), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){

  printf("No 2.0");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(163), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(164), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(165), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(167), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(168), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){

  printf("No 3.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(196), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(197), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(198), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(201), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(202), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){

  printf("No 4.0");



  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(229), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(230), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(231), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(232), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(233), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(234), UNITY_DISPLAY_STYLE_INT);

}

  void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){

    printf("No 5.0");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

    initialStepCommand(motorConfig);



    motorStep(motorConfig);



    UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(261), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(262), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(266), UNITY_DISPLAY_STYLE_INT);

  }

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){

  printf("No 6.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(297), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(298), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(300), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(301), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(302), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){

  printf("No 7.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  motorRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(329), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(330), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(331), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(332), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(334), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){

  printf("No 8.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(358), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(359), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(360), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(362), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(363), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){

  printf("No 9.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(388), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(389), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(390), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(391), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(392), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(393), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){

  printf("No 10.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  motorRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig->motorElement)), (((void *)0)), (_U_UINT)(418), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(419), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(420), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(421), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(422), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(423), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(455), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(456), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(457), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(459), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(460), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(461), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(462), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(463), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(464), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(497), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(498), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(499), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(500), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(501), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(504), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(505), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(548), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(549), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(550), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next->next)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(551), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(553), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(554), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(555), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(557), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(558), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(559), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(560), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(596), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(597), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(598), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(600), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(601), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(602), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(603), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(605), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(606), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(607), UNITY_DISPLAY_STYLE_INT);

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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(642), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(643), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(644), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(646), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(647), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig0->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(648), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(650), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(651), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(652), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(653), UNITY_DISPLAY_STYLE_INT);



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



  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head)), (_U_SINT)(_UP)((&motorConfig0->motorElement)), (((void *)0)), (_U_UINT)(687), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->motorElement)), (((void *)0)), (_U_UINT)(688), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((motorRoot->head->next->next)), (_U_SINT)(_UP)((&motorConfig2->motorElement)), (((void *)0)), (_U_UINT)(689), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(691), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(692), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(693), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(695), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(696), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(697), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(698), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((tempHigh)), (_U_SINT)((Motor3->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(714), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((tempLow)), (_U_SINT)((Motor3->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(715), UNITY_DISPLAY_STYLE_INT);

}





void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){

      printf("No 14.0");

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(722), UNITY_DISPLAY_STYLE_INT);



}

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){

  printf("motorConfigInit\n");

  printf("No 1.0");

  MotorInfo motor0;

  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->counter)), (((void *)0)), (_U_UINT)(740), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->slot)), (((void *)0)), (_U_UINT)(741), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepHighCommand)), (((void *)0)), (_U_UINT)(742), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig0->stepLowCommand)), (((void *)0)), (_U_UINT)(743), UNITY_DISPLAY_STYLE_INT);

  if ((((motorConfig0->motorElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(744))));};

  if ((((motorConfig0->motorElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(745))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((motorConfig0->motorElement.callBack)), (((void *)0)), (_U_UINT)(746), UNITY_DISPLAY_STYLE_HEX32);



}



void test_extractMotorConfigInfo_(void){

   printf("extractMotorConfigInfo\n");

   printf("No 2.0");

   MotorConfigInfo* motorConfig;

   MotorInfo* Motor0 = motorInit(func1,10000,0);

   motorConfig = extractMotorConfigInfo(Motor0->motorConfiguration->motorElement.args);

   UnityAssertEqualNumber((_U_SINT)((Motor0)), (_U_SINT)((motorConfig->motorElement.args)), (((void *)0)), (_U_UINT)(756), UNITY_DISPLAY_STYLE_INT);

}



void test_dmaQueue_add_one_motorElement_into_Queue(void){

    printf("dmaQueue\n");

    printf("No 3.0");

    motorRoot = createLinkedList();

    MotorInfo motor2;

    MotorConfigInfo* motorConfig2 = motorConfigInit(&motor2,func1,2);

    dmaQueue(&motorConfig2->motorElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(766), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(778), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(779), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig0->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(797), UNITY_DISPLAY_STYLE_HEX32);

    temp = dequeue(motorRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->motorElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(799), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(800))));};



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(827), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(828), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(829), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(860), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(861), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(863), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(864), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(866), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(867), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(903), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(904), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(905), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(907), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(908), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(909), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(910), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(911), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(912), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){

    printf("No 4.3");

    motorRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(937), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(938), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(939), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(940), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(942), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(976), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(977), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(978), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(980), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(981), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(982), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(986), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(987), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(988), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(990), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(991), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(992), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1022), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1023), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1027), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1028), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1030), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1031), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1032), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1034), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1035), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1069), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1070), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1072), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1073), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1074), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1076), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1077), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1078), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1110), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1111), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1113), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1114), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1115), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1117), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1118), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1119), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1153), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1154), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1156), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1157), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1158), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1160), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1161), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1162), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1192), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1193), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1194), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1195), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1196), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1197), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1198), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1199), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1228), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1229), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1230), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1232))));};

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1233), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1234), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1236), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1237), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1238), UNITY_DISPLAY_STYLE_INT);

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1271), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1272), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1273), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1275), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1276), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1277), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1279), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1280), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1314), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1315), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1316), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1318), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1319), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1320), UNITY_DISPLAY_STYLE_INT);



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1322))));};



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1324), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1325), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1326), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1327), UNITY_DISPLAY_STYLE_INT);

    if (((1) != (motor2->step))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1328)));};

    if (((1) != (motor2->sleep))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(1329)));};



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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1365), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1366), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1367), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1369), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1370), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1371), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1373), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1374), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1375), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1376), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1377), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1378), UNITY_DISPLAY_STYLE_INT);



   if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1380))));};

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

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1420), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1421), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1422), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1424), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1425), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1426), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1428), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(1429), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1430), UNITY_DISPLAY_STYLE_HEX32);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1434), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1435), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1437), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1438), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1439), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1441), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1442), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1443), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1445), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1446), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();



    if ((((motorRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1450))));};



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1452), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1453), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1454), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1456), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1457), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1459), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1460), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1461), UNITY_DISPLAY_STYLE_INT);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1498), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1499), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1500), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1502), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1503), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1504), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->step)), (((void *)0)), (_U_UINT)(1506), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->sleep)), (((void *)0)), (_U_UINT)(1507), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1508), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1509), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1511), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1512), UNITY_DISPLAY_STYLE_HEX32);

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



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1548), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1549), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1550), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1552), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1553), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1554), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->step)), (((void *)0)), (_U_UINT)(1556), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->sleep)), (((void *)0)), (_U_UINT)(1557), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(1558), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(1559), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(1561), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(1562), UNITY_DISPLAY_STYLE_HEX32);

}
