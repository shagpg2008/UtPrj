/*
* This template can be used for those don't care about the efficient of delete operator.
*
*
*/

#ifndef __CMapTableT3_HPP__
#define __CMapTableT3_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T, const unsigned short MAP_SIZE, const unsigned short MAX_NUM, typename MAP_SIZE_TYPE = unsigned char>
class CMapTableT3
{

public:
  CMapTableT3()
  {
    clear();
  }
  
  ~CMapTableT3()
  {
    
  }

  inline T *get(unsigned short index)
  {
    MAP_SIZE_TYPE itemIndex = -1;
    if(
#ifdef CHECK_INDEX_BOUNDARY
    index >= MAX_NUM || 
#endif
    (itemIndex = m_maps[index]) == (MAP_SIZE_TYPE)-1)
    {
      return NULL;
    }
    return &m_items[itemIndex];
  }
 
  inline void set(unsigned short index, const T& data)
  {
    if(index < MAX_NUM && m_maps[index] < MAP_SIZE)
    {
      m_items[m_maps[index]] = data;
    }
  }

  inline bool add(unsigned short index)
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
        m_maps[index] = m_allocNum++;
        ret = true;
      }
    }

    return ret;
  }

  inline void del(unsigned short index)
  {
    if(
#ifdef CHECK_INDEX_BOUNDARY
    index >= MAX_NUM || 
#endif
    m_allocNum <= 0 || m_maps[index] == (MAP_SIZE_TYPE)-1)
    {
      return ;
    }
    
    unsigned short last = (MAP_SIZE_TYPE)-1;
    m_allocNum--;

    if(m_maps[index] != m_allocNum)
    {
      while(last == (MAP_SIZE_TYPE)-1 && m_allocNum > 0) {
        for(unsigned short  i = 0; i <= m_allocNum; i++) {
          if(m_maps[i] == m_allocNum) {
            last = i;
            break;
          }
        }
        
        if(last != (MAP_SIZE_TYPE)-1) {
          break ;
        }
        
        m_allocNum--;
      }
      
      if(last == (MAP_SIZE_TYPE)-1) {
        return ;
      }
    
      set(index, m_items[last]);
      m_maps[last] = m_maps[index];
    }
    
    m_maps[index] = (MAP_SIZE_TYPE)-1;
  }

  inline void clear()
  {
    m_allocNum = 0;
    memset(m_maps, -1, sizeof(m_maps));
  }
/*
  inline MAP_SIZE_TYPE& begin()
  {
    m_iterator = 0;
    return m_items[m_iterator];
  }
  
  inline MAP_SIZE_TYPE& next()
  {
    return m_items[++m_iterator];
  }
  
  inline bool empty()
  {
    return m_iterator >= m_allocNum;
  }
  */
private:
  unsigned short m_allocNum;
  unsigned short m_iterator;
  T m_items[MAP_SIZE];
  MAP_SIZE_TYPE m_maps[MAX_NUM];
};

#endif
