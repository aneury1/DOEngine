#pragma once

#include "Color.h"
#include "Geometric.h"
#include "TTFText.h"
#include "Texture.h"

namespace doengine
{

class NativeTextRenderer;
class NativeTexture;
class Texture;
class Renderer
{
  public:
    virtual bool isRenderOk() = 0;
    virtual void* getNativeRenderer() = 0;
    virtual void destroy() = 0;
    virtual void clear() = 0;
    virtual void setDrawColor(const Color&) = 0;
    virtual void updateScreen() = 0;

    virtual void DrawPoint(const Point& point, const Color& color) = 0;
    virtual void DrawLine(const Point& p1, const Point& p2,
                          const Color& color) = 0;
    virtual void DrawRect(const Rect& rect, const Color& color) = 0;
    virtual void DrawFillRect(const Rect& rect, const Color& color) = 0;
    virtual void FillCircle(int x, int y, int radius, const Color& color) = 0;
    virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                              const Color& p) = 0;
    virtual void DrawRoundedRect(int x, int y, int w, int h, int cornerRadius,
                                 Color color) = 0;
    virtual NativeTexture* loadTextureFromImageFile(const char* src,
                                                    Color color) = 0;
    virtual NativeTextRenderer* getTextRenderer() = 0;
};

}; // namespace doengine