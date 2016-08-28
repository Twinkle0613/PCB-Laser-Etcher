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
#include "DMA_setting.h"
#include "DMA.h"
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

   HostTim2 = ((void *)0);

   HostDma1_Channel3 = ((void *)0);

   HostDma1 = ((void *)0);

   root = ((void *)0);

}

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){



    root = createLinkedList();

    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    if ((((root->head)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(113))));};

    TIM2_IRQHandler();

     UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(116))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(117))));};

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(118))));};

}

void test_Test_TIMxIRQHandler_two_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);

    int arr[] = {5};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(&motor2->timerElement,10);



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(146), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(147), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(148), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(149), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(150))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(151))));};

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),152); };

}

void test_Test_TIMxIRQHandler_5_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){

    root = createLinkedList();

    uint16_t arr2[] = {10,5,7};

    uint16_t arr[] = {5,7};

    MotorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    MotorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(&motor1->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(&motor2->timerElement,10);



    setBaseTime(root,100);

    setCurrentTime(root,108);

    timerQueue(&motor3->timerElement,14);

    { test_assert_cycle_link_list(root,arr2,sizeof(arr2)/sizeof(uint32_t),184); };



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(187), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(188), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(189), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(190), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(192), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(193))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(194))));};



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),196); };

}





void test_timerDelay_generate_delay_10_by_adding_elemMotor1_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);

   ListElement *elemMotor3 = createLinkedElement(0);

   setBaseTime(root,0);

   TIM_SetCounter(((TIM_TypeDef*) ((uint32_t)HostTim2)),20);

   _timerDelay(elemMotor1,10);



   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(210), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(211), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(212), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(213), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);



}

void test_timerDelay_generate_delay_by_adding_elemMotor1_and_elemMotor2_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);

   uint32_t stickTable[] = {2,0,0};

   setTickSequence(stickTable);



   setCurrentTime(root,0);

   setBaseTime(root,0);



   _timerDelay(elemMotor1,10);

   _timerDelay(elemMotor2,20);



     UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((12)), (_U_SINT)((elemMotor2->actionTime)), (((void *)0)), (_U_UINT)(243), UNITY_DISPLAY_STYLE_INT);



     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(245), UNITY_DISPLAY_STYLE_HEX32);

     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(246), UNITY_DISPLAY_STYLE_HEX32);

     UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(247), UNITY_DISPLAY_STYLE_HEX32);

}

void test_timerDelay_generate_delay_2_and_10_by_adding_elemMotor1_and_elemMotor2_into_queue(void){



   ListElement *elemMotor1 = createLinkedElement(0);

   ListElement *elemMotor2 = createLinkedElement(0);



   uint32_t stickTable[] = {1,0,0};

   setTickSequence(stickTable);



   setBaseTime(root,0);



   _timerDelay(elemMotor1,10);

   _timerDelay(elemMotor2,2);



   UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((elemMotor1->actionTime)), (((void *)0)), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((elemMotor2->actionTime)), (((void *)0)), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(276), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor1)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(277), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((elemMotor2)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(278), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(279), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(280), UNITY_DISPLAY_STYLE_INT);

}



void test_getTick_BaseTime_is_100000_and_TIM2_CNT_is_200_the_getTick_should_return_100200(void){

  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))))), (((void *)0)), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);



}





void test_getTickInterval_tickRecord1_is_3000_and_tickRecord2_is_4000_the_getTickInterval_should_return_1000(void){

  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  setBaseTime(root,1000);

  TIM_SetCounter(((TIM_TypeDef*) ((uint32_t)HostTim2)),2000);

  (tickRecord1 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );

  setBaseTime(root,1000);

  TIM_SetCounter(((TIM_TypeDef*) ((uint32_t)HostTim2)),3000);

  (tickRecord2 = getTick(((TIM_TypeDef*) ((uint32_t)HostTim2))) + root->baseTime );

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getTickInterval())), (((void *)0)), (_U_UINT)(302), UNITY_DISPLAY_STYLE_INT);



}



void test_getTickInterval_tickRecord1_is_10000_and_tickRecord2_is_10000_the_getTickInterval_should_return_0(void){

}



void test_getFakeTick(void){



  uint32_t stickTable[] = {1000,2000,3000};

  setTickSequence(stickTable);

  UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(322), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(323), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((getFakeTick())), (((void *)0)), (_U_UINT)(324), UNITY_DISPLAY_STYLE_INT);



}





