
#include "Event.h"
#include "DOEngine_SDL_includes.h"
#include "EventHandler.h"
#include "v2d_vector.h"
#include <vector>

std::vector<KeyDownEvent*> Event::keydown;
std::vector<KeyUpEvent*> Event::keyup;
std::vector<MouseMovementEvent*> Event::mouse;
std::vector<MouseEvent*> Event::mouseEvent;
std::vector<JoyButtonUpEvent*> Event::joyButtonUpList;
std::vector<JoyButtonDownEvent*> Event::joyButtonDownList;
std::vector<JoyButtonTriggerEvent*> Event::joyButtonTriggerList;

float Event::timeElapsed = 0.0f;

void Event::PollEvent()
{
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
            SDL_Log("Window quit");
            Application::getApplication()->Quit();
            // SDL_Log("SDL_KEYDOWN");
        }
        break;
        case SDL_KEYUP: {
            ////    SDL_Log("SDL_KEYUP");
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
            Point mouse;
            SDL_GetMouseState(&mouse.x, &mouse.y);

            SDL_Log("SDL_MOUSEMOTION x: %ld,  y:%ld", mouse.x, mouse.y);
            SDL_Log("Mouse Count = %ld", Event::mouseEvent.size());

            for (auto itMouse : Event::mouseEvent)
            {
                itMouse->MouseMove(event.motion.which, mouse.x, mouse.y);
            }
        }
        break;
        case SDL_MOUSEBUTTONDOWN: {
            ///     SDL_Log("SDL_MOUSEBUTTONDOWN");
            for (auto it : mouseEvent)
                it->MouseButtonDown(
                    event.button.which,
                    static_cast<MouseButton>(event.button.button));
        }
        break;
        case SDL_MOUSEBUTTONUP: {
            /// SDL_Log("SDL_MOUSEBUTTONUP");

            for (auto it : mouseEvent)
                it->MouseButtonUp(event.button.which, static_cast<MouseButton>(
                                                          event.button.button));
        }
        break;
        case SDL_MOUSEWHEEL: {
            ////    SDL_Log("SDL_MOUSEWHEEL");
        }
        break;
        case SDL_JOYAXISMOTION:
        case SDL_CONTROLLERAXISMOTION:
            SDL_Log("SDL_CONTROLLERAXISMOTION Axis %d, Value %d",
                    event.jaxis.axis, event.jaxis.value);
            break;
        case SDL_JOYBUTTONUP:
            SDL_Log("SDL_JOYBUTTONUP  %d", event.jbutton.button);
            break;
        case SDL_JOYBUTTONDOWN:
            SDL_Log("SDL_JOYBUTTONDOWN %d", event.jbutton.button);
            break;
        default:
            break;
        }

        /*if(keyDown==true && keydown.size()>0)
        {
           for(auto it : keydown)
              it->OnKeydown(event.key.keysym.sym);
           keyDown = false;
        }
        if(keyUp==true && keyup.size()>0)
        {
           for(auto it : keyup)
              it->OnKeyup(event.key.keysym.sym);
           keyUp = false;
        }*/
    }
}

void Event::getMousePosition(int* x, int* y)
{
    SDL_GetMouseState(x, y);
}

void Event::AddKeyPressEventListener(KeyUpEvent* ev)
{
    Event::keyup.emplace_back(ev);
}

void Event::AddKeyPressEventListener(KeyDownEvent* ev)
{
    Event::keydown.emplace_back(ev);
}

void Event::RemoveKeyPressEventListener(KeyUpEvent* ev)
{
    auto& evts = Event::keyup;
    for (auto it = evts.begin(); it != evts.end(); ++it)
    {
        if (*it == ev)
        {
            evts.erase(it);
        }
    }
}

void Event::RemoveKeyPressEventListener(KeyDownEvent* ev)
{
    auto& evts = Event::keydown;
    for (auto it = evts.begin(); it != evts.end(); ++it)
    {
        if (*it == ev)
        {
            evts.erase(it);
        }
    }
}

void Event::AddMouseEvent(MouseEvent* event)
{
    Event::mouseEvent.push_back(event);
    /// SDL_Log("Adding EVent Handler %02x", event);
}

void Event::RemovedMouseEvent(MouseEvent* event)
{
    auto& evts = Event::mouseEvent;
    for (auto it = evts.begin(); it != evts.end(); ++it)
    {
        if (*it == event)
            evts.erase(it);
    }
    /// SDL_Log("Adding EVent Handler %02x", event);
}