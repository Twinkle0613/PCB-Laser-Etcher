#include "unity.h"
#include "Motor.h"
//General Library
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM standard Library
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
//Own Library
#include "Host.h"
#include "Registers.h"
#include "DMA.h"
#include "Timer.h"
#include "Linklist.h"
#include "DMA_setting.h"
#include "peripherals.h"
#include "Timer_setting.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"

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
  HostDma1_Channel3 = NULL;
  HostDma1 = NULL;
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
  TEST_ASSERT_EQUAL(0xAA,motorConfig->stepLowCommand);
  TEST_ASSERT_EQUAL(0x55,motorConfig->stepHighCommand);
  
}

void test_getCommond_(void){
  printf("NO.01");
  motorInfo motor1; 
  motorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);
  motorConfig->stepHighCommand = 0xFF;
  motorConfig->stepLowCommand = 0xF0;
  TEST_ASSERT_EQUAL(0xF0,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
  TEST_ASSERT_EQUAL(0xFF,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(0,motorConfig->counter);
  
}
  // motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
  // motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
  // motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
  

void test_resetMotorDriveBuffer_(void){
  printf("NO.02");
  resetMotorDriveBuffer();
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
}

/*
  DMA1_Channel3->CNDTR = 3    DMA is OFF.
                                           (FIRST_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(FirMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0xFF;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[SECOND_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0; 

*/
void test_motorStep_put_motorConfig1_that_relate_First_Motor_into_the_motorStep_motorDriveBuffer_should_be_update(void){
  printf("NO.03");
    startDMA(DMA1_Channel3); 
  txRoot = createLinkedList();
  setDataNumber(DMA1_Channel3,3);
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

  DMA1_Channel3->CNDTR = 3    DMA is ON.
                                          (SECOND_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(triMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0; 

*/

void test_motorStep_When_DMA_is_started_Second_motor_can_not_be_update(void){
  printf("NO.04.1");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,3);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*

  DMA1_Channel3->CNDTR = 3    DMA is off.
                                          (THIRD_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(triMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0xAA; 

*/

void test_motorStep_When_DMA_is_off_third_motor_can_be_update(void){
  printf("NO.04.2");
  setDataNumber(DMA1_Channel3,3);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*

  DMA1_Channel3->CNDTR = 3    DMA is On.
                                          (THIRD_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(triMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0xAA; 

*/

void test_motorStep_When_DMA_is_On_third_motor_can_be_update(void){
  printf("NO.04.3");
  setDataNumber(DMA1_Channel3,3);
  startDMA(DMA1_Channel3); 
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

  DMA1_Channel3->CNDTR = 2    DMA is ON.
                                          (FIRST_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(firMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0; 

*/
void test_motorStep_One_Command_is_transmitted_first_motor_can_be_update(void){
  printf("NO.06");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*

  DMA1_Channel3->CNDTR = 2    DMA is NO.
                                          (SECOND_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(secMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0; 

*/
void test_motorStep_One_Command_is_transmitted_second_motor_can_not_be_update(void){
  printf("NO.05");
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,SECOND_MOTOR);
  initialStepCommand(motorConfig);
    
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*

  DMA1_Channel3->CNDTR = 2    DMA is ON.
                                          (THIRD_MOTOR)
  motorDriveBuffer[FIRST_MOTOR]  = 0;   motorStep(firMotor);    motorDriveBuffer[FIRST_MOTOR]  = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;      -------->            motorDriveBuffer[SECOND_MOTOR] = 0; 
  motorDriveBuffer[THIRD_MOTOR] = 0;                           motorDriveBuffer[THIRD_MOTOR] = 0; 

*/
void test_motorStep_One_Command_is_transmitted_Third_motor_can_be_update(void){
  printf("NO.07");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*
            
   ------  motorStep(firMotor);   ------
  |3| | |     -------->          |3| |1|
  ------                         ------
*/
void test_motorStep_add_third_motor_and_first_motor_commad_into_tx_buffer(void){
  printf("NO.08");

  
  txRoot = createLinkedList();
  
  setDataNumber(DMA1_Channel3,3);
  motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig3);
  motorStep(motorConfig3);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig1);
  motorStep(motorConfig1);
  
  
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig3->txElement);
  TEST_ASSERT_EQUAL_PTR(txRoot->head->next,&motorConfig1->txElement);
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*
            
   ------  motorStep(firMotor);   ------
  |3| | |     -------->          |3|2| |
  ------                         ------
*/
void test_motorStep_add_third_and_sec_commad_into_tx_buffer(void){
  printf("NO.08");

  
  txRoot = createLinkedList();
  
  setDataNumber(DMA1_Channel3,3);
  motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig3);
  motorStep(motorConfig3);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,3);
  motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
  initialStepCommand(motorConfig2);
  motorStep(motorConfig2);
  
  
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig3->txElement);
  TEST_ASSERT_EQUAL_PTR(txRoot->head->next,&motorConfig2->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
  TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
  
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}
