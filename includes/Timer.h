#ifndef TIMER_H_DEFINED
#define TIMER_H_DEFINED
#include<functional>
namespace doengine
{

class Timer
{
    public:
    Timer(float length);
    ~Timer();
    int getLength();
    float getTime();
    bool isTimeout();
    void Update(float t);
    void reset();
    void addTimerCallback(std::function<void()> cb);
    private:
    bool pause = false;
    bool timeout= false;
    float len =0;
    float current_time  = 0;
    std::function<void()> timeout_callback;
};




};

#endif 