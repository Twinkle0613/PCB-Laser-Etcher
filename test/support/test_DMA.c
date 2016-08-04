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

#define motorConfig3 Motor3->motorConfiguration
#define motorConfig2 Motor2->motorConfiguration
#define motorConfig1 Motor1->motorConfiguration

#define motor2Config motor2->motorConfiguration
#define motor1Config motor1->motorConfiguration
#define motor0Config motor0->motorConfiguration


void resetMotorDriveBuffer(void);
void setUp(void)
{
 HostGpioA= malloc((sizeof(GPIO_TypeDef)));
 HostDma1_Channel3 = malloc((sizeof(DMA_Channel_TypeDef)));
 HostDma1 = malloc((sizeof(DMA_TypeDef)));
}

void tearDown(void)
{
  free(HostDma1_Channel3);
  free(HostDma1);
  free(HostGpioA);
   HostGpioA = NULL;
  HostDma1_Channel3 = NULL;
  HostDma1 = NULL;
  resetMotorDriveBuffer();
}

void func1(void){
  
  printf("Hello World\n");
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

void test_motorConfigInit_the_txDetail_was_set_by_motorConfigInit_the_setting_of_txDetail_should_pass_the_test(void){
  printf("No 1.0");
  motorInfo motor1; 
  motorConfigInfo* txDetail = motorConfigInit(&motor1,func1,FIRST_MOTOR);
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
   motorConfigInfo* motorConfig;
   motorInfo* Motor3 = motorInit(func1,0,THIRD_MOTOR);
   motorConfig = readMotorConfigInfo(Motor3->motorConfiguration->txElement.args);
   TEST_ASSERT_EQUAL(Motor3,motorConfig->txElement.args);
}

void test_dmaQueue_add_one_txElement_into_Queue(void){
    printf("No 3.0");
    txRoot = createLinkedList();
    motorInfo motor1; 
    motorInfo motor2; 
    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    dmaQueue(&txDetail1->txElement);
    TEST_ASSERT_EQUAL_PTR(&txDetail1->txElement,txRoot->head);
}

void test_dmaQueue_add_two_txElement_into_Queue(void){
    printf("No 3.1");
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
    printf("No 3.2");
    txRoot = createLinkedList();
    struct ListElement *temp;
    motorInfo motor1; 
    motorInfo motor2; 
    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);
    motorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);
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
    motorInfo* motor0 = motorInit(func1,1000,0);
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

    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);

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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    
    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
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
    // printf("No 5.3"); 
    // txRoot = createLinkedList();
    // setDataNumber(DMA1_Channel3,3);
    
    // motorInfo* motor0 = motorInit(func1,1000,0);
    // motorInfo* motor1 = motorInit(func1,1000,1);
    // motorInfo* motor2 = motorInit(func1,1000,2);
    
    // initialStepCommand(motor0Config);
    // initialStepCommand(motor1Config);
    // initialStepCommand(motor2Config);
    
    // motorStep(motor0Config);
    // motorStep(motor1Config);
    
    // DMA1_Channel3_IRQHandler();
    // DMA1_Channel3_IRQHandler();
    
    // TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    // TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
    // TEST_ASSERT_EQUAL(0,motor0Config->counter);
    // TEST_ASSERT_EQUAL(0,motor1Config->counter);
    // TEST_ASSERT_NULL(txRoot->head);
    
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

    motorInfo* motor0 = motorInit(func1,1000,0);
    motorInfo* motor1 = motorInit(func1,1000,1);
    motorInfo* motor2 = motorInit(func1,1000,2);
    
    initialStepCommand(motor0Config);
    initialStepCommand(motor1Config);
    initialStepCommand(motor2Config);
    
    motorStep(motor0Config);
    motorStep(motor1Config);
    motorStep(motor2Config);

    DMA1_Channel3_IRQHandler();
    DMA1_Channel3_IRQHandler();
    
   // TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
   // TEST_ASSERT_EQUAL(motor1Config->stepHighCommand,motorDriveBuffer[1]);
   // TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
   // TEST_ASSERT_EQUAL(0,motor0Config->counter);
   // TEST_ASSERT_EQUAL(0,motor1Config->counter);
   // TEST_ASSERT_EQUAL(0,motor2Config->counter);
   // TEST_ASSERT_NULL(txRoot->head);
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
    // txRoot = createLinkedList();
    // setDataNumber(DMA1_Channel3,3);
    
    // motorInfo* motor0 = motorInit(func1,1000,0);
    // motorInfo* motor1 = motorInit(func1,1000,1);
    // motorInfo* motor2 = motorInit(func1,1000,2);
    
    // initialStepCommand(motor0Config);
    // initialStepCommand(motor1Config);
    // initialStepCommand(motor2Config);
    
    
    // motorStep(motor2Config);
    // setDataNumber(DMA1_Channel3,1);
    // motorStep(motor0Config);
    

    // DMA1_Channel3_IRQHandler();
    // TEST_ASSERT_EQUAL(motor0Config->stepLowCommand,motorDriveBuffer[0]);
    // TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    
    // DMA1_Channel3_IRQHandler();
    // TEST_ASSERT_EQUAL_PTR(&motor0Config->txElement,txRoot->head);
    // TEST_ASSERT_EQUAL(motor0Config->stepHighCommand,motorDriveBuffer[0]);
    // TEST_ASSERT_EQUAL(motor2Config->stepHighCommand,motorDriveBuffer[2]);
    // TEST_ASSERT_EQUAL(2,motor0Config->counter);
    // TEST_ASSERT_EQUAL(0,motor2Config->counter);
    
    // DMA1_Channel3_IRQHandler();
    // TEST_ASSERT_NULL(txRoot->head);
}
