
#include "Geometric.h"
#include "Texture.h"
#include "DOEngine_SDL_includes.h"
#include <string>

namespace doengine
{

struct SDLTexture : public NativeTexture
{
    int texture = -1;
    std::string path;
    SDL_Renderer *renderer;
    bool valid = false;
    SDL_Texture* this_texture;
    Point size;
    SDL_Color originalColor;
    virtual ~SDLTexture();
    SDLTexture();
    virtual SDLTexture* loadFromFile(const char* src)override;
    virtual void SetTransparentColor(const Color& color)override;
    virtual bool validTexture() override;
    virtual void Draw(int x, int y) override;
    virtual void Draw(const Rect& offset) override;
    virtual void Draw(const Rect& offset, const Rect& clipset) override;
    virtual void ModulateColor(const Color& color) override;
    virtual void Destroy() override;
    virtual int getWidth() override;
    virtual int getHeight() override;
    virtual NativeTexture* subTexture(Rect clipset) override;
    virtual NativeTexture* setNativeTexture(void *text)override;
     
   
};

} // namespace doengine