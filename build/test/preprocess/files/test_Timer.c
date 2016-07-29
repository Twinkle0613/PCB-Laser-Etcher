#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "CustomAssertion.h"
#include "Timer_setting.h"
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


























void testMotor123(motorInfo* whichMotor){

  whichMotor->step = 1;

  whichMotor->sleep = 1;

}



void setUp(void)

{

  HostTim2= malloc((sizeof(TIM_TypeDef)));

}



void tearDown(void)

{

   free(HostTim2);

   HostTim2 = ((void *)0);

}

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){



    root = createLinkedList();

    motorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(&motor1->timerElement,10);



    if ((((root->head)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(66))));};

    TIM2_IRQHandler();

     UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(69))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(70))));};

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(71))));};

}

void test_Test_TIMxIRQHandler_two_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    motorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);

    int arr[] = {5};



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(&motor1->timerElement,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(&motor2->timerElement,10);



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(100), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(101), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(102), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(103))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(104))));};

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),105); };

}

void test_Test_TIMxIRQHandler_5_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    int arr2[] = {10,5,7};

     int arr[] = {5,7};

    motorInfo* motor1 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor2 = motorInit(testMotor123,0,FIRST_MOTOR);

    motorInfo* motor3 = motorInit(testMotor123,0,FIRST_MOTOR);



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(&motor1->timerElement,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(&motor2->timerElement,10);



    _updateBaseTime(root,100);

    updateCurTime(root,108);

    timerQueue(&motor3->timerElement,14);

    { test_assert_cycle_link_list(root,arr2,sizeof(arr2)/sizeof(uint32_t),138); };



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(141), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(142), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(143), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(144), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((110)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(146), UNITY_DISPLAY_STYLE_INT);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(147))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(148))));};



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),150); };

}
