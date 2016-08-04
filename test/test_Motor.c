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
  HostDma1_Channel3 = NULL;
  HostDma1 = NULL;
  resetMotorDriveBuffer();
   free(HostGpioA);
   HostGpioA = NULL;
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
  /* Initialzation Motor */
  TEST_ASSERT_EQUAL(StpMtr_Clockwise,whichMotor->direation);
  TEST_ASSERT_EQUAL(StpMtr_Low,whichMotor->step);
  TEST_ASSERT_EQUAL(StpMtr_Slp_Off,whichMotor->sleep);
  TEST_ASSERT_EQUAL(StpMtr_Full_step,whichMotor->microstep);
  TEST_ASSERT_EQUAL(0,whichMotor->period);
  TEST_ASSERT_EQUAL(0,whichMotor->state);
  /* Initialzation Timer Elemenet */
  TEST_ASSERT_NULL(whichMotor->timerElement.next);
  TEST_ASSERT_NULL(whichMotor->timerElement.prev);
  TEST_ASSERT_EQUAL_PTR(testMotor,whichMotor->timerElement.callBack);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->timerElement.args);
  TEST_ASSERT_EQUAL(0,whichMotor->timerElement.actionTime);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->counter);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->slot);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->stepHighCommand);
  TEST_ASSERT_EQUAL(0,whichMotor->motorConfiguration->stepLowCommand);
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->txElement.next);
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->txElement.prev);
  TEST_ASSERT_EQUAL_PTR(testMotor,whichMotor->motorConfiguration->txElement.callBack);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->motorConfiguration->txElement.args);
  
}

void test_setCallBack_the_callBack_of_timerElement_of_whichMotor_was_set_the_address_of_testMotor_functon_(void){
  printf("No 1.1");
  MotorInfo* whichMotor = motorInit(testMotor,0,FIRST_MOTOR);
  setCallBack(&whichMotor->timerElement,testMotor);
  whichMotor->timerElement.callBack(whichMotor);
  TEST_ASSERT_EQUAL(1,whichMotor->step);
  TEST_ASSERT_EQUAL(1,whichMotor->sleep);
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
  TEST_ASSERT_EQUAL(0xAA,motorConfig->stepLowCommand);
  TEST_ASSERT_EQUAL(0x55,motorConfig->stepHighCommand);  
}

void test_getCommond_first_called_getCommand_should_return_0xAA_and_second_called_getCommand_should_retun_0x55(void){
  printf("No 1.1");
  MotorInfo motor1; 
  MotorConfigInfo* motorConfig = motorConfigInit(&motor1,func1,FIRST_MOTOR);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,THIRD_MOTOR);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
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
    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
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
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
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
  MotorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig3);
  motorStep(motorConfig3);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,2);
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
  MotorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
  initialStepCommand(motorConfig3);
  motorStep(motorConfig3);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,3);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
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
    
    MotorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);
    motorSet(Motor3,Motor_Clockwise,Motor_Full_step);
    
    TEST_ASSERT_EQUAL(tempHigh,Motor3->motorConfiguration->stepHighCommand);
    TEST_ASSERT_EQUAL(tempLow,Motor3->motorConfiguration->stepLowCommand);
}


void test_DMA_channel_marco_the_DMAy_chanelx_that_was_executed_in_system_was_defined_into_DMA_channel_marco(void){
      printf("No 14.0");
    setDataNumber(DMA_Channel,3);
    TEST_ASSERT_EQUAL(3,DMA1_Channel3->CNDTR);
  
}



///////////////////////////////////////////

#define motorConfig3 Motor3->motorConfiguration
#define motorConfig2 Motor2->motorConfiguration
#define motorConfig1 Motor1->motorConfiguration

#define motor2Config motor2->motorConfiguration
#define motor1Config motor1->motorConfiguration
#define motor0Config motor0->motorConfiguration


