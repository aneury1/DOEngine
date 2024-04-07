#pragma once

#include "Color.h"
#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include <vector>

struct CanvasCommand
{
    virtual void Draw() = 0;
};

struct CanvasRectCommand : public CanvasCommand
{
    SDL_Rect offset;
    SDL_Color color;
    bool filled;
    virtual void Draw() override;
};

struct CanvasPointDrawCommand : public CanvasCommand
{
    SDL_Rect offset;
    SDL_Color color;
    virtual void Draw() override;
};

struct CanvasCircleCommand : public CanvasCommand
{

    double radius;
    SDL_Point where;
    SDL_Color color;

    virtual void Draw() override;
};

struct CanvasTextDrawerCommand : public CanvasCommand
{

    SDL_Point where;
    doengine::Color color;
    std::string text;
    virtual void Draw() override;
};

class Canvas
{
    SDL_Color _bg;
    SDL_Color _filler;
    SDL_Rect _offset;
    bool clear = false;

    std::vector<CanvasCommand*> commands_to_draw;

  public:
    const static SDL_Color black;

    Canvas();

    Canvas* fillColor(SDL_Color color);
    Canvas* setRect(SDL_Rect rect);

    Canvas* DrawRect(int x, int y, int w, int h, bool filled);
    Canvas* DrawPoint(int x, int y);
    Canvas* FillCircle(int x, int y, double rsize = 50);
    Canvas* FillText(const char* str, int x, int y);

    Canvas* setCanvasBackgroundColor(SDL_Color color);
    Canvas* update();
    Canvas* clearCanvas();

    void getColor(SDL_Color* color)
    {
        color = &_filler;
    }

    const SDL_Rect getCanvasSize() const
    {
        return _offset;
    }
};


// Create a gradient color between two colors at a specific position
SDL_Color GradientColor(SDL_Color startColor, SDL_Color endColor,
                        float position)
{
    SDL_Color result;
    result.r = startColor.r + (endColor.r - startColor.r) * position;
    result.g = startColor.g + (endColor.g - startColor.g) * position;
    result.b = startColor.b + (endColor.b - startColor.b) * position;
    result.a = startColor.a + (endColor.a - startColor.a) * position;
    return result;
}

// Draw a horizontal line on the renderer with a gradient
void DrawGradientHorizontalLine(SDL_Renderer* renderer, int x, int y, int width,
                                SDL_Color startColor, SDL_Color endColor)
{
    for (int i = 0; i < width; i++)
    {
        float position =
            (float)i /
            (float)(width - 1); // Normalized position for the gradient
        SDL_Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x + i, y);
    }
}

// Draw a gradient-filled rectangle on the renderer
void DrawGradientRect(SDL_Renderer* renderer, int x, int y, int width,
                      int height, SDL_Color startColor, SDL_Color endColor)
{
    for (int i = 0; i < height; i++)
    {
        float position =
            (float)i /
            (float)(height - 1); // Normalized position for the gradient
        SDL_Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, y + i, x + width - 1, y + i);
    }
}

// Draw a gradient-filled circle on the renderer
void DrawGradientCircle(SDL_Renderer* renderer, int centerX, int centerY,
                        int radius, SDL_Color startColor, SDL_Color endColor)
{
    for (int y = centerY - radius; y <= centerY + radius; y++)
    {
        for (int x = centerX - radius; x <= centerX + radius; x++)
        {
            float distance = sqrtf((x - centerX) * (x - centerX) +
                                   (y - centerY) * (y - centerY));
            if (distance <= radius)
            {
                float position =
                    distance / radius; // Normalized position for the gradient
                SDL_Color color = GradientColor(startColor, endColor, position);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                                       color.a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}
