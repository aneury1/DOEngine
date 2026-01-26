#ifndef MENUSTRING_LIST_H_DEFINED
#define MENUSTRING_LIST_H_DEFINED
#include <vector>
#include <string>
#include <functional>
#include "GameObject.h"
#include "Event.h"
#include "TTFText.h"

namespace doengine
{
struct MenuStringList : std::vector<std::string>,
                        public GameObject,
                        public KeyboardInputhandlingEvent
{
    doengine::TTFText* text;

    std::string font_id;

    bool is_focused = true;

    std::function<void(int)> on_accepted;

  

    enum MenuOrientation
    {
        Vertical,
        Horiozontal
    } orientation;

    std::vector<Rect> offsets;
    int current_selection = 0;

    void createOffsetVector()
    {
        offsets.clear();
        for (size_t i = 0; i < size(); i++)
        {
            std::string value = at(i);
            offsets.emplace_back(Rect{position.x, position.y + (i * 64), 0,
                                      text->getFontHeight()});
        }
    }

    MenuStringList(std::initializer_list<std::string> str)
        : std::vector<std::string>(str)
    {
        text = new doengine::TTFText();
        text->setFont(
            "/home/neonland/Documents/DOEngine/assets/fonts/DroidSans.ttf", 18);
        position.x = Application::getApplication()->getW() / 2 - 100;
        position.y = Application::getApplication()->getH() / 2 - 100;
        createOffsetVector();
       // bg = new MenuPanelBackground(this);
    }
    virtual ~MenuStringList()
    {
    }
    virtual void Update(float timer = 0)
    {
    }
    virtual void Render()
    {

        for (size_t i = 0; i < offsets.size(); i++)
        {
            std::string value = at(i);
            text->DrawText(offsets[i].x, offsets[i].y, value.c_str());
        }

        offsets[current_selection].w = 200;

        renderer->DrawRect(offsets[current_selection], doengine::Colors::red);
    }
    virtual void OnKeydown(const Keyboard& keyboard)
    {
        auto keys = keyboard.getKeysBitset();
        if (keys[doengine::SCANCODE_DOWN])
        {
            current_selection++;
        }
        if (keys[doengine::SCANCODE_UP])
        {
            current_selection--;
        }
        if (keys[doengine::SCANCODE_KP_ENTER] ||
            keys[doengine::SCANCODE_RETURN])
        {
            if (on_accepted)
                on_accepted(current_selection);
        }
        if (current_selection > size() - 1)
            current_selection = 0;
        if (current_selection < 0)
            current_selection = size() - 2;
    }
    virtual void OnKeyup(const Keyboard&)
    {
    }

    void setAcceptedCallback(std::function<void(int)> cb)
    {
        on_accepted=cb;
    }
};

}

#endif /// MENUSTRING_LIST_H_DEFINED