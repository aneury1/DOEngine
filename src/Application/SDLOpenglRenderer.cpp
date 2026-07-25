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

#include "SDLOpenglRenderer.h"
#include "Application.h"
#include "SDLTTFText.h"
#include "SDLTexture.h"
#include "opengl_decls.h"
#include <assert.h>
#include <cmath>

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
    LogOuput(logger_type::Error, "Info: %s", SDL_GetError());

    SDL_GL_MakeCurrent(window, context);

    /// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /// GLint profile;

    ////glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);

    primitiveGLRenderer = std::make_shared<PrimitiveGLRenderer>();
    ////Mat4 projection = Mat4::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    LogOuput(logger_type::Information, "GL context created successfully %s",
             SDL_GetError());
    /// primitiveGLRenderer->setProjection(projection);
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
    glClearColor(this->current_color.r / 255, current_color.g / 255,
                 current_color.b / 255, current_color.a / 255);
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

void SDLOpenglRenderer::RenderSetClipRect(const Rect&)
{
}

void SDLOpenglRenderer::ResetRenderSetClipRect()
{
}

void SDLOpenglRenderer::DrawPoint(const Point& point, const Color&)
{
    primitiveGLRenderer->drawPoint(point, Colors::green);
}

void SDLOpenglRenderer::DrawLine(const Point& p1, const Point& p2,
                                 const Color& color)
{
    primitiveGLRenderer->drawLine(p1, p2, color, 5);
}

void SDLOpenglRenderer::DrawRect(const Rect& rect, const Color& color)
{
    primitiveGLRenderer->drawRect(rect, color, false);
}

void SDLOpenglRenderer::DrawRect(const Rect& rect, const Color& color,
                                 int  )
{
    primitiveGLRenderer->drawRect(rect, color, false);
}

void SDLOpenglRenderer::DrawFillRect(const Rect& rect, const Color& color)
{
    primitiveGLRenderer->drawRect(rect, color, true);
}

void SDLOpenglRenderer::FillCircle(int x, int y, int radius, const Color& color)
{
    primitiveGLRenderer->drawCircle({x, y}, radius, color, 32, true);
}

void SDLOpenglRenderer::DrawTriangle(int  , int  , int  , int  , int  ,
                                     int  , const Color&  )
{
}

void SDLOpenglRenderer::DrawRoundedRect(int , int , int , int ,
                                        int , Color )
{
}

std::shared_ptr<NativeTexture> SDLOpenglRenderer::loadTextureFromImageFile(const char* src,
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

    auto texture = std::make_shared<SDLTexture>();
    texture->id = textureID;

    SDL_FreeSurface(surface);
    return texture;
}

std::shared_ptr<NativeTexture> SDLOpenglRenderer::loadTextureFromImageFile(const char* src)
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

    auto texture = std::make_shared<SDLTexture>();
    texture->id = textureID;

    SDL_FreeSurface(surface);
    return texture;
}

std::shared_ptr<NativeTextRenderer> SDLOpenglRenderer::getTextRenderer()
{
    return  std::make_shared<SDLTTFText>();
}

std::shared_ptr<NativeTexture> SDLOpenglRenderer::createTexture()
{
    return std::make_shared<SDLTexture>();
}

} // namespace doengine