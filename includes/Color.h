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

namespace Colors{
    static const Color red(255, 0, 0, 255);
    static const Color white(255, 255, 255, 255);
    static const Color green(10, 255, 0, 255);
    static const Color blue(0, 0, 255, 255);
    static const Color yellow(243, 216, 64, 255);
    static const Color yellow1(100, 155, 0, 255);
    static const Color purple(0, 255, 244, 255);
    static const Color purple1(166, 0, 247, 255);
    static const Color black(0, 0, 0, 255);
    static const Color black1(0x43, 0x43, 0x43, 255);
    static const Color black2(0x60, 0x60, 0x60, 255);
    static const Color black3(0x90, 0x90, 0x90, 255);
    static const Color gold(255, 215, 0, 255);
    static const Color gray(100, 100, 100, 255);
    static const Color darkGrey(26, 31, 40, 255);
    static const Color blue5(19, 26, 50, 255);
    static const Color orange(226,116,17,255);
    static const Color cyan(21,204,209,255);
    static const Color skyBlue(77, 216, 255, 255);
}

template<typename D>
D toColor(const Color& o){
    D t;
    t.r = o.r;
    t.g = o.g;
    t.b = o.b;
    t.a = o.a;
    return t;
}


} // namespace doengine