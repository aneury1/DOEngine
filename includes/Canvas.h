#pragma once

#include "Color.h"
#include "Renderer.h"
#include <cmath>
#include <string>
#include <vector>

#ifdef TODO

struct CanvasCommand
{
    virtual void Draw() = 0;
};

struct CanvasRectCommand : public CanvasCommand
{
    Rect offset;
    Color color;
    bool filled;
    virtual void Draw() override;
};

struct CanvasPointDrawCommand : public CanvasCommand
{
    Rect offset;
    Color color;
    virtual void Draw() override;
};

struct CanvasCircleCommand : public CanvasCommand
{

    double radius;
    Point where;
    Color color;

    virtual void Draw() override;
};

struct CanvasTextDrawerCommand : public CanvasCommand
{

    Point where;
    Color color;
    std::string text;
    virtual void Draw() override;
};

class Canvas
{
    Color _bg;
    Color _filler;
    Rect _offset;
    bool clear = false;

    std::vector<CanvasCommand*> commands_to_draw;

  public:
    const static Color black;

    Canvas();

    Canvas* fillColor(Color color);
    Canvas* setRect(Rect rect);

    Canvas* DrawRect(int x, int y, int w, int h, bool filled);
    Canvas* DrawPoint(int x, int y);
    Canvas* FillCircle(int x, int y, double rsize = 50);
    Canvas* FillText(const char* str, int x, int y);

    Canvas* setCanvasBackgroundColor(Color color);
    Canvas* update();
    Canvas* clearCanvas();

    void getColor(Color* color)
    {
        color = &_filler;
    }

    const Rect getCanvasSize() const
    {
        return _offset;
    }
};

// Create a gradient color between two colors at a specific position
Color GradientColor(Color startColor, Color endColor, float position)
{
    Color result;
    result.r = startColor.r + (endColor.r - startColor.r) * position;
    result.g = startColor.g + (endColor.g - startColor.g) * position;
    result.b = startColor.b + (endColor.b - startColor.b) * position;
    result.a = startColor.a + (endColor.a - startColor.a) * position;
    return result;
}

// Draw a horizontal line on the renderer with a gradient
void DrawGradientHorizontalLine(Renderer* renderer, int x, int y, int width,
                                Color startColor, Color endColor)
{
    for (int i = 0; i < width; i++)
    {
        float position =
            (float)i /
            (float)(width - 1); // Normalized position for the gradient
        Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x + i, y);
    }
}

// Draw a gradient-filled rectangle on the renderer
void DrawGradientRect(Renderer* renderer, int x, int y, int width, int height,
                      Color startColor, Color endColor)
{
    for (int i = 0; i < height; i++)
    {
        float position =
            (float)i /
            (float)(height - 1); // Normalized position for the gradient
        Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, y + i, x + width - 1, y + i);
    }
}

// Draw a gradient-filled circle on the renderer
void DrawGradientCircle(Renderer* renderer, int centerX, int centerY,
                        int radius, Color startColor, Color endColor)
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
                Color color = GradientColor(startColor, endColor, position);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                                       color.a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

#endif