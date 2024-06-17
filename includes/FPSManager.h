#pragma once
namespace doengine
{
class FpsManager
{
    long start, elapsed, wait, fps;

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
    virtual float getElapsedTime();
};

} // namespace doengine