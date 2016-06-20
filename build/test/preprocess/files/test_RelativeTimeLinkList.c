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



void xtest_recordTime_Add_data(void){

  timeRecordList *record = recordTime(10,20,10);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->baseTime)), (((void *)0)), (_U_UINT)(19), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((record->currentTime)), (((void *)0)), (_U_UINT)(20), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((record->rate)), (((void *)0)), (_U_UINT)(21), UNITY_DISPLAY_STYLE_INT);

}







void xtest_reative_Time_Link_list_a_time_element_is_added_into_link_list(void){

   printf("No.01\n");

   struct Linkedlist *ptr = createLinkedList();

   int arr[] = {10};

   AddTimeList(recordTime(10,20,10),ptr);

   { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),31); };

}

void xtest_reative_Time_Link_list_two_time_element_is_added_into_link_list(void){

   printf("No.02\n");

   struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);



    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),50); };

}

void test_reative_Time_Link_list_three_time_element_is_added_into_link_list(void){

    printf("No.03\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),69); };

}

void test_reative_Time_Link_list_four_time_element_is_added_into_link_list(void){

    printf("No.04\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    AddTimeList(recordTime(100,109,13),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),92); };

}

void test_reative_Time_Link_list_five_time_element_is_added_into_link_list(void){

    printf("No.04\n");

    struct Linkedlist *ptr = createLinkedList();

    int arr[] = {10,5,5,2,3};

    AddTimeList(recordTime(10,20,10),ptr);

    AddTimeList(recordTime(100,105,10),ptr);

    AddTimeList(recordTime(100,108,12),ptr);

    AddTimeList(recordTime(100,109,13),ptr);

    AddTimeList(recordTime(100,110,25),ptr);

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),116); };

}
