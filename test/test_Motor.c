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

#include "mock_MockFunction.h"
#include "mock_getTick.h"

void resetMotorDriveBuffer(void);
MotorInfo motor; 

uint32_t* tickPointer = NULL;
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
  HostDma1_Channel3 = NULL;
  HostDma1 = NULL;
  HostGpioA = NULL;
  resetMotorDriveBuffer();
  motorRoot = NULL;
  root = NULL;
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
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->motorElement.next);
  TEST_ASSERT_NULL(whichMotor->motorConfiguration->motorElement.prev);
  TEST_ASSERT_EQUAL_PTR(testMotor,whichMotor->motorConfiguration->motorElement.callBack);
  TEST_ASSERT_EQUAL_PTR(whichMotor,whichMotor->motorConfiguration->motorElement.args);
  
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


//************initialStepCommand************//
void test_initialStepCommand_the_value_stepLowCommand_and_stepHighCommand_is_changed_to_0xAA_and_0x55(void){
  printf("No 1.0");
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,FIRST_MOTOR);
  initialStepCommand(motorConfig);
  TEST_ASSERT_EQUAL(0xAA,motorConfig->stepLowCommand);
  TEST_ASSERT_EQUAL(0x55,motorConfig->stepHighCommand);  
}

//***************getCommand************//
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


//***************resetMotorDriveBuffer************//
void test_resetMotorDriveBuffer_the_data_of_motoDriveBuffer_should_become_0(void){
  printf("No 1.2");
  resetMotorDriveBuffer();
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[3]);
}

//***********************motorStep*********************//
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
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,motorRoot->head->next);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
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
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,motorRoot->head->next);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
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
  
  motorRoot = createLinkedList();
  setDataNumber(DMA_Channel,Motor_Number);
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);  
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
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
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,2);
    MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
    initialStepCommand(motorConfig);
    
    motorStep(motorConfig);
    
    TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorConfig->counter);
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
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);

  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
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
  motorRoot = createLinkedList();
  setDataNumber(DMA1_Channel3,2);
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);
  
  motorStep(motorConfig);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
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
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,0);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(0,motorConfig->counter);
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
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,1);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(0,motorConfig->counter);
}


/*
                    DmaPointer                                          DmaPointer
                       V                                                   V
                    update                                               update
                      ||                                                  ||
                      V                                                   V
       slot0  slot1  slot2                                 slot0  slot1  slot2  
      ------------------   motorStep(firMotorConfig);     ----------------- 
     |  0  |  0  |  0  |         ------->                | 0  |  0  |  low  | 
     ------------------                                  ----------------- 
     (motorDriveBuffer)

*/
void test_motorStep_when_DmaPointer_point_to_slot2_the_data_of_slot2_still_can_be_update(void){
  printf("No 10.0");
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,1);
  motorRoot = createLinkedList();
  MotorConfigInfo* motorConfig = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig);
  motorStep(motorConfig);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig->motorElement);
  TEST_ASSERT_EQUAL(motorConfig->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig->counter);
}



/*
    Head-->Motor0Element                   Head-->Motor0Element->Motor2Element
        
       slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low    |   0   |  0  |         ------->              | low |  0   |  low  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)
*/

void test_motorStep_the_firMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_firMotorElem(void){
  printf("NO 11.0");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);
  initialStepCommand(motorConfig0); //slot 0
  initialStepCommand(motorConfig2); //slot 2
  
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig0);
  
  startDMA(DMA1_Channel3); 
  setDataNumber(DMA1_Channel3,2);
  motorStep(motorConfig2);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig2->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next,&motorConfig0->motorElement);
  
  TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig0->stepLowCommand,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig0->counter);
  TEST_ASSERT_EQUAL(1,motorConfig2->counter);
}

/*
  
    Head-->Motor0Element                               Head-->Motor0Element->Motor1Element
                update
                  V
        slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   0   |  0  |         ------->              | low |  low   |  0  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)

*/


void test_motorStep_the_secMotorElem_is_added_into_linked_list_the_next_of_triMotorElem_should_point_to_secMotorElem(void){
  printf("No 12.0");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);
  
  initialStepCommand(motorConfig0);
  initialStepCommand(motorConfig1);
  
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig0);
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig1);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig1->motorElement);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig0->stepLowCommand,motorDriveBuffer[0]);
  
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig0->counter);
  TEST_ASSERT_EQUAL(1,motorConfig1->counter);
}

/*
  
    Head-->Motor0Element                               Head-->Motor0Element->Motor1Element
                update
                  V
         slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   0   |  0  |         ------->              | low |  low   |  0  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)
     
    Head-->Motor0Element->Motor1Element               Head-->Motor0Element->Motor0Element->Motor2Element
                update
                  V
         slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   low   |  0  |         ------->            | low |  low   |  low  | 
     -----------------------                                ---------------------

*/

