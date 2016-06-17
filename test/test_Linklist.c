#include "unity.h"
#include "Linklist.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
void setUp(void)
{
}

void tearDown(void)
{
}

 void test_Head_and_Tail_euqal_NULL(void)
{
	struct Linkedlist *ptr = createLinkedList();
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NULL(ptr->Head);
	TEST_ASSERT_NULL(ptr->tail);
}


void test_creatlikedelement(){
	 struct ListElement *newNode;
	 newNode = createLinkedElement(9);
	 TEST_ASSERT_EQUAL(9,newNode->value);
} 

void test_addlist_add_in_4_value(void)
{
     TEST_ASSERT_EQUAL(3, addList(createLinkedElement(3), createLinkedList()));
     TEST_ASSERT_EQUAL(9, addList(createLinkedElement(9), createLinkedList()));
     TEST_ASSERT_EQUAL(27, addList(createLinkedElement(27), createLinkedList()));
     TEST_ASSERT_EQUAL(81, addList(createLinkedElement(81), createLinkedList()));
}
 
void test_addlist_add_in_pisitive_8_value(void)
{
     TEST_ASSERT_EQUAL(1, addList(createLinkedElement(1), createLinkedList()));
     TEST_ASSERT_EQUAL(2, addList(createLinkedElement(2), createLinkedList()));
     TEST_ASSERT_EQUAL(3, addList(createLinkedElement(3), createLinkedList()));
     TEST_ASSERT_EQUAL(4, addList(createLinkedElement(4), createLinkedList()));
	   TEST_ASSERT_EQUAL(5, addList(createLinkedElement(5), createLinkedList()));
     TEST_ASSERT_EQUAL(6, addList(createLinkedElement(6), createLinkedList()));
     TEST_ASSERT_EQUAL(7, addList(createLinkedElement(7), createLinkedList()));
     TEST_ASSERT_EQUAL(8, addList(createLinkedElement(8), createLinkedList()));

}
 
void test_addlist_add_in_negative_8_value(void)
{
     TEST_ASSERT_EQUAL(-1, addList(createLinkedElement(-1), createLinkedList()));
     TEST_ASSERT_EQUAL(-2, addList(createLinkedElement(-2), createLinkedList()));
     TEST_ASSERT_EQUAL(-3, addList(createLinkedElement(-3), createLinkedList()));
     TEST_ASSERT_EQUAL(-4, addList(createLinkedElement(-4), createLinkedList()));
	   TEST_ASSERT_EQUAL(-5, addList(createLinkedElement(-5), createLinkedList()));
     TEST_ASSERT_EQUAL(-6, addList(createLinkedElement(-6), createLinkedList()));
     TEST_ASSERT_EQUAL(-7, addList(createLinkedElement(-7), createLinkedList()));
     TEST_ASSERT_EQUAL(-8, addList(createLinkedElement(-8), createLinkedList()));

}