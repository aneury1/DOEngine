
/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */
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
    Color(ColorT rp, ColorT gp, ColorT bp, ColorT ap) : r{rp}, g{gp}, b{bp}, a{ap}
    {
    }

    ColorT r;
    ColorT g;
    ColorT b;
    ColorT a;


    [[nodiscard]]
    static Color opposite(const Color& color) noexcept
    {
        return Color{
            static_cast<ColorT>(255 - color.r),
            static_cast<ColorT>(255 - color.g),
            static_cast<ColorT>(255 - color.b),
            color.a
        };
    }

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