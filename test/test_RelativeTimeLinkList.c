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

/*

    recordTime(curTime,prevTime,rate);


*/
void test_recordTime_Add_data(void){
  printf("No.00\n");
  timeRecordList *record = recordTime(10,20,10);
  TEST_ASSERT_EQUAL(10,record->baseTime);
  TEST_ASSERT_EQUAL(20,record->currentTime);
  TEST_ASSERT_EQUAL(10,record->rate);
}

/*
  Condition: Rate > Intervel2
     BaseTime    currentTime   currentActTime
      ||            ||            ||                             Intervel1 = CurrentTime - BaseTime;
      V             V             V                              Intervel2 = (currentActTime + actTime1) - Intervel1;
      |-------------|-------------|                              NewActTime = Rate - Intervel2;
      <--Intervel1->              |-------------|        
                                  <--actTime1-->
                    |---------------------------|<-NewActTime->
                    <-------Intervel2----------->                  
                    |-----------------------------------------|              
                    <------------------rate------------------->
*/


/*
          Head-->NULL               Head-->10-->NULL
*/
void test_relative_Time_Link_list_a_time_element_is_added_into_link_list(void){
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
void test_relative_Time_Link_list_two_time_element_is_added_into_link_list(void){
   printf("No.02\n");   
   struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                            rate = 12
                                                     |------------------|       
          0          10      15              0          10      15      20 
          |----------|-------|               |----------|-------|-------|      
                     <---5--->        =>                <---5--><---5--->
                     
          Head-->10-->5-->NULL               Head-->10-->5-->5->NULL

*/
void test_relative_Time_Link_list_three_time_element_is_added_into_link_list(void){
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
                                                         |--------------------|       
          0          10      15      20        0          10      15      20  22
          |----------|-------|-------|         |----------|-------|-------|---|      
                     <---5---><---5-->  =>                <---5---><--5--><-2->     
                     
          Head-->10-->5-->5-->NULL               Head-->10-->5-->5-->2->NULL
                           
*/


void test_relative_Time_Link_list_four_time_element_is_added_into_link_list(void){
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
                     
          Head-->10-->5-->5-->NULL                      Head-->10-->5-->5-->2->NULL
                           
*/


void test_relative_Time_Link_list_five_time_element_is_added_into_link_list(void){
    printf("No.05\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5,5,2,3};
    AddTimeList(recordTime(10,20,10),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    AddTimeList(recordTime(100,108,12),ptr);
    AddTimeList(recordTime(100,109,13),ptr);
    AddTimeList(recordTime(100,110,25),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
  Condition: Rate < Intervel2
     BaseTime    currentTime   currentActTime
      ||            ||            ||                             Intervel1 = CurrentTime - BaseTime;
      V             V             V                              Intervel2 = (currentActTime + actTime1) - Intervel1;
      |-------------|-------------|                             
      <--Intervel1->              |-------------|               
                                  <--actTime1-->
                    |---------------------------|
                    <-------Intervel2----------->                  
                    |-------------|             
                    <----rate---->
*/



/*
                                                     rate = 10
                                                       ||
                                                       V
                                                    |------|<--5-->       
          0                20                 0                   20      
          |----------------|                  |--------------------|     
          <-------20------>          =>       <--5--><--10--><--5-->
                     
          Head-->20-->NULL                    Head-->15-->5-->NULL

*/

void test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2(void){
    printf("No.06\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {15,5};
    AddTimeList(recordTime(10,20,20),ptr);
    AddTimeList(recordTime(100,105,10),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}


/*
                                                    rate = 4
                                                     |------|       
          0          10      15              0          10      15      
          |----------|-------|               |----------|-------|
                     <---5--->        =>     <---8--><--4--><-3->           
                     
          Head-->10-->5-->NULL               Head-->10-->2-->3->NULL

*/
void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){
    printf("No.07\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,2,3};
   addList(ptr,createLinkedElement(10));
   addList(ptr,createLinkedElement(5));

   AddTimeList(recordTime(100,108,4),ptr);
    
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                              rate = 13
                                                           |----------------|       
          0          10      15     22              0          10      15  18       22
          |----------|-------|------|               |-----------|-------|---|-------|
                                           =>       <--5-->           
                     
          Head-->10-->5-->7-->NULL               Head-->10-->5-->3-->4-->NULL

*/

void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){
    printf("No.08\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,5,3,4};
   addList(ptr,createLinkedElement(10));
   addList(ptr,createLinkedElement(5));
   addList(ptr,createLinkedElement(7));
   AddTimeList(recordTime(100,105,13),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                           rate = 7
                                                          |---------|       
          0          10      15     22              0          10  12     15          22
          |----------|-------|------|               |-----------|--|-----|-----------|
                     <---5--->            =>        <--5-->           
                     
          Head-->10-->5-->7-->NULL               Head-->10-->2-->3-->7-->NULL

*/

void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void){
    printf("No.09\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {10,2,3,7};
   addList(ptr,createLinkedElement(10));
   addList(ptr,createLinkedElement(5));
   addList(ptr,createLinkedElement(7));
   AddTimeList(recordTime(100,105,7),ptr);
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}


/*
  Condition: Rate == Intervel2
     BaseTime    currentTime   currentActTime
      ||            ||            ||                             Intervel1 = CurrentTime - BaseTime;
      V             V             V                              Intervel2 = (currentActTime + actTime1) - Intervel1;
      |-------------|-------------|                             
      <--Intervel1->              |-------------|               
                                  <--actTime1-->
                    |---------------------------|
                    <-------Intervel2----------->                  
                    |---------------------------|             
                    <-----------rate------------>
*/
