#pragma once
#include <map>
#include <SDL.h>
#include "Window.h"
 
struct DrawConfiguration
{
   SDL_Rect  offset;
   SDL_Rect  clip;
   SDL_Point point;
   SDL_Surface *sf;
   SDL_Texture *texture;
   SDL_Renderer *render;
   SDL_Color original_color;
   SDL_Color mod_color;
   float angle;
   int id; 
   bool valid;
   DrawConfiguration();
};

enum
{
    ARKANOID_SPRITE = 0, 
    BALL_SPRITE,
    
    DOODLE_SPRITE,
    PLATFORM_SPRITE,

    GREEN_SPRITE,
    RED_SPRITE,
    WHITE_SPRITE,


    TOTAL_TEXTURE_LOADED
};


class Texture
{
    DrawConfiguration *texture_config;

    void extract_orginal_mod();

public:

    Texture(const char *src);
    Texture(const char *src,SDL_Color color);
    ~Texture();
    
    int getW();
    int getH();

    void Draw(int x, int y, int w, int h);
    void Draw(int x, int y, int w, int h, int cx, int cy, int cw, int ch);

   static std::map<int, Texture *>texture_ints;
   static bool LoadTexture(int id, const char *path);
   static void DrawTexture(int id, Rect offset, Rect clip, float *angle=nullptr, Point *point=nullptr, bool flipped = false);
   static Texture *getTexture(int id){
       return texture_ints[id];
   }
};


