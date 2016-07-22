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






void resetMotorDriveBuffer(void);

motorInfo motor;



void setUp(void)

{

  HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));

  HostDma1 = malloc((sizeof(DMA_TypeDef)));

}



void tearDown(void)

{

  free(HostDma1_Channel3);

  free(HostDma1);

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

  resetMotorDriveBuffer();

}





void func1(void){



}



void resetMotorDriveBuffer(void){

  motorDriveBuffer[FIRST_MOTOR] = 0;

  motorDriveBuffer[SECOND_MOTOR] = 0;

  motorDriveBuffer[THIRD_MOTOR] = 0;

}



void initialStepCommand(motorConfigInfo* motorConfiguration){

  motorConfiguration->stepLowCommand = 0xAA;

  motorConfiguration->stepHighCommand = 0x55;

}



void test_initialStepCommand_(void){

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((motorConfig->stepLowCommand)), (((void *)0)), (_U_UINT)(63), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((motorConfig->stepHighCommand)), (((void *)0)), (_U_UINT)(64), UNITY_DISPLAY_STYLE_INT);



}



void test_getCommond_(void){

  printf("NO.01");

  motorInfo motor1;

  motorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  motorConfig->stepHighCommand = 0xFF;

  motorConfig->stepLowCommand = 0xF0;

  UnityAssertEqualNumber((_U_SINT)((0xF0)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(74), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(75), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((getCommand(motorConfig))), (((void *)0)), (_U_UINT)(76), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(77), UNITY_DISPLAY_STYLE_INT);

}



void test_resetMotorDriveBuffer_(void){

  printf("NO.02");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(84), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_off_third_motor_can_be_update(void){

  printf("NO.04.2");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_On_the_third_motor_can_not_be_update(void){

  printf("NO.04.3");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(146), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_put_motorConfig1_that_relate_First_Motor_into_the_motorStep_motorDriveBuffer_should_be_update(void){

  printf("NO.03");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(180), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(184), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_started_Second_motor_can_not_be_update(void){

  printf("NO.04.1");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(213), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(215), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(216), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(217), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_first_motor_can_be_update(void){

  printf("NO.06");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(247), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(248), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(250), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(251), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_second_motor_can_not_be_update(void){

  printf("NO.05");



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(281), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(282), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(283), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_Third_motor_can_be_update(void){

  printf("NO.07");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(310), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(311), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(312), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(313), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(314), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_two_Command_is_transmitted_first_motor_can_not_be_update(void){

  printf("NO.07.1");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(341), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(344), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(345), UNITY_DISPLAY_STYLE_INT);

}







void test_motorStep_add_third_motor_and_first_motor_commad_into_tx_buffer(void){

  printf("NO.08");





  txRoot = createLinkedList();



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig3);

  motorStep(motorConfig3);



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig1);

  motorStep(motorConfig1);







  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(369), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->txElement)), (((void *)0)), (_U_UINT)(370), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(371), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(372), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(373), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(374), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_add_third_and_sec_commad_into_tx_buffer(void){

  printf("NO.08");



  txRoot = createLinkedList();



  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig3);

  motorStep(motorConfig3);



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig2);

  motorStep(motorConfig2);





  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(407), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->txElement)), (((void *)0)), (_U_UINT)(408), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(409), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(411), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(413), UNITY_DISPLAY_STYLE_INT);

}
