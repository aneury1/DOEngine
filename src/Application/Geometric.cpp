#include "Geometric.h"
#include "DOEngine_SDL_includes.h"
#include <cmath>
namespace doengine
{



bool checkCollisionPointVsRect(const Rect& rect, const Point point)
{
    return (point.x >= rect.x &&
            point.x <= rect.x + rect.w &&
            point.y >= rect.y &&
            point.y <= rect.y + rect.h);
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

    /*
     float center1_x = (rect1.left() + rect1.right()) / 2;
     float center1_y = (rect1.top() + rect1.bottom()) / 2;

     float center2_x = (rect2.left() + rect2.right()) / 2;
     float center2_y = (rect2.top() + rect2.bottom()) / 2;
     float half_width1 = (rect1.right() - rect1.left()) / 2;
     float half_height1 = (rect1.bottom() - rect1.top()) / 2;

     float half_width2 = (rect2.right() - rect2.left()) / 2;
     float half_height2 = (rect2.bottom() - rect2.top()) / 2;
     float dist_x = abs(center1_x - center2_x);
     float dist_y = abs(center1_y - center2_y);

     float min_dist_x = half_width1 + half_width2;
     float min_dist_y = half_height1 + half_height2;

     bool col = dist_x < min_dist_x && dist_y < min_dist_y;
     return col;
     */
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

CircleGenerator::CircleGenerator(float rad, uint32_t quality):
    radius{rad},
    quality{quality},
    da{(2.0f * M_PI)/static_cast<float>(quality)}
{
}

Point CircleGenerator::getPoint(uint32_t i)
{
    float angle{da  * static_cast<float>(i)};
    return {(radius * cos(angle)),( radius * sin(angle)) };
}


}; // namespace doengine