#include "Timer.h"

namespace doengine
{
Timer::Timer(float length)
{
    current_time = 0;
    len = length;
    timeout_callback = nullptr;
}
Timer::~Timer()
{

}
int Timer::getLength()
{
    return len;
}
bool Timer::isTimeout()
{
    return timeout;
}
void Timer::Update(float t)
{
    current_time += t;
    if(current_time >= len)
    {
        current_time -= len;
        timeout = true;
        if(timeout_callback)
            timeout_callback();
    }
}
void Timer::reset()
{
    current_time = 0;
    timeout = false;
}
float Timer::getTime()
{
    return current_time;
}
void Timer::addTimerCallback(std::function<void()> cb)
{
    timeout_callback = cb;
}

} // namespace doengine