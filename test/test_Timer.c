//General Library
#include "unity.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//STM standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
//Own Library
#include "getTick.h"
#include "DMA.h"
#include "DMA_setting.h"
#include "Host.h"
#include "Timer.h"
#include "Linklist.h"
#include "Registers.h"
#include "peripherals.h"
#include "projectStruct.h"
//#include "Timer_setting.h"
#include "CustomAssertion.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "Motor.h"
#include "mock_MockFunction.h"
#include "mock_getTick.h"
// #include "getTick.h"

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

void testMotor123(MotorInfo* whichMotor){
  whichMotor->step = 1;
  whichMotor->sleep = 1;
}

void initialStepCommand(MotorConfigInfo* motorConfiguration){
  motorConfiguration->stepLowCommand = 0xAA;
  motorConfiguration->stepHighCommand = 0x55;
}

void resetMotorDriveBuffer(void){
  motorDriveBuffer[0] = 0;
  motorDriveBuffer[1] = 0;
  motorDriveBuffer[2] = 0;
}


void setUp(void)
{
  getFakeTick_StubWithCallback(fake_getFakeTick);
  getTick_StubWithCallback(fake_getTick);
  
  HostTim2= malloc((sizeof(TIM_TypeDef)));
  HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));
  HostDma1 = malloc((sizeof(DMA_TypeDef)));
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
   free(HostTim2);
   HostTim2 = NULL;
   HostDma1_Channel3 = NULL;
   HostDma1 = NULL;
   root = NULL;
}

/*

    head                                head     
     ||                                  ||
     V                                   V
    10      => TIMx_IRQHandler()  =>    NULL

*/

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){
  
    root = createLinkedList();
    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);

    _updateBaseTime(root,10);
    updateCurTime(root,20);
    timerQueue(&motor1->timerElement,10);
    
    TEST_ASSERT_NOT_NULL(root->head);
    TIM2_IRQHandler();
     TEST_ASSERT_EQUAL(20,root->baseTime);
    TEST_ASSERT_NULL(motor1->timerElement.next);
    TEST_ASSERT_NULL(motor1->timerElement.prev);
    TEST_ASSERT_NULL(root->head);
}

/*

    head                                head     
     ||                                  ||
     V                                   V
    10-->5     => TIMx_IRQHandler()  =>  5

*/
void test_Test_TIMxIRQHandler_two_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){
  
    root = createLinkedList();
    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);
    int arr[] = {5};

    _updateBaseTime(root,10);
    updateCurTime(root,20);
    timerQueue(&motor1->timerElement,10);
    
    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(&motor2->timerElement,10);
    
    TIM2_IRQHandler();
    TEST_ASSERT_EQUAL(110,root->baseTime);
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->prev);
    TEST_ASSERT_NULL(motor1->timerElement.next);
    TEST_ASSERT_NULL(motor1->timerElement.prev);
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
}

/*

    head                                        head     
     ||                                          ||
     V                                           V
    10-->5-->7     => TIMx_IRQHandler()  =>      5-->7

*/


void test_Test_TIMxIRQHandler_5_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){
    root = createLinkedList();
    uint16_t arr2[] = {10,5,7};
    uint16_t arr[] = {5,7};
    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);
    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);

    _updateBaseTime(root,10);
    updateCurTime(root,20);
    timerQueue(&motor1->timerElement,10);
    
    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(&motor2->timerElement,10);
    
    _updateBaseTime(root,100);
    updateCurTime(root,108);
    timerQueue(&motor3->timerElement,14);
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr2,root);
    
    TIM2_IRQHandler();
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
    TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->prev);
    
    TEST_ASSERT_EQUAL(110,root->baseTime);
    TEST_ASSERT_NULL(motor1->timerElement.next);
    TEST_ASSERT_NULL(motor1->timerElement.prev);
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
}
//************timerDelay***************

