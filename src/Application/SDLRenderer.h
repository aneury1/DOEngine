#pragma once

extern "C"
{
#include <SDL2/SDL.h>
}

#include "Renderer.h"
#include "Geometric.h"
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


    virtual void DrawPoint(const Point& point, const Color& color);
    virtual void DrawLine(const Point& p1, const Point& p2, const Color& color);
    virtual void DrawRect(const Rect& rect, const Color& color );
    virtual void DrawFillRect(const Rect& rect, const Color& color );
    virtual void FillCircle(int x, int y, int radius, const Color& color);
    virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,const Color& p);


    virtual NativeTexture *loadTextureFromImageFile(const char *src, Color color)override;
    virtual NativeTextRenderer *getTextRenderer() override;

  private:
    SDL_Renderer* renderer;
};
