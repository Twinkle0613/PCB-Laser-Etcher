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

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

  resetMotorDriveBuffer();

   free(HostGpioA);

   HostGpioA = ((void *)0);

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

  if ((((whichMotor->motorConfiguration->txElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(79))));};

  if ((((whichMotor->motorConfiguration->txElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(80))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((testMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->txElement.callBack)), (((void *)0)), (_U_UINT)(81), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((whichMotor)), (_U_SINT)(_UP)((whichMotor->motorConfiguration->txElement.args)), (((void *)0)), (_U_UINT)(82), UNITY_DISPLAY_STYLE_HEX32);



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

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(111), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_INT);

}



void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){

  printf("No 1.1");

  MotorInfo motor1;

  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(120), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(121), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

}



void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){

  printf("No 1.2");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(129), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){

  printf("No 2.0");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(158), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){

  printf("No 3.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(189), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(190), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(191), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(192), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){

  printf("No 4.0");



  txRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(220), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);

}

  void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){

    printf("No 5.0");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

    initialStepCommand(motorConfig);



    motorStep(motorConfig);



    UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(251), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(252), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(253), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(254), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(255), UNITY_DISPLAY_STYLE_INT);

  }

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){

  printf("No 6.0");



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(287), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(289), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(290), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(291), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){

  printf("No 7.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(318), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(319), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(320), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(321), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(322), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){

  printf("No 8.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(346), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(347), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(348), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(350), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){

  printf("No 9.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(375), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(376), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(377), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(378), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(379), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){

  printf("No 10.0");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  txRoot = createLinkedList();

  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(404), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(405), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(406), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(407), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(408), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_the_firMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_firMotorElem(void){

  printf("NO 11.0");



  txRoot = createLinkedList();



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,0);

  initialStepCommand(motorConfig3);

  motorStep(motorConfig3);



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,2);

  initialStepCommand(motorConfig1);

  motorStep(motorConfig1);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(439), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->txElement)), (((void *)0)), (_U_UINT)(440), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(441), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(442), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(443), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(444), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_the_secMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_secMotorElem(void){

  printf("No 12.0");



  txRoot = createLinkedList();



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig3);

  motorStep(motorConfig3);



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig2);

  motorStep(motorConfig2);





  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(478), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->txElement)), (((void *)0)), (_U_UINT)(479), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(480), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(481), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(482), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(484), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((_U_SINT)((tempHigh)), (_U_SINT)((Motor3->motorConfiguration->stepHighCommand)), (((void *)0)), (_U_UINT)(502), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((tempLow)), (_U_SINT)((Motor3->motorConfiguration->stepLowCommand)), (((void *)0)), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);

}





void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){

      printf("No 14.0");

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CNDTR)), (((void *)0)), (_U_UINT)(510), UNITY_DISPLAY_STYLE_INT);



}

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){

  printf("No 1.0");

  MotorInfo motor1;

  MotorConfigInfo* txDetail = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->counter)), (((void *)0)), (_U_UINT)(531), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FIRST_MOTOR)), (_U_SINT)((txDetail->slot)), (((void *)0)), (_U_UINT)(532), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepHighCommand)), (((void *)0)), (_U_UINT)(533), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepLowCommand)), (((void *)0)), (_U_UINT)(534), UNITY_DISPLAY_STYLE_INT);

  if ((((txDetail->txElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(535))));};

  if ((((txDetail->txElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(536))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((txDetail->txElement.callBack)), (((void *)0)), (_U_UINT)(537), UNITY_DISPLAY_STYLE_HEX32);



}



void test_readMotorConfigInfo_(void){

   printf("No 2.0");

   MotorConfigInfo* motorConfig;

   MotorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);

   motorConfig = readMotorConfigInfo(Motor3->motorConfiguration->txElement.args);

   UnityAssertEqualNumber((_U_SINT)((Motor3)), (_U_SINT)((motorConfig->txElement.args)), (((void *)0)), (_U_UINT)(546), UNITY_DISPLAY_STYLE_INT);

}



void test_dmaQueue_add_one_txElement_into_Queue(void){

    printf("No 3.0");

    txRoot = createLinkedList();

    MotorInfo motor1;

    MotorInfo motor2;

    MotorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(556), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_txElement_into_Queue(void){

    printf("No 3.1");

    txRoot = createLinkedList();

    MotorInfo motor1;

    MotorInfo motor2;

    MotorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    MotorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    dmaQueue(&txDetail2->txElement);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(569), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(570), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_txElement_into_Queue_and_deQueue(void){

    printf("No 3.2");

    txRoot = createLinkedList();

    ListElement *temp;

    MotorInfo motor1;

    MotorInfo motor2;

    MotorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    MotorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    dmaQueue(&txDetail2->txElement);

    temp = dequeue(txRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(584), UNITY_DISPLAY_STYLE_HEX32);

    temp = dequeue(txRoot);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(586), UNITY_DISPLAY_STYLE_HEX32);

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(587))));};



}

