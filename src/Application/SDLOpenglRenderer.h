/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */


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
    std::shared_ptr<WindowManager> mgr;
    Color current_color;
    SDL_Window* window;
    SDL_GLContext context;


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
    virtual void DrawTexture(const std::variant<std::string, int> &,int , int ){}
    virtual void DrawTexture(const std::variant<std::string, int> &,const Rect& ){}
    virtual void DrawTexture(const std::variant<std::string, int>&,const Rect&, const Rect& ){}
    virtual void QueryTexture(const std::variant<std::string, int>&, Rect& ) {}
};
} // namespace  doengine

#endif