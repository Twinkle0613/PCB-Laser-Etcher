#include "unity.h"
#include "Linklist.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "CustomAssertion.h"


void setUp(void)
{
}

void tearDown(void)
{
}

 void test_head_and_Tail_euqal_NULL(void)
{
	struct Linkedlist *ptr = createLinkedList();
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NULL(ptr->head);
	TEST_ASSERT_NULL(ptr->tail);
}


void test_creatlikedelement(){
	 struct ListElement *newNode;
	 newNode = createLinkedElement(9);
	 TEST_ASSERT_EQUAL_UINT32(9,newNode->actionTime);
   TEST_ASSERT_NULL(newNode->next);
   
} 

void test_addlist_one_element_was_added_into_Link_list(void)
{
   	struct Linkedlist *ptr = createLinkedList();
    struct ListElement *newNode = createLinkedElement(9);
    addList(ptr,newNode);
    TEST_ASSERT_EQUAL_UINT32(9,ptr->head->actionTime);
}

void test_addlist_a_few_elements_were_added_into_link_list(void){
    struct Linkedlist *ptr = createLinkedList();
    uint32_t arr[] = {9,8,7,6,5};
    addList(ptr,createLinkedElement(9));
    addList(ptr,createLinkedElement(8));
    addList(ptr,createLinkedElement(7));
    addList(ptr,createLinkedElement(6));
    addList(ptr,createLinkedElement(5));
    TEST_ASSERT_LINK_LIST_WITH_ARR(arr,ptr);
}

/*
             ----      ----
   head --->| 9 |---> | 8 |
        <-- ---- <--- ----


*/

void test_double_link_list_(void){
  
   struct Linkedlist *ptr = createLinkedList();
   struct ListElement *Element9 = createLinkedElement(9);
   struct ListElement *Element8 = createLinkedElement(8);
   struct ListElement *Element7 = createLinkedElement(7);
   struct ListElement *Element6 = createLinkedElement(6);
   addList(ptr,Element9);
   addList(ptr,Element8);
   addList(ptr,Element7);
   addList(ptr,Element6);
   TEST_ASSERT_EQUAL_PTR(ptr->head,Element9->prev);
   TEST_ASSERT_EQUAL_PTR(Element9,Element8->prev);
   TEST_ASSERT_EQUAL_PTR(Element8,Element7->prev);
   TEST_ASSERT_EQUAL_PTR(Element7,Element6->prev);
  
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

void test_cycle_link_list(void){
  
   struct Linkedlist *ptr = createLinkedList();
   struct ListElement *Element9 = createLinkedElement(9);
   struct ListElement *Element8 = createLinkedElement(8);
   struct ListElement *Element7 = createLinkedElement(7);
   struct ListElement *Element6 = createLinkedElement(6);
   _addList(ptr,Element9);
   _addList(ptr,Element8);
   _addList(ptr,Element7);
   _addList(ptr,Element6);
   
   TEST_ASSERT_EQUAL_PTR(Element8,Element9->next);
   TEST_ASSERT_EQUAL_PTR(Element7,Element8->next);
   TEST_ASSERT_EQUAL_PTR(Element6,Element7->next);
   TEST_ASSERT_EQUAL_PTR(Element9,Element6->next);
   TEST_ASSERT_EQUAL_PTR(ptr->head,Element6->next);
   
   TEST_ASSERT_EQUAL_PTR(Element6,ptr->head->prev);
   TEST_ASSERT_EQUAL_PTR(Element6,Element9->prev);
   TEST_ASSERT_EQUAL_PTR(Element9,Element8->prev);
   TEST_ASSERT_EQUAL_PTR(Element8,Element7->prev);
   TEST_ASSERT_EQUAL_PTR(Element7,Element6->prev);
  
}