#include "RelativeTimeLinkList.h"
#include "CustomAssertion.h"
#include "projectStruct.h"
#include "Timer_setting.h"
#include "peripherals.h"
#include "Registers.h"
#include "Linklist.h"
#include "Host.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "unity.h"






















void setUp(void)

{

  HostTim2= malloc((sizeof(TIM_TypeDef)));

}



void tearDown(void)

{

   free(HostTim2);

   HostTim2 = ((void *)0);

}

void test_timerListAdd_a_time_element_is_added_into_link_list(void){

   printf("No.01 - timerListAdd\n");

   Linkedlist *ptr = createLinkedList();

   uint16_t arr[] = {10};

   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);

   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),62); };

}

void test_timerListAdd_two_time_element_is_added_into_link_list(void){

   printf("No.02 - timerListAdd\n");

   Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5};

   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

    timerListAdd(ptr,10);

   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

    timerListAdd(ptr,10);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),85); };

}

void test_timerListAdd_three_time_element_is_added_into_link_list(void){

    printf("No.03 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,5};

   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,108);

   timerListAdd(ptr,12);



   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),114); };

}

void test_timerListAdd_four_time_element_is_added_into_link_list(void){

    printf("No.04 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,5,2};



   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,108);

   timerListAdd(ptr,12);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,109);

   timerListAdd(ptr,13);

}

 void test_timerListAdd_five_time_element_is_added_into_link_list(void){

     printf("No.05 - timerListAdd\n");

 }

void test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2(void){

    printf("No.06 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {15,5};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,20);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),233); };

}

void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.07 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,2,3};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,4);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),264); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.08 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,3,4};



   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,108);

   timerListAdd(ptr,14);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),298); };

}

void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.09 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,2,3,7};



   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,108);

   timerListAdd(ptr,14);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

   timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),333); };

}

void test_relative_Time_Link_list_one_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.10 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,0};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,5);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),376); };

}

void test_relative_Time_Link_list_two_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.11 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,0};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),408); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.12 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,7,0};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),441); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval_within_15(void){

    printf("No.13 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,0,7};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),474); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_that_period_equal_timeInterval_within_15(void){

    printf("No.14 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,0,0,7};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),511); };

}

void test_relative_Time_Link_list_the_link_list_contain_three_0_that_period_equal_timeInterval_within_15(void){

    printf("No.15 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,0,0,0,7};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),551); };

}

void test_relative_Time_Link_list_the_link_list_contain_four_0_that_period_equal_timeInterval_within_15(void){

    printf("No.16 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    ListElement* store1;

    ListElement* store2;

    uint16_t arr[] = {10,5,0,0,0,0,7};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);







    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);



    store1 = ptr->head->next->next;

    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(593), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next;

    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(600), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next->next;

    setBaseTime(ptr,100);

    setCurrentTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(607), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),609); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_at_end_that_period_equal_timeInterval_within_15(void){

    printf("No.17 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();



    uint16_t arr[] = {10,5,7,0,0};



    setBaseTime(ptr,10);

    setCurrentTime(ptr,20);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,105);

    timerListAdd(ptr,10);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);



    ListElement* store1 = ptr->head->next->next->next;

    setBaseTime(ptr,100);

    setCurrentTime(ptr,108);

    timerListAdd(ptr,14);

    ListElement* store2 = ptr->head->next->next->next;



    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(650), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),651); };

}

void test_relative_Time_Link_list_contain_a_0_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.18 - timerListAdd\n");

    Linkedlist *ptr = createLinkedList();

    uint16_t arr[] = {10,5,0,3,4,9};



   setBaseTime(ptr,10);

   setCurrentTime(ptr,20);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

   timerListAdd(ptr,10);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,108);

   timerListAdd(ptr,14);



   setBaseTime(ptr,100);

   setCurrentTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),689); };

}