void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){
  printf("No 1.0");
  MotorInfo motor1; 
  MotorConfigInfo* txDetail = motorConfigInit(&motor1,func1,FIRST_MOTOR);
  TEST_ASSERT_EQUAL(0,txDetail->counter);
  TEST_ASSERT_EQUAL(FIRST_MOTOR,txDetail->slot);
  TEST_ASSERT_EQUAL(0,txDetail->stepHighCommand);
  TEST_ASSERT_EQUAL(0,txDetail->stepLowCommand);
  TEST_ASSERT_NULL(txDetail->txElement.next);
  TEST_ASSERT_NULL(txDetail->txElement.prev);
  TEST_ASSERT_EQUAL_PTR(func1,txDetail->txElement.callBack);

}

void test_readMotorConfigInfo_(void){
   printf("No 2.0");
   MotorConfigInfo* motorConfig;
   MotorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);
   motorConfig = readMotorConfigInfo(Motor3->motorConfiguration->txElement.args);
   TEST_ASSERT_EQUAL(Motor3,motorConfig->txElement.args);
}

void test_dmaQueue_add_one_txElement_into_Queue(void){
    printf("No 3.0");
    txRoot = createLinkedList();
    MotorInfo motor1; 
    MotorInfo motor2; 
    MotorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    dmaQueue(&txDetail1->txElement);
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,txRoot->head);
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
    
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&txDetail2->txElement,txRoot->head->next);
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
    temp = dmaDequeue(txRoot);
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,temp);
    temp = dmaDequeue(txRoot);
    TEST_ASSERT_EQUAL_PTR(&txDetail2->txElement,temp);
    TEST_ASSERT_NULL(txRoot->head);

}

