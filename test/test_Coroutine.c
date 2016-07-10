#include "unity.h"
#include "Coroutine.h"
#include "mock_MockFunction.h"
#include <malloc.h>
#include "Linklist.h"
#include "RelativeTimeLinkList.h"
#include "stepperMotor.h"
#include "CustomAssertion.h"
#include "peripherals.h"
#include "Host.h"
#include "Registers.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

void setUp(void)
{
  HostGpioA= malloc((sizeof(GPIO_TypeDef)));
  HostTim2= malloc((sizeof(TIM_TypeDef)));
}

void tearDown(void)
{
   free(HostGpioA);
   free(HostTim2);
   HostGpioA = NULL;
   HostTim2 = NULL;
}

void testMotor123(motorInfo* whichMotor){
  whichMotor->step = 1;
  whichMotor->sleep = 1;
}

/*

    head                                head     
     ||                                  ||
     V                                   V
    10      => TIMx_IRQHandler()  =>    NULL

*/

void test_Test_TIMxIRQHandler_a_timerElement_exist_in_root_after_TIMxIRQHandler_the_head_of_roof_should_become_null(void){
  
    root = createLinkedList();
    motorInfo* motor1 = motorInit(testMotor123);
    motorInfo* motor2 = motorInit(testMotor123);
    motorInfo* motor3 = motorInit(testMotor123);

    updateBaseTime(root,10);
    updateCurTime(root,20);
    newTimerListAdd(&motor1->timerElement,10);
    
    TEST_ASSERT_NOT_NULL(root->head);
    TIM2_IRQHandler();
    
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
    motorInfo* motor1 = motorInit(testMotor123);
    motorInfo* motor2 = motorInit(testMotor123);
    motorInfo* motor3 = motorInit(testMotor123);
    int arr[] = {5};

    updateBaseTime(root,10);
    updateCurTime(root,20);
    newTimerListAdd(&motor1->timerElement,10);
    
    updateBaseTime(root,100);
    updateCurTime(root,105);
    newTimerListAdd(&motor2->timerElement,10);
    
    TIM2_IRQHandler();
    
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
    int arr2[] = {10,5,7};
     int arr[] = {5,7};
    motorInfo* motor1 = motorInit(testMotor123);
    motorInfo* motor2 = motorInit(testMotor123);
    motorInfo* motor3 = motorInit(testMotor123);

    updateBaseTime(root,10);
    updateCurTime(root,20);
    newTimerListAdd(&motor1->timerElement,10);
    
    updateBaseTime(root,100);
    updateCurTime(root,105);
    newTimerListAdd(&motor2->timerElement,10);
    
    updateBaseTime(root,100);
    updateCurTime(root,108);
    newTimerListAdd(&motor3->timerElement,14);
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr2,root);
    
    TIM2_IRQHandler();
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head);
    TEST_ASSERT_EQUAL_PTR(&motor2->timerElement,root->head->next->next);
    TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->next);
    TEST_ASSERT_EQUAL_PTR(&motor3->timerElement,root->head->prev);
  
    TEST_ASSERT_NULL(motor1->timerElement.next);
    TEST_ASSERT_NULL(motor1->timerElement.prev);
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
}

