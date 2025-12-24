#pragma once
#include "Color.h"
#include "Logger.h"
#include <map>
#include <stdint.h>

namespace doengine
{

struct Mat4 {
    float m[16];
    
    Mat4() {
        for (int i = 0; i < 16; i++) m[i] = 0.0f;
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    
    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
        Mat4 result;
        result.m[0] = 2.0f / (right - left);
        result.m[5] = 2.0f / (top - bottom);
        result.m[10] = -2.0f / (far - near);
        result.m[12] = -(right + left) / (right - left);
        result.m[13] = -(top + bottom) / (top - bottom);
        result.m[14] = -(far + near) / (far - near);
        return result;
    }
    
    static Mat4 translate(float x, float y) {
        Mat4 result;
        result.m[12] = x;
        result.m[13] = y;
        return result;
    }
    
    static Mat4 scale(float x, float y) {
        Mat4 result;
        result.m[0] = x;
        result.m[5] = y;
        return result;
    }
    
    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.m[row * 4 + col] = 0.0f;
                for (int i = 0; i < 4; i++) {
                    result.m[row * 4 + col] += m[row * 4 + i] * other.m[i * 4 + col];
                }
            }
        }
        return result;
    }
};



struct Point
{
    int x;
    int y;

    Point() = default;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    const Point& operator=(const Point& p)
    {
        x = p.x;
        y = p.y;
        return (*this);
    }
    const Point& operator=(const int p)
    {
        x = p;
        y = p;
        return (*this);
    }

    const Point& operator+(float pxy)
    {
        x += pxy;
        y += pxy;
        return (*this);

    }

    const Point& operator+(int pxy)
    {
        x += pxy;
        y += pxy;
        return (*this);

    }
    const Point& operator+(const Point& pxy)
    {
        x += pxy.x;
        y += pxy.y;
        return (*this);

    }
    const Point& operator+=(const Point& pxy)
    {
        x += pxy.x;
        y += pxy.y;
        return (*this);

    }

    const Point& operator*(float pxy)
    {
        x += pxy;
        y += pxy;
        return (*this);
    }

    const Point& operator*(int pxy)
    {
        x += pxy;
        y += pxy;
        return (*this);
    }
    const Point& operator*(const Point& pxy)
    {
        x += pxy.x;
        y += pxy.y;
        return (*this);
    }
    const Point& operator*=(const Point& pxy)
    {
        x += pxy.x;
        y += pxy.y;
        return (*this);
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
    Rect(int x, int y, int w, int h) : x{x}, y{y}, w{w}, h{h}
    {
    }

    Rect& operator=(const Rect& other)
    {
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
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
    inline void LogIt()
    {
        LogOuput(logger_type::Information, "[%d, %d, %d %d]", x, y, w, h);
    }
};

void DrawPoint(const Point& point, const Color& color);
void DrawLine(const Point& p1, const Point& p2, const Color& color);
void DrawRect(const Rect& rect, const Color& color);
void DrawFillRect(const Rect& rect, const Color& color);
void FillCircle(int x, int y, int radius, const Color& color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  const Color& p);

bool checkPointOnRect(Point point, Rect rect);
bool checkCollision(const Rect& rect1, const Rect& rect2);
bool checkCollisionPointVsRect(const Rect& rect, const Point point);
bool checkCollisionCircleRec(const Point& cicle, float radius,
                             const Rect& rect);
bool isPointOnRectBorder(int mx, int my, const doengine::Rect& r,
                         int thickness = 1);

void generateCirclePoints(Point center, double r, int steps, Point* out);

/// @brief mention, idea taken from
/// https://www.youtube.com/watch?v=3CWsy4kP6wU&t=24s
struct CircleGenerator
{
    float radius = 0.0f;
    uint32_t quality;
    float const da = 0.0f;

    CircleGenerator(float rad, uint32_t quality);

    Point getPoint(uint32_t i);
};

} // namespace doengine