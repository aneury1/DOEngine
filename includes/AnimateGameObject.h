#ifndef ANIMATED_GAMEOBJECT_H_DEFINED
#define ANIMATED_GAMEOBJECT_H_DEFINED
#include "GameObject.h"
#include "Timer.h"
namespace doengine
{

class AnimateGameObject : public GameObject
{

    public:

    struct Animation
    {
        Timer timer;
        int frameCount;

        int getCurrentFrame()
        {
            return static_cast<int>(timer.getTime() / timer.getLength() * frameCount);
        }

        void step(float fl)
        {
            timer.Update(fl);
        }
    };     

    AnimateGameObject();
    virtual void Update(float elapsed) = 0;
    virtual void Render() = 0;
    void step(float elapsed); /// call it manually on Update...todo Put automatica on merge it GameState.
};




};

#endif