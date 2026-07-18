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


#ifndef TEXTFIELD_UI_H_DEFINED
#define TEXTFIELD_UI_H_DEFINED

#include "Application.h"
#include "Event.h"
#include "Geometric.h"
#include "Renderer.h"
#include "TTFText.h"
#include <functional>
#include <string>

namespace doengine
{

class TextField : public MouseEvent,
                  public KeyboardInputhandlingEvent,
                  public TextInputEvent
{
  private:
    virtual void MouseMove(const Mouse& mouse);
    virtual void MouseButtonDown(const Mouse& mouse);
    virtual void MouseButtonUp(const Mouse&);
    virtual void MouseWheel(const Mouse&);

    virtual void OnKeydown(const Keyboard& keyboard);
    virtual void OnKeyup(const Keyboard&);
    virtual void OnTextInput(const std::string& text);

  public:
    TextField(int x, int y, int w, int h, const std::string& font);

    void Render();

    std::string getText() const;

    void setOnEnterKeyPressed(std::function<void(const std::string&)> fn);

  private:
    Rect rect;
    Color textColor;
    Color bgColor;
    Color borderColor;
    std::string text;
    bool focused;

    std::string fontsrc;
    std::shared_ptr<doengine::TTFText> font;
    std::shared_ptr<doengine::Renderer> renderer;

    std::function<void(const std::string&)> onEnterPressed;
};

} // namespace doengine

#endif