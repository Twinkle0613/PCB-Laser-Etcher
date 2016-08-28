#include "mock_getTick.h"
#include "mock_MockFunction.h"
#include "Motor.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "CustomAssertion.h"
#include "projectStruct.h"
#include "peripherals.h"
#include "Registers.h"
#include "Linklist.h"
#include "Timer.h"
#include "Host.h"
#include "Dma.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "unity.h"


























uint32_t* tickPointer = ((void *)0);

void setTickSequence(uint32_t tickTable[]){

  tickPointer = tickTable;

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

   HostTim2 = ((void *)0);

   HostDma1_Channel3 = ((void *)0);

   HostDma1 = ((void *)0);

   root = ((void *)0);

}

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){



    root = createLinkedList();

    MotorInfo* motor1 = motorInit(testMotor123,0,0);

    MotorInfo* motor2 = motorInit(testMotor123,0,1);

    MotorInfo* motor3 = motorInit(testMotor123,0,2);



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    if ((((root->head)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(107))));};

    TIM2_IRQHandler();

     UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(110))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(111))));};

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(112))));};

}

void test_Test_TIMxIRQHandler_two_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    MotorInfo* motor1 = motorInit(testMotor123,0,0);

    MotorInfo* motor2 = motorInit(testMotor123,0,1);

    MotorInfo* motor3 = motorInit(testMotor123,0,2);

    int arr[] = {5};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(&motor2->timerElement,10);



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(141), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(142), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(143), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(144))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(145))));};

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),146); };

}

void test_Test_TIMxIRQHandler_5_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){

    root = createLinkedList();

    uint16_t arr2[] = {10,5,7};

    uint16_t arr[] = {5,7};

    MotorInfo* motor1 = motorInit(testMotor123,0,0);

    MotorInfo* motor2 = motorInit(testMotor123,0,1);

    MotorInfo* motor3 = motorInit(testMotor123,0,2);



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(&motor2->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,108);

    timerQueue(&motor3->timerElement,14);

    { test_assert_cycle_link_list(root,arr2,sizeof(arr2)/sizeof(uint32_t),178); };



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(181), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(182), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(183), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(184), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(186), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(187))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(188))));};



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),190); };

}





void test_timerDelay_generate_delay_10_by_adding_elemMotor1_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);

   ListElement *elemMotor3 = createLinkedElement(0);

   setBaseTime(root,0);

   TIM_SetCounter(((TIM_TypeDef*) ((uint32_t)HostTim2)),20);

   timerDelay(elemMotor1,10);



   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(203), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(204), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(205), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(206), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(207), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(208), UNITY_DISPLAY_STYLE_INT);



}

void test_timerDelay_generate_delay_by_adding_elemMotor1_and_elemMotor2_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);

   uint32_t stickTable[] = {2,0,0};

   setTickSequence(stickTable);



   setCurrentTime(root,0);

   setBaseTime(root,0);



   timerDelay(elemMotor1,10);

   timerDelay(elemMotor2,20);



     UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(236), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((12)), (_U_SINT)((elemMotor2->actionTime)), (((void *)0)), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);



     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(239), UNITY_DISPLAY_STYLE_HEX32);

     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(240), UNITY_DISPLAY_STYLE_HEX32);

     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(241), UNITY_DISPLAY_STYLE_HEX32);

}

void test_timerDelay_generate_delay_2_and_10_by_adding_elemMotor1_and_elemMotor2_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);



   uint32_t stickTable[] = {1,0,0};

   setTickSequence(stickTable);



   setBaseTime(root,0);



   timerDelay(elemMotor1,10);

   timerDelay(elemMotor2,2);



   UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(267), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((elemMotor2->actionTime)), (((void *)0)), (_U_UINT)(268), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(270), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(271), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(272), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

}



void test_getTick_BaseTime_is_100000_and_TIM2_CNT_is_200_the_getTick_should_return_100200(void){

  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(280), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(281), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(282), UNITY_DISPLAY_STYLE_INT);



}



