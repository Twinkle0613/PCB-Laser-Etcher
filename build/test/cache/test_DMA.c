#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "Timer_setting.h"
#include "projectStruct.h"
#include "peripherals.h"
#include "Linklist.h"
#include "Registers.h"
#include "Host.h"
#include "Timer.h"
#include "DMA_setting.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "DMA.h"
#include "unity.h"








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

}



void func1(void){





}

void test_motorConfigInit_initialize_the_txDetail(void){



  motorInfo motor1;

  motorConfigInfo* txDetail = motorConfigInit(&motor1,func1,FIRST_MOTOR);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->counter)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FIRST_MOTOR)), (_U_SINT)((txDetail->slot)), (((void *)0)), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepHighCommand)), (((void *)0)), (_U_UINT)(98), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepLowCommand)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

  if ((((txDetail->txElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(100))));};

  if ((((txDetail->txElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(101))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((txDetail->txElement.callBack)), (((void *)0)), (_U_UINT)(102), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1)), (_U_SINT)(_UP)((txDetail->txElement.args)), (((void *)0)), (_U_UINT)(103), UNITY_DISPLAY_STYLE_HEX32);

}





void test_dmaQueue_add_one_txElement_into_Queue(void){

    txRoot = createLinkedList();

    motorInfo motor1;

    motorInfo motor2;

    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(113), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_txElement_into_Queue(void){

    txRoot = createLinkedList();

    motorInfo motor1;

    motorInfo motor2;

    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    motorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    dmaQueue(&txDetail2->txElement);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(125), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(126), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(139), UNITY_DISPLAY_STYLE_HEX32);

    temp = dmaDequeue();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(141), UNITY_DISPLAY_STYLE_HEX32);

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(142))));};



}
