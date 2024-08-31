#pragma once
#include "Geometric.h"
#include "Texture.h"

namespace doengine
{

class Texture;

struct NativeTexture
{
    virtual ~NativeTexture()
    {
    }
    virtual NativeTexture* loadFromFile(const char* src) = 0;
    virtual bool validTexture() = 0;
    virtual void Draw(const Rect& offset) = 0;
    virtual void Draw(const Rect& offset, const Rect& clipset) = 0;
    virtual void ModulateColor(const Color& color) = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual NativeTexture* subTexture(Rect clipset) = 0;
};

struct NativeTextRenderer
{
    virtual void setColor(doengine::Color fg, doengine::Color bg) = 0;
    virtual void setColor(doengine::Color color) = 0;
    virtual void setFont(const std::string& path, int fntsize) = 0;
    virtual void DrawText(const char* text, int x, int y) = 0;
    virtual void getTextSize(const std::string& text, int* w, int* h) = 0;
    virtual void setFontSize(int fntSize) = 0;
    virtual void setForegroundColor(doengine::Color color) = 0;
    virtual void setBackgroundColor(doengine::Color color) = 0;
    virtual Texture* createText(const std::string& text) = 0;
};

} // namespace doengine