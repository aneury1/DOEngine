#include "Geometric.h"
#include <SDL2/SDL.h>
#include <cmath>
namespace doengine
{

bool checkCollisionPointVsRect(const Rect& rect, const Point point)
{
    return (point.x >= rect.x && point.y >= rect.y && point.y <= rect.h &&
            point.x <= rect.w);
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

}; // namespace doengine