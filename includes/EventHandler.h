
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

#include "Joypad.h"
#include "Keyboard.h"
#include "Mouse.h"

using doengine::devices::Joypad;
using doengine::devices::Keyboard;
using doengine::devices::Mouse;

namespace doengine
{


struct KeyboardInputhandlingEvent
{
   KeyboardInputhandlingEvent();
   virtual ~KeyboardInputhandlingEvent();
   virtual void OnKeydown(const Keyboard&) = 0;
   virtual void OnKeyup(const Keyboard&) = 0;
};

class KeyUpEvent
{
  public:
    ~KeyUpEvent()
    {
    }

    virtual void OnKeyup(const Keyboard&) = 0;
};

class JoyButtonDownEvent
{
  public:
    ~JoyButtonDownEvent()
    {
    }

    virtual void OnButtonDown(const Joypad&) = 0;
};

class JoyButtonUpEvent
{
  public:
    ~JoyButtonUpEvent()
    {
    }

    virtual void OnButtonUp(const Joypad&) = 0;
};

class JoyButtonTriggerEvent
{
  public:
    ~JoyButtonTriggerEvent()
    {
    }

    virtual void OnButtonTriggered(const Joypad&) = 0;
};

class MouseMovementEvent
{
  public:
    ~MouseMovementEvent()
    {
    }

    virtual void OnMouseMovement(int x, int y) = 0;
};

class MouseStopEvent
{
  public:
    ~MouseStopEvent()
    {
    }

    virtual void OnMouseMovement(int x, int y) = 0;
};

class TouchEventDown
{
  public:
    ~TouchEventDown()
    {
    }

    virtual void OnTouchDown(int x, int y) = 0;
};

class TouchUpDown
{
  public:
    ~TouchUpDown()
    {
    }

    virtual void OnTouchUp(int x, int y) = 0;
};

class OnMessageQueue
{
  public:
    ~OnMessageQueue()
    {
    }

    virtual void HandleByDescriptor(int fd, void* buffer) = 0;
};

struct MouseEvent
{
    virtual ~MouseEvent();
    MouseEvent();
    virtual void MouseWheel(const Mouse&) = 0;
    virtual void MouseMove(const Mouse&) = 0;
    virtual void MouseButtonDown(const Mouse&) = 0;
    virtual void MouseButtonUp(const Mouse&) = 0;
};


struct TextInputEvent
{
    virtual ~TextInputEvent();
    TextInputEvent();
    virtual void OnTextInput(const std::string& text) = 0;
};



} // namespace doengine