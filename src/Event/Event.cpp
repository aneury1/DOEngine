
#include "Event.h"
#include "Application.h"
#include "DOEngine_SDL_includes.h"
#include "EventHandler.h"
#include "SDLJoypad.h"
#include "SDLKeyboard.h"
#include "SDLMouse.h"
#include "v2d_vector.h"
#include <vector>

namespace doengine
{

std::vector<KeyDownEvent*> Event::keydown;
std::vector<KeyUpEvent*> Event::keyup;
std::vector<MouseEvent*> Event::mouseEvent;
std::vector<JoyButtonUpEvent*> Event::joyButtonUpList;
std::vector<JoyButtonDownEvent*> Event::joyButtonDownList;
std::vector<JoyButtonTriggerEvent*> Event::joyButtonTriggerList;
std::map<int, Joypad*> Event::joypadsConnected;
std::map<int, bool> Event::keys;

float Event::timeElapsed = 0.0f;

void Event::PollEvent()
{
    Point mouse;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: {
            SDL_Log("Window quit");
            Application::getApplication()->Quit();
            break;
        }
        case SDL_KEYDOWN: {
            SDL_Log("SDL_KEYDOWN");
            /// SDLKeyboard keyboard;
            keys[event.key.keysym.sym] = true;
            for (auto itKeyboard : Event::keydown)
                itKeyboard->OnKeydown(event.key.keysym.sym);
        }
        break;
        case SDL_KEYUP: {
            SDL_Log("SDL_KEYUP");
            //  SDLKeyboard keyboard;
            keys[event.key.keysym.sym] = false;
            for (auto itKeyboard : Event::keyup)
                itKeyboard->OnKeyup(event.key.keysym.sym);
        }
        break; /**< Key released */
        case SDL_TEXTEDITING: {
            /// SDL_Log("SDL_TEXTEDITING");
        }
        break; /**< Keyboard text editing (composition) */
        case SDL_TEXTINPUT: {
            /// SDL_Log("SDL_TEXTEDITING");
        }
        break; /**< Keyboard text input */
        case SDL_MOUSEMOTION: {
            Point mousePos;
            auto mask = getMousePosition(&mousePos.x, &mousePos.y);
            SDLMouse mouse(event.motion.which, mask, mousePos);

            SDL_Log("SDL_MOUSEMOTION x: %d,  y:%d", mousePos.x, mousePos.y);
            SDL_Log("mousePos Count = %ld", Event::mouseEvent.size());

            for (auto itMouse : Event::mouseEvent)
            {
                itMouse->MouseMove(event.button.which, mousePos.x, mousePos.y);
            }
        }
        break;
        case SDL_MOUSEBUTTONDOWN: {
            Point mousePos;
            std::bitset<Mouse::BUTTONS_COUNT> buttonPressed;
            auto mask = getMousePosition(&mousePos.x, &mousePos.y);
            SDLMouse mouse(event.button.which, mask, mousePos);
            mouse.getButtonStateBitset(buttonPressed);

            SDL_Log("SDL_MOUSEBUTTONDOWN %ld", buttonPressed.to_ulong());
            SDL_Log("mousePos Count = %ld", Event::mouseEvent.size());

            for (auto it : Event::mouseEvent)
                it->MouseButtonDown(event.button.which, MouseButton::Middle,
                                    mousePos.x, mousePos.y);
        }
        break;
        case SDL_MOUSEBUTTONUP: {
            Point mousePos;
            std::bitset<Mouse::BUTTONS_COUNT> buttonPressed;
            auto mask = getMousePosition(&mousePos.x, &mousePos.y);
            SDLMouse mouse(event.motion.which, mask, mousePos);
            mouse.getButtonStateBitset(buttonPressed);

            // SDL_Log("SDL_MOUSEBUTTONUP %d", buttonPressed.to_ulong());
            // SDL_Log("mousePos Count = %ld", Event::mouseEvent.size());

            for (auto it : mouseEvent)
                it->MouseButtonUp(event.button.which, MouseButton::Middle,
                                  mousePos.x, mousePos.y);
        }
        break;
        case SDL_MOUSEWHEEL: {
            SDL_Log("SDL_MOUSEWHEEL");
        }
        break;
        case SDL_JOYAXISMOTION:
        case SDL_CONTROLLERAXISMOTION:
            SDL_Log("SDL_CONTROLLERAXISMOTION Axis %d, Value %d",
                    event.jaxis.axis, event.jaxis.value);

            for (auto it : joyButtonTriggerList)
            {
                //@todo fix this?
                // auto joypad = joypadsConnected[event.jaxis.which];
                // if (joypad != nullptr)
                //    it->OnButtonTriggered(event.jaxis.which, *joypad);
            }
            break;
        case SDL_JOYBUTTONUP:
            ////SDL_Log("SDL_JOYBUTTONUP  %d", event.jbutton.button);

            for (auto it : joyButtonUpList)
            {
                //@todo fix this?
                // auto joypad = joypadsConnected[event.jbutton.which];
                // if (joypad != nullptr)
                //     it->OnButtonUp(*joypad);
            }
            break;
        case SDL_JOYBUTTONDOWN:
            ////  SDL_Log("SDL_JOYBUTTONDOWN %d", event.jbutton.button);

            for (auto it : joyButtonDownList)
            {
                //@todo fix this?
                // auto joypad = joypadsConnected[event.jbutton.which];
                // if (joypad != nullptr)
                //     it->OnButtonDown(*joypad);
            }
            break;
        case SDL_JOYDEVICEREMOVED: {
            SDL_Log("SDL_JOYDEVICEREMOVED  %d", event.jbutton.which);
            //@todo fix this?
            /* auto joypad = joypadsConnected[event.jdevice.which];

             if (joypad != nullptr)
             {
                 auto sdlJoypad = dynamic_cast<SDLJoypad*>(
                     joypadsConnected[event.jdevice.which]);

                 SDL_Joystick* nativeJoystick = sdlJoypad->getNativeJoystick();
                 if (nativeJoystick != nullptr)
                 {
                     SDL_JoystickClose(sdlJoypad->getNativeJoystick());
                     delete sdlJoypad;
                     joypadsConnected[event.jdevice.which] = nullptr;
                 }*/
        }
        break;
        case SDL_JOYDEVICEADDED: {
            SDL_Log("SDL_JOYDEVICEADDED  %d", event.jbutton.which);

            SDL_Joystick* joystick = SDL_JoystickOpen(event.jdevice.which);
            if (joystick != nullptr)
                joypadsConnected[event.jdevice.which] = new SDLJoypad(joystick);
            else
                SDL_Log("Joystick:  %s", SDL_GetError());
        }
        break;

        default:
            break;
        }
    }
    Event::timeElapsed = Application::getApplication()->getElapsedTime();
}

