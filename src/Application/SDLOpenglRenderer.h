#ifndef SDLOPENGL_RENDERER_H_DEFINED
#define SDLOPENGL_RENDERER_H_DEFINED
#include "Color.h"
#include "SDLRenderer.h"
#include "WindowManager.h"

#include <Renderer.h>
#include "DOEngine_SDL_includes.h"
#include "opengl_decls.h"


namespace doengine
{
 
struct SDLOpenglRenderer : Renderer
{
    PrimitiveGLRenderer *primitiveGLRenderer;

    SDL_GLContext context;
    WindowManager* mgr;
    Color current_color;
    SDL_Window* window;

  public:
    SDLOpenglRenderer(SDL_Window* window);
    virtual bool isRenderOk();
    virtual void* getNativeRenderer();
    virtual void destroy();
    virtual void clear();
    virtual void setDrawColor(const Color&);
    virtual void updateScreen();

    virtual void RenderSetClipRect(const Rect&);
    virtual void ResetRenderSetClipRect();
    virtual void DrawPoint(const Point& point, const Color& color);
    virtual void DrawLine(const Point& p1, const Point& p2, const Color& color);
    virtual void DrawRect(const Rect& rect, const Color& color);
    virtual void DrawRect(const Rect& rect, const Color& color, int thickness);
    virtual void DrawFillRect(const Rect& rect, const Color& color);
    virtual void FillCircle(int x, int y, int radius, const Color& color);
    virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                              const Color& p);
    virtual void DrawRoundedRect(int x, int y, int w, int h, int cornerRadius,
                                 Color color);
    virtual NativeTexture* loadTextureFromImageFile(const char* src,
                                                    Color color);
    virtual NativeTexture* loadTextureFromImageFile(const char* src);
    virtual NativeTextRenderer* getTextRenderer();
    virtual NativeTexture* createTexture();
};
} // namespace  doengine

#endif