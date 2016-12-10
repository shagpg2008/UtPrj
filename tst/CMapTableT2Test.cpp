#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTest/UtestMacros.h>
#define CHECK_INDEX_BOUNDARY
#define private public
#include <CMapTableT.hpp>
#include <CMapTableT2.hpp>

typedef struct Item
{
  unsigned int crnti;
  unsigned short ueIndex;
  unsigned short priority;
}TItem;

typedef CMapTableT<TItem, 50, 600> CItemListOrig;
typedef CMapTableT2<TItem, 50, 600> CItemList;

TEST_GROUP(CMapTableT2Grp)
{
  void setup()
  {
    
  }
  
  void teardown()
  {
    
  }
  
//  CMapTableT<TItem, 50, 600>  allocList;
};

TEST(CMapTableT2Grp, add0)
{
  CHECK_TRUE(sizeof(CItemList) < sizeof(CItemListOrig));
   CItemList list;
   unsigned int index = 0;
   CHECK_TRUE(list.add(index));
   POINTERS_EQUAL(list.get(index), &list.m_items[0]);
   CHECK_EQUAL(1, list.m_allocNum);
}

TEST(CMapTableT2Grp, del0)
{
   CItemList list;
   unsigned int index = 0;
   POINTERS_EQUAL(list.get(index), NULL);
   CHECK_EQUAL(0, list.m_allocNum);
   list.del(index);
   POINTERS_EQUAL(list.get(index), NULL);
   CHECK_EQUAL(0, list.m_allocNum);
}

TEST(CMapTableT2Grp, add1)
{
   CItemList list;
   unsigned int index = 1;
   CHECK_TRUE(list.add(index));
   CHECK_TRUE(list.add(index));
   POINTERS_EQUAL(list.get(index), &list.m_items[0]);
   CHECK_EQUAL(1, list.m_allocNum);
}

TEST(CMapTableT2Grp, add2)
{
   CItemList list;
   unsigned int index = 0;
   CHECK_TRUE(list.add(index));
   CHECK_TRUE(list.add(index+3));
   POINTERS_EQUAL(list.get(index), &list.m_items[0]);
   POINTERS_EQUAL(list.get(index+3), &list.m_items[1]);
   CHECK_EQUAL(2, list.m_allocNum);
}
TEST(CMapTableT2Grp, add1000)
{
   CItemList list;
   unsigned int index = 1000;
   CHECK_FALSE(list.add(index));
   CHECK_EQUAL(0, list.m_allocNum);
}

TEST(CMapTableT2Grp, add1del1)
{
   CItemList list;
   unsigned int index = 0;
   CHECK_TRUE(list.add(index));
   CHECK_EQUAL(1, list.m_allocNum);
   list.del(index);
   POINTERS_EQUAL(list.get(index), NULL);
   POINTERS_EQUAL(list.m_maps[index], (unsigned char)-1);
   CHECK_EQUAL(0, list.m_allocNum);
}

TEST(CMapTableT2Grp, add50del50)
{
   CItemList list;
   unsigned int index = 0;
   TItem item = {0};
   
   for(index = 0; index < 50; index++)
   {
     CHECK_TRUE(list.add(index));
     CHECK_EQUAL(index+1, list.m_allocNum);
     item.crnti = index + 20;
     list.set(index, item);
     POINTERS_EQUAL(list.get(index), &list.m_items[index]);
     CHECK_EQUAL(list.get(index)->crnti, item.crnti); 
   }
   
   CHECK_FALSE(list.add(index));
   
   for(index = 0; index < 50; index++)
   {
     list.del(index);
     POINTERS_EQUAL(list.m_maps[index], (unsigned char)-1);
     POINTERS_EQUAL(list.get(index), NULL);
     CHECK_EQUAL(49-index, list.m_allocNum); 
     if(index < 25)
     {
       unsigned short last = 49-index;
       POINTERS_EQUAL(list.get(last), &list.m_items[index]);
       CHECK_EQUAL(list.get(last)->crnti, list.m_items[index].crnti); 
       CHECK_EQUAL(list.m_index[index], last);
     }
     else if(index < 49)
     {
       unsigned short last = list.m_allocNum-1;
       unsigned short next = index+1;
       POINTERS_EQUAL(list.get(next), &list.m_items[last]);
       CHECK_EQUAL(list.get(next)->crnti, list.m_items[last].crnti); 
       CHECK_EQUAL(list.m_index[last], next);
     }
   }
  
   CHECK_EQUAL(0, list.m_allocNum);
}

TEST(CMapTableT2Grp, add50while_del)
{
   CItemList list;
   unsigned int index = 0;
   
   for(index = 0; index < 50; index++)
   {
     CHECK_TRUE(list.add(index));
     CHECK_EQUAL(1, list.m_allocNum);
     POINTERS_EQUAL(list.get(index), &list.m_items[0]);
     list.del(index);
     POINTERS_EQUAL(list.m_maps[index],  (unsigned char)-1);
     POINTERS_EQUAL(list.get(index), NULL);
   }
   
   list.del(index);
   
   for(index = 0; index < 50; index++)
   {
     POINTERS_EQUAL(list.m_maps[index],  (unsigned char)-1);
     POINTERS_EQUAL(list.get(index), NULL);
     CHECK_EQUAL(0, list.m_allocNum); 
     list.del(index);
     POINTERS_EQUAL(list.m_maps[index],  (unsigned char)-1);
     POINTERS_EQUAL(list.get(index), NULL);
     CHECK_EQUAL(0, list.m_allocNum); 
   }
  
   CHECK_EQUAL(0, list.m_allocNum);
}

TEST(CMapTableT2Grp, Iterator)
{
   CItemList list;
   unsigned int index = 0;
   TItem item = {0};
   
   for(index = 0; index < 50; index++)
   {
     CHECK_TRUE(list.add(index));
     CHECK_EQUAL(index+1, list.m_allocNum);
     item.crnti = index + 20;
     list.set(index, item);
     POINTERS_EQUAL(list.get(index), &list.m_items[index]);
   }
   
   for(index = list.begin(); !list.empty(); index = list.next())
   {
     CHECK_EQUAL(list.get(index)->crnti, index+20); 
     CHECK_EQUAL(list.m_iterator, index);
   }
}

TEST(CMapTableT2Grp, miscItem)
{
   CItemList list;
   unsigned int index = 0;
   CHECK_TRUE(list.add(index));
   CHECK_EQUAL(1, list.m_allocNum);
   TItem *pItem = list.get(index);
   POINTERS_EQUAL(pItem, &list.m_items[list.m_maps[index]]);
   TItem item = {3, 2, 1};
   list.set(index, item);
   
   TItem item2 = {1, 3, 2};
   list.set(1000, item2);
   CHECK_EQUAL(pItem->crnti, 3);
   CHECK_EQUAL(pItem->ueIndex, 2);
   CHECK_EQUAL(pItem->priority, 1);
   list.clear();
   POINTERS_EQUAL(list.get(index), NULL);
   POINTERS_EQUAL(list.m_maps[index],  (unsigned char)-1);
   CHECK_EQUAL(0, list.m_allocNum);
}


