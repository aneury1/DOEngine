#pragma once
#include "Geometric.h"
#include <unordered_map>
#include <variant>
namespace doengine
{

const int default_tile_size = 32;

struct TileOffset{
   doengine::Rect textureOffset;
   doengine::Color color;
   std::variant<std::string, int> texture_id;
};


struct Tile
{

    Rect offset;
    int layer;
    char type;
    Tile()
    {
    }
    Tile(int x, int y, int s, char type)
    {
        offset.x = x;
        offset.y = y;
        offset.w = s;
        offset.h = s;
        this->type = type;
    }
    Tile(int x, int y, char s)
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