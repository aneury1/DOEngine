#pragma once
#include <map>
#include <vector>
#include <variant>
#include "GameObject.h"
#include "SpriteOffset.h"
#include "Geometric.h"

namespace doengine
{
class Sprite : public GameObject
{
  protected:
    Rect offset;
    Rect clipset;
    SpriteAnimationOffset *animations;
    std::variant<std::string, int> texture_id;
  public:
    virtual ~Sprite() = default;
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    virtual bool isColliding(GameObject* other) = 0;
};
} // namespace doengine