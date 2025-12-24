#ifndef REACTIVE_NATIVE_H_DEFINED
#define REACTIVE_NATIVE_H_DEFINED

#include <atomic>
#include <functional>

namespace doengine
{

struct Int
{
   std::function<void(int)> callback;
   std::atomic<int> value;
  
   const int operator()()
   {
        return value;
   }
   int operator=(const int v)
   {
        value = v;
        callback(v);
   }
};



};



#endif

