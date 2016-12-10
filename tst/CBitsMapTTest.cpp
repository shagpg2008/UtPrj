#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTest/UtestMacros.h>
#define private public
#define CHECK_INDEX_BOUNDARY
#include <CBitsMapT.hpp>

typedef CBitsMapT<20> CBitsMap;

TEST_GROUP(CBitsMapTGrp)
{
  void setup()
  {
  }
  
  void teardown()
  {
    
  }
};

TEST(CBitsMapTGrp, SetAndReset)
{
   CBitsMap bitmap;
   
   CHECK_EQUAL(4, sizeof(bitmap));
   bitmap.set(0);
   bitmap.set(10);
   bitmap.set(19);
   bitmap.set(21);
   
   CHECK_TRUE(bitmap.isset(0));
   CHECK_TRUE(bitmap.isset(10));
   CHECK_TRUE(bitmap.isset(19));
   CHECK_FALSE(bitmap.isset(21));
   CHECK_FALSE(bitmap.isset(1));
   CHECK_FALSE(bitmap.isset(9));
   CHECK_FALSE(bitmap.isset(11));
   CHECK_FALSE(bitmap.isset(18));
   
   bitmap.reset(10);
   CHECK_FALSE(bitmap.isset(10));
   CHECK_FALSE(bitmap.isset(9));
   CHECK_FALSE(bitmap.isset(11));
}
