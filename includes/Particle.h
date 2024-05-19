#pragma once

namespace doengine
{

class Particle
{
  public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

}; // namespace doengine