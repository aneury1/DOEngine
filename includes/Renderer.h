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

#include "Color.h"
#include "Geometric.h"
#include "Texture.h"
#include <variant>
#include <string>
namespace doengine
{
class NativeTexture;
class NativeTextRenderer;
class Renderer
{
  public:
    virtual bool isRenderOk() = 0;
    virtual void* getNativeRenderer() = 0;
    virtual void destroy() = 0;
    virtual void clear() = 0;
    virtual void setDrawColor(const Color&) = 0;
    virtual void updateScreen() = 0;

    virtual void RenderSetClipRect(const Rect& ) = 0;
    virtual void ResetRenderSetClipRect() = 0;

    virtual void DrawTexture(const std::variant<std::string, int> &,int x, int y) = 0;
    virtual void DrawTexture(const std::variant<std::string, int> &,const Rect& ) = 0;
    virtual void DrawTexture(const std::variant<std::string, int>&,const Rect&, const Rect& ) = 0;
    virtual void QueryTexture(const std::variant<std::string, int>&, Rect& info) = 0;



    virtual void DrawPoint(const Point& point, const Color& color) = 0;
    virtual void DrawLine(const Point& p1, const Point& p2,
                          const Color& color) = 0;
    virtual void DrawRect(const Rect& rect, const Color& color) = 0;
    virtual void DrawRect(const Rect& rect, const Color& color, int thickness) = 0;
    virtual void DrawFillRect(const Rect& rect, const Color& color) = 0;
    virtual void FillCircle(int x, int y, int radius, const Color& color) = 0;
    virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                              const Color& p) = 0;
    virtual void DrawRoundedRect(int x, int y, int w, int h, int cornerRadius,
                                 Color color) = 0;
    virtual std::shared_ptr<NativeTexture> loadTextureFromImageFile(const char* src,
                                                    Color color) = 0;
    virtual std::shared_ptr<NativeTexture> loadTextureFromImageFile(const char* src) = 0;
    virtual std::shared_ptr<NativeTextRenderer> getTextRenderer() = 0;

    virtual std::shared_ptr<NativeTexture> createTexture() =0;
};

} // namespace doengine