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
    public doengine::MouseEvent 
{
   
    private:
        std::string fontsrc;
        doengine::TTFText *font;
        bool function_active = true;
        bool active = false;
        doengine::Rect start{};
        doengine::Rect current{};
        std::function<void(Rect)> onSelectionFinished;
        void setup();

    public:
        SelectionRect();
        doengine::Rect NormalizeRect(const doengine::Rect& a, const doengine::Rect& b);
        void setFont(const std::string& font);
        virtual ~SelectionRect();
        virtual void startDraggingPoint(const doengine::Rect& start);
        virtual void updateCoords(const doengine::Rect& rect);
        virtual void render(doengine::Renderer *render);
        virtual void OnKeydown(const Keyboard&keyboard);
        virtual void OnKeyup(const Keyboard&keyboard);
        virtual void MouseMove(const Mouse& mouse);
        virtual void MouseWheel(const Mouse&){}
        virtual void MouseButtonDown(const Mouse& mouse);
        virtual void MouseButtonUp(const Mouse& mouse);
        void registerSelectionRectFinished(std::function<void(Rect)> fn);
        void setFontColor(const doengine::Color& color);
};

}

#endif
