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


#include "SDLRenderer.h"
#include "Logger.h"
#include "SDLTTFText.h"
#include "SDLTexture.h"

namespace doengine
{

SDLRenderer::SDLRenderer(SDL_Renderer* nativeRenderer)
    : renderer(nativeRenderer)
{
}

bool SDLRenderer::isRenderOk()
{
    return renderer != NULL;
}

void* SDLRenderer::getNativeRenderer()
{
    return static_cast<void*>(renderer);
}

void SDLRenderer::destroy()
{
    if (isRenderOk() || renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

}

void SDLRenderer::clear()
{
    SDL_RenderClear(renderer);
}

void SDLRenderer::setDrawColor(const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SDLRenderer::updateScreen()
{
    SDL_RenderPresent(renderer);
}

void SDLRenderer::RenderSetClipRect(const Rect& rect)
{
    SDL_Rect rectx{rect.x, rect.y, rect.w,rect.h};
    SDL_RenderSetClipRect(renderer, &rectx);
}

void SDLRenderer::ResetRenderSetClipRect()
{
    SDL_RenderSetClipRect(renderer, nullptr);
}

void SDLRenderer::DrawPoint(const Point& point, const Color& color)
{
    this->setDrawColor(color);
    SDL_RenderDrawPoint(renderer, point.x, point.y);
}
void SDLRenderer::DrawLine(const Point& p1, const Point& p2, const Color& color)
{
    this->setDrawColor(color);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}
void SDLRenderer::DrawRect(const Rect& rect, const Color& color)
{
    this->setDrawColor(color);
    SDL_Rect rect1;
    rect1.w = rect.w;
    rect1.h = rect.h;
    rect1.x = rect.x;
    rect1.y = rect.y;
    SDL_RenderDrawRect(renderer, &rect1);
    int border = 0;
    for (auto i = 0; i < border; i++)
    {
        rect1.x += 1;
        rect1.y += 1;
        rect1.w -= 1;
        rect1.h -= 1;
    }
}
void SDLRenderer::DrawFillRect(const Rect& rect, const Color& color)
{
    this->setDrawColor(color);
    SDL_Rect rect1;
    rect1.w = rect.w;
    rect1.h = rect.h;
    rect1.x = rect.x;
    rect1.y = rect.y;
    SDL_RenderFillRect(renderer, &rect1);
}

void SDLRenderer::DrawRect(const Rect& rect, const Color& color, int thickness)
{
    if (thickness <= 0)
        return;

    // Set draw color
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        color.a
    );

    // Draw rectangle borders by expanding inward
    for (int i = 0; i < thickness; ++i)
    {
        SDL_Rect r;
        r.x = rect.x + i;
        r.y = rect.y + i;
        r.w = rect.w - (i * 2);
        r.h = rect.h - (i * 2);

        // Avoid invalid rects
        if (r.w <= 0 || r.h <= 0)
            break;

        SDL_RenderDrawRect(renderer, &r);
    }
}

void SDLRenderer::FillCircle(int x, int y, int radius, const Color& color)
{
    this->setDrawColor(color);
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    if (!radius)
        return;

    auto drawline = [&](int sx, int ex, int ny) {
        for (int i = sx; i <= ex; i++)
            DrawPoint({i, ny}, color);
    };

    while (y0 >= x0)
    {

        drawline(x - x0, x + x0, y - y0);
        drawline(x - y0, x + y0, y - x0);
        drawline(x - x0, x + x0, y + y0);
        drawline(x - y0, x + y0, y + x0);
        if (d < 0)
            d += 4 * x0++ + 6;
        else
            d += 4 * (x0++ - y0--) + 10;
    }
}
void SDLRenderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                               const Color& p)
{
    this->setDrawColor(p);
    DrawLine({x1, y1}, {x2, y2}, p);
    DrawLine({x2, y2}, {x3, y3}, p);
    DrawLine({x3, y3}, {x1, y1}, p);
}

std::shared_ptr<NativeTexture> SDLRenderer::loadTextureFromImageFile(const char* src,
                                                     Color  )
{
    auto texture = std::make_shared<SDLTexture>();
    return texture->loadFromFile(src);
}

std::shared_ptr<NativeTexture> SDLRenderer::loadTextureFromImageFile(const char* src)
{
    auto texture = std::make_shared<SDLTexture>();
    return texture->loadFromFile(src);
}
 
std::shared_ptr<NativeTexture> SDLRenderer::createTexture()
{
    return std::make_shared<SDLTexture>();   
}

std::shared_ptr<NativeTextRenderer> SDLRenderer::getTextRenderer()
{
    auto textRenderer = std::make_shared<doengine::SDLTTFText>();
    return textRenderer;
}
void SDLRenderer::DrawTexture(const std::variant<std::string, int> &id,int x, int y)
{
    auto text = TextureManager::getTextureManager()->getTexture(id);
    if(text)
        text->Draw(x,y);
}
void SDLRenderer::DrawTexture(const std::variant<std::string, int>& id,const Rect& offset)
{
    auto text = TextureManager::getTextureManager()->getTexture(id);
    if(text)
        text->Draw(offset);
}
void SDLRenderer::DrawTexture(const std::variant<std::string, int>&id,const Rect& offset, const Rect& clipset )
{
    auto text = TextureManager::getTextureManager()->getTexture(id);
    if(text)
        text->Draw(offset, clipset);
}

void SDLRenderer::QueryTexture(const std::variant<std::string, int>& id, Rect& info)
{
    auto text = TextureManager::getTextureManager()->getTexture(id);
    if(text)
    {
        info.w = text->getWidth();
        info.h = text->getHeight();
    }
}

void renderFilledCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    for (int dy = -radius; dy <= radius; ++dy)
    {
        for (int dx = -radius; dx <= radius; ++dx)
        {
            if (dx * dx + dy * dy <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void renderRoundedRect(SDL_Renderer* renderer, int x, int y, int w, int h,
                       int cornerRadius, Color color)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);

    renderFilledCircle(renderer, x + cornerRadius, y + cornerRadius,
                       cornerRadius);

    renderFilledCircle(renderer, x + w - cornerRadius, y + cornerRadius,
                       cornerRadius);

    renderFilledCircle(renderer, x + cornerRadius, y + h - cornerRadius,
                       cornerRadius);

    renderFilledCircle(renderer, x + w - cornerRadius, y + h - cornerRadius,
                       cornerRadius);

    SDL_Rect topRect = {x + cornerRadius, y, w - 2 * cornerRadius,
                        cornerRadius};
    SDL_Rect bottomRect = {x + cornerRadius, y + h - cornerRadius,
                           w - 2 * cornerRadius, cornerRadius};
    SDL_RenderFillRect(renderer, &topRect);
    SDL_RenderFillRect(renderer, &bottomRect);

    SDL_Rect leftRect = {x, y + cornerRadius, cornerRadius,
                         h - 2 * cornerRadius};
    SDL_Rect rightRect = {x + w - cornerRadius, y + cornerRadius, cornerRadius,
                          h - 2 * cornerRadius};
    SDL_RenderFillRect(renderer, &leftRect);
    SDL_RenderFillRect(renderer, &rightRect);

    SDL_Rect inRect;
    int tenPercentH = w * 0.04;
    int tenPercentV = h * 0.04;
    inRect.x = x + tenPercentH;
    inRect.y = y + tenPercentV;
    inRect.w = w - tenPercentH - 5;
    inRect.h = h - tenPercentV - 5;
    SDL_RenderFillRect(renderer, &inRect);
}

void SDLRenderer::DrawRoundedRect(int x, int y, int w, int h, int cornerRadius,
                                  Color color)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    renderRoundedRect(renderer, x, y, w, h, cornerRadius, color);
}

}; // namespace doengine