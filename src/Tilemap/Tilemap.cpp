#include "Tilemap.h"
#include "Logger.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

namespace doengine
{

SimpleLayerTileMap::SimpleLayerTileMap() : TileMap()
{

    std::cout << "HERER";
    texture = nullptr;
    std::cout << "HERER";
    thisMap.clear();
    std::cout << "HERER";
}
SimpleLayerTileMap::~SimpleLayerTileMap()
{
    std::cout << "HERER";
}

void SimpleLayerTileMap::setMapRenderer(MapRenderer* render)
{
    this->mapRenderer = render;
}
void SimpleLayerTileMap::loadTileMapFromFile(const char* file)
{
    /// readMapFile("../sample/assets/maps/simple-map1.map", thisMap);

    for (int r = 0; r <= rows; r++)
    {
        /// std::string row = thisMapFile[r + 2];
        /// DO_TRACE("Row=%s", row.c_str());
        // std::vector<char> chars = splitChar(row, " \r\n\t\0");
        // thisMapRows.emplace_back(chars);
    }
}

void SimpleLayerTileMap::saveLoadedTileMap()
{
}

void SimpleLayerTileMap::setTileType(int r, int c, char t)
{
    if ((r >= 0 || r <= this->rows) && (c >= 0 || c <= this->cols))
    {
        /// DO_TRACE("CHANGE ROW=%d, COL=%d FROM %c TO %d", r, c,
        /// thisMapRows[r][c],
        //          t);
        // thisMapRows[r][c] = t;
    }
}
char SimpleLayerTileMap::getTileType(int r, int c)
{
    if ((r >= 0 || r <= this->rows) && (c >= 0 || c <= this->cols))
    {
        ////  return thisMapRows[r][c];
    }
    return (char)0xFF;
}

void SimpleLayerTileMap::render()
{
}
void SimpleLayerTileMap::update()
{
}
} // namespace doengine
