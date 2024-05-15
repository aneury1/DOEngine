#pragma once
#include "Joypad.h"
#include "EventHandler.h"
#include <map>
#include <vector>

using doengine::devices::Joypad;

struct Event
{
    static float timeElapsed;
    static std::vector<KeyDownEvent*> keyPressed;
    static std::vector<KeyDownEvent*> keydown;
    static std::vector<KeyUpEvent*> keyup;
    static std::vector<MouseEvent*> mouseEvent;
    static std::vector<JoyButtonUpEvent*> joyButtonUpList;
    static std::vector<JoyButtonDownEvent*> joyButtonDownList;
    static std::vector<JoyButtonTriggerEvent*> joyButtonTriggerList;
    static std::map<int, Joypad*> joypadsConnected;

    static int getMousePosition(int* x, int* y);

    static void PollEvent();
    static void AddKeyPressEventListener(KeyUpEvent* ev);
    static void AddKeyPressEventListener(KeyDownEvent* ev);
    static void RemoveKeyPressEventListener(KeyUpEvent* ev);
    static void RemoveKeyPressEventListener(KeyDownEvent* ev);
    static void AddMouseEvent(MouseEvent* event);
    static void RemovedMouseEvent(MouseEvent* event);
    static void AddJoypadEventListener(JoyButtonUpEvent* ev);
    static void AddJoypadEventListener(JoyButtonDownEvent* ev);
    static void AddJoypadEventListener(JoyButtonTriggerEvent* ev);
    static void RemoveJoypadEventListener(JoyButtonUpEvent* ev);
    static void RemoveJoypadEventListener(JoyButtonDownEvent* ev);
    static void RemoveJoypadEventListener(JoyButtonTriggerEvent* ev);
};
