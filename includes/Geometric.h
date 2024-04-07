#pragma once
// #include "DOEngine.h"


extern "C"
{
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
}

typedef SDL_Rect Rect;
typedef SDL_Color Color;
typedef SDL_Point Point;

void DrawPoint(const Point& point, const Color& color);
void DrawLine(const Point& p1, const Point& p2, const Color& color);
void DrawRect(const Rect& rect, const Color& color );
void DrawFillRect(const Rect& rect, const Color& color );
void FillCircle(int x, int y, int radius, const Color& color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  const Color& p);