void test_updateMotorDriveBuffer_the_linkedlist_only_contain_motor0Element_and_Update_the_triMotor_slot_buffer(void){

     printf("No 4.0");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);

    dmaQueue(&motor0->motorConfiguration->txElement);

    updateMotorDriveBuffer();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(611), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(612), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_and_motor1Element_and_Update_the_triMotor_and_secMotor_slot_buffer(void){

    printf("No 4.1");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);



    dmaQueue(&motor0->motorConfiguration->txElement);

    dmaQueue(&motor1->motorConfiguration->txElement);



    updateMotorDriveBuffer();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(642), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(643), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(644), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(645), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_motor1Element_and_motor2Elementent_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){

    printf("No 4.2");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    dmaQueue(&motor0->motorConfiguration->txElement);

    dmaQueue(&motor1->motorConfiguration->txElement);

    dmaQueue(&motor2->motorConfiguration->txElement);



    updateMotorDriveBuffer();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(680), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(681), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(682), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(683), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(684), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(685), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){

    printf("No 4.3");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    initialStepCommand(motor0->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(712), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(713), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(714), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_motor1Element_and_motor2Element_after_function_they_should_dequeue(void){

    printf("No 4.4");

    txRoot = createLinkedList();

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(747), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(748), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head->next->next)), (((void *)0)), (_U_UINT)(749), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(751), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(752), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(753), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(757), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(758), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(759), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_they_should_dequeue(void){

    printf("No 4.5");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor2->motorConfiguration);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(789), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(790), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(794), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(795), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(796), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_linkedList_contain_motor2Element(void){

    printf("No 4.6");

    txRoot = createLinkedList();

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



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(830), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(831), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_is_emply(void){

    printf("No 4.7");

    txRoot = createLinkedList();

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





    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(864), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(865), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(866), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_only_contain_motor1Element(void){

    printf("No 4.8");

    txRoot = createLinkedList();

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



    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(900), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(901), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(902), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(904), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(905), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(906), UNITY_DISPLAY_STYLE_INT);

}

void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_will_update_motor0Element_Command(void){

    printf("No 5.0");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    motorStep(motor0->motorConfiguration);



    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(933), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(934), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_HEX32);



}

void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_was_called_in_2_times_and_the_head_of_queue_is_point_to_null(void){

    printf("No 5.1");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    motorStep(motor0->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(964), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(965), UNITY_DISPLAY_STYLE_INT);

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(966))));};



}

void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_will_update_triMotorSlot_and_secMotorSlot_Command(void){

    printf("No 5.2");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1000), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1001), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1002), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1003), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(1004), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(1005), UNITY_DISPLAY_STYLE_HEX32);

}

void test_DMA1_Channel3_IRQHandler_motor0Element_and_motor1Element_that_updated_completely_should_be_dequeue(void){

    printf("No 5.3");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);



    motorStep(motor0->motorConfiguration);

    motorStep(motor1->motorConfiguration);



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1039), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1040), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1041), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1042), UNITY_DISPLAY_STYLE_INT);

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1043))));};



}

void test_DMA1_Channel3_IRQHandler_motor0Element__motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){

       printf("No 5.31");

    txRoot = createLinkedList();

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



    DMA1_Channel3_IRQHandler();

    DMA1_Channel3_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1079), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(1080), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1081), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1083), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1084), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1085), UNITY_DISPLAY_STYLE_INT);

   if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1086))));};

}

void test_DMA1_Channel3_IRQHandler_motor0Element_and_motor1Element_(void){

    printf("No 5.4");

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



    MotorInfo* motor0 = motorInit(func1,1000,0);

    MotorInfo* motor1 = motorInit(func1,1000,1);

    MotorInfo* motor2 = motorInit(func1,1000,2);



    initialStepCommand(motor0->motorConfiguration);

    initialStepCommand(motor1->motorConfiguration);

    initialStepCommand(motor2->motorConfiguration);





    motorStep(motor2->motorConfiguration);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

    motorStep(motor0->motorConfiguration);





    DMA1_Channel3_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1129), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1130), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(1133), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(1134), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepHighCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(1135), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1136), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(1137), UNITY_DISPLAY_STYLE_INT);



    DMA1_Channel3_IRQHandler();

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1140))));};

}
