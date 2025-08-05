#pragma once
namespace doengine
{
class FpsManager
{
    long previous, current, fps;
    float deltaTime;

  public:
    FpsManager() : previous{0L}, current{0L}, fps{60L}, deltaTime{0.0f}
    {
    }

    virtual ~FpsManager()
    {
    }

    virtual void setFPS(long fps = 60);
    virtual void Start();
    virtual void End();
    virtual float getDeltaTime();
};

} // namespace doengine