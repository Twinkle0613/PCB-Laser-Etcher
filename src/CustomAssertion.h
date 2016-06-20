#ifndef CustomAssertion_H
#define CustomAssertion_H
#include <stdint.h>
#include <stdio.h>
#include "Linklist.h"

#define CUSTOM_TEST_FAIL(lineNo,msg,...)                        \
        {                                                       \
         char buffer[256];                                      \
         sprintf(buffer,msg, ## __VA_ARGS__);                   \
         UNITY_TEST_FAIL(lineNo,buffer);                        \
        }

#define TEST_ASSERT_LINK_LIST_WITH_ARR(arr,newList){                               \
     test_assert_link_list(newList,arr,sizeof(arr)/sizeof(uint32_t),__LINE__);     \
                                                                    }
        
void test_assert_link_list(struct Linkedlist *newList,uint32_t arr[],int arraySize,int lineNo);
#endif // CustomAssertion_H
