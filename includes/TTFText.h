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
#include <string>

#include "Application.h"
#include "Color.h"
#include "DOEngine.h"
#include "Geometric.h"
#include "Texture.h"

using std::string;

namespace doengine
{
class NativeBitmapTextRenderer;
class NativeTextRenderer;
class Texture;
class Renderer;
class TTFText
{

    std::shared_ptr<NativeTextRenderer> nativeRenderer;
    NativeBitmapTextRenderer* nativeBitmapRenderer;

  public:
    TTFText();
    void setColor(Color color);
    void setForegroundColor(const Color& color);
    void setFont(const std::string& path, int fntsize);
    void DrawText(const char* text, int x, int y);
    void DrawText(int x, int y, const char *fmt, ...);
    std::shared_ptr<Texture> createText(const std::string& text);
    void   wrapText(const char* text, int maxWidth, char* wrappedText);
    std::shared_ptr<Texture>  createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg);

    int getFontHeight();
};

} // namespace doengine

