/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_reative_Time_Link_list_three_time_element_is_added_into_link_list(void);
extern void test_reative_Time_Link_list_four_time_element_is_added_into_link_list(void);
extern void test_reative_Time_Link_list_five_time_element_is_added_into_link_list(void);


//=======Test Reset Option=====
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


//=======MAIN=====
int main(void)
{
  UnityBegin("test_RelativeTimeLinkList.c");
  RUN_TEST(test_reative_Time_Link_list_three_time_element_is_added_into_link_list, 62);
  RUN_TEST(test_reative_Time_Link_list_four_time_element_is_added_into_link_list, 84);
  RUN_TEST(test_reative_Time_Link_list_five_time_element_is_added_into_link_list, 107);

  return (UnityEnd());
}