#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "Registers.h"
#include "Host.h"
#include "peripherals.h"
#include "CustomAssertion.h"
#include "stepperMotor.h"
#include "RelativeTimeLinkList.h"
#include "Linklist.h"
#include "mock_MockFunction.h"
#include "Coroutine.h"
#include "unity.h"
















void setUp(void)

{

 HostGpioA= malloc((sizeof(GPIO_TypeDef)));

 HostTim2= malloc((sizeof(TIM_TypeDef)));

}



void tearDown(void)

{

   free(HostGpioA);

   free(HostTim2);

   HostGpioA = ((void *)0);

   HostTim2 = ((void *)0);

}



void testMotor123(motorInfo* whichMotor){

  whichMotor->step = 1;

  whichMotor->sleep = 1;

}

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){



    root = createLinkedList();

    motorInfo* motor1 = motorInit();

    motorInfo* motor2 = motorInit();

    motorInfo* motor3 = motorInit();



    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(&motor1->timerElement,10);



    if ((((root->head)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(56))));};

    TIM2_IRQHandler();



    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(59))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(60))));};

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(61))));};

}

void test_Test_TIMxIRQHandler_two_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    motorInfo* motor1 = motorInit();

    motorInfo* motor2 = motorInit();

    motorInfo* motor3 = motorInit();

    int arr[] = {5};



    setCallBack(&motor2->timerElement,testMotor123);

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(&motor1->timerElement,10);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(&motor2->timerElement,10);



    TIM2_IRQHandler();



    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(91), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(92), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(93), UNITY_DISPLAY_STYLE_HEX32);

    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(94))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(95))));};

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),96); };

}

void test_Test_TIMxIRQHandler_5_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_will_point_to_last_timerElement(void){



    root = createLinkedList();

    int arr2[] = {10,5,7};

     int arr[] = {5,7};

    motorInfo* motor1 = motorInit();

    motorInfo* motor2 = motorInit();

    motorInfo* motor3 = motorInit();

    setCallBack(&motor2->timerElement,testMotor123);

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(&motor1->timerElement,10);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(&motor2->timerElement,10);



    updateBaseTime(root,100);

    updateCurTime(root,108);

    newTimerListAdd(&motor3->timerElement,14);

    { test_assert_cycle_link_list(root,arr2,sizeof(arr2)/sizeof(uint32_t),129); };



    TIM2_IRQHandler();

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(132), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor2->timerElement)), (_U_SINT)(_UP)((root->head->next->next)), (((void *)0)), (_U_UINT)(133), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->next)), (((void *)0)), (_U_UINT)(134), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((&motor3->timerElement)), (_U_SINT)(_UP)((root->head->prev)), (((void *)0)), (_U_UINT)(135), UNITY_DISPLAY_STYLE_HEX32);



    if ((((motor1->timerElement.next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(137))));};

    if ((((motor1->timerElement.prev)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(138))));};



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),140); };



}



void test_TIM2_IRQHandler_call_the_function(void){



      root = createLinkedList();

      motorInfo* motor1 = motorInit();

      motorInfo* motor2 = motorInit();



      setCallBack(&motor2->timerElement,testMotor123);



      updateBaseTime(root,10);

      updateCurTime(root,20);

      newTimerListAdd(&motor1->timerElement,10);



      updateBaseTime(root,100);

      updateCurTime(root,105);

      newTimerListAdd(&motor2->timerElement,10);



      TIM2_IRQHandler();

      UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->sleep)), (((void *)0)), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor2->step)), (((void *)0)), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

}
