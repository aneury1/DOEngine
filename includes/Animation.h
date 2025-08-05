#ifndef ANIMATION_H_DEFINED
#define ANIMATION_H_DEFINED
#include "Delay.h"
#include "Application.h"
namespace doengine
{
    class Animation
    {
        Timer timer;
        long frame_count;
        public:

        Animation();
        Animation(long frameCount, float len);
        long getCurrentFrame();
        float getLength();
        void step(float deltaTime);
        void step();
    
    };

////@todo move to cpp file.

Animation::Animation(): timer{0},frame_count{0}
{}

Animation::Animation(long frameCount, float len):timer{len}, frame_count{frameCount}
{}  

long Animation::getCurrentFrame()
{
    return static_cast<long>(timer.getTime()/timer.getLength() * frame_count);
}

float Animation::getLength()
{
    return timer.getLength();
}

void Animation::step(float deltaTime)
{
    timer.step(deltaTime);
}
        
void Animation::step()
{
    this->step(Application::getApplication()->getDeltaTime());
} 




}






#endif /// ANIMATION_H_DEFINED