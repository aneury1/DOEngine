#pragma once
#include "Geometric.h"
#include "TTFText.h"
#include <vector>
namespace doengine
{

const int default_tile_size = 32;
struct Tile
{
    bool debug;
    std::string tileset_path;
    Rect offset;
    Rect clipset;
    Texture *texture;
    TTFText *textTexture;
    int layer;
    int type;
    int index;
    Tile()
    {
        debug = true;
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

    void Draw(Renderer *render);
};

struct TileInfo
{

    /// @brief <tile char="2" x="" y="" name="metal" nondestructible="true"/>
    Rect offset;
    char chr;
    std::string name;
    bool destrutible;
    bool visible;
};


struct TileMapLayer
{
    int layer_number;
    /// Tileset info
    std::vector<TileInfo> tileset_info;
    std::vector<char> mapdata;
};

struct TileMapData
{
    /*
       Metadata
       rows="20" 
       cols="20" 
       tilesize="16"
       texture="/home/neon/Desktop/DOEngine/assets/images/battlecitysprites.png"
       texture_id="1"
    */
   bool valid;
   int16_t rows;
   int16_t cols;
   int16_t tilesize;
   std::string texture_path;
   std::string texture_id;
   std::vector<TileMapLayer> layers;

   static TileMapData *fromXMLStr(const std::string& path);
   static TileMapData *fromXMLFile(const std::string& path);
};






struct AnimateTile : public Tile{
   std::vector<Rect> tiles;
   int delay;
   int current;
   Rect getCurrent();
   AnimateTile& operator++();
   AnimateTile& operator++(int);
   AnimateTile& operator--();
   AnimateTile& operator--(int);
};






} // namespace doengine