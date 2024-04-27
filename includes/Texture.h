#pragma once 
#include <string>
#include "Geometric.h"
#include "Renderer.h"

struct NativeTexture{
   virtual ~NativeTexture(){}
   virtual NativeTexture* loadFromFile(const char *src) =0;
   virtual bool validTexture()=0;
   virtual void Draw(const Rect &offset) = 0;
   virtual void Draw(const Rect &offset, const Rect& clipset) = 0;
   virtual void ModulateColor(const Color& color) = 0;
   virtual int getWidth() = 0;
   virtual int getHeight() = 0;
};


class Texture 
{
   NativeTexture *realNativeTexture;
   public:
   Texture(std::string path); 
   ~Texture();
   void Draw(const Rect &offset) ;
   void Draw(const Rect &offset, const Rect& clipset) ;
   void ModulateColor(const Color& color) ;
   int getWidth() ;
   int getHeight() ;
   bool validTexture(){
      return realNativeTexture->validTexture();
   }

};