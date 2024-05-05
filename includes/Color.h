#pragma once

typedef unsigned char ColorT;
typedef unsigned int  ColorL;
struct Color {
    
    ColorT r;
    ColorT g;
    ColorT b;
    ColorT a;
    
    Color(){
        r=g=b=0;
        a=255;
    }
    Color(ColorT c){
        r=g=b=a=c;
    }
    Color(ColorT r, ColorT g, ColorT b, ColorT a){
        this->r=r;
        this->g=g;
        this->b=b;
        this->a=a;
    }
    Color(ColorL c){
        r = (c >> 24) & 0xFF;
        g = (c >> 16) & 0xFF;
        b = (c >> 8) & 0xFF;
        a =  c & 0xFF;
    }
    Color(const Color& color){
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
    Color operator=(const Color& color){
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
        return *this;
    }
 
};

static const Color red(255,0,0,255);
static const Color white(255,255,255,255);
static const Color green(0,255,0,255);
static const Color blue(0,0,255,255);
static const Color yellow(100,155,0,255);
static const Color purple(0,255,244,255);