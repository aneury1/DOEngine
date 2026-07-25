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


#ifndef MESSAGE_BOX_H_DEFINED
#define MESSAGE_BOX_H_DEFINED
#include "Application.h"
#include "Renderer.h"
#include "Geometric.h"
#include "Event.h"
#include "Logger.h"
#include "TTFText.h"
#include <memory>
#include <functional>
#include <string>
namespace doengine
{

enum class MessageBoxFlag : int
{
     AcceptOnly,
     YesOrNot,
     YesOrNotOrCancel
};

struct MessageBox : public doengine::MouseEvent
{
    std::shared_ptr<doengine::Renderer> renderer;
    doengine::Rect position;
    doengine::Rect tposition;
    doengine::Rect bposition;
    doengine::Rect cposition;
    bool visible = true;
    std::string text;
    std::unique_ptr<doengine::TTFText> font;
    std::function<void(int)> onClick;
    MessageBoxFlag flags;

    MessageBox(const std::string& text,
               const std::string& fontsrc,
               std::function<void(int)> onClick);
    
    void setFlags(MessageBoxFlag flag)
    {
        flags = flag;
    }
    virtual void MouseMove(const Mouse&) override {}
    virtual void MouseButtonDown(const Mouse&) override {}
    virtual void MouseButtonUp(const Mouse&) override;
    void show(){
        visible = true;
    }
    void hide(){
        visible = false;
    }
    void render();
};  
}

#endif