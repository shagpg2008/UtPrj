#ifndef __MapTableT_HPP__
#define __MapTableT_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T, //the item content would be stored.
	const unsigned short MAP_SIZE, //the item max number.
	const unsigned short MAX_NUM,  //the max index.
	const unsigned short MIN_NUM = 0, // the min index, Note, it would reduce memory if MIN_NUM > 0.
	typename MAP_SIZE_TYPE = unsigned char, //the type which can contain MAP_SIZE.
	typename MAP_INDEX_TYPE = unsigned short> //the type which can contain MAX_NUM.
class MapTableT
{
  static const MAP_SIZE_TYPE  MAP_SIZE_INVALID  = ((MAP_SIZE_TYPE)-1);
  static const MAP_INDEX_TYPE MAP_INDEX_INVALID = ((MAP_INDEX_TYPE)-1);

public:
  MapTableT()
  {
    clear();
  }
  
  ~MapTableT()
  {
    
  }

  inline T& operator [](MAP_INDEX_TYPE index)
  {
  	return *get(index);
  }

  inline T *get(MAP_INDEX_TYPE index)
  {
    MAP_SIZE_TYPE itemIndex = -1;
#ifdef CHECK_INDEX_BOUNDARY
    if(index < MIN_NUM || index >= MAX_NUM)
    {
      return NULL;
    }
#endif
    if((itemIndex = m_maps[index-=MIN_NUM]) == MAP_SIZE_INVALID)
    {
      return NULL;
    }
    return &m_items[itemIndex];
  }
 
  inline void set(MAP_INDEX_TYPE index, const T& data)
  {
#ifdef CHECK_INDEX_BOUNDARY
    if(index < MIN_NUM || index >= MAX_NUM)
    {
      return ;
    }
#endif
    if(m_maps[index-=MIN_NUM] < MAP_SIZE)
    {
      m_items[m_maps[index]] = data;
    }
  }

  inline bool add(MAP_INDEX_TYPE index, const T& data)
  {
    if(!add(index))
	{
		return false;
	}

	set(index, data);
	return true;
  }

  inline bool add(MAP_INDEX_TYPE index)
  {
    bool ret = false;
#ifdef CHECK_INDEX_BOUNDARY
    if(index < MIN_NUM || index >= MAX_NUM)
    {
      return false;
    }
#endif
	index -= MIN_NUM;
    if(m_maps[index] != MAP_SIZE_INVALID)
    {
      ret = true;
    }
    else
    {
      if(m_allocNum < MAP_SIZE)
      {
        m_maps[index] = m_allocNum;
        m_index[m_allocNum++] = index;
        ret = true;
      }
    }

    return ret;
  }

  inline void del(MAP_INDEX_TYPE index)
  {
#ifdef CHECK_INDEX_BOUNDARY
    if(index < MIN_NUM || index >= MAX_NUM)
    {
      return ;
    }
#endif
    index -= MIN_NUM;
	MAP_SIZE_TYPE itemIndex = m_maps[index];

    if(m_allocNum <= 0 || itemIndex == MAP_SIZE_INVALID)
    {
      return ;
    }

	m_allocNum--;
    MAP_INDEX_TYPE last = m_index[m_allocNum];
    
    if(last != index)
    {
      //set(index+MIN_NUM, m_items[last]);
      m_items[itemIndex] = m_items[m_allocNum];
      m_index[itemIndex] = last;
      m_maps[last] = itemIndex;
    }
    
    m_maps[index] = MAP_SIZE_INVALID;
  }

  inline void clear()
  {
    m_allocNum = 0;
    memset(m_maps, MAP_SIZE_INVALID, sizeof(m_maps));
  }

  inline MAP_INDEX_TYPE begin()
  {
    m_iterator = 0;
    return m_index[m_iterator]+MIN_NUM;
  }
  
  inline MAP_INDEX_TYPE next()
  {
    return m_index[++m_iterator]+MIN_NUM;
  }

  inline MAP_SIZE_TYPE num()
  {
    return m_allocNum;
  }
  
  inline bool empty()
  {
    return m_iterator >= m_allocNum;
  }
  
private:
  unsigned short m_allocNum;
  unsigned short m_iterator;
  T m_items[MAP_SIZE];
  MAP_INDEX_TYPE m_index[MAP_SIZE];
  MAP_SIZE_TYPE  m_maps[MAX_NUM-MIN_NUM];
};

#endif

