#include "unity.h"
#include "Linklist.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "CustomAssertion.h"
#include "projectStruct.h"

void setUp(void)
{
}

void tearDown(void)
{
}

 void test_createLinkedList_the_new_list_was_initialized_by_the_function(void)
{
	Linkedlist *newList = createLinkedList();
	TEST_ASSERT_NOT_NULL(newList);
	TEST_ASSERT_NULL(newList->head);
	TEST_ASSERT_NULL(newList->tail);
  TEST_ASSERT_EQUAL(0,newList->baseTime);
  TEST_ASSERT_EQUAL(0,newList->curTime);
  TEST_ASSERT_EQUAL(0,newList->count);
}


void test_creatlikedelement_the_element_was_initialized_by_the_function(void){
	 ListElement *newNode;
	 newNode = createLinkedElement(9);
	 TEST_ASSERT_EQUAL_UINT16(9,newNode->actionTime);
   TEST_ASSERT_NULL(newNode->next);
   
} 



/*

      ----------------------------------------------------
      ||            ||                                   ^
      V             V                                   ||
    ------         ----        ----        ----        ----
   |      | ----> |   | ----> |   | ----> |   | ----> |   |
   | head |       | 9 |       | 8 |       | 7 |       | 6 |
   |      | <---- |   | <---- |   | <---- |   | <---- |   |
   -------        ----        ----        ----        ----
     ||            ||                                   ^  
     V             V                                   ||
     ----------------------------------------------------
   
*/

void test_cycle_link_list_Elem9_Elem8_Elem7_and_Elem6_add_to_link_list(void){
  
   Linkedlist *list = createLinkedList();
   ListElement *Element9 = createLinkedElement(9);
   ListElement *Element8 = createLinkedElement(8);
   ListElement *Element7 = createLinkedElement(7);
   ListElement *Element6 = createLinkedElement(6);
   addList(list,Element9);
   addList(list,Element8);
   addList(list,Element7);
   addList(list,Element6);
   
   TEST_ASSERT_EQUAL_PTR(Element8,Element9->next);
   TEST_ASSERT_EQUAL_PTR(Element7,Element8->next);
   TEST_ASSERT_EQUAL_PTR(Element6,Element7->next);
   TEST_ASSERT_EQUAL_PTR(Element9,Element6->next);
   TEST_ASSERT_EQUAL_PTR(list->head,Element6->next);
   
   TEST_ASSERT_EQUAL_PTR(Element6,list->head->prev);
   TEST_ASSERT_EQUAL_PTR(Element6,Element9->prev);
   TEST_ASSERT_EQUAL_PTR(Element9,Element8->prev);
   TEST_ASSERT_EQUAL_PTR(Element8,Element7->prev);
   TEST_ASSERT_EQUAL_PTR(Element7,Element6->prev);
   
  TEST_ASSERT_EQUAL_PTR(Element7,Element6->prev);
  TEST_ASSERT_EQUAL_PTR(4,list->count);
}

void test_timerListDelete_delete_a_Node(void){
   printf("elementDelete\n");
   Linkedlist *list = createLinkedList();
   uint16_t arr[] = {9,8,6};
   ListElement *Element9 = createLinkedElement(9);
   ListElement *Element8 = createLinkedElement(8);
   ListElement *Element7 = createLinkedElement(7);
   ListElement *Element6 = createLinkedElement(6);

   addList(list,Element9);
   addList(list,Element8);
   addList(list,Element7);
   addList(list,Element6);
   TEST_ASSERT_EQUAL_PTR(4,list->count);
   linkedListRemove(list,list->head->next->next);
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,list);
   TEST_ASSERT_EQUAL_PTR(3,list->count);
  
}

/*
      head  Delete                   head
       V      V                       V
     ----    ----    ----           ----    ----
    | 1 |-> | 2 |-> | 3 |     =>   | 1 |-> | 3 |
    ---- <- ---- <- ----           ---- <- ----

*/     

void test_elementDetele_Detele_node_that_is_between_two_node(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {1,3};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);
   
   linkedListRemove(list,Element2);
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,list);
   TEST_ASSERT_EQUAL(2,list->count);
}

/*
      Delete
        V 
      head                          head
       V                             V
     ----    ----    ----           ----    ----
    | 1 |-> | 2 |-> | 3 |     =>   | 2 |-> | 3 |
    ---- <- ---- <- ----           ---- <- ----

*/   

void test_elementDetele_Detele_the_node_that_was_pointed_by_head(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {2,3};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);
   
   linkedListRemove(list,Element1);
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,list);
   TEST_ASSERT_EQUAL(2,list->count);
}

/*
      head            Delete         head
       V               V              V
     ----    ----    ----           ----    ----
    | 1 |-> | 2 |-> | 3 |     =>   | 1 |-> | 2 |
    ---- <- ---- <- ----           ---- <- ----

*/  
void test_elementDetele_Detele_the_node_that_is_last_node_in_linked_list(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {1,2};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);   
   linkedListRemove(list,Element3);
   TEST_ASSERT_CYCLE_LINK_LIST_WITH_ARR(arr,list);
   TEST_ASSERT_EQUAL(2,list->count);
}

/*
      head             head
       V                V
     ----               
    | 1 |->      =>    NULL   
    ---- <-          

*/ 

void test_elementDetele_Detele_the_node_that_is_the_only_one_elem_in_linked_list(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
      
   linkedListRemove(list,Element1);
   TEST_ASSERT_NULL(list->head);
   TEST_ASSERT_EQUAL(0,list->count);
}  