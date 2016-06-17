#include "Linklist.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



 void test_Head_and_Tail_euqal_NULL(void)

{

 struct Linkedlist *ptr = createLinkedList();

 if ((((ptr)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(17))));};

 if ((((ptr->Head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(18))));};

 if ((((ptr->tail)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(19))));};

}





void test_creatlikedelement(){

  struct ListElement *newNode;

  newNode = createLinkedElement(9);

  UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((newNode->value)), (((void *)0)), (_U_UINT)(26), UNITY_DISPLAY_STYLE_INT);

}



void test_addlist_add_in_4_value(void)

{

     UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((addList(createLinkedElement(3), createLinkedList()))), (((void *)0)), (_U_UINT)(31), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((9)), (_U_SINT)((addList(createLinkedElement(9), createLinkedList()))), (((void *)0)), (_U_UINT)(32), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((27)), (_U_SINT)((addList(createLinkedElement(27), createLinkedList()))), (((void *)0)), (_U_UINT)(33), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((81)), (_U_SINT)((addList(createLinkedElement(81), createLinkedList()))), (((void *)0)), (_U_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}



void test_addlist_add_in_pisitive_8_value(void)

{

     UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((addList(createLinkedElement(1), createLinkedList()))), (((void *)0)), (_U_UINT)(39), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((addList(createLinkedElement(2), createLinkedList()))), (((void *)0)), (_U_UINT)(40), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((addList(createLinkedElement(3), createLinkedList()))), (((void *)0)), (_U_UINT)(41), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((addList(createLinkedElement(4), createLinkedList()))), (((void *)0)), (_U_UINT)(42), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((addList(createLinkedElement(5), createLinkedList()))), (((void *)0)), (_U_UINT)(43), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((addList(createLinkedElement(6), createLinkedList()))), (((void *)0)), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((addList(createLinkedElement(7), createLinkedList()))), (((void *)0)), (_U_UINT)(45), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((8)), (_U_SINT)((addList(createLinkedElement(8), createLinkedList()))), (((void *)0)), (_U_UINT)(46), UNITY_DISPLAY_STYLE_INT);



}



void test_addlist_add_in_negative_8_value(void)

{

     UnityAssertEqualNumber((_U_SINT)((-1)), (_U_SINT)((addList(createLinkedElement(-1), createLinkedList()))), (((void *)0)), (_U_UINT)(52), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-2)), (_U_SINT)((addList(createLinkedElement(-2), createLinkedList()))), (((void *)0)), (_U_UINT)(53), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-3)), (_U_SINT)((addList(createLinkedElement(-3), createLinkedList()))), (((void *)0)), (_U_UINT)(54), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-4)), (_U_SINT)((addList(createLinkedElement(-4), createLinkedList()))), (((void *)0)), (_U_UINT)(55), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((-5)), (_U_SINT)((addList(createLinkedElement(-5), createLinkedList()))), (((void *)0)), (_U_UINT)(56), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-6)), (_U_SINT)((addList(createLinkedElement(-6), createLinkedList()))), (((void *)0)), (_U_UINT)(57), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-7)), (_U_SINT)((addList(createLinkedElement(-7), createLinkedList()))), (((void *)0)), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((_U_SINT)((-8)), (_U_SINT)((addList(createLinkedElement(-8), createLinkedList()))), (((void *)0)), (_U_UINT)(59), UNITY_DISPLAY_STYLE_INT);



}
