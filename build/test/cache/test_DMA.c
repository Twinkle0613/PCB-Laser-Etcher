#include "Motor.h"
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

  HostDma1_Channel3 = ((void *)0);

  HostDma1 = ((void *)0);

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

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->counter)), (((void *)0)), (_U_UINT)(67), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FIRST_MOTOR)), (_U_SINT)((txDetail->slot)), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepHighCommand)), (((void *)0)), (_U_UINT)(69), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((txDetail->stepLowCommand)), (((void *)0)), (_U_UINT)(70), UNITY_DISPLAY_STYLE_INT);

  if ((((txDetail->txElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(71))));};

  if ((((txDetail->txElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(72))));};

  UnityAssertEqualNumber((_U_SINT)(_UP)((func1)), (_U_SINT)(_UP)((txDetail->txElement.callBack)), (((void *)0)), (_U_UINT)(73), UNITY_DISPLAY_STYLE_HEX32);



}





void test_dmaQueue_add_one_txElement_into_Queue(void){

    txRoot = createLinkedList();

    motorInfo motor1;

    motorInfo motor2;

    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(84), UNITY_DISPLAY_STYLE_HEX32);

}



void test_dmaQueue_add_two_txElement_into_Queue(void){

    txRoot = createLinkedList();

    motorInfo motor1;

    motorInfo motor2;

    motorConfigInfo* txDetail1 = motorConfigInit(&motor1,func1,FIRST_MOTOR);

    motorConfigInfo* txDetail2 = motorConfigInit(&motor2,func1,FIRST_MOTOR);

    dmaQueue(&txDetail1->txElement);

    dmaQueue(&txDetail2->txElement);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(97), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail1->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(110), UNITY_DISPLAY_STYLE_HEX32);

    temp = dmaDequeue();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&txDetail2->txElement)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(112), UNITY_DISPLAY_STYLE_HEX32);

    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(113))));};



}

void test_updateMotorDriveBuffer_the_linkedlist_only_contain_triMotorElement_and_Update_the_triMotor_slot_buffer(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    initialStepCommand(motorConfig3);

    dmaQueue(&motorConfig3->txElement);

    updateMotorDriveBuffer();

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig3->counter)), (((void *)0)), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_triMotorElement_secMotorElement_and_Update_the_triMotor_and_secMotor_slot_buffer(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    dmaQueue(&motorConfig3->txElement);

    dmaQueue(&motorConfig2->txElement);

    updateMotorDriveBuffer();

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig3->counter)), (((void *)0)), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_the_linkedlist_contain_triMotorElement_secMotorElement_and_firMotorElement_and_Update_the_triMotor_secMotor_and_firMotor_slot_buffer(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

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

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(197), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig3->counter)), (((void *)0)), (_U_UINT)(198), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_after_function_it_should_dequeue(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    initialStepCommand(motorConfig3);



    motorStep(motorConfig3);

    updateMotorDriveBuffer();



    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(225))));};

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(226), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(227), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(228), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_secMotorElem_and_firMotorElem_after_function_they_should_dequeue(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);



    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    initialStepCommand(motorConfig1);



    motorStep(motorConfig3);

    motorStep(motorConfig2);

    motorStep(motorConfig1);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig3->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(259), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(260), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->txElement)), (_U_SINT)(_UP)((txRoot->head->next->next)), (((void *)0)), (_U_UINT)(261), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepLowCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);



    updateMotorDriveBuffer();



    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(269))));};

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(270), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepHighCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepHighCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(272), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_firMotorElem_after_function_they_should_dequeue(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);



    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    initialStepCommand(motorConfig1);



    motorStep(motorConfig3);

    motorStep(motorConfig1);



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig3->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(300), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->txElement)), (_U_SINT)(_UP)((txRoot->head->next)), (((void *)0)), (_U_UINT)(301), UNITY_DISPLAY_STYLE_HEX32);



    updateMotorDriveBuffer();



    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(305))));};

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(306), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(307), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepHighCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(308), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_firMotorElem_after_function_linkedList_contain_firMotorElement(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);



    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    initialStepCommand(motorConfig1);



    motorStep(motorConfig3);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),1);

    motorStep(motorConfig1);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig1->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(340), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(341), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig1->stepLowCommand)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_secMotorElem_after_function_linkedList_is_emply(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);



    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    initialStepCommand(motorConfig1);



    motorStep(motorConfig3);

    motorStep(motorConfig2);



    updateMotorDriveBuffer();



    if ((((txRoot->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(373))));};

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(374), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepHighCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(375), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(376), UNITY_DISPLAY_STYLE_INT);

}

void test_updateMotorDriveBuffer_Queue_contain_triMotorElem_and_secMotorElem_after_function_linkedList_only_contain_secMotorElem(void){

    txRoot = createLinkedList();

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

    motorConfigInfo* motorConfig3 = motorConfigInit(&motor,func1,THIRD_MOTOR);

    motorConfigInfo* motorConfig2 = motorConfigInit(&motor,func1,SECOND_MOTOR);

    motorConfigInfo* motorConfig1 = motorConfigInit(&motor,func1,FIRST_MOTOR);



    initialStepCommand(motorConfig3);

    initialStepCommand(motorConfig2);

    initialStepCommand(motorConfig1);



    motorStep(motorConfig3);

    setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),2);

    motorStep(motorConfig2);



    updateMotorDriveBuffer();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motorConfig2->txElement)), (_U_SINT)(_UP)((txRoot->head)), (((void *)0)), (_U_UINT)(407), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((motorConfig3->stepHighCommand)), (_U_SINT)((motorDriveBuffer[THIRD_MOTOR])), (((void *)0)), (_U_UINT)(408), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((motorConfig2->stepLowCommand)), (_U_SINT)((motorDriveBuffer[SECOND_MOTOR])), (((void *)0)), (_U_UINT)(409), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[FIRST_MOTOR])), (((void *)0)), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motorConfig3->counter)), (((void *)0)), (_U_UINT)(412), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motorConfig2->counter)), (((void *)0)), (_U_UINT)(413), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorConfig1->counter)), (((void *)0)), (_U_UINT)(414), UNITY_DISPLAY_STYLE_INT);

}
