#pragma once 

#include "DOEngine.h"
#include "Renderer.h"

class Texture
{
 

   public:
   static void setTextureFromText(void *nativeSurface);
   static bool IsloadThisTexture(std::string id);
   static int  LoadTexture(std::string path, std::string id);
   static void DrawImage(std::string id, int x, int y, int w, int h);
   static void setRender(Renderer* render);
 
};