void test_getTickInterval_tickRecord1_is_3000_and_tickRecord2_is_4000_the_getTickInterval_should_return_1000(void){

  uint32_t stickTable[] = {2000,3000,3000};

  setTickSequence(stickTable);

  setBaseTime(root,1000);



  (tickRecord1 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );



  (tickRecord2 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTickInterval())), (((void *)0)), (_U_UINT)(294), UNITY_DISPLAY_STYLE_INT);



}



void test_getTickInterval_tickRecord1_is_10000_and_tickRecord2_is_10000_the_getTickInterval_should_return_0(void){

  uint32_t stickTable[] = {2000,3000,3000};

  setTickSequence(stickTable);

  setBaseTime(root,8000);



  (tickRecord1 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );

  setBaseTime(root,7000);



  (tickRecord2 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((getTickInterval())), (((void *)0)), (_U_UINT)(307), UNITY_DISPLAY_STYLE_INT);



}







void test_TIM2_IRQHandler_when_timer_expire_for_motor1_the_TIM2_IRQHandler_was_called(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,1000,2000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);



   timerDelay(&motor0->timerElement,2000);

   timerDelay(&motor1->timerElement,6000);



   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(326), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(327), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(328), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(329), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(330), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(334), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(335), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(336), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(337), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(338), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(339), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(341), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(342), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(344), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(345), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(346), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(347), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(348), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);



}

void test_TIM2_IRQHandler_link_list_contain_two_timerElement_when_timer_interrupt(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,1000,1000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);



   timerDelay(&motor0->timerElement,2000);

   timerDelay(&motor1->timerElement,6000);



   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(381), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(382), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(383), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(384), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(385), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(388), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(389), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(390), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(391), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(392), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(393), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(394), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(396), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(397), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(398), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(399), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(400), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(401), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(402), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(403), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(404), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((7000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(407), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(408), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(409), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(411))));};



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(413), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(414), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(415), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(417), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(418), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(419), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(420), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(421), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(422), UNITY_DISPLAY_STYLE_INT);



}

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);



   uint32_t stickTable[] = {0,1000,1000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);



   timerDelay(&motor0->timerElement,2);

   timerDelay(&motor1->timerElement,2);





   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(457), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(458), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(461), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(462), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(463), UNITY_DISPLAY_STYLE_HEX32);





   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(468), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(469), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(470), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(471), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(472))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(478), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(479), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(480), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(481), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(482), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(483), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(484), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(485), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(486), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(487), UNITY_DISPLAY_STYLE_INT);



}

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_2(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);



   uint32_t stickTable[] = {0,0,1000,2000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);



   timerDelay(&motor0->timerElement,2);

   timerDelay(&motor1->timerElement,2);

   timerDelay(&motor2->timerElement,5);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(523), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(524), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(525), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(527), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(528), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(529), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(530), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(534), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(535), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(536), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(537), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(539), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(540), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(542), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(544), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(545), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(547), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(549), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(550), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(551), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(552), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(553), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(554), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(555), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3005)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(558), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(559), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(560), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(561), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(562))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(568), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(569), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(570), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(571), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(573), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(574), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(575), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(576), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(577), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(578), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(581), UNITY_DISPLAY_STYLE_INT);



}

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);



   uint32_t stickTable[] = {0,0,1000,2000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);



   timerDelay(&motor0->timerElement,2);

   timerDelay(&motor1->timerElement,2);

   timerDelay(&motor2->timerElement,2);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(618), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(619), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(620), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(622), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(623), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(624), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(625), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(629), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(630), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(631), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(632), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(633))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(639), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(640), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(641), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(642), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(644), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(645), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(646), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(647), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(648), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(649), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(650), UNITY_DISPLAY_STYLE_INT);



}

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0_3(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);



   uint32_t stickTable[] = {0,0,0,1000,2000,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,2);

   timerDelay(&motor1->timerElement,2);

   timerDelay(&motor2->timerElement,2);

   timerDelay(&motor3->timerElement,5);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(688), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(689), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(690), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(691), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(693), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(694), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(695), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(696), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(697), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(701), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(702), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(703), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(704), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(706), UNITY_DISPLAY_STYLE_HEX32);





   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(709), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(711), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(712), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(713), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(714), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(716), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(717), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(718), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(719), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(720), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(721), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(722), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(723), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(724), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((4005)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(728), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(729), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(730), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(731), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(732))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(738), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(739), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(740), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(741), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next->next)), (((void *)0)), (_U_UINT)(742), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(744), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(745), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(746), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(747), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(748), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(749), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(750), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(751), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(752), UNITY_DISPLAY_STYLE_INT);

}

