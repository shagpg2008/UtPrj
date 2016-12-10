
#ifndef _sort___hpp
#define _sort___hpp

#define exchange(a,b) {  \
  Item temp = a;  \
  a = b;  \
  b = temp;  \
}

#define compare_exchange(a,b) if(a > b) exchange(a, b)

template <typename Item>  
void insert_sort(Item array[],int left,int right)
{
  int i;
  int j;
  int cur;
  
  /*find the min element ,put it in the leftest position, use it as a guard*/
  for(i = right;i>left;i--)
  {
    compare_exchange(array[i-1], array[i]);
  }

  for(i = left + 2; i <= right;i++)
  {
    cur = array[i];
    j = i;

    while(cur < array[j-1]) 
    {
      array[j] = array[j-1]; 
      j--;
    }
    array[j] = cur;
  }
}

#define M 16
template <typename Item>  
void quick_sort(Item a[], int left, int right) {
  if (right-left < M) {// prevent little array recursion  
    insert_sort(a, left, right);
    return;  
  }
  // median-of-three  
  compare_exchange(a[left], a[(left+right)/2]);  
  compare_exchange(a[left], a[right]);  
  compare_exchange(a[right], a[(left+right)/2]);  
  // three-way-partition  
  Item v = a[right];
  int i = left-1, p = left-1, j = right, q = right;  
  for (;;) {  
    while (a[++i] < v) {}  
    while (a[--j] > v)  
      if (j == left)  
        break;  
    if (i >= j)  
      break;  
    exchange(a[i], a[j]);  
    if (a[i] == v)  
    {
      ++p;
      exchange(a[p], a[i]);  
    }

    if (a[j] == v)  
    {
      --q;
      exchange(a[q], a[j]);
    }
  }  
  exchange(a[i], a[right]);  
  // move equal elements to middle of array  
  j = i-1;  
  i = i+1;  
  for (int k = left; k <= p; ++k, --j)  
    exchange(a[k], a[j]);  
  for (int k = right-1; k >= q; --k, ++i)  
    exchange(a[k], a[i]);  
  quick_sort(a, left, j);  
  quick_sort(a, i, right);  
}  

#undef exchange
#undef compare_exchange
#undef M
#endif