void test_motorStep_Motor0Element_Motor1Element_and_Motor2Element_was_added_into_linked_list_at_the_same_time(void){
  printf("No 12.1");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);
  
  initialStepCommand(motorConfig0);
  initialStepCommand(motorConfig1);
  initialStepCommand(motorConfig2);
  
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig0);
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig1);
  motorStep(motorConfig2);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig1->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next,&motorConfig2->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next->next,&motorConfig0->motorElement);
  
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig0->stepLowCommand,motorDriveBuffer[0]);
  
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig0->counter);
  TEST_ASSERT_EQUAL(1,motorConfig1->counter);
  TEST_ASSERT_EQUAL(1,motorConfig2->counter);
}

/*
    Head-->Motor0Element->Motor2Element        Head-->Motor0Element->Motor2Element->Motor1Element
                                                                   update
                                                                      V
       slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low    |   0   |  low  |         ------->           | low |  0   |  low  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)
*/

void test_motorStep_did_not_update_slot1_but_add_the_Motor2Element_into_linked_list(void){
  printf("NO 12.2");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);
  
  initialStepCommand(motorConfig0); //slot 0
  initialStepCommand(motorConfig1); //slot 0
  initialStepCommand(motorConfig2); //slot 2
  
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig0);
  
  setDataNumber(DMA1_Channel3,2);
  motorStep(motorConfig2);

  setDataNumber(DMA1_Channel3,1);
  motorStep(motorConfig1);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig2->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next,&motorConfig1->motorElement);
  
  TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig0->stepLowCommand,motorDriveBuffer[0]);
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  
  TEST_ASSERT_EQUAL(1,motorConfig0->counter);
  TEST_ASSERT_EQUAL(0,motorConfig1->counter);
  TEST_ASSERT_EQUAL(1,motorConfig2->counter);
}

/*
  
    Head-->Motor0Element->Motor1Element               Head-->Motor0Element->Motor1Element->Motor2Element

        slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   low   |  0  |         ------->            | low |  low   |  0  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DataNumber_is_0_the_slot2_cant_be_update_but_the_Motor2Element_was_added_into_linked_list(void){
  printf("No 12.3");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);
  
  initialStepCommand(motorConfig0);
  initialStepCommand(motorConfig1);
  initialStepCommand(motorConfig2);
  
  setDataNumber(DMA1_Channel3,3);
  motorStep(motorConfig0);
  setDataNumber(DMA1_Channel3,2);
  motorStep(motorConfig1);
  setDataNumber(DMA1_Channel3,0);
  motorStep(motorConfig2);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig1->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next,&motorConfig2->motorElement);
  
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(motorConfig0->stepLowCommand,motorDriveBuffer[0]);
  
  TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
  TEST_ASSERT_EQUAL(1,motorConfig0->counter);
  TEST_ASSERT_EQUAL(1,motorConfig1->counter);
  TEST_ASSERT_EQUAL(0,motorConfig2->counter);
  
}

/*
  
    Head-->Motor0Element->Motor1Element               Head-->Motor0Element->Motor1Element->Motor2Element

        slot0  slot1  slot2                                   slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    ---------------------
     |  0   |   0   |  0   |         ------->                |  0  |  0   |  0  | 
     -----------------------                                ---------------------
     (motorDriveBuffer)

*/

void test_motorStep_when_DataNumber_is_0_the_all_of_slot_cant_be_update_but_the_all_MotorElement_were_added_into_linked_list(void){
  printf("No 12.4");

  motorRoot = createLinkedList();
  
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor,func1,0);
  MotorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,1);
  MotorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,2);
  
  initialStepCommand(motorConfig0);
  initialStepCommand(motorConfig1);
  initialStepCommand(motorConfig2);
  
  setDataNumber(DMA1_Channel3,0);
  motorStep(motorConfig0);
  motorStep(motorConfig1);
  motorStep(motorConfig2);
  
  TEST_ASSERT_EQUAL_PTR(motorRoot->head,&motorConfig0->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next,&motorConfig1->motorElement);
  TEST_ASSERT_EQUAL_PTR(motorRoot->head->next->next,&motorConfig2->motorElement);
  
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
  TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
  
  TEST_ASSERT_EQUAL(0,motorConfig0->counter);
  TEST_ASSERT_EQUAL(0,motorConfig1->counter);
  TEST_ASSERT_EQUAL(0,motorConfig2->counter);
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

#define motor2Config motor2->motorConfiguration
#define motor1Config motor1->motorConfiguration
#define motor0Config motor0->motorConfiguration


