#ifndef __CMapTableT2_HPP__
#define __CMapTableT2_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T, const unsigned short MAP_SIZE, const unsigned short MAX_NUM, typename TIndex = unsigned short, typename MAP_SIZE_TYPE = unsigned char>
class CMapTableT2
{

public:
  CMapTableT2()
  {
    clear();
  }
  
  ~CMapTableT2()
  {
    
  }

  inline T *get(TIndex index)
  {
    MAP_SIZE_TYPE itemIndex = -1;
    if(index >= MAX_NUM || (itemIndex = m_maps[index]) == (MAP_SIZE_TYPE)-1)
    {
      return NULL;
    }
    return &m_items[itemIndex];
  }
 
  inline void set(TIndex index, const T& data)
  {
    if(index < MAX_NUM && m_maps[index] < MAP_SIZE)
    {
      m_items[m_maps[index]] = data;
    }
  }

  inline bool add(TIndex index)
  {
    bool ret = false;
#ifdef CHECK_INDEX_BOUNDARY
    if(index >= MAX_NUM)
    {
      return ret;
    }
#endif
    if(m_maps[index] != (MAP_SIZE_TYPE)-1)
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

  inline void del(TIndex index)
  {
    if(index >= MAX_NUM || m_allocNum <= 0 || m_maps[index] == (MAP_SIZE_TYPE)-1)
    {
      return ;
    }
    
    TIndex last = m_index[m_allocNum-1];
    
    if(last != index)
    {
      set(index, m_items[last]);
      m_maps[last] = m_maps[index];
      m_index[index] = last;
    }
    
    m_maps[index] = (MAP_SIZE_TYPE)-1;
    m_allocNum--;
  }

  inline void clear()
  {
    m_allocNum = 0;
    memset(m_maps, -1, sizeof(m_maps));
  }

  inline TIndex& begin()
  {
    m_iterator = 0;
    return m_index[m_iterator];
  }
  
  inline TIndex& next()
  {
    return m_index[++m_iterator];
  }
  
  inline bool empty()
  {
    return m_iterator >= m_allocNum;
  }
  
private:
  unsigned short m_allocNum;
  unsigned short m_iterator;
  TIndex m_index[MAP_SIZE];
  T m_items[MAP_SIZE];
  MAP_SIZE_TYPE m_maps[MAX_NUM];
};

#endif
