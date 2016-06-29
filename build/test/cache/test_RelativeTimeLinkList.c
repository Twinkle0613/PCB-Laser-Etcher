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



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    updateBaseTime(ptr,100);

    updateCurTime(ptr,109);

    timerListAdd(ptr,6);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),592); };

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



    updateBaseTime(ptr,100);

    updateCurTime(ptr,108);

    timerListAdd(ptr,14);



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),630); };

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



    { test_assert_cycle_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),668); };

}

void test_relative_Time_Link_list_initial_the_first_Node_contain_0_and_add_a_new_node(void){

      printf("No.19 - timerListAdd\n");

      struct Linkedlist *ptr = createLinkedList();

      int arr[] = {0,10};

}
