#pragma once

extern "C"
{
#include <SDL2/SDL.h>
}

#include "Geometric.h"
#include "Renderer.h"

namespace doengine
{

class SDLRenderer : public Renderer
{
  public:
    SDLRenderer(SDL_Renderer* nativeRenderer);
    virtual bool isRenderOk() override;
    virtual void* getNativeRenderer() override;
    virtual void destroy() override;
    virtual void clear() override;
    virtual void setDrawColor(const Color& color) override;
    virtual void updateScreen() override;
    virtual void RenderSetClipRect(const Rect& ) override;
    virtual void ResetRenderSetClipRect() override;


    virtual void DrawPoint(const Point& point, const Color& color);
    virtual void DrawLine(const Point& p1, const Point& p2, const Color& color);
    virtual void DrawRect(const Rect& rect, const Color& color);
    virtual void DrawRect(const Rect& rect, const Color& color, int thickness);
    virtual void DrawFillRect(const Rect& rect, const Color& color);
    virtual void FillCircle(int x, int y, int radius, const Color& color);
    virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                              const Color& p);

    virtual void DrawRoundedRect(int x, int y, int w, int h, int roundedRadius,
                                 Color color) override;

    virtual NativeTexture* loadTextureFromImageFile(const char* src,
                                                    Color color) override;
    virtual NativeTexture* loadTextureFromImageFile(const char* src) override;
    virtual NativeTextRenderer* getTextRenderer() override;

     virtual NativeTexture* createTexture()override;

  private:
    SDL_Renderer* renderer;
};

} // namespace doengine