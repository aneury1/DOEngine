#pragma once

#include "Geometric.h"
#include "Texture.h"
#include "Tile.h"
#include <cstddef>
#include <string>
#include <vector>

namespace doengine
{

#define VALUE_IN_ARRAY(X, Y, W, A) A[Y * W + X]

class TileMap;
struct MapRenderer
{

    TileMap* tilemap;

  public:
    MapRenderer(TileMap* tilemap)
    {
        this->tilemap = tilemap;
    }
    virtual void RenderTileMap(
        const std::vector<std::vector<char>>& tilemap) = 0;
    virtual void RenderTile(const Rect& rect) = 0;
    virtual void RenderTile(int x, int y, int w, int h, Color color) = 0;
    virtual void RenderTile(const Tile& tile) = 0;
};

struct TileMap
{

  protected:
    MapRenderer* mapRenderer;

  public:
    TileMap() : mapRenderer(nullptr)
    {
    }
    virtual ~TileMap()
    {
    }
    virtual void setMapRenderer(MapRenderer* render) = 0;
    virtual void loadTileMapFromFile(const char* file) = 0;
    virtual void saveLoadedTileMap() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
};

/*
    the simplest Tilemap the DOEngine Handler, support not layer
    single layer,  allow from 0 - 255 tiles types for map,
    definition must be implemented or provide by developers.

    this not support scroll, Row and columns must be divide by Avail Space
    it could be

    file structure would be.
    C = Columns
    R = Rows

    tilesetimage\n
    RowCount\n
    ColumnCount\n
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
struct SimpleLayerTileMap : public TileMap
{

  protected:
    int margin_top;
    int margin_left;

    std::string tileset_asset;
    int tilesize_width;
    int tilesize_height;
    int rows;
    int cols;

    std::vector<std::string> thisMapFile;

    /// @todo convert To Tile vector or maybe one dimension array.
    std::vector<std::vector<char>> thisMapRows;

    Texture* texture;

  public:
    int getTileSize()
    {
        return 32;
    }
    SimpleLayerTileMap();
    virtual ~SimpleLayerTileMap();
    virtual void loadTileMapFromFile(const char* file);
    virtual void saveLoadedTileMap();
    virtual void setTileType(int r, int c, char t);
    virtual char getTileType(int r, int c);
    virtual void setMapRenderer(MapRenderer* render);
    virtual void render();
    virtual void update();

    int getMarginLeft()
    {
        return margin_left;
    }
    int getMarginTop()
    {
        return margin_top;
    }

    int setMarginLeft(int s)
    {
        return (margin_left = s);
    }
    int getMarginTop(int s)
    {
        return (margin_top = s);
    }

    int getRowCount()
    {
        return rows;
    }
    int getColumnCount()
    {
        return rows;
    }
};

}; // namespace doengine