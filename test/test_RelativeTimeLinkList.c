#include "unity.h"
#include "RelativeTimeLinkList.h"
#include "Linklist.h"
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "CustomAssertion.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void xtest_recordTime_Add_data(void){
  timeRecordList *record = recordTime(10,20,10);
  TEST_ASSERT_EQUAL(10,record->baseTime);
  TEST_ASSERT_EQUAL(20,record->currentTime);
  TEST_ASSERT_EQUAL(10,record->rate);
}
/*
          Head-->NULL               Head-->10-->NULL
*/
void xtest_reative_Time_Link_list_a_time_element_is_added_into_link_list(void){
   printf("No.01\n");
   struct Linkedlist *ptr = createLinkedList();
   int arr[] = {10};
   AddTimeList(recordTime(10,20,10),ptr);
   TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                  rate = 10
                                               |------------|       
          0          10                  0          10      15      
          |----------|                  |----------|-------|     
          <---10---->          =>       <---10----><---5--->
                     
          Head-->10-->NULL               Head-->10-->5-->NULL

*/
void xtest_reative_Time_Link_list_two_time_element_is_added_into_link_list(void){
   printf("No.02\n");   
   struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
   // printf("prt->head->next->actionTime = %d",ptr->head->actionTime);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                            rate = 12
                                                     |-------------------|       
          0          10      15              0          10      15      20 
          |----------|-------|               |----------|-------|-------|      
                     <---5--->        =>                <---5--><---5--->
                     
          Head-->10-->5-->NULL               Head-->10-->5-->5->NULL

*/
void test_reative_Time_Link_list_three_time_element_is_added_into_link_list(void){
    printf("No.03\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5,5};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    AddTimeList(recordTime(100,108,12),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                                rate = 13
                                                         |---------------------|       
          0          10      15      20        0          10      15      20  22
          |----------|-------|-------|         |----------|-------|-------|---|      
                     <---5---><---5-->  =>                <---5---><--5--><-2->     
                     
          Head-->10-->5-->5-->NULL               Head-->10-->5-->5-->2->NULL
                           
*/


void test_reative_Time_Link_list_four_time_element_is_added_into_link_list(void){
    printf("No.04\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5,5,2};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    AddTimeList(recordTime(100,108,12),ptr);
    AddTimeList(recordTime(100,109,13),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                                          rate = 25
                                                                  |------------------------|       
          0          10      15      20  22           0          10      15      20  22    25
          |----------|-------|-------|---|            |----------|-------|-------|---|-----|      
                     <---5---><--5--><-2->      =>               <---5---><--5--><-2-><-3-->     
                     
          Head-->10-->5-->5-->NULL               Head-->10-->5-->5-->2->NULL
                           
*/


void test_reative_Time_Link_list_five_time_element_is_added_into_link_list(void){
    printf("No.04\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5,5,2,3};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    AddTimeList(recordTime(100,108,12),ptr);
    AddTimeList(recordTime(100,109,13),ptr);
    AddTimeList(recordTime(100,110,25),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}


