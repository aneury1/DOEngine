#pragma once
#include "Geometric.h"
namespace doengine
{

const int default_tile_size = 32;
struct Tile
{
    Rect offset;
    int layer;
    int type;
    Tile()
    {
    }
    Tile(int x, int y, int s, int type)
    {
        offset.x = x;
        offset.y = y;
        offset.w = s;
        offset.h = s;
        this->type = type;
    }
    Tile(int x, int y, int s)
    {
        offset.x = x;
        offset.y = y;
        offset.w = s;
        offset.h = s;
        this->type = 0;
    }
    Tile(int x, int y)
    {
        offset.x = x;
        offset.y = y;
        offset.w = default_tile_size;
        offset.h = default_tile_size;
        this->type = type;
    }
};

} // namespace doengine