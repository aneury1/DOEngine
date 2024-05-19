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
    if (isRenderOk())
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
    /// DO_TRACE("SDLRenderer::updateScreen");
    SDL_RenderPresent(renderer);
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
        // Modified to draw scan-lines instead of edges
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

NativeTexture* SDLRenderer::loadTextureFromImageFile(const char* src,
                                                     Color color)
{
    auto texture = new SDLTexture();
    return texture->loadFromFile(src);
}

NativeTextRenderer* SDLRenderer::getTextRenderer()
{
    auto textRenderer = new SDLTTFText();
    return textRenderer;
}

// Function to render a filled circle
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

// Function to render a rounded rectangle
void renderRoundedRect(SDL_Renderer* renderer, int x, int y, int w, int h,
                       int cornerRadius, Color color)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    /// SDL_RenderDrawRect(renderer, &rect);

    // Render top-left corner
    renderFilledCircle(renderer, x + cornerRadius, y + cornerRadius,
                       cornerRadius);

    // Render top-right corner
    renderFilledCircle(renderer, x + w - cornerRadius, y + cornerRadius,
                       cornerRadius);

    // Render bottom-left corner
    renderFilledCircle(renderer, x + cornerRadius, y + h - cornerRadius,
                       cornerRadius);

    // Render bottom-right corner
    renderFilledCircle(renderer, x + w - cornerRadius, y + h - cornerRadius,
                       cornerRadius);

    // Render top and bottom rectangles
    SDL_Rect topRect = {x + cornerRadius, y, w - 2 * cornerRadius,
                        cornerRadius};
    SDL_Rect bottomRect = {x + cornerRadius, y + h - cornerRadius,
                           w - 2 * cornerRadius, cornerRadius};
    SDL_RenderFillRect(renderer, &topRect);
    SDL_RenderFillRect(renderer, &bottomRect);

    // Render left and right rectangles
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