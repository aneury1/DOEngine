#pragma once

typedef unsigned char ColorT;
union Color {
    struct
    {
        ColorT r;
        ColorT g;
        ColorT b;
        ColorT a;
    };
    unsigned int rgba;
};

static const Color red(255,0,0,255);
static const Color white(255,255,255,255);
static const Color green(0,255,0,255);
static const Color blue(0,0,255,255);
static const Color yellow(100,155,0,255);
static const Color purple(0,255,244,255);
