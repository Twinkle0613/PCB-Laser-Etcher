#include "projectStruct.h"
#include "CustomAssertion.h"
#include "Linklist.h"
#include "unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



 void test_createLinkedList_the_new_list_was_initialized_by_the_function(void)

{

 Linkedlist *newList = createLinkedList();

 if ((((newList)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(20))));};

 if ((((newList->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(21))));};

 if ((((newList->tail)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(22))));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->baseTime)), (((void *)0)), (_U_UINT)(23), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->curTime)), (((void *)0)), (_U_UINT)(24), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->count)), (((void *)0)), (_U_UINT)(25), UNITY_DISPLAY_STYLE_INT);

}





void test_creatlikedelement_the_element_was_initialized_by_the_function(void){

  ListElement *newNode;

  newNode = createLinkedElement(9);

  UnityAssertEqualNumber((_U_SINT)(_UU16)((9)), (_U_SINT)(_UU16)((newNode->actionTime)), (((void *)0)), (_U_UINT)(32), UNITY_DISPLAY_STYLE_UINT16);

   if ((((newNode->next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(33))));};



}

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



   UnityAssertEqualNumber((_U_SINT)(_UP)((Element8)), (_U_SINT)(_UP)((Element9->next)), (((void *)0)), (_U_UINT)(67), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element8->next)), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((Element7->next)), (((void *)0)), (_U_UINT)(69), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element9)), (_U_SINT)(_UP)((Element6->next)), (((void *)0)), (_U_UINT)(70), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((list->head)), (_U_SINT)(_UP)((Element6->next)), (((void *)0)), (_U_UINT)(71), UNITY_DISPLAY_STYLE_HEX32);



   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((list->head->prev)), (((void *)0)), (_U_UINT)(73), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((Element9->prev)), (((void *)0)), (_U_UINT)(74), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element9)), (_U_SINT)(_UP)((Element8->prev)), (((void *)0)), (_U_UINT)(75), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element8)), (_U_SINT)(_UP)((Element7->prev)), (((void *)0)), (_U_UINT)(76), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element6->prev)), (((void *)0)), (_U_UINT)(77), UNITY_DISPLAY_STYLE_HEX32);



  UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element6->prev)), (((void *)0)), (_U_UINT)(79), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((4)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(80), UNITY_DISPLAY_STYLE_HEX32);

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

   UnityAssertEqualNumber((_U_SINT)(_UP)((4)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_HEX32);

   linkedListRemove(list,list->head->next->next);

   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),98); };

   UnityAssertEqualNumber((_U_SINT)(_UP)((3)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_HEX32);



}

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

   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),123); };

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

}

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

   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),149); };

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

}

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

   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),171); };

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

}

void test_elementDetele_Detele_the_node_that_is_the_only_one_elem_in_linked_list(void){

   ListElement *Element1 = createLinkedElement(1);

   ListElement *Element2 = createLinkedElement(2);

   ListElement *Element3 = createLinkedElement(3);



   Linkedlist *list = createLinkedList();

   addList(list,Element1);



   linkedListRemove(list,Element1);

   if ((((list->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(193))));};

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

}
