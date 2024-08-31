#pragma once
namespace doengine
{

typedef unsigned char ColorT;
struct Color
{
    Color()
    {
        r = g = a = b = 255;
    }
    Color(ColorT r, ColorT g, ColorT b, ColorT a) : r{r}, g{g}, b{b}, a{a}
    {
    }

    ColorT r;
    ColorT g;
    ColorT b;
    ColorT a;
};

static const Color red(255, 0, 0, 255);
static const Color white(255, 255, 255, 255);
static const Color green(10, 255, 0, 255);
static const Color blue(0, 0, 255, 255);
static const Color yellow(100, 155, 0, 255);
static const Color purple(0, 255, 244, 255);
static const Color black(0, 0, 0, 255);
static const Color gold(255, 215, 0, 255);
static const Color gray(100, 100, 100, 255);
static const Color blue5(19, 26, 50, 255);
} // namespace doengine