#include "Geometric.h"
#include <cmath>

namespace doengine
{

bool checkCollision(const Rect& rect1, const Rect& rect2)
{
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
}

}; // namespace doengine