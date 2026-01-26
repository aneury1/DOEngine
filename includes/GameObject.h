#pragma once
#include "Application.h"
#include "Renderer.h"
#include "Geometric.h"
#include <string>
namespace doengine
{
class GameObject
{
  protected:
    
    Rect position;
    Renderer *renderer;
    
    
    bool renderable;
    bool solid;
    int layer;

    std::string sprite_id;
    std::string texture_id;

  public:
    GameObject();
    virtual ~GameObject();
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    Renderer* getRenderer();
    Rect getPosition();
};

} // namespace doengine