void test_TIM2_IRQHandler_when_timer_expire_for_motor1_the_TIM2_IRQHandler_was_called(void){



   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,1000,2000,3000};

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   setTickSequence(stickTable);

   initialStepCommand(motor0->motorConfiguration);



   _timerDelay(&motor0->timerElement,2000);

   _timerDelay(&motor1->timerElement,6000);



   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(344), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(345), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(346), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(350), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(351), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(352), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(353), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(354), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(355), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(357), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(358), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(359), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(360), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(362), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(363), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(364), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(365), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2000);

   _timerDelay(&motor1->timerElement,6000);



   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(397), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(398), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(399), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(400), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(401), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(404), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(405), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(406), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(407), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(408), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(409), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(412), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(413), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(414), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(415), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(417), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(418), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(419), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(420), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((7000)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(423), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(424), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(425), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(426), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(427))));};



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(429), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(430), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(431), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(432), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(433), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(434), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(435), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(436), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(437), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(438), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2);

   _timerDelay(&motor1->timerElement,2);





   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(473), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(474), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(477), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(478), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(479), UNITY_DISPLAY_STYLE_HEX32);





   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((1002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(484), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(485), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(486), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(487), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(488))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(494), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(495), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(496), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(497), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(498), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(499), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(500), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(501), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(502), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2);

   _timerDelay(&motor1->timerElement,2);

   _timerDelay(&motor2->timerElement,5);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(539), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(540), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(541), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(543), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(544), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(545), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(546), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((2002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(550), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(551), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(552), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0001)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(553), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(555), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(556), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(558), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(560), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(561), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(563), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(565), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(566), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(567), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(568), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(569), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(570), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(571), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();

   UnityAssertEqualNumber((_U_SINT)((3005)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(574), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(575), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(576), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(577), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(578))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(584), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(585), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(586), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(587), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(589), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(590), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(591), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(592), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(593), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(594), UNITY_DISPLAY_STYLE_INT);





   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(597), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2);

   _timerDelay(&motor1->timerElement,2);

   _timerDelay(&motor2->timerElement,2);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(634), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(635), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(636), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(638), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(639), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(640), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(641), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(645), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(646), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(647), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x0000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(648), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(649))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(655), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(656), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(657), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(658), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(660), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(661), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(662), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(663), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(664), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(665), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(666), UNITY_DISPLAY_STYLE_INT);



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



   _timerDelay(&motor0->timerElement,2);

   _timerDelay(&motor1->timerElement,2);

   _timerDelay(&motor2->timerElement,2);

   _timerDelay(&motor3->timerElement,5);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(704), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(705), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(706), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(707), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(709), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(710), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(711), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(712), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(713), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((3002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(717), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(718), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(719), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(720), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(722), UNITY_DISPLAY_STYLE_HEX32);





   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((root->head->actionTime)), (((void *)0)), (_U_UINT)(725), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(727), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(728), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(729), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(730), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(732), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(733), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(734), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(735), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(736), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(737), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(738), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(739), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(740), UNITY_DISPLAY_STYLE_INT);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((4005)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(744), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(745), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(746), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(747), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(748))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(754), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(755), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(756), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(757), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next->next)), (((void *)0)), (_U_UINT)(758), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(760), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(761), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(762), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(763), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(764), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(765), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(766), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(767), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(768), UNITY_DISPLAY_STYLE_INT);

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



   _timerDelay(&motor0->timerElement,2);

   _timerDelay(&motor1->timerElement,2);

   _timerDelay(&motor2->timerElement,2);

   _timerDelay(&motor3->timerElement,2);



   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(805), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(806), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(807), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(808), UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(810), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(811), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(812), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(813), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(814), UNITY_DISPLAY_STYLE_HEX32);



   TIM2_IRQHandler();



   UnityAssertEqualNumber((_U_SINT)((4002)), (_U_SINT)((tickRecord1)), (((void *)0)), (_U_UINT)(818), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((tickRecord2)), (((void *)0)), (_U_UINT)(819), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(820), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(821), UNITY_DISPLAY_STYLE_INT);

   if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(822))));};











   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head)), (((void *)0)), (_U_UINT)(828), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next)), (((void *)0)), (_U_UINT)(829), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next)), (((void *)0)), (_U_UINT)(830), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next)), (((void *)0)), (_U_UINT)(831), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->motorConfiguration->motorElement)), (_U_SINT)(_UP)((motorRoot->head->next->next->next->next)), (((void *)0)), (_U_UINT)(832), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor0->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(834), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor1->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(835), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(836), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor3->motorConfiguration->counter)), (((void *)0)), (_U_UINT)(837), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor0->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[0])), (((void *)0)), (_U_UINT)(838), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor1->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[1])), (((void *)0)), (_U_UINT)(839), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor2->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[2])), (((void *)0)), (_U_UINT)(840), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((motor3->motorConfiguration->stepLowCommand)), (_U_SINT)((motorDriveBuffer[3])), (((void *)0)), (_U_UINT)(841), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3))->CCR&0x01)), (((void *)0)), (_U_UINT)(842), UNITY_DISPLAY_STYLE_INT);





}

