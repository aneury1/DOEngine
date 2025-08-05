#pragma once
#include "GameObjectPool.h"
#include <algorithm>
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
      GameObjectPool::ref.push_back(this);
    }

    virtual ~GameObject()
    {
        auto ref = std::find(GameObjectPool::ref.begin(), GameObjectPool::ref.end(), this);
    }
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    virtual bool isColliding(GameObject* other);
};

} // namespace doengine