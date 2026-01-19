#include "SDLOpenglRenderer.h"
#include "Application.h"
#include "SDLTTFText.h"
#include "SDLTexture.h"
#include <assert.h>
#include <cmath>
#include "opengl_decls.h"

namespace doengine
{
 

SDLOpenglRenderer::SDLOpenglRenderer(SDL_Window* window)
    : window(window), context(nullptr)
{
    mgr = Application::getApplication()->getWindow();
    
    context = SDL_GL_CreateContext(window);
///
  ///  LoadMinimalGL();
    
    if (!context)
    {
        LogOuput(logger_type::Error, "Failed to create GL context: %s",
                 SDL_GetError());
        return;
    }
    LogOuput(logger_type::Error, "Info: %s",
                 SDL_GetError());
    
    SDL_GL_MakeCurrent(window, context);
    
    
    ///glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ///GLint profile;
    
    ////glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);

    primitiveGLRenderer = new PrimitiveGLRenderer();
    ////Mat4 projection = Mat4::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    LogOuput(logger_type::Information, "GL context created successfully %s", SDL_GetError());
    ///primitiveGLRenderer->setProjection(projection);
}

bool SDLOpenglRenderer::isRenderOk()
{
    return context != nullptr;
}

void* SDLOpenglRenderer::getNativeRenderer()
{
    return context;
}

void SDLOpenglRenderer::destroy()
{
    if (context)
    {
        SDL_GL_DeleteContext(context);
        context = nullptr;
    }
}

void SDLOpenglRenderer::clear()
{
    glClearColor(this->current_color.r / 255, current_color.g / 255, current_color.b/255,
                 current_color.a / 255);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SDLOpenglRenderer::setDrawColor(const Color& color)
{
    current_color = color;
}

void SDLOpenglRenderer::updateScreen()
{
    SDL_GL_SwapWindow(window);
}

void SDLOpenglRenderer::RenderSetClipRect(const Rect& rect)
{
 
}

void SDLOpenglRenderer::ResetRenderSetClipRect()
{
}

void SDLOpenglRenderer::DrawPoint(const Point& point, const Color& color)
{
    primitiveGLRenderer->drawPoint(point, Colors::green);
}

void SDLOpenglRenderer::DrawLine(const Point& p1, const Point& p2,
                                 const Color& color)
{
   primitiveGLRenderer->drawLine(p1,p2,color, 5);
}

void SDLOpenglRenderer::DrawRect(const Rect& rect, const Color& color)
{
   primitiveGLRenderer->drawRect(rect,color, false);
}

void SDLOpenglRenderer::DrawRect(const Rect& rect, const Color& color,
                                 int thickness)
{
   primitiveGLRenderer->drawRect(rect,color, false);
}

void SDLOpenglRenderer::DrawFillRect(const Rect& rect, const Color& color)
{
    primitiveGLRenderer->drawRect(rect,color, true);
}

void SDLOpenglRenderer::FillCircle(int x, int y, int radius, const Color& color)
{
    primitiveGLRenderer->drawCircle({x,y}, radius,color,32,true);
}

void SDLOpenglRenderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3,
                                     int y3, const Color& color)
{

}

void SDLOpenglRenderer::DrawRoundedRect(int x, int y, int w, int h,
                                        int cornerRadius, Color color)
{
}

NativeTexture* SDLOpenglRenderer::loadTextureFromImageFile(const char* src,
                                                           Color color)
{
    SDL_Surface* surface = IMG_Load(src);
    if (!surface)
        return nullptr;

    SDL_SetColorKey(surface, SDL_TRUE,
                    SDL_MapRGB(surface->format, color.r, color.g, color.b));

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format,
                 GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDLTexture* texture = new SDLTexture();
    texture->id = textureID;

    SDL_FreeSurface(surface);
    return texture;
}

NativeTexture* SDLOpenglRenderer::loadTextureFromImageFile(const char* src)
{
    SDL_Surface* surface = IMG_Load(src);
    if (!surface)
        return nullptr;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format,
                 GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDLTexture* texture = new SDLTexture();
    texture->id = textureID;

    SDL_FreeSurface(surface);
    return texture;
}

NativeTextRenderer* SDLOpenglRenderer::getTextRenderer()
{
    return new SDLTTFText();
}

NativeTexture* SDLOpenglRenderer::createTexture()
{
    return new SDLTexture();
}

} // namespace doengine