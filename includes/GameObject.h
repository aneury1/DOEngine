#pragma once

#include <string>
namespace doengine
{
class GameObject
{
  protected:
    bool renderable;
    bool solid;
    int layer;

    std::string sprite_id;
    std::string texture_id;

  public:
    GameObject()
    {
    }

    virtual ~GameObject()
    {
    }
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    virtual bool isColliding(GameObject* other);
};

} // namespace doengine