void test_timerDelay_generate_delay_10_by_adding_elemMotor1_into_queue(void){
  
   ListElement *elemMotor1 = createLinkedElement(0);
   ListElement *elemMotor2 = createLinkedElement(0);
   ListElement *elemMotor3 = createLinkedElement(0);
   _updateBaseTime(root,0);
   TIM_SetCounter(TIM2,20);
   timerDelay(elemMotor1,10);
   
   TEST_ASSERT_EQUAL(10,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(10,elemMotor1->actionTime);
   TEST_ASSERT_EQUAL_PTR(elemMotor1,root->head);
   TEST_ASSERT_EQUAL_PTR(elemMotor1,root->head->next);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
  
}

/*
                                                    rate = 20
                                             |---------------|       
          0          10                 0          10        22          
          |----------|                  |----------|--------|
                                =>                
                     
          Head-->10-->NULL               Head-->10-->12-->NULL

*/

void test_timerDelay_generate_delay_by_adding_elemMotor1_and_elemMotor2_into_queue(void){
  
   ListElement *elemMotor1 = createLinkedElement(0);
   ListElement *elemMotor2 = createLinkedElement(0);
   
   _updateBaseTime(root,0);
   TIM_SetCounter(TIM2,0);
   timerDelay(elemMotor1,10);
   _updateBaseTime(root,0);
   TIM_SetCounter(TIM2,2);
  
   timerDelay(elemMotor2,20);
   
   TEST_ASSERT_EQUAL(10,elemMotor1->actionTime);
   TEST_ASSERT_EQUAL(12,elemMotor2->actionTime);
   
   TEST_ASSERT_EQUAL_PTR(elemMotor1,root->head);
   TEST_ASSERT_EQUAL_PTR(elemMotor2,root->head->next);
   TEST_ASSERT_EQUAL_PTR(elemMotor1,root->head->next->next);
}

/*
                                                    
                                                   
          0          10                 0          10       
          |----------|                  |----------|
                                =>                
                     
          Head-->10-->NULL               Head-->3-->7-->NULL
*/

void test_timerDelay_generate_delay_2_and_10_by_adding_elemMotor1_and_elemMotor2_into_queue(void){
  
   ListElement *elemMotor1 = createLinkedElement(0);
   ListElement *elemMotor2 = createLinkedElement(0);
   
   _updateBaseTime(root,0);
   TIM_SetCounter(TIM2,0);
   timerDelay(elemMotor1,10);
   _updateBaseTime(root,0);
   TIM_SetCounter(TIM2,1);
  
   timerDelay(elemMotor2,2);
   
   TEST_ASSERT_EQUAL(7,elemMotor1->actionTime);
   TEST_ASSERT_EQUAL(3,elemMotor2->actionTime);
   
   TEST_ASSERT_EQUAL_PTR(elemMotor2,root->head);
   TEST_ASSERT_EQUAL_PTR(elemMotor1,root->head->next);
   TEST_ASSERT_EQUAL_PTR(elemMotor2,root->head->next->next);
   TEST_ASSERT_EQUAL(3,TIM2->ARR);
}

void test_getTick_BaseTime_is_100000_and_TIM2_CNT_is_200_the_getTick_should_return_100200(void){
  
  _updateBaseTime(root,100000);
  TIM_SetCounter(TIM2,200);
  TEST_ASSERT_EQUAL(200,getTick(TIM2));
  
}


void test_recordCurrentTick_BaseTime_is_1000000_and_TIM2_CNT_is_2000_tickRecord_contains_1000200(void){
 /*
  _updateBaseTime(root,1000000);
  TIM_SetCounter(TIM2,2000);
  recordCurrentTick(tickRecord1);
  TEST_ASSERT_EQUAL(1002000,tickRecord1);
 */ 
}

void test_getTickInterval_tickRecord1_is_3000_and_tickRecord2_is_4000_the_getTickInterval_should_return_1000(void){
  uint32_t stickTable[] = {1000,2000,3000};
  setTickSequence(stickTable);
  _updateBaseTime(root,1000);
  TIM_SetCounter(TIM2,2000);
  recordCurrentTick(tickRecord1);
  _updateBaseTime(root,1000);
  TIM_SetCounter(TIM2,3000);
  recordCurrentTick(tickRecord2);
  TEST_ASSERT_EQUAL(1000,getTickInterval() );
  
}

void test_getTickInterval_tickRecord1_is_10000_and_tickRecord2_is_10000_the_getTickInterval_should_return_0(void){
  /*
  _updateBaseTime(root,8000);
  TIM_SetCounter(TIM2,2000);
  recordCurrentTick(tickRecord1);
  _updateBaseTime(root,7000);
  TIM_SetCounter(TIM2,3000);
  recordCurrentTick(tickRecord2);
  TEST_ASSERT_EQUAL(0,getTickInterval() );
  */
}

void test_getFakeTick(void){
  
  uint32_t stickTable[] = {1000,2000,3000};
  setTickSequence(stickTable);
  TEST_ASSERT_EQUAL(1000,getFakeTick());
  TEST_ASSERT_EQUAL(2000,getFakeTick());
  TEST_ASSERT_EQUAL(3000,getFakeTick());
  
}
//********TIM2_IRQHandler*********

void test_TIM2_IRQHandler_when_timer_expire_for_motor1_the_TIM2_IRQHandler_was_called(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,1000,2000,3000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);

   _timerDelay(&motor0->timerElement,2000);
   _timerDelay(&motor1->timerElement,6000);
  
   TEST_ASSERT_EQUAL(2000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   TEST_ASSERT_EQUAL(3000,tickRecord1);
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

}

/*
     Head                                   Head
      V                                      V                        Head
   -------     -------  TIM2_IRQHandler    -------  TIM2_IRQHandler      V
  | 2000 | -> | 4000 |      --->          | 4000 |      --->           NULL 
  -------     -------                     -------

                                          motorHead                      motorHead
                                             V                             V               
                                           ---------  TIM2_IRQHandler  ---------   ---------
                                          | motor0 |     --->         | motor0 |->| motor1 |
                                          ---------                   ---------   ---------
*/
void test_TIM2_IRQHandler_link_list_contain_two_timerElement_when_timer_interrupt(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,1000,1000,3000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);

   _timerDelay(&motor0->timerElement,2000);
   _timerDelay(&motor1->timerElement,6000);
  
   TEST_ASSERT_EQUAL(2000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(4000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   
   TIM2_IRQHandler();
   TEST_ASSERT_EQUAL(3000,tickRecord1);
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
   
   TIM2_IRQHandler();
   TEST_ASSERT_EQUAL(7000,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(4000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0000,TIM2->CR1&0x0001);
   TEST_ASSERT_NULL(root->head);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
}

/*
     Head                                   
      V                                     Head
   -------     -------   TIM2_IRQHandler     V
  |  2   | -> |  0   |       --->          NULL
  -------     -------              

                                             motorHead                      
                                                V                             
                                             ---------   ---------   
                                            | motor0 |->| motor1 |
                                            ---------   ---------   
*/
void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   
   uint32_t stickTable[] = {0,1000,1000,3000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
  
   _timerDelay(&motor0->timerElement,2);
   _timerDelay(&motor1->timerElement,2);
   //timerDelay(&motor2->timerElement,0);
  
   TEST_ASSERT_EQUAL(2,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   //TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(1002,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(0x0000,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(2,TIM2->ARR);
   TEST_ASSERT_NULL(root->head);
  // TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL(2,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
}

/*
     Head                                             Head
      V                                                 V
   -------     -------     ------- TIM2_IRQHandler   ------
  |  2   | -> |  0   | -> |  3   |      --->        |  3  | 
  -------     -------     -------                   ------

                                             motorHead                      
                                                V                             
                                             ---------   ---------   
                                            | motor0 |->| motor1 |
                                            ---------   ---------  
*/

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_2(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   
   uint32_t stickTable[] = {0,0,1000,2000,3000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
  
   _timerDelay(&motor0->timerElement,2);
   _timerDelay(&motor1->timerElement,2);
   _timerDelay(&motor2->timerElement,5);
  
   TEST_ASSERT_EQUAL(2,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(2002,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0001,TIM2->CR1&0x0001);
   //TEST_ASSERT_NULL(root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
  
   TIM2_IRQHandler();
   TEST_ASSERT_EQUAL(3005,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0000,TIM2->CR1&0x0001);
   TEST_ASSERT_NULL(root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[2]);
   
   
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
}


/*
     Head                                   
      V                                              Head
   -------     -------     ------- TIM2_IRQHandler     V
  |  2   | -> |  0   | -> |  0   |      --->          NULL
  -------     -------     -------           

                                             motorHead                      
                                                V                             
                                             ---------   ---------   ---------
                                            | motor0 |->| motor1 |->| motor2 |
                                            ---------   ---------   ---------
*/

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   
   uint32_t stickTable[] = {0,0,1000,2000,3000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
  
   _timerDelay(&motor0->timerElement,2);
   _timerDelay(&motor1->timerElement,2);
   _timerDelay(&motor2->timerElement,2);
  
   TEST_ASSERT_EQUAL(2,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(3002,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(2,TIM2->ARR);
   TEST_ASSERT_EQUAL(0x0000,TIM2->CR1&0x0001);
   TEST_ASSERT_NULL(root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
  
}

/*
     Head                                                         Head
      V                                                            V
   -------     -------     -------     ------  TIM2_IRQHandler   ------
  |  2   | -> |  0   | -> |  0   | -> |  3  |     --->          |  3  |
  -------     -------     -------     ------                    ------

                                             motorHead                      
                                                V                             
                                             ---------   ---------   ---------  
                                            | motor0 |->| motor1 |->| motor2 |
                                            ---------   ---------   ---------  
*/

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0_3(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   
   uint32_t stickTable[] = {0,0,0,1000,2000,3000,4000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
  
   _timerDelay(&motor0->timerElement,2);
   _timerDelay(&motor1->timerElement,2);
   _timerDelay(&motor2->timerElement,2);
   _timerDelay(&motor3->timerElement,5);
  
   TEST_ASSERT_EQUAL(2,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3,motor3->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(3002,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3,TIM2->ARR);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   //TEST_ASSERT_NULL(root->head);
   TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(0,motor3->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(0,motorDriveBuffer[3]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
   
   TIM2_IRQHandler();
  
   TEST_ASSERT_EQUAL(4005,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(3,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,TIM2->CR1&0x0001);
   TEST_ASSERT_NULL(root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor3->motorConfiguration->motorElement,motorRoot->head->next->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor3->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[3]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
}

/*
     Head                                   
      V                                                          Head
   -------     -------     -------     ------  TIM2_IRQHandler     V
  |  2   | -> |  0   | -> |  0   | -> |  0  |     --->           NULL
  -------     -------     -------     ------      

                                             motorHead                      
                                                V                             
                                             ---------   ---------   ---------   ---------
                                            | motor0 |->| motor1 |->| motor2 |->| motor3 |
                                            ---------   ---------   ---------   ---------
*/

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0_2(void){
  
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,3);
   
   uint32_t stickTable[] = {0,0,0,1000,2000,3000,4000};
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   setTickSequence(stickTable);
   initialStepCommand(motor0->motorConfiguration);
   initialStepCommand(motor1->motorConfiguration);
   initialStepCommand(motor2->motorConfiguration);
   initialStepCommand(motor3->motorConfiguration);
  
   _timerDelay(&motor0->timerElement,2);
   _timerDelay(&motor1->timerElement,2);
   _timerDelay(&motor2->timerElement,2);
   _timerDelay(&motor3->timerElement,2);
  
   TEST_ASSERT_EQUAL(2,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor3->timerElement.actionTime);
   
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next->next);
   
   TIM2_IRQHandler();
   
   TEST_ASSERT_EQUAL(4002,tickRecord1);
   TEST_ASSERT_EQUAL(0,tickRecord2);
   TEST_ASSERT_EQUAL(2,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,TIM2->CR1&0x0001);
   TEST_ASSERT_NULL(root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head);
   //TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   //TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   //TEST_ASSERT_EQUAL(3,root->head->actionTime);
   //motorController call motorStep
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->motorConfiguration->motorElement,motorRoot->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->motorConfiguration->motorElement,motorRoot->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor3->motorConfiguration->motorElement,motorRoot->head->next->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->motorConfiguration->motorElement,motorRoot->head->next->next->next->next);
   
   TEST_ASSERT_EQUAL(1,motor0->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor1->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor2->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(1,motor3->motorConfiguration->counter);
   TEST_ASSERT_EQUAL(motor0->motorConfiguration->stepLowCommand,motorDriveBuffer[0]);
   TEST_ASSERT_EQUAL(motor1->motorConfiguration->stepLowCommand,motorDriveBuffer[1]);
   TEST_ASSERT_EQUAL(motor2->motorConfiguration->stepLowCommand,motorDriveBuffer[2]);
   TEST_ASSERT_EQUAL(motor3->motorConfiguration->stepLowCommand,motorDriveBuffer[3]);
   TEST_ASSERT_EQUAL(0x01,DMA1_Channel3->CCR&0x01);
  
  
}

/*

        Head                       Head
         V                          V
                                 -------
       NULL        ---->        | 1000 |
                                -------

*/ 


void test_new_timerDelay_call_timerDelay_to_delay_1000_tick_the_link_list_should_contain_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,2000,3000,4000};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
}


/*

          Head             Head
           V                V
        -------          -------   -------
       | 1000 |    ->   | 1000 |->| 2000 |
       -------          -------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_1000_and_2000_tick_the_link_list_should_contain_two_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,0,3000,4000};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,3000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
}


/*

          Head             Head
           V                V
        -------          -------   -------       -------   -------   -------
       | 1000 |    ->   | 1000 |->| 2010 |  ->  | 1000 |->| 2010 |->| 3020 |
       -------          -------   -------       -------   -------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_1000_3000_and_6000_tick_the_link_list_should_contain_three_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {10,30,4000};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,3000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2010,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(10,root->curTime);
   
   _timerDelay(&motor2->timerElement,6000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2010,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(3020,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(30,root->curTime);
   
}


/*
                        curTime = 20
          Head             Head
           V                V
        -------          ------   ------      
       | 1000 |    ->   | 100 |->| 880 |  
       -------          ------   ------      

*/ 
void test_new_timerDelay_call_timerDelay_to_delay_1000_and_100_tick_the_link_list_should_contain_two_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {20,30,4000};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,100);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(880,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(100,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(20,root->baseTime);
   TEST_ASSERT_EQUAL(0,TIM2->CNT);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(100,TIM2->ARR);
   TEST_ASSERT_EQUAL(20,root->curTime);
   
}

/*

          Head             Head                    Head
           V                V                       V
        -------          -------   -------       -------   -------   -------
       | 1000 |    ->   | 1000 |->| 2010 |  ->  | 1000 |->| 130  |->| 1880 |
       -------          -------   -------       -------   -------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_1000_1100_and_6000_tick_the_link_list_should_contain_three_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {10,30};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,3000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2010,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(10,root->curTime);
   
   _timerDelay(&motor2->timerElement,1100);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1880,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(130,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(30,root->curTime);
   
}

/*

          Head             Head                    Head
           V                V                       V
        -------          -------   -------       -------   -------   -------     ------   ------   ------   -------
       | 1000 |    ->   | 1000 |->| 2010 |  ->  | 1000 |->| 130  |->| 1880 | -> | 100 |->| 860 |->| 130 |->| 1880 |
       -------          -------   -------       -------   -------   -------     ------   ------   ------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_100_1000_1100_and_3000_tick_the_link_list_should_contain_four_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   MotorInfo* motor3 = motorInit(motorController,1000,2);
   
   uint32_t stickTable[] = {10,30,40};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,3000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2010,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(10,root->curTime);
   
   _timerDelay(&motor2->timerElement,1100);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1880,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(130,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(30,root->curTime);
   
   _timerDelay(&motor3->timerElement,100);
   TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->next->next->next->next);
   TEST_ASSERT_EQUAL(860,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1880,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(130,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(100,motor3->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(100,TIM2->ARR);
   TEST_ASSERT_EQUAL(40,root->curTime);
   
}

/*

          Head             Head                    Head
           V                V                       V
        -------          -------   -------       -------   -------   -------
       | 1000 |    ->   | 1000 |->| 2000 |  ->  | 1000 |->|  0   |->| 2000 |
       -------          -------   -------       -------   -------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_6000_tick_the_link_list_should_contain_three_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,0};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,3000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor2->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(2000,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
}


/*

          Head             Head                    Head
           V                V                       V
        -------          -------   -------       -------   -------   -------
       | 1000 |    ->   | 1000 |->| 2000 |  ->  | 1000 |->|  0   |->|   0  |
       -------          -------   -------       -------   -------   -------

*/ 

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_1000_tick_the_link_list_should_contain_three_time_element(void){
   MotorInfo* motor0 = motorInit(motorController,1000,0);
   MotorInfo* motor1 = motorInit(motorController,2000,1);
   MotorInfo* motor2 = motorInit(motorController,1000,2);
   uint32_t stickTable[] = {0,0};
   setTickSequence(stickTable);
   setDataNumber(DMA1_Channel3,NumberOfMotor);
   
   _timerDelay(&motor0->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor1->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
   _timerDelay(&motor2->timerElement,1000);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head);
   TEST_ASSERT_EQUAL_PTR(&motor1->timerElement,root->head->next);
   TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
   TEST_ASSERT_EQUAL_PTR(&motor0->timerElement,root->head->next->next->next);
   
   TEST_ASSERT_EQUAL(1000,motor0->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor1->timerElement.actionTime);
   TEST_ASSERT_EQUAL(0,motor2->timerElement.actionTime);
   TEST_ASSERT_EQUAL(1,TIM2->CR1&0x0001);
   TEST_ASSERT_EQUAL(1000,TIM2->ARR);
   TEST_ASSERT_EQUAL(0,root->curTime);
   
}
