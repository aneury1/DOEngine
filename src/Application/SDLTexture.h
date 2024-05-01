#include "Texture.h"
#include "Geometric.h"

struct SDLTexture : public NativeTexture {
    
   bool valid = false;
   SDL_Texture *this_texture;
   Point size;
   SDL_Color originalColor;
   virtual ~SDLTexture();
   virtual SDLTexture* loadFromFile(const char *src);
   virtual bool validTexture()override;
   virtual void Draw(const Rect &offset)override;
   virtual void Draw(const Rect &offset, const Rect& clipset)override;
   virtual void ModulateColor(const Color& color)override;
   virtual int getWidth()override;
   virtual int getHeight()override;
   virtual NativeTexture *subTexture(Rect clipset)override;
};