void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){
  printf("motorConfigInit\n");
  printf("No 1.0");
  MotorInfo motor0; 
  MotorConfigInfo* motorConfig0 = motorConfigInit(&motor0,func1,0);
  TEST_ASSERT_EQUAL(0,motorConfig0->counter);
  TEST_ASSERT_EQUAL(0,motorConfig0->slot);
  TEST_ASSERT_EQUAL(0,motorConfig0->stepHighCommand);
  TEST_ASSERT_EQUAL(0,motorConfig0->stepLowCommand);
  TEST_ASSERT_NULL(motorConfig0->motorElement.next);
  TEST_ASSERT_NULL(motorConfig0->motorElement.prev);
  TEST_ASSERT_EQUAL_PTR(func1,motorConfig0->motorElement.callBack);

}

void test_extractMotorConfigInfo_(void){
   printf("extractMotorConfigInfo\n");
   printf("No 2.0");
   MotorConfigInfo* motorConfig;
   MotorInfo* Motor0 = motorInit(func1,10000,0);
   motorConfig = extractMotorConfigInfo(Motor0->motorConfiguration->motorElement.args);
   TEST_ASSERT_EQUAL(Motor0,motorConfig->motorElement.args);
}

void test_dmaQueue_add_one_motorElement_into_Queue(void){
    printf("dmaQueue\n");
    printf("No 3.0");
    motorRoot = createLinkedList();
    MotorInfo motor2; 
    MotorConfigInfo* motorConfig2 = motorConfigInit(&motor2,func1,2);
    dmaQueue(&motorConfig2->motorElement);
    TEST_ASSERT_EQUAL_PTR(&motorConfig2->motorElement,motorRoot->head);
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
    TEST_ASSERT_EQUAL_PTR(&motorConfig0->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motorConfig1->motorElement,motorRoot->head->next);
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
    
    temp = dmaDequeue(motorRoot);
    TEST_ASSERT_EQUAL_PTR(&motorConfig0->motorElement,temp);
    temp = dmaDequeue(motorRoot);
    TEST_ASSERT_EQUAL_PTR(&motorConfig1->motorElement,temp);
    TEST_ASSERT_NULL(motorRoot->head);

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
    printf("updateMotorDriveBuffer\n");
    printf("No 4.0");  
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    MotorInfo* motor0 = motorInit(func1,1000,0);
    initialStepCommand(motor0Config);
    dmaQueue(&motor0Config->motorElement);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
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
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);

    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    
    dmaQueue(&motor0Config->motorElement);
    dmaQueue(&motor1Config->motorElement);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
    
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(1,motor1Config->counter);
}



/*
  
    Head-->motor0Element->motor1Element->motor2Element
    
      slot0  slot1  slot2                                  slot0  slot1  slot2   
      ------------------   updateMotorDriveBuffer();     ---------------------- 
     |  0  |  0  |  0  |         ------->               | Low |  Low  |  Low  | 
     ------------------                                 -----------------------
       (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_the_linkedlist_contain_motor0Element_motor1Element_and_motor2Elementent_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){
    printf("No 4.2");      
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    dmaQueue(&motor0Config->motorElement);
    dmaQueue(&motor1Config->motorElement);
    dmaQueue(&motor2Config->motorElement);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head->next->next);
    
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
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    initialStepCommand(motor0Config);
    
    motorStep(motor0Config);
    updateMotorDriveBuffer();

    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(2,motor0Config->counter);

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
    motorRoot = createLinkedList();
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
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head->next->next);
    
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepLowCommand,motorDriveBuffer[2]);
    
    updateMotorDriveBuffer();

    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);

    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL(2,motor2Config->counter);
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
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(func1,1000,0);
    MotorInfo* motor1 = motorInit(func1,1000,1);
    MotorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor2Config);
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head->next);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head->next);
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor2Config->counter);
}

/*
  
    Head-->motor0Element->motor2Element                    Head->motor0Element->motor2Element 
    
         slot0  slot1  slot2                                 slot0  slot1  slot2  
      -----------------------   updateMotorDriveBuffer();    -----------------------
     |  0   |   0   |  low  |         ------->              |  0  |  low  |  High  | 
     -----------------------                                -----------------------
     (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor2Element_after_function_linkedList_contain_motor2Element(void){
    printf("No 4.6");     
    motorRoot = createLinkedList();
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
   
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
    
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepLowCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_EQUAL(1,motor1Config->counter);
    TEST_ASSERT_EQUAL(2,motor2Config->counter);
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
    motorRoot = createLinkedList();
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
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);

    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
}


/*
  
    Head-->motor1Element                                  Head-->motor1Element->motor0Element
    
        slot0  slot1  slot2                                  slot0  slot1  slot2   
      -----------------------   updateMotorDriveBuffer();    ------------------------
     |  0   |   low   |  0  |         ------->              |  low  |  High   |  0  | 
     -----------------------                                ------------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_motor0Element_and_motor1Element_after_function_linkedList_only_contain_motor1Element(void){
    printf("No 4.8");     
    motorRoot = createLinkedList();
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
    
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head->next);
    
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
}



/**********************_motorMovementHandler************************/