void test_new_timerDelay_call_timerDelay_to_delay_1000_tick_the_link_list_should_contain_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,2000,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);

   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(866), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(867), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(868), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(869), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(870), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(871), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_and_2000_tick_the_link_list_should_contain_two_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0,3000,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(895), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(896), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(897), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(898), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(899), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(900), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(903), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(904), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(905), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(906), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(907), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(908), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(909), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(910), UNITY_DISPLAY_STYLE_INT);

}

void test_new_timerDelay_call_timerDelay_to_delay_1000_3000_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {10,30,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(933), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(934), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(936), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(937), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(938), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(941), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(942), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(943), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(944), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(945), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(946), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(947), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(948), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor2->timerElement,6000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(951), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(952), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(953), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(954), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(955), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(956), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3020)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(957), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(958), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(959), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(960), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_and_100_tick_the_link_list_should_contain_two_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {20,30,4000};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(983), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(984), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(985), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(986), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(987), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(988), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(991), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(992), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(993), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((880)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(994), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(995), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(996), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CNT)), (((void *)0)), (_U_UINT)(997), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(998), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(999), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1000), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1100_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {10,30};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1023), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1024), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1025), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1026), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1027), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1028), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1031), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1032), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1033), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1034), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1035), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1036), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1037), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1038), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor2->timerElement,1100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1041), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1042), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1043), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1044), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1045), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1046), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1047), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1048), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1049), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1050), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_100_1000_1100_and_3000_tick_the_link_list_should_contain_four_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   MotorInfo* motor3 = motorInit(motorController,1000,2);



   uint32_t stickTable[] = {10,30,40};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1075), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1076), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1077), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1078), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1079), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1080), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1083), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1084), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1085), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1086), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2010)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1087), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1088), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1089), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1090), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor2->timerElement,1100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1093), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1094), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1095), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1096), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1097), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1098), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1099), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1100), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1101), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1102), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor3->timerElement,100);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1105), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1106), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1107), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1108), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next->next)), (((void *)0)), (_U_UINT)(1109), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((860)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1110), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1880)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1111), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((130)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1112), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((motor3->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1113), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1114), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1115), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((40)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1116), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_6000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1139), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1140), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1141), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1142), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1143), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1144), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,3000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1147), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1148), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1149), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1150), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1151), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1152), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1153), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1154), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor2->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1157), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1158), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1159), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1160), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1161), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2000)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1162), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1163), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1164), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1165), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1166), UNITY_DISPLAY_STYLE_INT);



}

void test_new_timerDelay_call_timerDelay_to_delay_1000_1000_and_1000_tick_the_link_list_should_contain_three_time_element(void){

   MotorInfo* motor0 = motorInit(motorController,1000,0);

   MotorInfo* motor1 = motorInit(motorController,2000,1);

   MotorInfo* motor2 = motorInit(motorController,1000,2);

   uint32_t stickTable[] = {0,0};

   setTickSequence(stickTable);

   setDataNumber(((DMA_Channel_TypeDef*) ((uint32_t)HostDma1_Channel3)),3);



   _timerDelay(&motor0->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1190), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1191), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1192), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1193), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1194), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1195), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor1->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1198), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1199), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1200), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1201), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1202), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1203), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1204), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1205), UNITY_DISPLAY_STYLE_INT);



   _timerDelay(&motor2->timerElement,1000);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1208), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor1->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(1209), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(1210), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((&motor0->timerElement)), (_U_SINT)(_UP)((root->head->next->next->next)), (((void *)0)), (_U_UINT)(1211), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((motor0->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1213), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor1->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1214), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->timerElement.actionTime)), (((void *)0)), (_U_UINT)(1215), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->CR1&0x0001)), (((void *)0)), (_U_UINT)(1216), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1000)), (_U_SINT)((((TIM_TypeDef*) ((uint32_t)HostTim2))->ARR)), (((void *)0)), (_U_UINT)(1217), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(1218), UNITY_DISPLAY_STYLE_INT);



}