int Event::getMousePosition(int* x, int* y)
{
    return SDL_GetMouseState(x, y);
}

int Event::getMousePosition(Point *p)
{
    return getMousePosition(&p->x, &p->y);
}

bool Event::isKeyPressed(int key){
    return keys[key];
}

void Event::AddKeyPressEventListener(KeyUpEvent* ev)
{
    Event::keyup.push_back(ev);
}

void Event::AddKeyPressEventListener(KeyDownEvent* ev)
{
    Event::keydown.push_back(ev);
}

void Event::RemoveKeyPressEventListener(KeyUpEvent* ev)
{
    auto& evts = Event::keyup;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == ev)
            it = evts.erase(it);
        else
            ++it;
    }
}

void Event::RemoveKeyPressEventListener(KeyDownEvent* ev)
{
    auto& evts = Event::keydown;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == ev)
            it = evts.erase(it);
        else
            ++it;
    }
}

void Event::AddMouseEvent(MouseEvent* event)
{
    Event::mouseEvent.push_back(event);
}

void Event::RemovedMouseEvent(MouseEvent* event)
{
    auto& evts = Event::mouseEvent;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == event)
            it = evts.erase(it);
        else
            ++it;
    }
}

void Event::AddJoypadEventListener(JoyButtonUpEvent* ev)
{
    Event::joyButtonUpList.push_back(ev);
}

void Event::AddJoypadEventListener(JoyButtonDownEvent* ev)
{
    Event::joyButtonDownList.push_back(ev);
}

void Event::AddJoypadEventListener(JoyButtonTriggerEvent* ev)
{
    Event::joyButtonTriggerList.push_back(ev);
}

void Event::RemoveJoypadEventListener(JoyButtonUpEvent* ev)
{
    auto& evts = Event::joyButtonUpList;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == ev)
            it = evts.erase(it);
        else
            ++it;
    }
}

void Event::RemoveJoypadEventListener(JoyButtonDownEvent* ev)
{
    auto& evts = Event::joyButtonDownList;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == ev)
            it = evts.erase(it);
        else
            ++it;
    }
}

void Event::RemoveJoypadEventListener(JoyButtonTriggerEvent* ev)
{
    auto& evts = Event::joyButtonTriggerList;
    for (auto it = evts.begin(); it != evts.end();)
    {
        if (*it == ev)
            it = evts.erase(it);
        else
            ++it;
    }
}

}; // namespace doengine
