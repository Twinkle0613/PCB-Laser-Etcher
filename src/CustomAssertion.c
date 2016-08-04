#include "CustomAssertion.h"
#include "Linklist.h"
#include <stdlib.h>
#include <stdint.h>
#include <unity.h>

void test_assert_link_list(Linkedlist *newList,uint32_t arr[],int arraySize,int lineNo){
   UNITY_TEST_ASSERT_NOT_NULL(newList,lineNo,"The Link-List should not be NULL!");
   UNITY_TEST_ASSERT_NOT_NULL(arr,lineNo,"The Array should not be NULL!");
   ListElement *testNode;
  int i = 0;

  for(testNode = newList->head; testNode !=NULL ; testNode = testNode->next ){

     if( (i+1) > arraySize ){
       CUSTOM_TEST_FAIL(lineNo,"The number of array is %d, No enough array to check the rest of element value in link list.",i+1);
     }else if(testNode->actionTime != arr[i]){
       CUSTOM_TEST_FAIL(lineNo,"Expected %d was %d. The element value is not the same with Array[%d].",arr[i],testNode->actionTime,i); 
     }
     i++;
   }
  
  
}


void test_assert_cycle_link_list(Linkedlist *newList,uint16_t arr[],int arraySize,int lineNo){
   UNITY_TEST_ASSERT_NOT_NULL(newList,lineNo,"The Link-List should not be NULL!");
   UNITY_TEST_ASSERT_NOT_NULL(arr,lineNo,"The Array should not be NULL!");
   ListElement *testNode;
  int i = 0;
   testNode = newList->head;
   do{
     //printf("arr[%d] = %d\n",i,arr[i]);
     if(testNode->actionTime != arr[i] ){
       CUSTOM_TEST_FAIL(lineNo,"Expected %d was %d. The element value is not the same with Array[%d].",arr[i],testNode->actionTime,i); 
     }
     testNode = testNode->next;
     i++;
   }while(testNode != newList->head);
}