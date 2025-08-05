#ifndef DELAYS_H_DEFINED
#define DELAYS_H_DEFINED
#include <type_traits>
#include <functional>
#include "Application.h"

namespace doengine
{

template<typename T>
struct NativeValue
{
    T value;
    NativeValue(const T val): value{val}{}
    T get(){return value;}
    NativeValue set(T v){value =v;}
};

struct TwoState
{
    bool value;

    TwoState* set(bool v){ value = v;}
    bool get()const{ return value;}
};


template<class T>
struct Counter
{
   static_assert(std::is_integral<T>::value, "Only integer values");


};

struct Timer
{
   float length, time;
   bool timeout;
   Timer():length{0},time{0}, timeout{false}{}
   Timer(float time):time{0},length{time}, timeout{false}{}

   void step(float deltaTime)
   {
        time += deltaTime;
        if(time >= length)
        {
            time -= length;
            timeout = true;
        }
   }
 
   void step()
   {
      float deltaTime = doengine::Application::getApplication()->getDeltaTime();
      step(deltaTime);
   }

   bool isTimeout()const {return timeout;}
   void setTime(float time, bool resetit=false){
     if(resetit)
        reset();
     this->time = time;
   }
   long getTime()const {return time;}
   long getLength()const {return length;}
   Timer* reset()
   {
        time = 0;
        timeout = false;
        return this;
   }

   Timer *resetIf(std::function<bool()> condition)
   {
        if(condition())
            reset();
        return this;
   }
};



}


#endif