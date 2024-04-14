#pragma once 

#include "DOEngine.h"
#include "Renderer.h"

class Texture
{
   static std::map<std::string, SDL_Texture*>textures;
   static SDL_Renderer* render;

   public:

   static bool IsloadThisTexture(std::string id);
   static int  LoadTexture(std::string path, std::string id);
   static void DrawImage(std::string id, int x, int y, int w, int h);
   static void setRender(SDL_Renderer* render);
   static void setRender(doengine::gfx::Renderer* render);
};