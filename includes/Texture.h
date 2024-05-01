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
   virtual NativeTexture *subTexture(Rect clipset) = 0;
};


class Texture 
{
   NativeTexture *realNativeTexture;
   Texture(){
      realNativeTexture = nullptr;
   }
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

   Texture *subTexture(const Rect& clipset);
  
};

class TextureManager {
   
   TextureManager(){}
   
   static TextureManager *instance;

   std::map<std::string, Texture*> textures;

   public:

   static TextureManager *getTextureManager();

   void loadTextureFromFile(std::string id, std::string src);

   void loadTextureFromTexture(std::string id, Texture* texture, const Rect &clipset);

   void addTexture(std::string id, Texture* texture);

   void removeTexture(std::string id);

   Texture *getTexture(std::string id);
   
};


