#include "Tilemap.h"
#include <fstream>
#include <stdio.h>

#define VALUE_IN_ARRAY(X, Y, W, A) A[Y * W + X]

TileMap::TileMap()
{
 
}

void TileMap::LoadMapFromArray(std::string strMap, int w, int h)
{
}

void TileMap::LoadMapFromArray(std::vector<unsigned> uMap, int w, int h)
{
}