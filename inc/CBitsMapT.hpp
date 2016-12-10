#ifndef _CBitsMapT_HPP_
#define _CBitsMapT_HPP_

#include <string.h>

static const unsigned char CONST_BITMAP_BITS[] = {
  0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80
};

typedef struct{
  unsigned short bits:3;
  unsigned short index:13;
}TIndexToBitmapIndex;

template<const unsigned short NumOfBits> class CBitsMapT
{
private:
  unsigned char m_bitmap[((((NumOfBits + 0x7)>>3) + 0x3) >> 2) << 2];

public:
  CBitsMapT() 
  {
     clear();
  }

  inline bool isset( unsigned short index)
  {
    if(index >= NumOfBits)
    {
      return false;
    }
    
    TIndexToBitmapIndex *lpBitmapIndex = (TIndexToBitmapIndex *)&index;
    return (m_bitmap[lpBitmapIndex->index]) & CONST_BITMAP_BITS[lpBitmapIndex->bits];
  }

  inline void set( unsigned short index)
  {
#ifdef CHECK_INDEX_BOUNDARY
    if(index >= NumOfBits)
    {
      return ;
    }
#endif
    TIndexToBitmapIndex *lpBitmapIndex = (TIndexToBitmapIndex *)&index;
    m_bitmap[lpBitmapIndex->index] |= CONST_BITMAP_BITS[lpBitmapIndex->bits];
  }  

  inline void reset(unsigned short index)
  {
#ifdef CHECK_INDEX_BOUNDARY
    if(index >= NumOfBits)
    {
      return ;
    }
#endif
    TIndexToBitmapIndex *lpBitmapIndex = (TIndexToBitmapIndex *)&index;
    m_bitmap[lpBitmapIndex->index] &= (unsigned char)(~ (CONST_BITMAP_BITS[lpBitmapIndex->bits]));
  }

  inline void clear()
  {
    memset(m_bitmap, 0, sizeof(m_bitmap));
  }

  void print()
  {
    char buff[(NumOfBits>>2) + 8] = {0};
    for(unsigned short index = 0; index < sizeof(m_bitmap); index ++)
    {
      sprintf(buff+index+index, "%02X", m_bitmap[index]);
    }
    printf("CBitsMapT:m_bitmap=%s\n", buff);
  }
};


#endif


