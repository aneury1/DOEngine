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

#include "SelectionRect.h"

namespace doengine
{

 void SelectionRect::setup()
 {
    if(!font)
        font = std::make_shared<doengine::TTFText>();
   if(!fontsrc.empty())
      font->setFont(fontsrc, 18);
   else
   {
 
   }
 }

SelectionRect::SelectionRect():
 font{nullptr}
{
  setup();
}

SelectionRect::~SelectionRect()
{
}

doengine::Rect SelectionRect::NormalizeRect(const doengine::Rect& a,
                                            const doengine::Rect& b)
{
    doengine::Rect r;
    r.x = std::min(a.x, b.x);
    r.y = std::min(a.y, b.y);
    r.w = std::abs(a.x - b.x);
    r.h = std::abs(a.y - b.y);
    return r;
}

void SelectionRect::setFont(const std::string& font)
{
    this->fontsrc = font;

    if(!this->font)
        setup();
    else
    {
        this->font->setFont(font, 18);
    }
}

void SelectionRect::startDraggingPoint(const doengine::Rect& start)
{
    if (!function_active)
        return;
    this->start.x = start.x;
    this->start.y = start.y;
}

void SelectionRect::updateCoords(const doengine::Rect& rect)
{
    if (function_active && active)
    {
        this->current.x = rect.x;
        this->current.y = rect.y;
    }
}

void SelectionRect::Render()
{
    if (!function_active)
    {
        return;
    }
    auto rect = NormalizeRect(start, current);
    renderer->DrawRect(rect, doengine::Colors::red);
    /// if(active)
    {
        int y = rect.y - 32;
        if (y <= 16)
            y = rect.y + 64;
        
        font->DrawText(rect.x, y, "(%d,%d, %d, %d)", rect.x, rect.y, rect.w, rect.h);

        if(onSelectionFinished)
        {
            ///LogOuput(logger_type::Error, "Calling Selection Rect Callback:[%d, %d, %d, %d]", 
            ////    rect.x, rect.y, rect.w, rect.h);
           //// onSelectionFinished({rect.x, rect.y, rect.w, rect.h});
        }
    }
}

void SelectionRect::OnKeydown(const Keyboard& keyboard)
{

    auto key = keyboard.getKeysBitset();

    if (key[SCANCODE_ESCAPE])
    {
        function_active = (!function_active);
    }
}

void SelectionRect::OnKeyup(const Keyboard&  )
{
}

void SelectionRect::MouseMove(const Mouse& mouse)
{
    if (function_active && active)
    {
        updateCoords({mouse.getMousePosition()});
    }
}
void SelectionRect::MouseButtonDown(const Mouse& mouse)
{
    if (function_active)
    {
        active = true;
        startDraggingPoint(mouse.getMousePosition());
        updateCoords({mouse.getMousePosition()});
    }
}
void SelectionRect::MouseButtonUp(const Mouse&  m)
{
    if (function_active)
    {
        active = false;
        if (onSelectionFinished)
        {
            auto rect = NormalizeRect(start, current);
            onSelectionFinished({rect.x, rect.y, rect.w, rect.h});
        }
    }
}
void SelectionRect::registerSelectionRectFinished(std::function<void(Rect)> fn)
{
    onSelectionFinished = std::move(fn);
}
void SelectionRect::setFontColor(const doengine::Color& color)
{
    if(font)
        font->setForegroundColor(color);
}

} // namespace doengine