#include <SDL.h>
#include <math.h>

#include "Window.h"
#include "GeometricRender.h"

void DrawPoint(const Point& p, const Color& c )
{
    extern Window *window;
    SDL_SetRenderDrawColor(window->getRender(), c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(window->getRender(), p.x , p.y);
}

void DrawRect(const Rect &r, const Color &c, bool filled)
{
    extern Window *window;
    SDL_SetRenderDrawColor(window->getRender(), c.r, c.g, c.b, c.a);
    SDL_Rect rect={r.x, r.y, r.w, r.h};
    if(filled)
    {
        SDL_RenderFillRect(window->getRender(), &rect);
    }
    else
    {
        SDL_RenderDrawRect(window->getRender(), &rect);
    }
}

void DrawLine(const Point& p1, const Point& p2, const Color& c)
{
   extern Window *window;
   SDL_SetRenderDrawColor(window->getRender(), c.r, c.g, c.b, c.a);
   SDL_RenderDrawLine(window->getRender(), p1.x, p1.y, p2.x,p2.y);
}

void DrawTriangle(const Point& p1, const Point& p2,  const Point& p3,const Color& c )
{
   DrawLine(p1,p2,c);
   DrawLine(p2,p3,c);
   DrawLine(p3,p1,c);
}




void Spline::Draw()
{
    extern Window *window;
    SDL_SetRenderDrawColor(window->getRender(), this->color->r, color->g, color->b, 255);
    for(auto it : points)
    {

    }


}



