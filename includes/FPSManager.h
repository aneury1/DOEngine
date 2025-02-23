#pragma once
#include <stdint.h>

namespace doengine
{
class FpsManager
{
    uint32_t start, elapsed, wait, fps;

  public:
    FpsManager() : start(0L), elapsed(0L), fps(60L)
    {
    }

    virtual ~FpsManager()
    {
    }

    virtual void setFPS(long fps = 60);
    virtual void Start();
    virtual void Handle();
    virtual uint32_t getDeltaTime();
    virtual float getElapsedTime();
};

} // namespace doengine