#pragma once
#include "Constant.h"
#include "Geometric.h"
#include "Texture.h"
#include "Renderer.h"
#include "Tile.h"
#include "TTFText.h"

#include <fstream>
#include <functional>
#include <cstddef>
#include <string>
#include <vector>
#include <map>

namespace doengine
{

#define VALUE_IN_ARRAY(X, Y, W, A) A[Y * W + X]

static int primeMap[]=
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,1,0,1,0,1,0,1,0,0,
    0,1,0,1,0,0,1,0,1,0,1,0,0,
    0,1,1,0,1,0,1,0,1,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,2,2,2,2,0,0,0,2,2,2,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,3,3,3,3,3,3,3,3,3,0,0,
    0,0,0,0,0,0,5,0,0,0,0,0,0
};


struct TileMap
{
   Texture *texture;
   std::string tilset_path;   
   std::vector<Tile*> tileset;
   TTFText *textTexture;



   enum class EditorCursorPosition{
     Left,
     Right,
     Top,
     Bottom
   };
   

   int r;
   int c;
   int tilesize;
   int *map;






   //// void show Tiler Selector
   bool showEditor;
   Rect offsetOfMap;
   Rect texturePosition;
   Rect cursorRect;
   int tileW = 16;
   int tileH = 16; 
   // Apply scaling (here your texture is drawn *2)
   int scaledTileW = tileW * 2;
   int scaledTileH = tileH * 2;
   // Cursor position in terms of grid (row, col)
   int cursorCol = 2;  // example: first column
   int cursorRow = 0;  // example: first row
   

   /// Selected Any Tileset
   bool isATileOnEditorSelected=false;
   int selColIdx = 0;
   int selRowIdx = 0;
   Rect selClipset;
   Rect previousOffset;


   void MoveEditorCursor(EditorCursorPosition c);
   void displayEditor();

   TileMap();
   //// Common functions
   virtual void loadTileMap(int r, int c, int ts, int *map);
   virtual void loadTexture(const std::string path);
   virtual void render(Renderer *render);




};

} // namespace doengine