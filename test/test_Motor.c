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
#include "Config.h"
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
  motorDriveBuffer[0] = 0;
  motorDriveBuffer[1] = 0;
  motorDriveBuffer[2] = 0;
}

void initialStepCommand(motorConfigInfo* motorConfiguration){
  motorConfiguration->stepLowCommand = 0xAA;
  motorConfiguration->stepHighCommand = 0x55;
}

void test_initialStepCommand_the_value_stepLowCommand_and_stepHighCommand_is_changed_to_0xAA_and_0x55(void){
  printf("No 1.0");
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig);
  TEST_ASSERT_EQUAL(0xAA,motorConfig->stepLowCommand);
  TEST_ASSERT_EQUAL(0x55,motorConfig->stepHighCommand);  
}

void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){
  printf("No 1.1");
  motorInfo motor1; 
  motorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig);
  TEST_ASSERT_EQUAL(0xAA,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
  TEST_ASSERT_EQUAL(0x55,getCommand(motorConfig));
  TEST_ASSERT_EQUAL(2,motorConfig->counter);
}

void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){
  printf("No 1.2");
  resetMotorDriveBuffer();
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[3]);
}


/*

       DmaPointer        
          V         
       Update                                                Update
         ||                                                   ||
         V                                                    V
        slot0  slot1  slot2                                 slot0  slot1  slot2   
      --------------------   motorStep(triMotorConfig);     -----------------
     |  0  |  0  |  0    |         ------->                | low  |  0  |  0  | 
     --------------------                                  -----------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot0_still_can_be_update(void){
  printf("No 2.0");
  setDataNumber(DMA1_Channel3,Motor_Number);
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

              update                                               update
   DmaPointer  ||                                          sending  ||
         V     V                                              V     V
      slot0  slot1  slot2                                 slot0  slot1  slot2  
      --------------------   motorStep(secMotorConfig);     -------------------
     |  0  |  0  |  0    |         ------->                | 0  |  low  |  0  | 
     --------------------                                  -------------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot1_still_can_be_update(void){
  printf("No 3.0");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,3);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*

                     
                     update                                               update
      DmaPointer      ||                                   DmaPointer      ||
         V            V                                       V            V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      --------------------   motorStep(secMotorConfig);     -------------------
     |  0  |  0  |  0  |         ------->                  | 0  |  0  |  low  | 
     --------------------                                  -------------------
     (motorDriveBuffer)

*/
void test_motorStep_when_DmaPointer_point_to_slot0_the_data_of_slot2_still_can_be_update(void){
  printf("No 4.0");
  
  txRoot = createLinkedList();
  setDataNumber(DMA_Channel,Motor_Number);
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);  
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

        Update                                             Update
         ||    DmaPointer                                    ||    DmaPointer  
         V       V                                           V       V     
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      --------------------   motorStep(firMotorConfig);     -------------------
     |  0  |  0  |  0    |         ------->                | 0  |  0  |  0   | 
     --------------------                                  -------------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot0_still_can_not_be_update(void){
  printf("No 5.0");
  startDMA(DMA1_Channel3); 
  txRoot = createLinkedList();
  setDataNumber(DMA1_Channel3,2);
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}




/*

     
              DmaPointer                                      DmaPointer 
                V                                                V
              Update                                          Update 
               ||                                               || 
               V                                                V
       slot0  slot1  slot2                              slot0  slot1  slot2  
      ------------------   motorStep(secMotorConfig);   ------------------ 
     |  0  |  0  |  0  |         ------->              | 0  |  Low  |  0 | 
     ------------------                                ------------------ 
     (motorDriveBuffer)

*/
void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot1_still_can_be_update(void){
  printf("No 6.0");
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
    
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

                     Update                                               Update
         DmaPointer   ||                                       DmaPointer  ||
               V      V                                              V     V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      --------------------   motorStep(firMotorConfig);     -------------------
     |  0  |  0  |  0    |         ------->                | 0  |  0  |  low  | 
     --------------------                                  -------------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DmaPointer_point_to_slot1_the_data_of_slot2_still_can_be_update(void){
  printf("No 7.0");
  startDMA(DMA1_Channel3); 
  txRoot = createLinkedList();
  setDataNumber(DMA1_Channel3,2);
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

       update                                               update
         ||         DmaPointer                               ||         DmaPointer
         V             V                                     V              V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      ------------------   motorStep(firMotorConfig);     ----------------- 
     |  0  |  0  |  0  |         ------->                | 0  |  0  |  0  | 
     ------------------                                  ----------------- 
     (motorDriveBuffer)

*/
void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot0_still_can_not_be_update(void){
  printf("No 8.0");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,1);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*

              update                                               update
                ||  DmaPointer                                      ||   DmaPointer
                V      V                                            V      V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      ------------------   motorStep(firMotorConfig);     ----------------- 
     |  0  |  0  |  0  |         ------->                | 0  |  0  |  0  | 
     ------------------                                  ----------------- 
     (motorDriveBuffer)

*/

void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot1_still_can_not_be_update(void){
  printf("No 9.0");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,1);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}


/*
                    DmaPointer                                          DmaPointer
                       V                                                   V
                    update                                               update
                      ||                                                  ||
                      V                                                   V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      ------------------   motorStep(firMotorConfig);     ----------------- 
     |  0  |  0  |  0  |         ------->                | 0  |  0  |  0  | 
     ------------------                                  ----------------- 
     (motorDriveBuffer)

*/
void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){
  printf("No 10.0");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,1);
  txRoot = createLinkedList();
  motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}



