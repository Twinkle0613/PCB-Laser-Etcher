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

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10};

   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);

   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),62); };

}

void test_timerListAdd_two_time_element_is_added_into_link_list(void){

   printf("No.02 - timerListAdd\n");

   struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5};

   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

    timerListAdd(ptr,10);

   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),85); };

}

void test_timerListAdd_three_time_element_is_added_into_link_list(void){

    printf("No.03 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5};

   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,12);



   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),114); };

}

void test_timerListAdd_four_time_element_is_added_into_link_list(void){

    printf("No.04 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2};



   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,12);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,109);

   timerListAdd(ptr,13);

}

 void test_timerListAdd_five_time_element_is_added_into_link_list(void){

     printf("No.05 - timerListAdd\n");

 }

void test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2(void){

    printf("No.06 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {15,5};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,20);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),233); };

}

void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.07 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,4);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),264); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.08 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,3,4};



   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),298); };

}

void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.09 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3,7};



   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),333); };

}

void test_relative_Time_Link_list_one_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.10 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,0};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,5);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),376); };

}

void test_relative_Time_Link_list_two_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.11 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),408); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.12 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,7,0};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),441); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval_within_15(void){

    printf("No.13 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,7};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),474); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_that_period_equal_timeInterval_within_15(void){

    printf("No.14 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,0,7};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),511); };

}

void test_relative_Time_Link_list_the_link_list_contain_three_0_that_period_equal_timeInterval_within_15(void){

    printf("No.15 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,0,0,7};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),551); };

}

void test_relative_Time_Link_list_the_link_list_contain_four_0_that_period_equal_timeInterval_within_15(void){

    printf("No.16 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    struct ListElement* store1;

    struct ListElement* store2;

    int arr[] = {10,5,0,0,0,0,7};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);







    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    store1 = ptr->head->next->next;

    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(593), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next;

    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(600), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next->next;

    _updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(607), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),609); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_at_end_that_period_equal_timeInterval_within_15(void){

    printf("No.17 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();



    int arr[] = {10,5,7,0,0};



    _updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    struct ListElement* store1 = ptr->head->next->next->next;

    _updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);

    struct ListElement* store2 = ptr->head->next->next->next;



    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(650), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),651); };

}

void test_relative_Time_Link_list_contain_a_0_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.18 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,3,4,9};



   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),689); };

}

void test_relative_Time_Link_list_initial_the_first_Node_contain_0_and_add_a_new_node(void){

      printf("No.19 - timerListAdd\n");

      struct Linkedlist *ptr = createLinkedList();

      int arr[] = {0,10};

}



void test_timerListDelete_delete_a_Node(void){

   printf("No.20 - timerListDelete\n");

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10,5,7};



   _updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   _updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   timerListDelete(ptr->head->next->next);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),742); };





}





void test_new_timerListAdd_(void){

  printf("No.21 - initialization root\n");

  root = createLinkedList();

  if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(751))));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(752), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(753), UNITY_DISPLAY_STYLE_INT);

}



void test_updateActionTime_initialy_the_actionTime_of_motor_is_0_that_change_to_9_and_20(void){

  printf("No.22 - updateActionTime\n");

  struct ListElement *motor1 = createLinkedElement(0);

  updateActionTime(motor1,9);

  UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(760), UNITY_DISPLAY_STYLE_INT);

  updateActionTime(motor1,20);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(762), UNITY_DISPLAY_STYLE_INT);

}

