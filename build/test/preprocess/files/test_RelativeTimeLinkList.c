#include "RelativeTimeLinkList.h"
#include "projectStruct.h"
#include "CustomAssertion.h"
#include "Linklist.h"
#include "unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}

void test_timerListAdd_a_time_element_is_added_into_link_list(void){

   printf("No.01 - timerListAdd\n");

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10};

   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);

   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),46); };

}

void test_timerListAdd_two_time_element_is_added_into_link_list(void){

   printf("No.02 - timerListAdd\n");

   struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5};

   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

    timerListAdd(ptr,10);

   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),69); };

}

void test_timerListAdd_three_time_element_is_added_into_link_list(void){

    printf("No.03 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5};

   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,12);



   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),98); };

}

void test_timerListAdd_four_time_element_is_added_into_link_list(void){

    printf("No.04 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2};



   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,12);



   updateBaseTime(ptr,100);

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



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,20);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),217); };

}

void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.07 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,4);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),248); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.08 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,3,4};



   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),282); };

}

void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.09 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3,7};



   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

    timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),317); };

}

void test_relative_Time_Link_list_one_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.10 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,0};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,5);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),360); };

}

void test_relative_Time_Link_list_two_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.11 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,7);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),392); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval(void){

    printf("No.12 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,7,0};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),425); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_period_equal_timeInterval_within_15(void){

    printf("No.13 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,7};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),458); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_that_period_equal_timeInterval_within_15(void){

    printf("No.14 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,0,7};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),495); };

}

void test_relative_Time_Link_list_the_link_list_contain_three_0_that_period_equal_timeInterval_within_15(void){

    printf("No.15 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,0,0,7};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),535); };

}

void test_relative_Time_Link_list_the_link_list_contain_four_0_that_period_equal_timeInterval_within_15(void){

    printf("No.16 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    struct ListElement* store1;

    struct ListElement* store2;

    int arr[] = {10,5,0,0,0,0,7};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);







    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    store1 = ptr->head->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(577), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(584), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(591), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),593); };

}

void test_relative_Time_Link_list_the_link_list_contain_two_0_at_end_that_period_equal_timeInterval_within_15(void){

    printf("No.17 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();



    int arr[] = {10,5,7,0,0};



    updateBaseTime(ptr,10);

    updateCurTime(ptr,20);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,105);

    timerListAdd(ptr,10);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    struct ListElement* store1 = ptr->head->next->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);

    struct ListElement* store2 = ptr->head->next->next->next;



    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(634), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),635); };

}

void test_relative_Time_Link_list_contain_a_0_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.18 - timerListAdd\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,0,3,4,9};



   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,13);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),673); };

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



   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,105);

   timerListAdd(ptr,10);



   updateBaseTime(ptr,100);

   updateCurTime(ptr,108);

   timerListAdd(ptr,14);



   timerListDelete(ptr->head->next->next);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),726); };





}





void test_new_timerListAdd_(void){

  printf("No.21 - initialization root\n");

  root = createLinkedList();

  if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(735))));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(736), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(737), UNITY_DISPLAY_STYLE_INT);

}



void test_updateActionTime_initialy_the_actionTime_of_motor_is_0_that_change_to_9_and_20(void){

  printf("No.22 - updateActionTime\n");

  struct ListElement *motor1 = createLinkedElement(0);

  updateActionTime(motor1,9);

  UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(744), UNITY_DISPLAY_STYLE_INT);

  updateActionTime(motor1,20);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(746), UNITY_DISPLAY_STYLE_INT);

}

void test_newTimerListAdd_create_three_TimerElement_that_added_to_relative_time_link_list_10_5_7(void){

    printf("No.23 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

    int arr[] = {10,5,7};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(768), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((10)), (_U_SINT)(_UP)((motor1->actionTime)), (((void *)0)), (_U_UINT)(769), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(774), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((5)), (_U_SINT)(_UP)((motor2->actionTime)), (((void *)0)), (_U_UINT)(775), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,108);

    newTimerListAdd(motor3,14);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(780), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((7)), (_U_SINT)(_UP)((motor3->actionTime)), (((void *)0)), (_U_UINT)(781), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),782); };

}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_10_3_2(void){

    printf("No.24 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,3,2};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(804), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(809), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,8);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(814), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),816); };



}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_8_2_5(void){

    printf("No.25 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {8,2,5};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(840), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(845), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,3);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(850), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(851), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(852), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),854); };



}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_10_0_5(void){

    printf("No.26 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,0,5};



    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(879), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(884), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(889), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),891); };



}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_10_5_0(void){

    printf("No.27 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,5,0};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(914), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(919), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,106);

    newTimerListAdd(motor3,9);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(924), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),926); };



}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_10_0_5_(void){

    printf("No.28 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

     int arr[] = {10,0,5};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(950), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(955), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(960), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),962); };



}

void test_newTimerListAdd_create_three_TimerElement_that_to_relative_time_link_list_10_0_0_5_(void){

    printf("No.29 - newTimerListAdd\n");

    root = createLinkedList();

    struct ListElement *motor1 = createLinkedElement(0);

    struct ListElement *motor2 = createLinkedElement(0);

    struct ListElement *motor3 = createLinkedElement(0);

    struct ListElement *motor4 = createLinkedElement(0);

     int arr[] = {10,0,0,5};

    updateBaseTime(root,10);

    updateCurTime(root,20);

    newTimerListAdd(motor1,10);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,5);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor4,5);



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1001), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1002), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor4)), (((void *)0)), (_U_UINT)(1003), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1004), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1005); };



}