/*
    Head-->triMotorElement                   Head-->triMotorElement->firMotorElement
        
       slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  0    |   0   |  0  |         ------->              | low |  0   |  low  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)
*/

void test_motorStep_the_firMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_firMotorElem(void){
  printf("NO 11.0");

  txRoot = createLinkedList();
  
  setDataNumber(DMA1_Channel3,3);
  motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig3);
  motorStep(motorConfig3);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig1);
  motorStep(motorConfig1);
  
  TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig3->txElement);
  TEST_ASSERT_EQUAL_PTR(txRoot->head->next,&motorConfig1->txElement);
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
}

/*
  
    Head-->triMotorElement                               Head-->triMotorElement->secMotorElement
                update
                  V
        3nd      2nd    1st                                     3nd   2nd   1st
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   0   |  0  |         ------->              | low |  low   |  0  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)

*/


void test_motorStep_the_secMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_secMotorElem(void){
  printf("No 12.0");

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



void test_motorSet_the_motor_setting_was_set_by_using_motorSet_the_stepHighCommand_and_stepLowCommand_should_return_the_motor_setting(void){
    printf("No 13.0");
    uint8_t tempHigh = Motor_Clockwise
                      |Motor_Step_High
                      |Motor_Full_step
                      |Motor_Sleep_Mode_Disable
                      |Motor_Sleep_Reset_Disable
                      |Motor_Enable;
    uint8_t tempLow = tempHigh&Motor_Step_Low;
    
    motorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);
    motorSet(Motor3,Motor_Clockwise,Motor_Full_step);
    
    TEST_ASSERT_EQUAL(tempHigh,Motor3->motorConfiguration->stepHighCommand);
    TEST_ASSERT_EQUAL(tempLow,Motor3->motorConfiguration->stepLowCommand);
}


void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){
      printf("No 14.0");
    setDataNumber(DMA_Channel,3);
    TEST_ASSERT_EQUAL(3,DMA1_Channel3->CNDTR);
  
}




/*

  DMA1_Channel3->CNDTR = 3    DMA was stoped.
                     
       Update                                               Update
         ||                                                   ||
         V                                                    V
        slot0  slot1  slot2                                 slot0  slot1  slot2       
      --------------------    motorStep(triMotorConfig);   ------------------
     |  0  |  0  |  0    |         ------->                | 0  |  0  |  0   | 
     --------------------                                 ------------------
     (motorDriveBuffer)

*/

// void xtest_motorStep_update_slot_command_when_the_DMA_was_stopped(void){
  // printf("NO.04.2");
  // txRoot = createLinkedList();
  // setDataNumber(DMA_Channel,3);
  // motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
  // initialStepCommand(motorConfig);
  
 // _motorStep(motorConfig);
  
  // TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
  // TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
// }


/*

  DMA1_Channel3->CNDTR = 3    DMA was started.
         
         Update
          ||
          V         
        Sending                                            Sending
         V                                                   V
        3nd   2nd    1st                                    3nd   2nd   1st
      --------------------   motorStep(triMotorConfig);     -----------------
     |  x  |  0  |  0    |         ------->                | x  |  0  |  0  | 
     --------------------                                  -----------------
     (motorDriveBuffer)

*/

// void xtest_motorStep_When_DMA_is_On_the_third_motor_can_not_be_update(void){
  // printf("NO.04.3");
  // setDataNumber(DMA1_Channel3,3);
  // startDMA(DMA1_Channel3); 
  // txRoot = createLinkedList();
  // motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
  // initialStepCommand(motorConfig);
  
  // motorStep(motorConfig);
  
  // TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  // TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
// }

/*

  DMA1_Channel3->CNDTR = 2    DMA was started.
     
       update
         ||  Sending                                            Sending
         V     V                                                  V
        3nd   2nd   1st                                    3nd   2nd   1st
      ------------------   motorStep(triMotorConfig);     ----------------- 
     |  x  |  x  |  0  |         ------->                | x  |  x  |  0  | 
     ------------------                                  ----------------- 
     (motorDriveBuffer)

*/
// void xtest_motorStep_One_Command_is_transmitted_Third_motor_can_be_update(void){
  // printf("NO.07");
  // startDMA(DMA1_Channel3); 
  // setDataNumber(DMA1_Channel3,2);
  // txRoot = createLinkedList();
  // motorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
  // initialStepCommand(motorConfig);
  // motorStep(motorConfig);
  // TEST_ASSERT_EQUAL_PTR(txRoot->head,&motorConfig->txElement);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(0,motorDriveBuffer[THIRD_MOTOR]);
  // TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
// }

