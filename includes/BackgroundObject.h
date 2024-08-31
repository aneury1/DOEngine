#pragma once
#include "Application.h"
#include "GameObject.h"

class Background : public GameObject
{
  protected:
    Window* window;

  public:
    Background(Window* window) : window{window}, GameObject(window)
    {
    }
    virtual ~Background()
    {
    }
    virtual void Update(long timestamp) = 0;
    virtual void Draw() = 0;
};

class ParallaxBackground : public Background
{
  public:
    ParallaxBackground(Window* window, const char* assets, int width, int h);
    virtual ~ParallaxBackground();
    virtual void Update(long timestamp);
    virtual void Draw();
};
