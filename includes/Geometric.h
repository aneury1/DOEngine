#pragma once

#include "DOEngine_SDL_includes.h"
#include "abstract/AbstractWindow.h"
#include "v2d_vector.h"

typedef SDL_Rect Rect;
typedef SDL_Color Color;

void DrawPoint(const Point& point, const Color& color);
void DrawLine(const Point& p1, const Point& p2, const Color& color);
void DrawRect(const Rect& rect, const Color& color );
void DrawFillRect(const Rect& rect, const Color& color );
void FillCircle(int x, int y, int radius, const Color& color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  const Color& p);