/****************updateMotorDriveBuffer*****************/
/*
  
    Head-->motor0Element
    
      slot0  slot1  slot2                                 slot0  slot1  slot2   
      ------------------   updateMotorDriveBuffer();     ------------------ 
     | 0   |  0  |  0  |         ------->               | Low |  0  |  0 | 
     ------------------                                 ------------------ 
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_the_linkedlist_only_contain_motor0Element_and_Update_the_triMotor_slot_buffer(void){
     printf("No 4.0");  
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    MotorInfo* motor0 = motorInit(func1,1000,0);
    initialStepCommand(motor0Config);
    dmaQueue(&motor0Config->txElement);
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
}


/*
  
    Head-->motor0Element->motor1Element
    
      slot0  slot1  slot2                                 slot0  slot1  slot2   
      ------------------   updateMotorDriveBuffer();     --------------------
     | 0   |  0  |  0  |         ------->               | Low |  low  |  0  | 
     ------------------                                 --------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_and_motor1Element_and_Update_the_triMotor_and_secMotor_slot_buffer(void){
    printf("No 4.1");    
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);

    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    
    dmaQueue(&motor0Config->txElement);
    dmaQueue(&motor1Config->txElement);
    
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(1,motor1Config->counter);
}



/*
  
    Head-->motor0Element->motor1Element->motor2Element
    
      slot0  slot1  slot2                                 slot0  slot1  slot2   
      ------------------   updateMotorDriveBuffer();         ---------------------- 
     |  0  |  0  |  0  |         ------->                   | Low |  Low  |  Low  | 
     ------------------                                     -----------------------
       (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_motor1Element_and_motor2Elementent_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){
    printf("No 4.2");      
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    dmaQueue(&motor0Config->txElement);
    dmaQueue(&motor1Config->txElement);
    dmaQueue(&motor2Config->txElement);
    
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor2Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepLowCommand,motorDriveBuffer[2]);
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(1,motor1Config->counter);
    TEST_ASSERT_EQUAL(1,motor2Config->counter);
}


/*
  
    Head-->motor0Element                             
    
      slot0  slot1  slot2                                 slot0  slot1  slot2   
      ------------------   updateMotorDriveBuffer();     ------------------ 
     | Low   |  0  |  0  |         ------->             | High |  0  |  0 | 
     ------------------                                 ------------------ 
     (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_after_function_it_should_dequeue(void){
    printf("No 4.3");      
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    initialStepCommand(motor0Config);
    
    motorStep(motor0Config);
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
}



/*
  
    Head-->motor0Element->motor1Element->motor2Element           
    
           slot0  slot1  slot2                                 slot0  slot1  slot2   
      -----------------------   updateMotorDriveBuffer();      -----------------------
     |  low   |  low  |  low  |         ------->              | High | High |  High  | 
     -----------------------                                  -----------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_motor0Element_motor1Element_and_motor2Element_after_function_they_should_dequeue(void){
    printf("No 4.4");           
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->txElement,txRoot->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->txElement,txRoot->head->next->next);
    
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepLowCommand,motorDriveBuffer[2]);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
}

/*
  
    Head-->motor0Element->motor2Element                 
    
           slot0  slot1  slot2                                 slot0  slot1  slot2   
      -------------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   0   |  low  |         ------->              | High |  0  |  High | 
     -------------------------                                ---------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_they_should_dequeue(void){
    printf("No 4.5"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor2Config);
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->txElement,txRoot->head->next);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
}

/*
  
    Head-->motor0Element->motor2Element                    Head-->motor2Element
    
         slot0  slot1  slot2                                 slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    -----------------------
     |  0   |   0   |  low  |         ------->              |  0  |  low  |  High  | 
     -----------------------                                -----------------------
     (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_linkedList_contain_motor2Element(void){
    printf("No 4.6");     
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor2Config);
    setDataNumber(DMA1_Channel3,1);
    motorStep(motor1Config);
    
    updateMotorDriveBuffer();
   
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
}

/*
  
    Head-->motor0Element->motor1Element        
    
         slot0  slot1  slot2                                 slot0  slot1  slot2 
      -----------------------   updateMotorDriveBuffer();    --------------------
     |  low   |  low  |  0  |         ------->              | High | High |  0  | 
     -----------------------                                --------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_is_emply(void){
    printf("No 4.7");  
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    
    updateMotorDriveBuffer();
    

    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
}


/*
  
    Head-->motor0Element                                  Head-->motor0Element->motor1Element
    
        slot0  slot1  slot2                                  slot0  slot1  slot2   
      -----------------------   updateMotorDriveBuffer();    ----------------------
     |  0   |   low   |  0  |         ------->              |  low  |  High   |  0  | 
     -----------------------                                ----------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_only_contain_motor1Element(void){
    printf("No 4.8");     
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor1Config);
    setDataNumber(DMA1_Channel3,2);
    motorStep(motor0Config);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
}
/**********************_DMA1_Channel3_IRQHandler************************/

