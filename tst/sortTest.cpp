#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTest/UtestMacros.h>
#include <stdio.h>
#define private public
#include <sort.hpp>

TEST_GROUP(qsortGrp)
{
  void setup()
  {
    
  }
  
  void teardown()
  {
    
  }
  
  void check_array(int sr1[], int sr2[], int len)
  {
    for(int index = 0; index < len; index++)
    {
      //printf("%d:sr1=%d,sr2=%d\n", index, sr1[index], sr2[index]);
      CHECK_EQUAL(sr1[index], sr2[index]);
    }
  }
};

TEST(qsortGrp, tenItems)
{
   int data[10] = {4,3,2,4,65, 7,8,9,43,32};
   int orde[10] = {2,3,4,4,7,  8,9,32,43,65};

   quick_sort(data, 0, 9);
   check_array(orde, data, 10);
}

TEST(qsortGrp, twentyItems)
{
   int data[20] = {4,3,2,4,65, 58,60,59,57,49, 52,53,51,52,59, 7,8,9,43,32 };
   int orde[20] = {2,3,4,4,7,  8,9,32,43,49,  51,52,52,53,57,  58,59,59,60,65};

   quick_sort(data, 0, 19);
   check_array(orde, data, 20);
}
