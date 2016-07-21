#include "unity.h"
#include "DMA.h"


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
#include "DMA_setting.h"
#include "Timer.h"
#include "Host.h"
#include "Registers.h"
#include "Linklist.h"
#include "peripherals.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"

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
}

void func1(void){
  
  
}


// void test_copyInform_except_first_MOTOR_item(void){
  // txBuffer[FIRST_MOTOR] = 0x11;
  // txBuffer[SECOND_MOTOR] = 0x44;
  // txBuffer[THIRD_MOTOR] = 0x88;
  // copyInformFromBufferToStorageExcept(FIRST_MOTOR);
  // TEST_ASSERT_EQUAL(txBuffer[SECOND_MOTOR],txStorage[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(txBuffer[THIRD_MOTOR],txStorage[THIRD_MOTOR]); 
// }

// void test_copyInform_except_second_MOTOR_item(void){
  // txBuffer[FIRST_MOTOR] = 0x11;
  // txBuffer[SECOND_MOTOR] = 0x44;
  // txBuffer[THIRD_MOTOR] = 0x88;
  // copyInformFromBufferToStorageExcept(SECOND_MOTOR);
  // TEST_ASSERT_EQUAL(txBuffer[FIRST_MOTOR],txStorage[FIRST_MOTOR]);
  // TEST_ASSERT_EQUAL(txBuffer[THIRD_MOTOR],txStorage[THIRD_MOTOR]); 
// }

// void test_copyInform_except_third_MOTOR_item(void){
  
  // txBuffer[FIRST_MOTOR] = 0x11;
  // txBuffer[SECOND_MOTOR] = 0x44;
  // txBuffer[THIRD_MOTOR] = 0x88;
  // copyInformFromBufferToStorageExcept(THIRD_MOTOR);
  // TEST_ASSERT_EQUAL(txBuffer[SECOND_MOTOR],txStorage[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(txBuffer[FIRST_MOTOR],txStorage[FIRST_MOTOR]);
  
// }

// void test_setMemoryAddress_set_a_memory_address(void){
  // setMemoryAddress(DMA1_Channel3,(uint32_t)txBuffer);
  // TEST_ASSERT_EQUAL_PTR(txBuffer,DMA1_Channel3->CMAR);
// }

// void test_copyWholeInform(void){
  // txStorage[FIRST_MOTOR] = 0x11;
  // txStorage[SECOND_MOTOR] = 0x44;
  // txStorage[THIRD_MOTOR] = 0x88;
  // copyWholeInform(txBuffer,txStorage);
  // TEST_ASSERT_EQUAL(txBuffer[FIRST_MOTOR],txStorage[FIRST_MOTOR]);
  // TEST_ASSERT_EQUAL(txBuffer[SECOND_MOTOR],txStorage[SECOND_MOTOR]);
  // TEST_ASSERT_EQUAL(txBuffer[THIRD_MOTOR],txStorage[THIRD_MOTOR]);
// }

void test_motorConfigInit_initialize_the_txDetail(void){
  
  motorInfo motor1; 
  motorConfigInfo* txDetail = motorConfigInit(&motor1,func1,FIRST_MOTOR);
  TEST_ASSERT_EQUAL(0,txDetail->counter);
  TEST_ASSERT_EQUAL(FIRST_MOTOR,txDetail->slot);
  TEST_ASSERT_EQUAL(0,txDetail->stepHighCommand);
  TEST_ASSERT_EQUAL(0,txDetail->stepLowCommand);
  TEST_ASSERT_NULL(txDetail->txElement.next);
  TEST_ASSERT_NULL(txDetail->txElement.prev);
  TEST_ASSERT_EQUAL_PTR(func1,txDetail->txElement.callBack);
  TEST_ASSERT_EQUAL_PTR(&motor1,txDetail->txElement.args);
}


void test_dmaQueue_add_one_txElement_into_Queue(void){
    txRoot = createLinkedList();
    motorInfo motor1; 
    motorInfo motor2; 
    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    dmaQueue(&txDetail1->txElement);
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,txRoot->head);
}

void test_dmaQueue_add_two_txElement_into_Queue(void){
    txRoot = createLinkedList();
    motorInfo motor1; 
    motorInfo motor2; 
    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    motorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);
    dmaQueue(&txDetail1->txElement);
    dmaQueue(&txDetail2->txElement);
    
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&txDetail2->txElement,txRoot->head->next);
}

void test_dmaQueue_add_two_txElement_into_Queue_and_deQueue(void){
    txRoot = createLinkedList();
    struct ListElement *temp;
    motorInfo motor1; 
    motorInfo motor2; 
    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    motorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);
    dmaQueue(&txDetail1->txElement);
    dmaQueue(&txDetail2->txElement);
    temp = dmaDequeue();
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,temp);
    temp = dmaDequeue();
    TEST_ASSERT_EQUAL_PTR(&txDetail2->txElement,temp);
    TEST_ASSERT_NULL(txRoot->head);

}