/*
  
    Head-->motor0Element                                   Head-->motor0Element
        counter = 1                                               counter = 2
        slot0  slot1  slot2                                 slot0  slot1  slot2   
      -----------------------   DMA1_Channel3_IRQHandler();  ----------------------
     |  low   |   0   |  0  |         ------->              | High |  0   |   0   | 
     -----------------------                                ----------------------
     (motorDriveBuffer)
*/
void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_will_update_motor0Element_Command(void){
    printf("No 5.0"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    motorStep(motor0Config);
    
    DMA1_Channel3_IRQHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    
}

/*
  
    Head-->motor0Element                                   Head-->NULL
        counter = 2                                               counter = 0
        slot0  slot1  slot2                                   slot0  slot1  slot2   
      -----------------------   DMA1_Channel3_IRQHandler();  ----------------------
     |  High   |   0   |  0  |         ------->             | High |  0   |  0    | 
     -----------------------                                ----------------------
     (motorDriveBuffer)

*/
void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_was_called_in_2_times_and_the_head_of_queue_is_point_to_null(void){
    printf("No 5.1"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    motorStep(motor0Config);
    
    DMA1_Channel3_IRQHandler();
    DMA1_Channel3_IRQHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_NULL(txRoot->head);
    
}


/*
  
    Head-->motor0Elementent->motor1Element                 Head-->motor0Elementent->motor1Element
    counter3 = 1  counter2 = 1                             counter = 2 counter = 2
        slot0  slot1  slot2                                    slot0  slot1  slot2
      -----------------------   DMA1_Channel3_IRQHandler();    ----------------------
     |  low   |   Low   |  0  |         ------->              | High |  High  |  0  | 
     -----------------------                                  ----------------------
     (motorDriveBuffer)

*/

void test_DMA1_Channel3_IRQHandler_the_DMA_IRQ_function_will_update_triMotorSlot_and_secMotorSlot_Command(void){
    printf("No 5.2"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    
    DMA1_Channel3_IRQHandler();
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->txElement,txRoot->head->next);
}

/*
  
    Head-->motor0Elementent->motor1Element                 Head-->NULL
    counter3 = 2  counter2 = 2                             counter = 0 counter = 0
         slot0  slot1  slot2                                    slot0  slot1  slot2 
      -----------------------   DMA1_Channel3_IRQHandler();    ----------------------
     |  High  |  High  |  0  |         ------->              | High |  High  |  0  | 
     -----------------------                                  ----------------------
     (motorDriveBuffer)

*/

void test_DMA1_Channel3_IRQHandler_motor0Element_and_motor1Element_that_updated_completely_should_be_dequeue(void){
    printf("No 5.3"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    
    DMA1_Channel3_IRQHandler();
    DMA1_Channel3_IRQHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_NULL(txRoot->head);
    
}

/*
  
    Head-->motor0Elementent->motor1Element->motor2Element          Head-->NULL
    counter3 = 2  counter2 = 2 counter1 = 2                 counter = 0 counter = 0 counter1 = 0 
        slot0  slot1  slot2                                         slot0  slot1  slot2   
      --------------------------  DMA1_Channel3_IRQHandler();    ----------------------
     |  High  |  High  |  High |          ------->              | High |  High  |  High  | 
     --------------------------                                 ----------------------
     (motorDriveBuffer)

*/

void test_DMA1_Channel3_IRQHandler_motor0Element__motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){
       printf("No 5.31"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);

    DMA1_Channel3_IRQHandler();
    DMA1_Channel3_IRQHandler();
    
   TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
   TEST_ASSERT_EQUAL(0,motor0Config->counter);
   TEST_ASSERT_EQUAL(0,motor1Config->counter);
   TEST_ASSERT_EQUAL(0,motor2Config->counter);
   TEST_ASSERT_NULL(txRoot->head);
}

/*
  
    Head-->motor0Elementent->motor1Element                 Head->motor1Element
    
        slot0  slot1  slot2                                   slot0  slot1  slot2
      -------------------------   DMA1_Channel3_IRQHandler()   ----------------------
     |   0   |   0   |  Low  |         ------->              | low |  0  |  High  | 
     -------------------------                                ----------------------
     (motorDriveBuffer)
     
    Head-->motor1Element                                    Head->NULL
    
        slot0  slot1  slot2                                   slot0  slot1  slot2
      -------------------------   DMA1_Channel3_IRQHandler()    ----------------------
     |   low   |   0   |  High |         ------->              | High |  0  |  High  | 
     -------------------------                                ----------------------
     (motorDriveBuffer)

*/

void test_DMA1_Channel3_IRQHandler_motor0Element_and_motor1Element_(void){
    printf("No 5.4"); 
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    
    motorStep(motor2Config);
    setDataNumber(DMA1_Channel3,1);
    motorStep(motor0Config);
    

    DMA1_Channel3_IRQHandler();
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    DMA1_Channel3_IRQHandler();
    TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
    
    DMA1_Channel3_IRQHandler();
    TEST_ASSERT_NULL(txRoot->head);
}
