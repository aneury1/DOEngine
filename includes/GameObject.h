#pragma once
#include "Application.h"
#include "Geometric.h"
#include "Renderer.h"

#include <string>
#include <variant>
namespace doengine
{

class Renderer;

enum ObjecType
{
    Player = 0,
    Level,
    Tile,
    AnimateTile,
    Npc,
    Ui,
    DebugObject,
    UknownObject,
    LastDefaultUnused
};

static unsigned long long id_pool = 0;
class GameObject
{
  private:
    long long id;

  protected:
    bool debuging_enable;

    Rect position;
    Renderer* renderer;

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

    inline const int getId()
    {
        return id;
    }
};

} // namespace doengine