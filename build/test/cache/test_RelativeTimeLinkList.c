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

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->baseTime)), (((void *)0)), (_U_UINT)(26), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((record->currentTime)), (((void *)0)), (_U_UINT)(27), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->rate)), (((void *)0)), (_U_UINT)(28), UNITY_DISPLAY_STYLE_INT);

}

void test_relative_Time_Link_list_a_time_element_is_added_into_link_list(void){

   printf("No.01\n");

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10};

   AddTimeList(recordTime(10,20,10),ptr);

   { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),54); };

}

void test_relative_Time_Link_list_two_time_element_is_added_into_link_list(void){

   printf("No.02\n");

   struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),72); };

}

void test_relative_Time_Link_list_three_time_element_is_added_into_link_list(void){

    printf("No.03\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),91); };

}

void test_relative_Time_Link_list_four_time_element_is_added_into_link_list(void){

    printf("No.04\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    AddTimeList(recordTime(100,109,13),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),114); };

}

void test_relative_Time_Link_list_five_time_element_is_added_into_link_list(void){

    printf("No.05\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2,3};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    AddTimeList(recordTime(100,109,13),ptr);

    AddTimeList(recordTime(100,110,25),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),138); };

}

void test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2(void){

    printf("No.06\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {15,5};

    AddTimeList(recordTime(10,20,20),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),176); };

}

void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.07\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3};

   addList(ptr,createLinkedElement(10));

   addList(ptr,createLinkedElement(5));



   AddTimeList(recordTime(100,108,4),ptr);



    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),199); };

}

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.08\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,3,4};

   addList(ptr,createLinkedElement(10));

   addList(ptr,createLinkedElement(5));

   addList(ptr,createLinkedElement(7));

   AddTimeList(recordTime(100,105,13),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),220); };

}

void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){

    printf("No.09\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,2,3,7};

   addList(ptr,createLinkedElement(10));

   addList(ptr,createLinkedElement(5));

   addList(ptr,createLinkedElement(7));

   AddTimeList(recordTime(100,105,7),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),242); };

}