/*
  
    Head-->motor0Element                                   Head-->motor0Element
        counter = 1                                               counter = 2
        slot0  slot1  slot2                                 slot0  slot1  slot2   
      -----------------------   motorMovementHandler();  ----------------------
     |  low   |   0   |  0  |         ------->              | High |  0   |   0   | 
     -----------------------                                ----------------------
     (motorDriveBuffer)
*/
void test_motorMovementHandler_the_DMA_IRQ_function_will_update_motor0Element_Command(void){
    printf("No 5.0"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    motorStep(motor0Config);
    
    motorMovementHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head->next);
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
    
}

/*
  
    Head-->motor0Element                                   Head-->NULL
        counter = 2                                               counter = 0
        slot0  slot1  slot2                                   slot0  slot1  slot2   
      -----------------------   motorMovementHandler();  ----------------------
     |  High   |   0   |  0  |         ------->             | High |  0   |  0    | 
     -----------------------                                ----------------------
     (motorDriveBuffer)

*/
void test_motorMovementHandler_the_DMA_IRQ_function_was_called_in_2_times_and_the_head_of_queue_is_point_to_null(void){
    printf("No 5.1"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    motorStep(motor0Config);
    
    motorMovementHandler();
    motorMovementHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
    
    TEST_ASSERT_NULL(motorRoot->head);
    TEST_ASSERT_EQUAL(1,motor0->step); // called callBack function
    TEST_ASSERT_EQUAL(1,motor0->sleep);
    
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
}


/*
  
    Head-->motor0Elementent->motor1Element                 Head-->motor0Elementent->motor1Element
    counter3 = 1  counter2 = 1                             counter = 2 counter = 2
        slot0  slot1  slot2                                    slot0  slot1  slot2
      -----------------------   motorMovementHandler();    ----------------------
     |  low   |   Low   |  0  |         ------->              | High |  High  |  0  | 
     -----------------------                                  ----------------------
     (motorDriveBuffer)

*/

void test_motorMovementHandler_the_DMA_IRQ_function_will_update_triMotorSlot_and_secMotorSlot_Command(void){
    printf("No 5.2"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    
    motorMovementHandler();
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
        
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(2,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
}

/*
  
    Head-->motor0Elementent->motor1Element                 Head-->NULL
    counter3 = 2  counter2 = 2                             counter = 0 counter = 0
         slot0  slot1  slot2                                    slot0  slot1  slot2 
      -----------------------   motorMovementHandler();    ----------------------
     |  High  |  High  |  0  |         ------->              | High |  High  |  0  | 
     -----------------------                                  ----------------------
     (motorDriveBuffer)

*/

void test_motorMovementHandler_motor0Element_and_motor1Element_that_updated_completely_should_be_dequeue(void){
    printf("No 5.3"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    
    motorMovementHandler();
    motorMovementHandler();
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
        
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
    
    TEST_ASSERT_NULL(motorRoot->head);
    
    TEST_ASSERT_EQUAL(1,motor0->step);
    TEST_ASSERT_EQUAL(1,motor0->sleep);
    TEST_ASSERT_EQUAL(1,motor1->step);
    TEST_ASSERT_EQUAL(1,motor1->sleep);
    TEST_ASSERT_NOT_EQUAL(1,motor2->step);
    TEST_ASSERT_NOT_EQUAL(1,motor2->sleep);
    
}

/*
  
    Head-->motor0Elementent->motor1Element->motor2Element          Head-->NULL
    counter3 = 2  counter2 = 2 counter1 = 2                 counter = 0 counter = 0 counter1 = 0 
        slot0  slot1  slot2                                         slot0  slot1  slot2   
      --------------------------  motorMovementHandler();    ----------------------
     |  High  |  High  |  High |          ------->              | High |  High  |  High  | 
     --------------------------                                 ----------------------
     (motorDriveBuffer)

*/

void test_motorMovementHandler_motor0Element__motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){
       printf("No 5.31"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);

    motorMovementHandler();
    motorMovementHandler();
    
   TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
   TEST_ASSERT_EQUAL(0,motor0Config->counter);
   TEST_ASSERT_EQUAL(0,motor1Config->counter);
   TEST_ASSERT_EQUAL(0,motor2Config->counter);
   
   TEST_ASSERT_EQUAL(1,motor0->step);
   TEST_ASSERT_EQUAL(1,motor0->sleep);
   TEST_ASSERT_EQUAL(1,motor1->step);
   TEST_ASSERT_EQUAL(1,motor1->sleep);
   TEST_ASSERT_EQUAL(1,motor2->step);
   TEST_ASSERT_EQUAL(1,motor2->sleep);
    
   TEST_ASSERT_NULL(motorRoot->head);
}

/*
    Head-->motor0Element->motor1Element                 Head->motor1Element
    
        slot0  slot1  slot2                                   slot0  slot1  slot2
      -------------------------   motorMovementHandler()   ----------------------
     |   0   |   0   |  Low  |         ------->              | low |  0  |  High  | 
     -------------------------                                ----------------------
     (motorDriveBuffer)
     
    Head-->motor1Element                                    Head->NULL
    
        slot0  slot1  slot2                                   slot0  slot1  slot2
      -------------------------   motorMovementHandler()      ----------------------
     |   low   |   0   |  High |         ------->            | High |  0  |  High  | 
     -------------------------                               ----------------------
     (motorDriveBuffer)
*/

void test_motorMovementHandler_motor0ment_and_motor1Element_(void){
    printf("No 5.4"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    
    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);

    motorStep(motor2Config);
    setDataNumber(DMA1_Channel3,1);
    motorStep(motor0Config);
    

    motorMovementHandler();
    TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(1,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(2,motor2Config->counter);
    
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor2Config->motorElement,motorRoot->head->next->next);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head->next);

    motorMovementHandler();
    
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head->next);
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(2,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);

    TEST_ASSERT_EQUAL(1,motor2->step);
    TEST_ASSERT_EQUAL(1,motor2->sleep);

    motorMovementHandler();
    
    TEST_ASSERT_NULL(motorRoot->head);
    
    TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
    TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    TEST_ASSERT_EQUAL(1,motor0->step);
    TEST_ASSERT_EQUAL(1,motor0->sleep);
    
    TEST_ASSERT_EQUAL(0,motor0Config->counter);
    TEST_ASSERT_EQUAL(0,motor1Config->counter);
    TEST_ASSERT_EQUAL(0,motor2Config->counter);
}

/*
    Head-->motor0Elementent->motor1Element->motor2Element          Head-->motor1Element
    counter3 = 2  counter2 = 1 counter1 = 2                 counter = 0 counter = 2 counter1 = 0 
        slot0  slot1  slot2                                         slot0  slot1  slot2   
      --------------------------  motorMovementHandler();    ----------------------
     |  High  |  low  |  High |          ------->              | High |  High  |  High  | 
     --------------------------                                 ----------------------
     (motorDriveBuffer)
*/

void test_motorMovementHandler_motor0Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){
    printf("No 5.5"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);

    motorMovementHandler();

    motor1Config->counter = 1;
    motorDriveBuffer[1] = motor0Config->stepLowCommand;

    motorMovementHandler();

   TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
   TEST_ASSERT_EQUAL(0,motor0Config->counter);
   TEST_ASSERT_EQUAL(2,motor1Config->counter);
   TEST_ASSERT_EQUAL(0,motor2Config->counter);
   
   TEST_ASSERT_EQUAL(1,motor0->step);
   TEST_ASSERT_EQUAL(1,motor0->sleep);
   TEST_ASSERT_EQUAL(1,motor2->step);
   TEST_ASSERT_EQUAL(1,motor2->sleep);
    
   TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1Config->motorElement,motorRoot->head->next);
}

