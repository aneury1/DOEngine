#pragma once
#include <SDL.h>
#include "Texture.h"
struct Object
{
protected:
   SDL_Rect offset;
   SDL_Rect clip;
   Texture *texture;
   SDL_Color default_color;
   int dx;
   int dy;

public:
   bool Collide(const Object &other)
   {
       return SDL_HasIntersection(&offset, &other.offset);
   }
   
   enum Position{UP,DOWN,LEFT,RIGHT};
   virtual void Move(int pos)=0;
   virtual void Draw()=0;
   virtual void Update()=0;
};