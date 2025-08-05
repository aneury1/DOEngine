#ifndef NATIVE_WRAPPER_H_DEFINED
#define NATIVE_WRAPPER_H_DEFINED

#include <functional>


template <typename T>
struct NativeType
{
   std::function<void(T)> onchange;
   T internalValue;
   NativeType operator =(const T& v)
   {
       internalValue = v;
       if(onchange)
       {
          onchange(internalValue);
       }
   }

   T getValue(){
    return internalValue;
   }
};






#endif