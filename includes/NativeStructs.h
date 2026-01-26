#pragma once
#include "Geometric.h"
#include "Texture.h"
#include "Geometric.h"
namespace doengine
{
struct GlyphInfo
{
    Rect src;
    int advance;
};

class Texture;

struct NativeTexture
{
    int id;
    Rect rectSize;
    virtual ~NativeTexture(){}
    NativeTexture(){}
  
    virtual NativeTexture* subTexture(Rect clipset) = 0;
    virtual NativeTexture* setNativeTexture(void *text) = 0;
    virtual NativeTexture* loadFromFile(const char* src) = 0;
    virtual void Draw(int x, int y) = 0;
    virtual void Draw(const Rect& offset) = 0;
    virtual void Draw(const Rect& offset, const Rect& clipset) = 0;
    virtual void SetTransparentColor(const Color& color) =0;
    virtual void ModulateColor(const Color& color) = 0;
    virtual void Destroy() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual bool validTexture() = 0;
};

struct NativeTextRenderer
{
    virtual int getFontHeight() = 0;
    virtual Rect getTextSize(const char* str) =0;
    virtual void setColor(doengine::Color fg, doengine::Color bg) = 0;
    virtual void setColor(doengine::Color color) = 0;
    virtual void setFont(const std::string& path, int fntsize) = 0;
    virtual void DrawText(const char* text, int x, int y) = 0;
    virtual void getTextSize(const std::string& text, int* w, int* h) = 0;
    virtual void setFontSize(int fntSize) = 0;
    virtual void setForegroundColor(doengine::Color color) = 0;
    virtual void setBackgroundColor(doengine::Color color) = 0;
    virtual Texture* createText(const std::string& text) = 0;
    virtual void wrapText(const char* text, int maxWidth, char* wrappedText) =0;
    virtual Texture*  createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg)= 0;
};

struct NativeBitmapTextRenderer
{
    enum class Alignment 
    {
        Left,
        Center,
        Right
    };
};




} // namespace doengine