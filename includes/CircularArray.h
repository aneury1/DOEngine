#ifndef CIRCULAR_ARRAY_H_DEFINED
#define CIRCULAR_ARRAY_H_DEFINED
#include <array>


template<typename T, const int size>
class CircularArray{
   
   static_assert(size>0,"Size must be higher than zero");
   std::array<T, size> _array;
   int cursor = 0;
   
   void fixBound(){

   }

   T operator ++(int){
      T v = _array[cursor];
      cursor++;
      fixBound();
      return v;
   }


};



#endif //CIRCULAR_ARRAY_H_DEFINED