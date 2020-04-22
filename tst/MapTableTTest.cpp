#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTest/UtestMacros.h>
#define CHECK_INDEX_BOUNDARY
#define private public
#include <MapTableT.hpp>

typedef struct Item
{
  unsigned int crnti;
  unsigned short ueIndex;
  unsigned short priority;
}TItem;

typedef MapTableT<Item, 50, 600, 100> CItemMap;

TEST_GROUP(MapTableTGrp)
{
  void setup()
  {
    
  }
  
  void teardown()
  {
    
  }
  
//  CMapTableT<TItem, 50, 600>  allocList;
};

TEST(MapTableTGrp, addremove_in_order)
{
  CItemMap itemList;
  Item item;
  
  CHECK_TRUE(sizeof(MapTableT<Item, 50, 600>) > sizeof(itemList));

  for(int index = 100; index < 600; index += 10)
  {
  	item.crnti = index + 20;

    itemList.add(index, item);
	CHECK_EQUAL(item.crnti, itemList[index].crnti);
  }

  for(unsigned short index = itemList.begin(); !itemList.empty(); index = itemList.next())
  {
    CHECK_EQUAL((unsigned short)(index+20), itemList[index].crnti);
    CHECK_EQUAL(index, itemList.m_index[itemList.m_maps[index-100]]+100);
  }

  CHECK_EQUAL(50, itemList.num());


  for(unsigned short index = 100; index < 600; index += 20)
  {
    itemList.del(index);
    CHECK_EQUAL((unsigned short)(index+10+20), itemList[index+10].crnti);
  }

  CHECK_EQUAL(25, itemList.num());

  for(unsigned short index = 590; index > 100; index -= 20)
  {
    CHECK_EQUAL((unsigned short)(index+20), itemList[index].crnti);
    itemList.del(index);
  }

  CHECK_EQUAL(0, itemList.num());
}


TEST(MapTableTGrp, addremove_no_order)
{
  CItemMap itemList;
  Item item;
  
  for(int index = 100; index < 600; index += 10)
  {
  	item.crnti = index + 20;

    itemList.add(index, item);
	CHECK_EQUAL(item.crnti, itemList[index].crnti);

	if(index > 200 && (index / 10) % 2) 
	{
	  itemList.del(index - 100);
	}
  }
  CHECK_EQUAL(30, itemList.num());
  
  CHECK_EQUAL((unsigned short)(100+20), itemList[100].crnti);
  CHECK_EQUAL((unsigned short)(120+20), itemList[120].crnti);
  POINTERS_EQUAL(NULL, itemList.get(210));
  CHECK_EQUAL((unsigned short)(480+20), itemList[480].crnti);
  POINTERS_EQUAL(NULL, itemList.get(490));
  CHECK_EQUAL((unsigned short)(500+20), itemList[500].crnti);
  CHECK_EQUAL((unsigned short)(510+20), itemList[510].crnti);
  CHECK_EQUAL((unsigned short)(520+20), itemList[520].crnti);
  CHECK_EQUAL((unsigned short)(590+20), itemList[590].crnti);
}