void test_timerQueue_create_three_TimerElement_that_added_to_relative_time_link_list_10_5_7(void){

    printf("No.23 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

    int arr[] = {10,5,7};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(784), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((10)), (_U_SINT)(_UP)((motor1->actionTime)), (((void *)0)), (_U_UINT)(785), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(790), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((5)), (_U_SINT)(_UP)((motor2->actionTime)), (((void *)0)), (_U_UINT)(791), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,108);

    timerQueue(motor3,14);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(796), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((7)), (_U_SINT)(_UP)((motor3->actionTime)), (((void *)0)), (_U_UINT)(797), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),798); };

}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_3_2(void){

    printf("No.24 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,3,2};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(820), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(825), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor3,8);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(830), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),832); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_8_2_5(void){

    printf("No.25 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {8,2,5};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(856), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(861), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor3,3);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(866), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(867), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(868), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),870); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_5(void){

    printf("No.26 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,0,5};



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(895), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(900), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor3,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(905), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),907); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_5_0(void){

    printf("No.27 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,5,0};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(930), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(935), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,106);

    timerQueue(motor3,9);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(940), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),942); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_5_(void){

    printf("No.28 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,0,5};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(966), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(971), UNITY_DISPLAY_STYLE_HEX32);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor3,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(976), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),978); };



}

void test_timerQueue_create_three_TimerElement_that_to_relative_time_link_list_10_0_0_5_(void){

    printf("No.29 - timerQueue\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

    struct ListElement *motor4 = createLinkedElement(0);

     int arr[] = {10,0,0,5};

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(motor1,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor2,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor3,5);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(motor4,5);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1017), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1018), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor4)), (((void *)0)), (_U_UINT)(1019), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1020), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1021); };



}

void test_timerDequeue_timer_list_link_contain_one_timerElement_using_timerDequeue_to_remove_first_timerElement(void){

    printf("No.30 - timerDequeue\n");

    root = createLinkedList();

    struct ListElement *elem1 = createLinkedElement(0);

    struct ListElement *elem2 = createLinkedElement(0);

    struct ListElement *temp;



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(elem1,10);



    temp = timerDequeue();

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1045))));};

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1046), UNITY_DISPLAY_STYLE_HEX32);

}

void test_timerDequeue_timer_list_link_contain_two_timerElement_using_timerDequeue_to_remove_first_timerElement(void){

    printf("No.31 - timerDequeue\n");

    root = createLinkedList();

    struct ListElement *elem1 = createLinkedElement(0);

    struct ListElement *elem2 = createLinkedElement(0);

    struct ListElement *temp;



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(elem1,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(elem2,5);



    temp = timerDequeue();

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1073), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1074), UNITY_DISPLAY_STYLE_HEX32);

}

void test_timerDequeue_timer_list_link_contain_three_timerElement_using_timerDequeue_to_remove_first_timerElement(void){

    printf("No.32 - timerDequeue\n");

    root = createLinkedList();

    struct ListElement *elem1 = createLinkedElement(0);

    struct ListElement *elem2 = createLinkedElement(0);

    struct ListElement *elem3 = createLinkedElement(0);

    struct ListElement *temp;



    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(elem1,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(elem2,5);



    _updateBaseTime(root,100);

    updateCurTime(root,108);

    timerQueue(elem3,14);



    temp = timerDequeue();

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1107), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem1)), (_U_SINT)(_UP)((temp)), (((void *)0)), (_U_UINT)(1108), UNITY_DISPLAY_STYLE_HEX32);

}



void test_updateHead_the_link_list_contain_one_timerElement_the_head_of_root_will_point_to_null(void){

    printf("No.33 - updateHead\n");

    root = createLinkedList();

    struct ListElement *elem1 = createLinkedElement(0);

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(elem1,10);

    updateHead(root);

    if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(1119))));};



}



void test_updateHead_the_link_list_contain_twon_timerElement_the_head_of_root_will_point_to_next_element(void){

    printf("No.34 - updateHead\n");

    root = createLinkedList();

    struct ListElement *elem1 = createLinkedElement(0);

    struct ListElement *elem2 = createLinkedElement(0);

    _updateBaseTime(root,10);

    updateCurTime(root,20);

    timerQueue(elem1,10);



    _updateBaseTime(root,100);

    updateCurTime(root,105);

    timerQueue(elem2,5);



    updateHead(root);

    UnityAssertEqualNumber((_U_SINT)(_UP)((elem2)), (_U_SINT)(_UP)((root->head)), (((void *)0)), (_U_UINT)(1137), UNITY_DISPLAY_STYLE_HEX32);

}
