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

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig->counter)), (((void *)0)), (_U_UINT)(77), UNITY_DISPLAY_STYLE_INT);



}











void test_resetMotorDriveBuffer_(void){

  printf("NO.02");

  resetMotorDriveBuffer();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(89), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_put_motorConfig1_that_relate_First_Motor_into_the_motorStep_motorDriveBuffer_should_be_update(void){

  printf("NO.03");

    (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(111), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_started_Second_motor_can_not_be_update(void){

  printf("NO.04.1");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(139), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(141), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(142), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(143), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_off_third_motor_can_be_update(void){

  printf("NO.04.2");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(165), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(167), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(168), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_When_DMA_is_On_third_motor_can_be_update(void){

  printf("NO.04.3");

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(192), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_first_motor_can_be_update(void){

  printf("NO.06");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(219), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(220), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_second_motor_can_not_be_update(void){

  printf("NO.05");



  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);

  initialStepCommand(motorConfig);



  motorStep(motorConfig);



  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(246), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(247), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(248), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(250), UNITY_DISPLAY_STYLE_INT);

}

void test_motorStep_One_Command_is_transmitted_Third_motor_can_be_update(void){

  printf("NO.07");

  (DMA_Cmd(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),ENABLE));

  setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

  txRoot = createLinkedList();

  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);

  initialStepCommand(motorConfig);

  motorStep(motorConfig);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig->txElement)), (((void *)0)), (_U_UINT)(270), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(272), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

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







  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(303), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig1->txElement)), (((void *)0)), (_U_UINT)(304), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(305), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(306), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(307), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(308), UNITY_DISPLAY_STYLE_INT);

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







  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head)), (_U_SINT)(_UP)((&motorConfig3->txElement)), (((void *)0)), (_U_UINT)(336), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((txRoot->head->next)), (_U_SINT)(_UP)((&motorConfig2->txElement)), (((void *)0)), (_U_UINT)(337), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(338), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(339), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(340), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

}
