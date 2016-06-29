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
      ||            ||            ||                             Interval1 = CurrentTime - BaseTime;
      V             V             V                              Interval2 = (currentActTime + actTime1) - Interval1;
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

void test_timerListAdd_a_time_element_is_added_into_link_list(void){
   printf("No.01 - timerListAdd\n");
   struct Linkedlist *ptr = createLinkedList();
   int arr[] = {10};
   updateBaseTime(ptr,10);
   updateCurTime(ptr,20);
   timerListAdd(ptr,10);
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                  rate = 10
                                               |------------|       
          0          10                  0          10      15      
          |----------|                  |----------|-------|     
          <---10---->          =>       <---10----><---5--->
                     
          Head-->10-->NULL               Head-->10-->5-->NULL

*/

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
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                            rate = 12
                                                     |------------------|       
          0          10      15              0          10      15      20 
          |----------|-------|               |----------|-------|-------|      
                     <---5--->        =>                <---5--><---5--->
                     
          Head-->10-->5-->NULL               Head-->10-->5-->5->NULL

*/

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
   
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                                rate = 13
                                                         |--------------------|       
          0          10      15      20        0          10      15      20  22
          |----------|-------|-------|         |----------|-------|-------|---|      
                     <---5---><---5-->  =>                <---5---><--5--><-2->     
                     
          Head-->10-->5-->5-->NULL               Head-->10-->5-->5-->2->NULL
                           
*/

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
/*
                                                                          rate = 25
                                                                  |------------------------|       
          0          10      15      20  22           0          10      15      20  22    25
          |----------|-------|-------|---|            |----------|-------|-------|---|-----|      
                     <---5---><--5--><-2->      =>               <---5---><--5--><-2-><-3-->     
                     
          Head-->10-->5-->5-->NULL                      Head-->10-->5-->5-->2->NULL
                           
*/

 void test_timerListAdd_five_time_element_is_added_into_link_list(void){
     printf("No.05 - timerListAdd\n");
    // struct Linkedlist *ptr = createLinkedList();
    // int arr[] = {10,5,5,2,3};
   // updateBaseTime(ptr,10);
   // updateCurTime(ptr,20);
   // timerListAdd(ptr,10);
   
   // updateBaseTime(ptr,100);
   // updateCurTime(ptr,105);
    // timerListAdd(ptr,10);
   
   // updateBaseTime(ptr,100);
   // updateCurTime(ptr,108);
   // timerListAdd(ptr,12);
   
   // updateBaseTime(ptr,100);
   // updateCurTime(ptr,109);
   // timerListAdd(ptr,13);
   
   // updateBaseTime(ptr,100);
   // updateCurTime(ptr,109);
   // timerListAdd(ptr,13);
   
   // updateBaseTime(ptr,100);
   // updateCurTime(ptr,110);
   // timerListAdd(ptr,25);
   
    // TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
 }


/*
  Condition: Rate < Intervel2
     BaseTime    currentTime   currentActTime
      ||            ||            ||                             Interval1 = CurrentTime - BaseTime;
      V             V             V                              Interval2 = (currentActTime + actTime1) - Intervel1;
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
    printf("No.06 - timerListAdd\n");
    struct Linkedlist *ptr = createLinkedList();
    int arr[] = {15,5};
    
    updateBaseTime(ptr,10);
    updateCurTime(ptr,20);
    timerListAdd(ptr,20);
    
    updateBaseTime(ptr,100);
    updateCurTime(ptr,105);
    timerListAdd(ptr,10);
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
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

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
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


/*
                                          rate = 10
                                       |-----------|       
          0          10                0          10                
          |----------|                 |-----------|
                                 =>    <----5--->           
                     
          Head-->10-->NULL               Head-->10-->0-->NULL

*/

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
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}



/*
                                                           rate = 7
                                                          |----------|       
          0          10      15                 0          10        15          
          |----------|-------|                  |-----------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->10-->5-->0-->NULL

*/
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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                                  rate = 14
                                                             |-------------------|       
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |-----------|--------|---------|
                     <---5--->            =>      <----5--->           
                     
          Head-->10-->5-->8-->NULL               Head-->10-->5-->8-->0-->NULL
*/
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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                              rate = 6
                                                          |------------|       
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |-----------|--------|---------|
                     <---5--->            =>      <----5--->           
                     
          Head-->10-->5-->8-->NULL               Head-->10-->5-->0-->8-->NULL
*/

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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                              rate = 6
                                                           |------------|       
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |------------|--------|---------|
                     <---5--->            =>      <---5--->           
                     
          Head-->10-->5-->0-->8-->NULL               Head-->10-->5-->0-->0-->8-->NULL
*/
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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}
/*
                                                              rate = 6
                                                           |------------|       
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |------------|--------|---------|
                     <---5--->            =>      <---5--->           
                     
          Head-->10-->5-->0-->0-->8-->NULL               Head-->10-->5-->0-->0-->0-->8-->NULL
*/
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
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                              rate = 6
                                                           |------------|       
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |------------|--------|---------|
                     <---5--->            =>      <---5--->           
                     
          Head-->10-->5-->0-->0-->0-->7-->NULL               Head-->10-->5-->0-->0-->0-->0-->7-->NULL
*/
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
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                              rate = 14
                                                          |-----------------------|       
          0          10      15      22           0           10        15        22  
          |----------|-------|-------|            |------------|--------|---------|
                     <---5--->            =>      <---5--->           
                     
          Head-->10-->5-->7-->0-->NULL               Head-->10-->5-->7-->0-->0-->NULL
*/

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
    
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                              rate = 13
                                                           |----------------|      
          0          10      15      22           0          10        15        22  
          |----------|-------|-------|            |------------|--------|---------|
                     <---5--->            =>      <---5--->           
                     
          Head-->10-->5-->0-->8-->NULL               Head-->10-->5-->0-->3-->4-->NULL
*/

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
   
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
                                                        
                                                          
          0                       0          10        
          |                       |-----------|
          
                         =>       
                     
     Head-->0-->NULL               Head-->0-->10-->NULL

*/

void test_relative_Time_Link_list_initial_the_first_Node_contain_0_and_add_a_new_node(void){
      printf("No.19 - timerListAdd\n");
      struct Linkedlist *ptr = createLinkedList();
      int arr[] = {0,10};
      
     // updateBaseTime(ptr,10);
     // updateCurTime(ptr,20);
     // timerListAdd(ptr,0);
     
     // updateBaseTime(ptr,100);
     // updateCurTime(ptr,108);
     // timerListAdd(ptr,10);
     
     // TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
}


