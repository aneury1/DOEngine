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
#include <memory>
#include "Geometric.h"
#include "Texture.h"
namespace doengine
{
struct GlyphInfo
{
    Rect src;
    int advance;
};

class Texture;

struct NativeTexture
{
    int id;
    Rect rectSize;
    virtual ~NativeTexture(){}
    NativeTexture(){}
  
    virtual std::shared_ptr<NativeTexture> subTexture(Rect clipset) = 0;
    virtual std::shared_ptr<NativeTexture> setNativeTexture(void *text) = 0;
    virtual std::shared_ptr<NativeTexture> loadFromFile(const char* src) = 0;
    virtual void Draw(int x, int y) = 0;
    virtual void Draw(const Rect& offset) = 0;
    virtual void Draw(const Rect& offset, const Rect& clipset) = 0;
    virtual void SetTransparentColor(const Color& color) = 0;
    virtual void Draw(const Rect& offset, const Rect& clipset,
                      const double angle) = 0;
    virtual void Draw(const Rect& offset, const Rect& clipset,
                      const double angle, const Point& center) = 0;
    virtual void ModulateColor(const Color& color) = 0;
    virtual void Destroy() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual bool validTexture() = 0;

    virtual void* getNativeBuffer() = 0;
};

struct NativeTextRenderer
{
    virtual int getFontHeight() = 0;
    virtual Rect getTextSize(const char* str) = 0;
    virtual void setColor(doengine::Color fg, doengine::Color bg) = 0;
    virtual void setColor(doengine::Color color) = 0;
    virtual void setFont(const std::string& path, int fntsize) = 0;
    virtual void DrawText(const char* text, int x, int y) = 0;
    virtual void getTextSize(const std::string& text, int* w, int* h) = 0;
    virtual void setFontSize(int fntSize) = 0;
    virtual void setForegroundColor(doengine::Color color) = 0;
    virtual void setBackgroundColor(doengine::Color color) = 0;
    virtual std::shared_ptr<Texture> createText(const std::string& text) = 0;
    virtual void wrapText(const char* text, int maxWidth, char* wrappedText) =0;
    virtual std::shared_ptr<Texture>  createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg)= 0;
};

struct NativeBitmapTextRenderer
{
    enum class Alignment
    {
        Left,
        Center,
        Right
    };
};

} // namespace doengine