/*
    Head-->motor0Elementent->motor1Element->motor2Element          Head-->motor0Element
    counter0 = 1  counter1 = 2 counter2 = 2                 counter0 = 2 counter1 = 0 counter2 = 0 
        slot0  slot1  slot2                                         slot0  slot1  slot2   
      --------------------------  motorMovementHandler();    ----------------------
     |  Low  |  High  |  High |          ------->              | High |  High  |  High  | 
     --------------------------                                 ----------------------
     (motorDriveBuffer)

*/

void test_motorMovementHandler_motor1Element_and_motor2Element_that_updated_completely_should_be_dequeue(void){
       printf("No 5.6"); 
    motorRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);

    MotorInfo* motor0 = motorInit(testMotor,1000,0);
    MotorInfo* motor1 = motorInit(testMotor,1000,1);
    MotorInfo* motor2 = motorInit(testMotor,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);

    motorMovementHandler();
    motor0Config->counter = 1;
    motorDriveBuffer[0] = motor0Config->stepLowCommand;
    motorMovementHandler();
    
   TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
   
   TEST_ASSERT_EQUAL(2,motor0Config->counter);
   TEST_ASSERT_EQUAL(0,motor1Config->counter);
   TEST_ASSERT_EQUAL(0,motor2Config->counter);
   
   TEST_ASSERT_EQUAL(1,motor1->step);
   TEST_ASSERT_EQUAL(1,motor1->sleep);
   TEST_ASSERT_EQUAL(1,motor2->step);
   TEST_ASSERT_EQUAL(1,motor2->sleep);
    
   TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0Config->motorElement,motorRoot->head->next);
}

