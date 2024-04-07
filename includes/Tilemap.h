#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Tile.h"

class TileMap
{
    typedef std::vector<Tile> TilesetLayer;
    std::vector<TilesetLayer> layers;
    int w;
    int h;

  public:
    TileMap();

    void LoadMapFromArray(std::string strMap, int w, int h);
    void LoadMapFromArray(std::vector<unsigned> uMap, int w, int h);
};