void test_relative_Time_Link_list_initial_the_first_Node_contain_0_and_add_a_new_node(void){

      printf("No.19 - timerListAdd\n");

      Linkedlist *ptr = createLinkedList();

      uint16_t arr[] = {0,10};

}









void test_new_timerListAdd_(void){

  printf("No.21 - initialization root\n");

  root = createLinkedList();

  if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(726))));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(727), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(728), UNITY_DISPLAY_STYLE_INT);

}



void test_updateActionTime_initialy_the_actionTime_of_motor_is_0_that_change_to_9_and_20(void){

  printf("No.22 - updateActionTime\n");

  ListElement *motor1 = createLinkedElement(0);

  updateActionTime(motor1,9);

  UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(735), UNITY_DISPLAY_STYLE_INT);

  updateActionTime(motor1,20);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(737), UNITY_DISPLAY_STYLE_INT);

}

void test_timerQueue_create_three_TimerElement_that_added_to_relative_time_link_list_10_5_7(void){

    printf("No.23 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    uint16_t arr[] = {10,5,7};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(764), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((10)), (_U_SINT)(_UP)((motor1->actionTime)), (((void *)0)), (_U_UINT)(765), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(770), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((5)), (_U_SINT)(_UP)((motor2->actionTime)), (((void *)0)), (_U_UINT)(771), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,108);

    timerQueue(motor3,14);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(777), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(778), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(779), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(781), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(782), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(783), UNITY_DISPLAY_STYLE_INT);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),785); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_3_2(void){

    printf("No.24 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    uint16_t arr[] = {10,3,2};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(812), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(813), UNITY_DISPLAY_STYLE_INT);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(818), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(819), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(820), UNITY_DISPLAY_STYLE_INT);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,8);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(826), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(827), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(828), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(830), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(831), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(832), UNITY_DISPLAY_STYLE_INT);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),834); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_8_2_5(void){

    printf("No.25 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

     uint16_t arr[] = {8,2,5};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(859), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(864), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,3);



    UnityAssertEqualNumber((_U_SINT)((8)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(870), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(871), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(872), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(874), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(875), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(876), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),878); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_1_9_0(void){

    printf("No.25.1 - timerQueue\n");



    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

     uint16_t arr[] = {1,9,0};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(903), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(908), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,100);

    timerQueue(motor3,1);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(914), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(915), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(916), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(918), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(919), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(920), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),922); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0(void){

    printf("No.26 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    uint16_t arr[] = {10,0,5};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(947), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,5);





    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(954), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(955), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(957), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(958), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),960); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_0(void){

    printf("No.26.0.1 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    uint16_t arr[] = {10,0,0};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(984), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,5);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,5);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(994), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(995), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(996), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(998), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(999), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1000), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next->next)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1001), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1003); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_5(void){

    printf("No.26.1 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    uint16_t arr[] = {10,0,5};



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1027), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1032), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,10);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1038), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1039), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1040), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(1042), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(1043), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(1044), UNITY_DISPLAY_STYLE_INT);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1046); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_5_0(void){

    printf("No.27 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

     uint16_t arr[] = {10,5,0};

    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1069), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1074), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,106);

    timerQueue(motor3,9);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1080), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1081), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1082), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(1084), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(1085), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(1086), UNITY_DISPLAY_STYLE_INT);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1088); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_5_(void){

    printf("No.28 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

     uint16_t arr[] = {10,0,5};

    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1111), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1116), UNITY_DISPLAY_STYLE_HEX32);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,5);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1122), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1123), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1124), UNITY_DISPLAY_STYLE_HEX32);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(1126), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(1127), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(1128), UNITY_DISPLAY_STYLE_INT);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1130); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_0_5_(void){

    printf("No.29 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);

    ListElement *motor3 = createLinkedElement(0);

    ListElement *motor4 = createLinkedElement(0);

     uint16_t arr[] = {10,0,0,5};

    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(motor1,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor2,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor3,5);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(motor4,5);



    UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(1169), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor3->actionTime)), (((void *)0)), (_U_UINT)(1170), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((motor4->actionTime)), (((void *)0)), (_U_UINT)(1171), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((motor2->actionTime)), (((void *)0)), (_U_UINT)(1172), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1174), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1175), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor4)), (((void *)0)), (_U_UINT)(1176), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1177), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1179); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_5000_1990(void){

    printf("No.29.1 - timerQueue\n");

    root = createLinkedList();

    ListElement *motor1 = createLinkedElement(0);

    ListElement *motor2 = createLinkedElement(0);



    uint16_t arr[] = {5010,1990};

    setBaseTime(root,0);

    setCurrentTime(root,1);

    timerQueue(motor1,7000);



    setBaseTime(root,100);

    setCurrentTime(root,110);

    timerQueue(motor2,5000);







    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1211), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1212), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1214); };



}

