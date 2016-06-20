#include "Linklist.h"
#include "CustomAssertion.h"
#include "unity.h"
void setUp(void)

{

}



void tearDown(void)

{

}





void test_test_assert_link_list_with_arr_the_first_parameter_is_NUll(void){

  uint32_t arr[] = {9,8,7,6,5,1,2,3};

  { test_assert_link_list(arr,((void *)0),sizeof(((void *)0))/sizeof(uint32_t),15); };

}



void test_test_assert_link_list_with_arr_the_second_parameter_is_NUll(void){

  struct Linkedlist *ptr = createLinkedList();

  { test_assert_link_list(((void *)0),ptr,sizeof(ptr)/sizeof(uint32_t),20); };

}



void test_test_assert_link_list_with_arr_a_few_elements_were_added_into_link_list(void){

    struct Linkedlist *ptr = createLinkedList();

    uint32_t arr[] = {9,8,7,6,5,1,2,3};

    addList(ptr,createLinkedElement(9));

    addList(ptr,createLinkedElement(8));

    addList(ptr,createLinkedElement(7));

    addList(ptr,createLinkedElement(6));

    addList(ptr,createLinkedElement(5));

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),31); };

}



void test_test_assert_link_list_with_arr_one_of_the_array_value_is_not_the_same_wtih_the_value_of_linkedElement(void){

    struct Linkedlist *ptr = createLinkedList();

    uint32_t arr[] = {9,8,7,6,5,1,2,3};

    addList(ptr,createLinkedElement(9));

    addList(ptr,createLinkedElement(8));

    addList(ptr,createLinkedElement(7));

    addList(ptr,createLinkedElement(6));

    addList(ptr,createLinkedElement(5));

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),42); };

}



void test_test_assert_link_list_with_arr_the_number_of_array_is_less_than_number_of_linkedlElememt(void){

    struct Linkedlist *ptr = createLinkedList();

    uint32_t arr[] = {9,8,7};

    addList(ptr,createLinkedElement(9));

    addList(ptr,createLinkedElement(8));

    addList(ptr,createLinkedElement(7));

    addList(ptr,createLinkedElement(6));

    addList(ptr,createLinkedElement(5));

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),53); };

}
