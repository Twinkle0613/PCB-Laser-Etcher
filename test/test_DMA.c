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
#include "Motor.h"


motorInfo motor;
void resetMotorDriveBuffer(void);
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

void initialStepCommand(motorConfigInfo* motorConfiguration){
  motorConfiguration->stepLowCommand = 0xAA;
  motorConfiguration->stepHighCommand = 0x55;
}

void resetMotorDriveBuffer(void){
  motorDriveBuffer[FIRST_MOTOR] = 0;
  motorDriveBuffer[SECOND_MOTOR] = 0;
  motorDriveBuffer[THIRD_MOTOR] = 0;
}

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
 // TEST_ASSERT_EQUAL_PTR(&motor1,txDetail->txElement.args);
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
/*
  
    Head-->triMotorElement
    
        3nd   2nd   1st                                    3nd   2nd   1st
      ------------------   updateMotorDriveBuffer();     ------------------ 
     | 0   |  0  |  0  |         ------->               | Low |  0  |  0 | 
     ------------------                                 ------------------ 
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_the_linkedlist_only_contain_triMotorElement_and_Update_the_triMotor_slot_buffer(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    initialStepCommand(motorConfig3);
    dmaQueue(&motorConfig3->txElement);
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(1,motorConfig3->counter);
}

/*
  
    Head-->triMotorElement->secMotorElement
    
        3nd   2nd    1st                                    3nd   2nd   1st
      ------------------   updateMotorDriveBuffer();     --------------------
     | 0   |  0  |  0  |         ------->               | Low |  low  |  0  | 
     ------------------                                 --------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_the_linkedlist_contain_triMotorElement_secMotorElement_and_Update_the_triMotor_and_secMotor_slot_buffer(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    dmaQueue(&motorConfig3->txElement);
    dmaQueue(&motorConfig2->txElement);
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(1,motorConfig3->counter);
    TEST_ASSERT_EQUAL(1,motorConfig2->counter);
}



/*
  
    Head-->triMotorElement->secMotorElement->firMotorElement
    
        3nd   2nd    1st                                         3nd   2nd   1st
      ------------------   updateMotorDriveBuffer();         ---------------------- 
     |  0  |  0  |  0  |         ------->                   | Low |  Low  |  Low  | 
     ------------------                                     -----------------------
       (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_the_linkedlist_contain_triMotorElement_secMotorElement_and_firMotorElement_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    dmaQueue(&motorConfig3->txElement);
    dmaQueue(&motorConfig2->txElement);
    dmaQueue(&motorConfig1->txElement);
    
    updateMotorDriveBuffer();
    TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
    TEST_ASSERT_EQUAL(1,motorConfig3->counter);
    TEST_ASSERT_EQUAL(1,motorConfig2->counter);
    TEST_ASSERT_EQUAL(1,motorConfig1->counter);
}


/*
  
    Head-->triMotorElement                             Head-->NULL
    
        3nd   2nd   1st                                    3nd   2nd   1st
      ------------------   updateMotorDriveBuffer();     ------------------ 
     | Low   |  0  |  0  |         ------->             | High |  0  |  0 | 
     ------------------                                 ------------------ 
     (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_after_function_it_should_dequeue(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    initialStepCommand(motorConfig3);
    
    motorStep(motorConfig3);
    updateMotorDriveBuffer();
    
    TEST_ASSERT_NULL(txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
}



/*
  
    Head-->triMotorElement->secMotorElement->firMotorElement           Head-->NULL
    
        3nd   2nd    1st                                         3nd   2nd   1st
      -----------------------   updateMotorDriveBuffer();      --------------------
     |  low   |  low  |  low  |         ------->              | High | High |  High  | 
     -----------------------                                  --------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_secMotorElem_and_firMotorElem_after_function_they_should_dequeue(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    motorStep(motorConfig3);
    motorStep(motorConfig2);
    motorStep(motorConfig1);
    
    TEST_ASSERT_EQUAL_PTR(&motorConfig3->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motorConfig2->txElement,txRoot->head->next);
    TEST_ASSERT_EQUAL_PTR(&motorConfig1->txElement,txRoot->head->next->next);
    
    TEST_ASSERT_EQUAL(motorConfig3->stepLowCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_NULL(txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepHighCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig1->stepHighCommand,motorDriveBuffer[FIRST_MOTOR]);
}

/*
  
    Head-->triMotorElement->firMotorElement                    Head-->NULL
    
        3nd      2nd    1st                                     3nd   2nd   1st
      -------------------------   updateMotorDriveBuffer();    ---------------------
     |  low   |   0   |  low  |         ------->              | High |  0  |  High | 
     -------------------------                                ---------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_firMotorElem_after_function_they_should_dequeue(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    motorStep(motorConfig3);
    motorStep(motorConfig1);
    
    TEST_ASSERT_EQUAL_PTR(&motorConfig3->txElement,txRoot->head);
    TEST_ASSERT_EQUAL_PTR(&motorConfig1->txElement,txRoot->head->next);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_NULL(txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig1->stepHighCommand,motorDriveBuffer[FIRST_MOTOR]);
}

/*
  
    Head-->triMotorElement->firMotorElement                    Head-->firMotorElement
    
        3nd      2nd    1st                                     3nd   2nd   1st
      -----------------------   updateMotorDriveBuffer();    --------------------
     |  low   |   0   |  0  |         ------->              | High |  0  |  low  | 
     -----------------------                                --------------------
     (motorDriveBuffer)

*/

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_firMotorElem_after_function_linkedList_contain_firMotorElement(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    motorStep(motorConfig3);
    setDataNumber(DMA1_Channel3,1);
    motorStep(motorConfig1);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motorConfig1->txElement,txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig1->stepLowCommand,motorDriveBuffer[FIRST_MOTOR]);
}

