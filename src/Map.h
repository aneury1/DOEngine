#pragma once
#include <SDL.h>
#include <vector>

struct Tile
{
   SDL_Rect offset;
   int type;
   int layer;

   Tile(int x, int y, int w, int h, int t, int l);
   Tile();
   Tile(SDL_Rect rect, int t, int l);

   virtual void Draw();
   virtual void Update();
};


struct Tileset
{
   std::vector<Tile*>layer0;
   public:
   Tileset(int r, int c, int *array, int tilesize=32);
   void Draw();
};