#include "CustomAssertion.h"
#include "Linklist.h"
#include "RelativeTimeLinkList.h"
#include "unity.h"










void setUp(void)

{

}



void tearDown(void)

{

}















void test_recordTime_Add_data(void){

  printf("No.00\n");

  timeRecordList *record = recordTime(10,20,10);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->baseTime)), (((void *)0)), (_U_UINT)(27), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((record->currentTime)), (((void *)0)), (_U_UINT)(28), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->rate)), (((void *)0)), (_U_UINT)(29), UNITY_DISPLAY_STYLE_INT);

}

void test_timerListAdd_a_time_element_is_added_into_link_list(void){

   printf("No.01 - timerListAdd\n");

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10};

   updateBaseTime(ptr,10);

   updateCurTime(ptr,20);

   timerListAdd(ptr,10);

   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),58); };

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

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),81); };

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



   { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),110); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),229); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),260); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),294); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),329); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),372); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),404); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),437); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),470); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),507); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),547); };

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(589), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(596), UNITY_DISPLAY_STYLE_HEX32);



    store1 = ptr->head->next->next->next->next;

    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);

    store2 = ptr->head->next->next->next->next;

    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(603), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),605); };

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



    UnityAssertEqualNumber((_U_SINT)(_UP)((store1)), (_U_SINT)(_UP)((store2)), (((void *)0)), (_U_UINT)(646), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),647); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),685); };

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

    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),738); };





}





void test_new_timerListAdd_(void){

  printf("No.21 - initialization root\n");

  root = createLinkedList();

  if ((((root->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(747))));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->curTime)), (((void *)0)), (_U_UINT)(748), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((root->baseTime)), (((void *)0)), (_U_UINT)(749), UNITY_DISPLAY_STYLE_INT);

}



void test_updateActionTime_initialy_the_actionTime_of_motor_is_0_that_change_to_9_and_20(void){

  printf("No.22 - updateActionTime\n");

  struct ListElement *motor1 = createLinkedElement(0);

  updateActionTime(motor1,9);

  UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(756), UNITY_DISPLAY_STYLE_INT);

  updateActionTime(motor1,20);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((motor1->actionTime)), (((void *)0)), (_U_UINT)(758), UNITY_DISPLAY_STYLE_INT);

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(780), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((10)), (_U_SINT)(_UP)((motor1->actionTime)), (((void *)0)), (_U_UINT)(781), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(786), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((5)), (_U_SINT)(_UP)((motor2->actionTime)), (((void *)0)), (_U_UINT)(787), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,108);

    newTimerListAdd(motor3,14);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(792), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((7)), (_U_SINT)(_UP)((motor3->actionTime)), (((void *)0)), (_U_UINT)(793), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),794); };

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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(816), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(821), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,8);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(826), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),828); };



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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(852), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(857), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,3);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(862), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(863), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(864), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),866); };



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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(891), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(896), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(901), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),903); };



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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(926), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(931), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,106);

    newTimerListAdd(motor3,9);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(936), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),938); };



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

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(962), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor2,10);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(967), UNITY_DISPLAY_STYLE_HEX32);



    updateBaseTime(root,100);

    updateCurTime(root,105);

    newTimerListAdd(motor3,5);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(972), UNITY_DISPLAY_STYLE_HEX32);



    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),974); };



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



    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head)), (_U_SINT)(_UP)((motor1)), (((void *)0)), (_U_UINT)(1013), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next->next)), (_U_SINT)(_UP)((motor2)), (((void *)0)), (_U_UINT)(1014), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next->next)), (_U_SINT)(_UP)((motor4)), (((void *)0)), (_U_UINT)(1015), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((_U_SINT)(_UP)((root->head->next)), (_U_SINT)(_UP)((motor3)), (((void *)0)), (_U_UINT)(1016), UNITY_DISPLAY_STYLE_HEX32);

    { test_assert_cycle_link_list(root,arr,sizeof(arr)/sizeof(uint32_t),1017); };



}