/*
  
    Head-->triMotorElement->secMotorElement           Head-->NULL
    
        3nd   2nd    1st                                         3nd   2nd   1st
      -----------------------   updateMotorDriveBuffer();    --------------------
     |  low   |  low  |  0  |         ------->              | High | High |  0  | 
     -----------------------                                --------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_secMotorElem_after_function_linkedList_is_emply(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    motorStep(motorConfig3);
    motorStep(motorConfig2);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_NULL(txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepHighCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
}

/*
  
    Head-->triMotorElement->secMotorElement                    Head-->secMotorElement
    
        3nd      2nd    1st                                     3nd   2nd   1st
      -----------------------   updateMotorDriveBuffer();    ----------------------
     |  low   |   0   |  0  |         ------->              | High |  low   |  0  | 
     -----------------------                                ----------------------
     (motorDriveBuffer)

*/
void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_secMotorElem_after_function_linkedList_only_contain_secMotorElem(void){
    txRoot = createLinkedList();
    setDataNumber(DMA1_Channel3,3);
    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);
    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);
    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);
    
    initialStepCommand(motorConfig3);
    initialStepCommand(motorConfig2);
    initialStepCommand(motorConfig1);
    
    motorStep(motorConfig3);
    setDataNumber(DMA1_Channel3,2);
    motorStep(motorConfig2);
    
    updateMotorDriveBuffer();
    
    TEST_ASSERT_EQUAL_PTR(&motorConfig2->txElement,txRoot->head);
    TEST_ASSERT_EQUAL(motorConfig3->stepHighCommand,motorDriveBuffer[THIRD_MOTOR]);
    TEST_ASSERT_EQUAL(motorConfig2->stepLowCommand,motorDriveBuffer[SECOND_MOTOR]);
    TEST_ASSERT_EQUAL(0,motorDriveBuffer[FIRST_MOTOR]);
    
    TEST_ASSERT_EQUAL(2,motorConfig3->counter);
    TEST_ASSERT_EQUAL(1,motorConfig2->counter);
    TEST_ASSERT_EQUAL(0,motorConfig1->counter);
}