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

#ifndef SELECTION_RECT_H_DEFINED
#define SELECTION_RECT_H_DEFINED

#include <string>
#include "Application.h"
#include "Renderer.h"
#include "TTFText.h"
#include "Event.h"
#include "EventHandler.h"
#include "Geometric.h"
#include "Draggable.h"

#include <functional>


namespace doengine
{


class SelectionRect : 
    public Draggable,
    public doengine::KeyboardInputhandlingEvent,
    public doengine::MouseEvent,
    public doengine::GameObject
{
   
    private:
        std::string fontsrc;
        std::shared_ptr<TTFText>font;
        bool function_active = true;
        bool active = false;
        doengine::Rect start{};
        doengine::Rect current{};
        std::function<void(Rect)> onSelectionFinished;
        void setup();

        virtual void OnKeydown(const Keyboard&keyboard);
        virtual void OnKeyup(const Keyboard&keyboard);
        virtual void MouseMove(const Mouse& mouse);
        virtual void MouseWheel(const Mouse&){}
        virtual void MouseButtonDown(const Mouse& mouse);
        virtual void MouseButtonUp(const Mouse& mouse);
        virtual void startDraggingPoint(const doengine::Rect& start);
        virtual void updateCoords(const doengine::Rect& rect);

    public:
        SelectionRect();
        doengine::Rect NormalizeRect(const doengine::Rect& a, const doengine::Rect& b);
        void setFont(const std::string& font);
        virtual ~SelectionRect();
        virtual void Render();
        virtual void Update(float  ){}
        void setFontColor(const doengine::Color& color);
        void registerSelectionRectFinished(std::function<void(Rect)> fn);

};

}

#endif
