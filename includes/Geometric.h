#pragma once
// #include "DOEngine.h"


struct Point{
    int x;
    int y;
};
 
struct Rect{
    int x;
    int y;
    int w;
    int h;
    inline int left(){ return x;}
    inline int top(){ return  y;}
    inline int bottom(){ return h+y;}
    inline int right(){ return w+x;}
    inline std::pair<int,int> center(){return {w/2,h/2};}
    template<typename T>
    T castTo(){
        return reinterpret_cast<T>(*this);
    }
};

void DrawPoint(const Point& point, const Color& color);
void DrawLine(const Point& p1, const Point& p2, const Color& color);
void DrawRect(const Rect& rect, const Color& color );
void DrawFillRect(const Rect& rect, const Color& color );
void FillCircle(int x, int y, int radius, const Color& color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  const Color& p);
