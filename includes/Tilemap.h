#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "Geometric.h"
#include "Texture.h"
#include "Tile.h"

#define VALUE_IN_ARRAY(X, Y, W, A) A[Y * W + X]


struct MapRenderer{
   virtual void RenderTile(Rect rect) = 0;
   virtual void RenderTile(int x, int y, int w, int h, Color color) = 0;
};

 struct TileMap{
    
    protected:
     MapRenderer *mapRenderer;
    public:

      TileMap(): mapRenderer(nullptr){}
      virtual ~TileMap(){}
      virtual void setMapRenderer(MapRenderer *render) = 0;
      virtual void loadTileMapFromFile(const char* file) = 0;
      virtual void render() = 0;
      virtual void update() = 0;
 };




/*
    the simplest Tilemap the DOEngine Handler, support not layer
    single layer,  allow from 0 - 255 tiles types for map, 
    definition must be implemented or provide by developers.

    it could be 
    
    file structure would be.
    C = Columns
    R = Rows

    tilesetimage\n
    tilesizew\n
    tilesizeh\n
    ColumnCount\n
    RowCount\n
    C C C C...C+n
    C C C C...
    ...
    ...
    R+n

    example: 
    10
    3 
    1 1 1 1 1 1 1 1 1 1
    1 0 0 0 0 0 0 0 0 1
    1 1 1 1 1 1 1 1 1 1
*/
 struct SimpleLayerTileMap : public TileMap{

    protected:
    Texture *texture;
    std::vector<std::string> thisMap;
    public:

    SimpleLayerTileMap();
    virtual ~SimpleLayerTileMap();
    virtual void loadTileMapFromFile(const char* file);
    virtual void setMapRenderer(MapRenderer *render);
    virtual void render();
    virtual void update();
 };