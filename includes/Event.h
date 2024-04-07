#pragma once

// #include "DOEngine.h"
#include "Application.h"
#include "abstract/EventHandler.h"
#include <vector>

struct Event
{
    static float timeElapsed;
    static std::vector<KeyDownEvent*> keydown;
    static std::vector<KeyUpEvent*> keyup;
    static std::vector<MouseMovementEvent*> mouse;
    static std::vector<MouseEvent*> mouseEvent;
    static std::vector<JoyButtonUpEvent*> joyButtonUpList;
    static std::vector<JoyButtonDownEvent*> joyButtonDownList;
    static std::vector<JoyButtonTriggerEvent*> joyButtonTriggerList;

    static void getMousePosition(int* x, int* y);

    static void PollEvent();
    static void AddKeyPressEventListener(KeyUpEvent* ev);
    static void AddKeyPressEventListener(KeyDownEvent* ev);
    static void RemoveKeyPressEventListener(KeyUpEvent* ev);
    static void RemoveKeyPressEventListener(KeyDownEvent* ev);
    static void AddMouseEvent(MouseEvent* event);
    static void RemovedMouseEvent(MouseEvent* event);

    static bool mousePressed;
    static bool mouseReleased;
    static bool keyDown;
    static bool keyUp;
};