void test_dequeue_timer_list_link_contain_one_timerElement_using_dequeue_to_remove_first_timerElement(void){

    printf("No.30 - dequeue\n");

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    ListElement *temp;



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(elem1,10);



    temp = dequeue(root);

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1239))));};

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1240), UNITY_DISPLAY_STYLE_HEX32);

}

void test_dequeue_timer_list_link_contain_two_timerElement_using_dequeue_to_remove_first_timerElement(void){

    printf("No.31 - dequeue\n");

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    ListElement *temp;



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(elem1,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(elem2,5);



    temp = dequeue(root);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1266), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1267), UNITY_DISPLAY_STYLE_HEX32);

}

void test_dequeue_timer_list_link_contain_three_timerElement_using_dequeue_to_remove_first_timerElement(void){

    printf("No.32 - dequeue\n");

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    ListElement *elem3 = createLinkedElement(0);

    ListElement *temp;



    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(elem1,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(elem2,5);



    setBaseTime(root,100);

    setCurrentTime(root,108);

    timerQueue(elem3,14);



    temp = dequeue(root);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1300), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1301), UNITY_DISPLAY_STYLE_HEX32);

}









void test_updateHead_the_link_list_contain_one_timerElement_the_head_of_root_will_point_to_null(void){

    printf("No.33 - updateHead\n");

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(elem1,10);

    updateHead(root);

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1315))));};



}



void test_updateHead_the_link_list_contain_twon_timerElement_the_head_of_root_will_point_to_next_element(void){

    printf("No.34 - updateHead\n");

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    setBaseTime(root,10);

    setCurrentTime(root,20);

    timerQueue(elem1,10);



    setBaseTime(root,100);

    setCurrentTime(root,105);

    timerQueue(elem2,5);



    updateHead(root);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1333), UNITY_DISPLAY_STYLE_HEX32);

}





void test_insertTimeElementIntoBack_(void){

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    ListElement *elem3 = createLinkedElement(0);



   addList(root,elem1);

   addList(root,elem2);

   insertTimeElementIntoBack(elem2,elem3);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((elem1)), (((void *)0)), (_U_UINT)(1346), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((elem3)), (((void *)0)), (_U_UINT)(1347), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((elem2)), (((void *)0)), (_U_UINT)(1348), UNITY_DISPLAY_STYLE_HEX32);

}







void test_insertTimeElementIntoFront_(void){

    root = createLinkedList();

    ListElement *elem1 = createLinkedElement(0);

    ListElement *elem2 = createLinkedElement(0);

    ListElement *elem3 = createLinkedElement(0);



   addList(root,elem1);

   addList(root,elem2);

   insertTimeElementIntoFront(elem2,elem3);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((elem1)), (((void *)0)), (_U_UINT)(1362), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((elem2)), (((void *)0)), (_U_UINT)(1363), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((elem3)), (((void *)0)), (_U_UINT)(1364), UNITY_DISPLAY_STYLE_HEX32);

}
