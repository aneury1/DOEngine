#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
// #include "DOEngine.h"
#include "Application.h"
#include "EventHandler.h"
#include "Geometric.h"
namespace doengine
{
struct Event
{
    


     
    typedef std::function<void(const Keyboard&)> KeyPressedCB;
    
    
    static float timeElapsed;
    static std::unordered_map<unsigned char, bool> keys_pressed;
    static std::vector<std::function<void(const Keyboard&)>> keydowncb;
    static std::vector<KeyDownEvent*> keydown;
    static std::vector<KeyUpEvent*> keyup;
    static std::vector<MouseEvent*> mouseEvent;
    static std::vector<JoyButtonUpEvent*> joyButtonUpList;
    static std::vector<JoyButtonDownEvent*> joyButtonDownList;
    static std::vector<JoyButtonTriggerEvent*> joyButtonTriggerList;
    static std::map<int, Joypad*> joypadsConnected;

    static int getMousePosition(int* x, int* y);
    static int getMousePosition(Point *point);
    static bool getLastKeyPressed(int scancode);


    static void PollEvent();
    static void AddKeyPressEventListener(KeyUpEvent* ev);
    static void AddKeyPressEventListener(KeyDownEvent* ev);
    static void AddKeyPressEventCallback(std::function<void(const Keyboard&)> ev);
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
} // namespace doengine