#ifndef CONSTANT_H_DEFINED
#define COSNTANT_H_DEFINED

namespace doengine
{

   
enum class DoEngineStatus{
   Success,
   Failed,
   Uknown
};

enum class TileMapFormat
{
    NameTileSizeWidthHeightMapSingleLayer,
    CustomTileMapFormat
};
}

#endif