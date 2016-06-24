#include "CustomAssertion.h"
#include "Linklist.h"
#include "unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}



 void test_head_and_Tail_euqal_NULL(void)

{

 struct Linkedlist *ptr = createLinkedList();

 if ((((ptr)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(20))));};

 if ((((ptr->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(21))));};

 if ((((ptr->tail)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(22))));};

}





void test_creatlikedelement(){

  struct ListElement *newNode;

  newNode = createLinkedElement(9);

  UnityAssertEqualNumber((_U_SINT)(_UU32)((9)), (_U_SINT)(_UU32)((newNode->actionTime)), (((void *)0)), (_U_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);

   if ((((newNode->next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(30))));};



}



void test_addlist_one_element_was_added_into_Link_list(void)

{

    struct Linkedlist *ptr = createLinkedList();

    struct ListElement *newNode = createLinkedElement(9);

    addList(ptr,newNode);

    UnityAssertEqualNumber((_U_SINT)(_UU32)((9)), (_U_SINT)(_UU32)((ptr->head->actionTime)), (((void *)0)), (_U_UINT)(39), UNITY_DISPLAY_STYLE_UINT32);

}



void test_addlist_a_few_elements_were_added_into_link_list(void){

    struct Linkedlist *ptr = createLinkedList();

    uint32_t arr[] = {9,8,7,6,5};

    addList(ptr,createLinkedElement(9));

    addList(ptr,createLinkedElement(8));

    addList(ptr,createLinkedElement(7));

    addList(ptr,createLinkedElement(6));

    addList(ptr,createLinkedElement(5));

    { test_assert_link_list(ptr,arr,sizeof(arr)/sizeof(uint32_t),50); };

}

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

   UnityAssertEqualNumber((_U_SINT)(_UP)((ptr->head)), (_U_SINT)(_UP)((Element9->prev)), (((void *)0)), (_U_UINT)(72), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element9)), (_U_SINT)(_UP)((Element8->prev)), (((void *)0)), (_U_UINT)(73), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element8)), (_U_SINT)(_UP)((Element7->prev)), (((void *)0)), (_U_UINT)(74), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element6->prev)), (((void *)0)), (_U_UINT)(75), UNITY_DISPLAY_STYLE_HEX32);



}
