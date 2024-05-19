#pragma once
#include "GameObject.h"
#include "Geometric.h"
namespace doengine
{
struct Tile : public GameObject
{
    int x;
    int y;
    int type;
    int tilesize;

    virtual void Update(float timer = 0)
    {
    }
    virtual void Render()
    {
    }
    virtual bool collideWith(const Rect& rect)
    {
    }
    virtual bool collideWith(const GameObject& object)
    {
    }

    int getTileType() const
    {
        return type;
    }
};

class AnimateTile : public Tile
{
};

}; // namespace doengine