//General Library
#include "unity.h"
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//STM32F1XX standard Library
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
//Own Library
#include "Host.h"
#include "Linklist.h"
#include "Registers.h"
#include "peripherals.h"
#include "Timer_setting.h"
#include "projectStruct.h"
#include "CustomAssertion.h"
#include "RelativeTimeLinkList.h"



void setUp(void)
{
  HostTim2= malloc((sizeof(TIM_TypeDef)));
}

void tearDown(void)
{
   free(HostTim2);
   HostTim2 = NULL;
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
   _updateBaseTime(ptr,10);
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
   _updateBaseTime(ptr,10);
   updateCurTime(ptr,20);
    timerListAdd(ptr,10);
   _updateBaseTime(ptr,100);
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
   _updateBaseTime(ptr,10);
   updateCurTime(ptr,20);
   timerListAdd(ptr,10);
   
   _updateBaseTime(ptr,100);
   updateCurTime(ptr,105);
    timerListAdd(ptr,10);
   
   _updateBaseTime(ptr,100);
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
    
    _updateBaseTime(ptr,10);
    updateCurTime(ptr,20);
    timerListAdd(ptr,20);
    
    _updateBaseTime(ptr,100);
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
    
    _updateBaseTime(ptr,10);
    updateCurTime(ptr,20);
    timerListAdd(ptr,10);
    
    _updateBaseTime(ptr,100);
    updateCurTime(ptr,105);
    timerListAdd(ptr,10);
    
    _updateBaseTime(ptr,100);
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
    
    _updateBaseTime(ptr,10);
    updateCurTime(ptr,20);
    timerListAdd(ptr,10);
    
    _updateBaseTime(ptr,100);
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
    
    _updateBaseTime(ptr,10);
    updateCurTime(ptr,20);
    timerListAdd(ptr,10);
    
    _updateBaseTime(ptr,100);
    updateCurTime(ptr,105);
    timerListAdd(ptr,10);
    
    _updateBaseTime(ptr,100);
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
    TEST_ASSERT_EQUAL_PTR(store1,store2);
    
    store1 = ptr->head->next->next->next;
    _updateBaseTime(ptr,100);
    updateCurTime(ptr,109);
    timerListAdd(ptr,6);
    store2 = ptr->head->next->next->next;
    TEST_ASSERT_EQUAL_PTR(store1,store2);
    
    store1 = ptr->head->next->next->next->next;
    _updateBaseTime(ptr,100);
    updateCurTime(ptr,109);
    timerListAdd(ptr,6);
    store2 = ptr->head->next->next->next->next;
    TEST_ASSERT_EQUAL_PTR(store1,store2);
    
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

    TEST_ASSERT_EQUAL_PTR(store1,store2);
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
      
     // _updateBaseTime(ptr,10);
     // updateCurTime(ptr,20);
     // timerListAdd(ptr,0);
     
     // _updateBaseTime(ptr,100);
     // updateCurTime(ptr,108);
     // timerListAdd(ptr,10);
     
     // TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
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
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,ptr);
  
  
}


void test_new_timerListAdd_(void){
  printf("No.21 - initialization root\n");
  root = createLinkedList();
  TEST_ASSERT_NULL(root->head);
  TEST_ASSERT_EQUAL(0,root->curTime);
  TEST_ASSERT_EQUAL(0,root->baseTime);  
}

void test_updateActionTime_initialy_the_actionTime_of_motor_is_0_that_change_to_9_and_20(void){
  printf("No.22 - updateActionTime\n");
  struct ListElement *motor1 = createLinkedElement(0);
  updateActionTime(motor1,9);
  TEST_ASSERT_EQUAL(9,motor1->actionTime);
  updateActionTime(motor1,20);
  TEST_ASSERT_EQUAL(20,motor1->actionTime);
}
/*
                                                                 rate = 14
                                                         |------------------------|       
          0          10      15                 0               10        15      22    
          |----------|-------|                  |---------------|--------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->10-->5-->7-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);
    TEST_ASSERT_EQUAL_PTR(10,motor1->actionTime);
    
    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);
    TEST_ASSERT_EQUAL_PTR(5,motor2->actionTime);
    
    _updateBaseTime(root,100);
    updateCurTime(root,108);
    timerQueue(motor3,14);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor3);
    TEST_ASSERT_EQUAL_PTR(7,motor3->actionTime);
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
}
/*
                                                           rate = 8
                                                         |----------|       
          0          10      15                 0               10        15          
          |----------|-------|                  |---------------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->10-->3-->2-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor3,8);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor3);

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}

/*
                                                       rate = 3
                                                          |---|       
          0          10      15                 0               10        15          
          |----------|-------|                  |---------------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->8-->2-->5-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor3,3);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor3);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor2);
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}

/*
                                                           rate = 10
                                                          |---------------|       
          0          10      15                 0               10        15          
          |----------|-------|                  |---------------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->0-->NULL               Head-->10-->0-->5-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,5);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor3,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor3);

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}
/*
                                                           rate = 7
                                                          |----------|       
          0          10      15                 0          10        15          
          |----------|-------|                  |-----------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->10-->5-->0-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);

    _updateBaseTime(root,100);
    updateCurTime(root,106);
    timerQueue(motor3,9);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor3);

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}

/*
                                                           rate = 7
                                                          |----------|       
          0          10      15                 0          10        15          
          |----------|-------|                  |-----------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->5-->NULL               Head-->10-->0-->5-->NULL

*/
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
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor2,10);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor2);

    _updateBaseTime(root,100);
    updateCurTime(root,105);
    timerQueue(motor3,5);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor3);

    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}


/*
                                                           rate = 7
                                                          |----------|       
          0          10      15                 0          10        15          
          |----------|-------|                  |-----------|--------|
                     <---5--->       =>         <----5--->           
                     
          Head-->10-->0-->5-->NULL               Head-->10-->0-->0-->5-->NULL

*/
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
    
    TEST_ASSERT_EQUAL_PTR(root->head,motor1);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next->next,motor2);
    TEST_ASSERT_EQUAL_PTR(root->head->next->next,motor4);
    TEST_ASSERT_EQUAL_PTR(root->head->next,motor3);
    TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,root);
  
}

/*

    head                                head     
     ||                                  ||
     V                                   V
    10      => TIMx_IRQHandler()  =>    NULL

*/
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
    TEST_ASSERT_NULL(root->head);
    TEST_ASSERT_EQUAL_PTR(elem1,temp);
}

/*

    head                                head     
     ||                                  ||
     V                                   V
    10-->5     => TIMx_IRQHandler()  =>  5

*/
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
    TEST_ASSERT_EQUAL_PTR(elem2,root->head);
    TEST_ASSERT_EQUAL_PTR(elem1,temp);
}

/*

    head                                        head     
     ||                                          ||
     V                                           V
    10-->5-->7     => TIMx_IRQHandler()  =>      5-->7

*/

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
    TEST_ASSERT_EQUAL_PTR(elem2,root->head);
    TEST_ASSERT_EQUAL_PTR(elem1,temp);
}

void test_updateHead_the_link_list_contain_one_timerElement_the_head_of_root_will_point_to_null(void){
    printf("No.33 - updateHead\n");
    root = createLinkedList();
    struct ListElement *elem1 = createLinkedElement(0);
    _updateBaseTime(root,10);
    updateCurTime(root,20);
    timerQueue(elem1,10);
    updateHead(root);
    TEST_ASSERT_NULL(root->head);
    
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
    TEST_ASSERT_EQUAL_PTR(elem2,root->head);
}