void test_TIM2_IRQHandler_link_list_contain_3_timerElemen_that_the_value_is_2_0_0_2(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,3);



   uint32_t stickTable[] = {0,0,0,1000,2000,3000,4000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);

   initialStepCommand(motor1->motorConfiguration);

   initialStepCommand(motor2->motorConfiguration);

   initialStepCommand(motor3->motorConfiguration);



   timerDelay(&motor0->timerElement,2);

   timerDelay(&motor1->timerElement,2);

   timerDelay(&motor2->timerElement,2);

   timerDelay(&motor3->timerElement,2);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(789), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(790), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(791), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(792), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(794), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(795), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(796), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(797), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(798), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((4002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(802), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(803), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(804), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(805), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(806))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(812), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(813), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(814), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(815), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next->next)), (((void *)0)), (_U_UINT)(816), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(818), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(819), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(820), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(821), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(822), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(823), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(824), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor3->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(825), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(826), UNITY_DISPLAY_STYLE_INT);





}

void test_new_timerDelay_call_timerDelay_to_delay_1000_tick_the_link_list_should_contain_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,2000,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(850), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(851), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(852), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(853), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(854), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(855), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_and_2000_tick_the_link_list_should_contain_two_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(879), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(880), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(881), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(882), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(883), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(884), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(887), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(888), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(889), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(890), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(891), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(892), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(893), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(894), UNITY_DISPLAY_STYLE_INT);

}

void test_new_timerDelay_call_timerDelay_to_delay_1000_3000_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {10,30,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(917), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(918), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(919), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(920), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(921), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(922), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(925), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(926), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(927), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(928), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(929), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(930), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(931), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(932), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor2->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(936), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(937), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(938), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(939), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(940), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3020)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(941), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(942), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(943), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(944), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_and_100_tick_the_link_list_should_contain_two_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {20,30,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(967), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(968), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(969), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(970), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(971), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(972), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(975), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(976), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(977), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((880)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(978), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(979), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(980), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(981), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(982), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(983), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(984), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1100_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {10,30};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1007), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1008), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1009), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1010), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1011), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1012), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1015), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1016), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1017), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1018), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1019), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1020), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1021), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1022), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor2->timerElement,1100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1025), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1026), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1027), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1028), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1029), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1030), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1031), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1032), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1033), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1034), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_100_1000_1100_and_3000_tick_the_link_list_should_contain_four_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,2);



   uint32_t stickTable[] = {10,30,40};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1059), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1060), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1061), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1062), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1063), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1064), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1067), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1068), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1069), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1070), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1071), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1072), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1073), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1074), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor2->timerElement,1100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1077), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1078), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1079), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1080), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1081), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1082), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1083), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1084), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1085), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1086), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor3->timerElement,100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1089), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1090), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1091), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1092), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(1093), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((860)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1094), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1095), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1096), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1097), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1098), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1099), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((40)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1100), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1123), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1124), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1125), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1126), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1127), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1128), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1131), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1132), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1133), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1134), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1135), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1136), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1137), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1138), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor2->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1141), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1142), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1143), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1144), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1145), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1146), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1147), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1148), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1149), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1150), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_1000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1174), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1175), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1176), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1177), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1178), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1179), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor1->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1182), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1183), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1184), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1185), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1186), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1187), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1188), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1189), UNITY_DISPLAY_STYLE_INT);



   timerDelay(&motor2->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1192), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1193), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1194), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1195), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1197), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1198), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1199), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1200), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1201), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1202), UNITY_DISPLAY_STYLE_INT);



}
