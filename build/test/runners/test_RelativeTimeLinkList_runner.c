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
extern void test_recordTime_Add_data(void);
extern void test_relative_Time_Link_list_a_time_element_is_added_into_link_list(void);
extern void test_relative_Time_Link_list_two_time_element_is_added_into_link_list(void);
extern void test_relative_Time_Link_list_three_time_element_is_added_into_link_list(void);
extern void test_relative_Time_Link_list_four_time_element_is_added_into_link_list(void);
extern void test_relative_Time_Link_list_five_time_element_is_added_into_link_list(void);
extern void test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2(void);
extern void test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void);
extern void test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void);
extern void test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2(void);


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
  RUN_TEST(test_recordTime_Add_data, 23);
  RUN_TEST(test_relative_Time_Link_list_a_time_element_is_added_into_link_list, 49);
  RUN_TEST(test_relative_Time_Link_list_two_time_element_is_added_into_link_list, 66);
  RUN_TEST(test_relative_Time_Link_list_three_time_element_is_added_into_link_list, 84);
  RUN_TEST(test_relative_Time_Link_list_four_time_element_is_added_into_link_list, 106);
  RUN_TEST(test_relative_Time_Link_list_five_time_element_is_added_into_link_list, 129);
  RUN_TEST(test_relative_Time_Link_list_added_a_time_Element_that_rate_smaller_than_Intervel2, 170);
  RUN_TEST(test_relative_Time_Link_list_added_two_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2, 190);
  RUN_TEST(test_relative_Time_Link_list_three_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2, 212);
  RUN_TEST(test_relative_Time_Link_list_four_time_Element_and_added_a_timeElement_that_rate_smaller_than_Intervel2, 234);

  return (UnityEnd());
}
