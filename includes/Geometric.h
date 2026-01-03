#pragma once

#include "Color.h"
#include <map>

namespace doengine
{
struct Point
{
    int x;
    int y;

    Point()=default;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

struct Rect
{
    int x;
    int y;
    int w;
    int h;
    Rect()
    {
        x = y = w = y = 10;
    }
    Rect(int w, int h) : x{0}, y{0}, w{w}, h{h}
    {
    }
    Rect(int x, int y,int w, int h) : x{x}, y{y}, w{w}, h{h}
    {
    }


    Rect& operator=(const Rect& other)
    {
        x= other.x;
        y= other.y;
        w= other.w;
        h= other.h;
        return (*this);
    }

    inline int left() const
    {
        return x;
    }
    inline int top() const
    {
        return y;
    }
    inline int bottom() const
    {
        return h + y;
    }
    inline int right() const
    {
        return w + x;
    }
    /* inline std::pair<int, int> center()
     {
         return {w / 2, h / 2};
     }*/
    template <typename T>
    T castTo()
    {
        return reinterpret_cast<T>(*this);
    }
};

void DrawPoint(const Point& point, const Color& color);
void DrawLine(const Point& p1, const Point& p2, const Color& color);
void DrawRect(const Rect& rect, const Color& color);
void DrawFillRect(const Rect& rect, const Color& color);
void FillCircle(int x, int y, int radius, const Color& color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  const Color& p);

bool checkCollision(const Rect& rect1, const Rect& rect2);
bool checkCollisionPointVsRect(const Rect& rect, const Point point);
bool checkCollisionCircleRec(const Point& cicle, float radius, const Rect& rect );
bool isPointOnRectBorder(int mx, int my, const doengine::Rect& r, int thickness = 1);

void generateCirclePoints(Point center, double r,
                            int steps, Point *out);


} // namespace doengine