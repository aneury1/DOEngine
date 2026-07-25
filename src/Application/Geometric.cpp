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
#include "Geometric.h"
#include "DOEngine_SDL_includes.h"
#include <cmath>
namespace doengine
{

bool checkCollisionPointVsRect(const Rect& rect, const Point point)
{
    return checkPointOnRect(point, rect);
    ////const float right  = rect.x + rect.w;
    ///const float bottom = rect.y + rect.h;
    ///return point.x >= rect.x && point.x < right &&
    ////       point.y >= rect.y && point.y < bottom;
}

bool checkPointOnRect(Point point, Rect rect)
{
    SDL_Point p{point.x, point.y};
    SDL_Rect  r{rect.x, rect.y, rect.w, rect.h};
    return SDL_PointInRect(&p, &r);
}

bool checkCollision(const Rect& rect1, const Rect& rect2)
{

    SDL_Rect o;
    SDL_Rect i;
    o.x = rect1.x;
    o.y = rect1.y;
    o.w = rect1.w;
    o.h = rect1.h;
    i.x = rect2.x;
    i.y = rect2.y;
    i.w = rect2.w;
    i.h = rect2.h;
    return SDL_HasIntersection(&o, &i);

}

bool checkCollisionCircleRec(const Point& circle, float radius, const Rect& rect ){
        // Find the closest point on the rectangle to the circle center.
    float closestX = std::max(rect.x, std::min(circle.x, rect.x + rect.w));
    float closestY = std::max(rect.y, std::min(circle.y, rect.y + rect.h));

    // Calculate the distance between the circle's center and this closest point.
    float dx = circle.x - closestX;
    float dy = circle.y - closestY;

    // If the distance is less than the circle's radius, an intersection occurs.
    return (dx * dx + dy * dy) <= (radius * radius);
}

bool isPointOnRectBorder(int mx, int my, const doengine::Rect& r, int thickness)
{
    bool insideX = (mx >= r.x && mx <= r.x + r.w);
    bool insideY = (my >= r.y && my <= r.y + r.h);

    if (!insideX || !insideY)
        return false;

    bool onLeft   = (mx >= r.x && mx <= r.x + thickness);
    bool onRight  = (mx >= r.x + r.w - thickness && mx <= r.x + r.w);
    bool onTop    = (my >= r.y && my <= r.y + thickness);
    bool onBottom = (my >= r.y + r.h - thickness && my <= r.y + r.h);

    return onLeft || onRight || onTop || onBottom;
}

void generateCirclePoints(Point center, double r,
                            int steps, Point *out)
{
    for (int i = 0; i < steps; ++i) {
        double theta = (2.0 * M_PI * i) / steps;
        out[i].x = center.x + r * cos(theta);
        out[i].y = center.y + r * sin(theta);
    }
}

std::vector<CollisionPosition> checkCollisionBySide(const Rect& src, const Rect& object)
{
    std::vector<CollisionPosition> ret;
    if(checkCollision(src, object))
    {
 

    }
    return ret;
}


CircleGenerator::CircleGenerator(float rad, uint32_t quality):
    radius{rad},
    quality{quality},
    da{static_cast<int>(2.0f * M_PI)/static_cast<float>(quality)}
{
}

Point CircleGenerator::getPoint(uint32_t i)
{
    float angle{da  * static_cast<float>(i)};
    return {static_cast<int>(radius * cos(angle)),static_cast<int>(radius * sin(angle)) };
}


}; // namespace doengine