//************getFakeTick****************//
void test_getFakeTick(void){
  
  uint32_t stickTable[] = {1000,2000,3000};
  setTickSequence(stickTable);
  TEST_ASSERT_EQUAL(1000,getFakeTick());
  TEST_ASSERT_EQUAL(2000,getFakeTick());
  TEST_ASSERT_EQUAL(3000,getFakeTick());
  
}

void test_getTick(void){
  uint32_t stickTable[] = {1000,2000,3000};
  setTickSequence(stickTable);
  TEST_ASSERT_EQUAL(1000,getTick(TIM2));
  TEST_ASSERT_EQUAL(2000,getTick(TIM2));
  TEST_ASSERT_EQUAL(3000,getTick(TIM2));
  
}
/*
getTickInterval = tickRecord2 - tickRecord1 = 200 - 100 = 100     recordTick = 300;        
                                                getTickInterval() = 100     recordTick = 300;        
     Head                                   Head                           Head
      V                                      V                              V
   -------     -------  TIM2_IRQHandler    -------  motorMovementHandler   -------     -------
  | 2000 | -> | 4000 |      --->          | 4000 |      --->              | 1900 | -> | 1800 | 
  -------     -------                     -------                         -------     -------

                                          motorHead                      motorHead
                                             V                              V               
                                           --------- motorMovementHandler   V
                                          | motor0 |     --->             NULL
                                          ---------                       
*/
void test_motorMovementHandler_the_DMA_interrupt_has_occured_two_time_the_timer_link_list_have_contained_two_element(void){
   printf("No 6.0"); 
   MotorInfo* motor0 = motorInit(motorController,2000,0);
   MotorInfo* motor1 = motorInit(motorController,6000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,100,200,300,400};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,2000);
   _timerDelay(&motor1->timerElement,6000);
   TEST_ASSERT_EQUAL(2000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(4000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(4000,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(2200,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(2300,root->curTime);
   TEST_ASSERT_EQUAL(2300,root->baseTime);
   TEST_ASSERT_EQUAL(1900,TIM2->ARR);
   TEST_ASSERT_EQUAL(1900,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1800,motor1->timerElement.actionTime);
}

/*
                                 getTickInterval = 100
                                 timerDelay(Element,2000 - getTickInterval);
                                  currentTick = 300;            
     Head                                   Head                           Head
      V                                      V                              V
   -------     -------  TIM2_IRQHandler    -------  motorMovementHandler   -------     -------
  | 2000 | -> | 4000 |      --->          | 4000 |      --->              | 1900 | -> | 1800 | 
  -------     -------                     -------                         -------     -------

                                          motorHead                      motorHead
                                             V                              V               
                                           --------- motorMovementHandler   V
                                          | motor0 |     --->             NULL
                                          ---------                       

                                                             period = 1900     1800
                                                             <------------><---------->       
                                                            |-------------|-----------|
                                                           0                        3700                                      
*/
void test_motorMovementHandler_the1(void){
   printf("No 6.1"); 
   MotorInfo* motor0 = motorInit(motorController,2000,0);
   MotorInfo* motor1 = motorInit(motorController,6000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,100,200,300};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,2000);
   _timerDelay(&motor1->timerElement,6000);
   TEST_ASSERT_EQUAL(2000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(4000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(4000,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(2100,tickRecord1);
   TEST_ASSERT_EQUAL(2200,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(2300,root->curTime);
   TEST_ASSERT_EQUAL(2300,root->baseTime);
   TEST_ASSERT_EQUAL(1900,TIM2->ARR);
   TEST_ASSERT_EQUAL(1900,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1800,motor1->timerElement.actionTime);
}

/*
                                 getTickInterval = 100
                                 timerDelay(Element,3000 - getTickInterval);
                                  currentTick = 300;        
     Head                                   Head                           Head
      V                                      V                              V
   -------     -------  TIM2_IRQHandler    -------  motorMovementHandler   -------     -------
  | 3000 | -> | 3000 |      --->          | 3000 |      --->              | 2700 | -> | 200  | 
  -------     -------                     -------                         -------     -------

                                          motorHead                      motorHead
                                             V                              V               
                                           --------- motorMovementHandler   V
                                          | motor0 |     --->             NULL
                                          ---------                       
                                          
                                          
                                                                          period = 2900
                                                                       <----------------->       
                                                                  |---|-------------|----|
                                                                  0  300          2700  300
*/

void test_motorMovementHandler_the_timer_link_list_has_contain_two_element_such_as_3000_and_6000(void){
   printf("No 6.2"); 
   MotorInfo* motor0 = motorInit(motorController,3000,0);
   MotorInfo* motor1 = motorInit(motorController,6000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,100,200,300};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,3000);
   _timerDelay(&motor1->timerElement,6000);
   TEST_ASSERT_EQUAL(3000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(3100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(3000,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(3100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3100,tickRecord1);
   TEST_ASSERT_EQUAL(3200,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(3300,root->curTime);
   TEST_ASSERT_EQUAL(3300,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(2700,TIM2->ARR);
   TEST_ASSERT_EQUAL(200,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2700,motor1->timerElement.actionTime);
}

/*
                                  getTickInterval = 0
                                  timerDelay(Element,3000 - getTickInterval);
                                  currentTick = 300;        
     Head                                   Head                           Head
      V                                      V                               V
   -------     -------  TIM2_IRQHandler    -------  motorMovementHandler   -------     -------
  | 3000 | -> | 3000 |      --->          | 3000 |      --->              | 3000 | -> | 300  | 
  -------     -------                     -------                         -------     -------

                                          motorHead                      motorHead
                                             V                              V               
                                           --------- motorMovementHandler   V
                                          | motor0 |     --->             NULL
                                          ---------                       
                                                                          period = 3000
                                                                       <----------------->       
                                                                  |---|-------------|----|
                                                                  0  300          3000  300
    
    
*/

void test_motorMovementHandler_with_3000_and_6000_elem_in_link_list(void){
   printf("No 6.3"); 
   MotorInfo* motor0 = motorInit(motorController,3000,0);
   MotorInfo* motor1 = motorInit(motorController,6000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,0,0,300};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,3000);
   _timerDelay(&motor1->timerElement,6000);
   TEST_ASSERT_EQUAL(3000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(3000,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(3000,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(3000,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3000,tickRecord1);
   TEST_ASSERT_EQUAL(3000,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(3300,root->curTime);
   TEST_ASSERT_EQUAL(3000,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(3000,TIM2->ARR);
   TEST_ASSERT_EQUAL(300,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3000,motor1->timerElement.actionTime);
}



/*
    
     Head                                           Head                                         
      V                                              V                                            
   -------   -------   -------  TIM2_IRQHandler   -------      -------  motorMovementHandler     
  | 1000 |->| 2000 |->| 4000 |     --->          | 2000 | --> | 4000 |        --->             
  -------   -------   -------                    -------      -------                          

                                               motorHead                      motorHead
                                                   V                              V               
                                                --------- motorMovementHandler    V
                                               | motor0 |     --->              NULL
                                               ---------                       
    Head                                               
     V                                        
   ------     ------     -------                                            
  | 900 | -> | 800 | -> | 4000 |                                               
  ------     ------     -------

*/

void test_motorMovementHandler_with_1000_2000_and_4000_elem_in_timer_link_list(void){
   printf("No 6.4"); 
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,3000,1);
   MotorInfo* motor2 = motorInit(motorController,7000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,0,100,200,300,400,500};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,1000);
   _timerDelay(&motor1->timerElement,3000);
   _timerDelay(&motor2->timerElement,7000);
   
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(1100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(2000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);   
   TEST_ASSERT_EQUAL(2000,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(1100,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(1100,tickRecord1);
   TEST_ASSERT_EQUAL(1200,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1300,root->curTime);
   TEST_ASSERT_EQUAL(1300,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(900,TIM2->ARR);
   
   TEST_ASSERT_EQUAL(900,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(800,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor2->timerElement.actionTime);
}


/*
    
     Head                                           Head                                         
      V                                              V                                            
   -------   -------   -------  TIM2_IRQHandler   -------      -------  motorMovementHandler     
  | 900  |->| 800  |->| 4000 |     --->          | 800  | --> | 4000 |        --->             
  -------   -------   -------                    -------      -------                          
  Motor0    Motor1     Motor2
                                               motorHead                      motorHead
                                                   V                              V               
                                                --------- motorMovementHandler    V
                                               | motor0 |     --->              NULL
                                               ---------                       
    
    Head    period = motor->period - getInterval = 900                                          
     V      DifBetweenBaseAndCur = 600
   ------     ------     -------                                            
  | 800 | -> | 700 | -> | 3300 |                                               
  ------     ------     -------
  Motor0    Motor1     Motor2
*/

void test_motorMovementHandler_with_900_800_and_4000_elem_in_timer_link_list(void){
   printf("No 6.5"); 
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,3000,1);
   MotorInfo* motor2 = motorInit(motorController,7000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,0,400,500,600};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,900);
   _timerDelay(&motor1->timerElement,1700);
   _timerDelay(&motor2->timerElement,5700);
   
   TEST_ASSERT_EQUAL(900,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(800,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(1300,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(800,TIM2->ARR);
   TEST_ASSERT_EQUAL(800,root->head->actionTime);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);   
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(1300,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(1300,tickRecord1);
   TEST_ASSERT_EQUAL(1400,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1500,root->curTime);
   TEST_ASSERT_EQUAL(900,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(800,TIM2->ARR);
   
   TEST_ASSERT_EQUAL(800,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(700,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3300,motor2->timerElement.actionTime);
}


/*
    
     Head                                           Head                                         
      V                                              V                                            
   -------   -------   -------  TIM2_IRQHandler   -------      -------  motorMovementHandler     
  |  1   |->|   9  |->|  90  |     --->          | 800  | --> | 4000 |        --->             
  -------   -------   -------                    -------      -------                          
  Motor0    Motor1     Motor2
                                               motorHead                      motorHead
                                                   V                              V               
                                                --------- motorMovementHandler    V
                                               | motor0 |     --->              NULL
                                               ---------                       
    
    Head    period = motor->period - getInterval = 900                                          
     V      DifBetweenBaseAndCur = 600
   ------     ------     -------                                            
  | 800 | -> | 700 | -> | 3300 |                                               
  ------     ------     -------
  Motor0    Motor1     Motor2
*/

void test_motorMovementHandler_with_1_9_and_90_elem_in_timer_link_list(void){
   printf("No 6.5"); 
   MotorInfo* motor0 = motorInit(motorController,1,0);
   MotorInfo* motor1 = motorInit(motorController,10,1);
   MotorInfo* motor2 = motorInit(motorController,100,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   uint32_t stickTable[] = {0,0,0,0,0,0,0,0,0,0,0,0};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
   
   _timerDelay(&motor0->timerElement,1);
   _timerDelay(&motor1->timerElement,2);
   _timerDelay(&motor2->timerElement,12);
   
   TEST_ASSERT_EQUAL(1,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(10,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(1,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(1,TIM2->ARR);
   TEST_ASSERT_EQUAL(1,root->head->actionTime);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);   
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(1,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(1,tickRecord1);
   TEST_ASSERT_EQUAL(1,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1,root->curTime);
   TEST_ASSERT_EQUAL(1,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(1,TIM2->ARR);
   
   TEST_ASSERT_EQUAL(1,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(10,motor2->timerElement.actionTime);
   
   //////New Start////////////
    TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(2,tickRecord1);
   TEST_ASSERT_EQUAL(1,tickRecord2);
   TEST_ASSERT_EQUAL(10,TIM2->ARR);
   TEST_ASSERT_EQUAL(10,root->head->actionTime);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);   
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(3,getDataNumber(DMA1_Channel3));
   TEST_ASSERT_EQUAL(1,DMA1_Channel3->CCR&0x01);
   TEST_ASSERT_EQUAL(0,DMA_GetITStatus(DMA1_IT_TC1));
   TEST_ASSERT_EQUAL(2,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(2,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(2,tickRecord1);
   TEST_ASSERT_EQUAL(1,tickRecord2);
   
   motorMovementHandler();
   TEST_ASSERT_EQUAL(2,tickRecord1);
   TEST_ASSERT_EQUAL(2,tickRecord2);
   TEST_ASSERT_NULL(motorRoot->head);
   TEST_ASSERT_EQUAL(0,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepHighCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepHighCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   //motorController call timerDelay
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TEST_ASSERT_EQUAL(2,root->curTime);
   TEST_ASSERT_EQUAL(2,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(1,TIM2->ARR);
   
   TEST_ASSERT_EQUAL(1,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(9,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   
   
}



void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_20_the_function_should_return_10(void){
  printf("No 7.0");
  tickRecord1 = 10;
  tickRecord2 = 20;
  
 TEST_ASSERT_EQUAL(10,getNewPeriod(20));
  
  
}

void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_5_the_function_should_return_1(void){
  printf("No 7.1");
  tickRecord1 = 10;
  tickRecord2 = 20;
  
 TEST_ASSERT_EQUAL(1,getNewPeriod(5));
  
  
}

void test_getNewPeriod_tickInterval_is_10_and_initial_period_is_10_the_function_should_return_1(void){
  printf("No 7.2");
  tickRecord1 = 10;
  tickRecord2 = 20;
  
 TEST_ASSERT_EQUAL(1,getNewPeriod(10));
  
  
}