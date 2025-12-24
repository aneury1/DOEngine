#include "SelectionRect.h"

namespace doengine
{

 void SelectionRect::setup()
 {
    if(!font)
        font = new doengine::TTFText();
    if(!fontsrc.empty())
        font->setFont(fontsrc, 18);
 }

SelectionRect::SelectionRect():
 font{nullptr}
{
  setup();
}

SelectionRect::~SelectionRect()
{
}

doengine::Rect SelectionRect::NormalizeRect(const doengine::Rect& a,
                                            const doengine::Rect& b)
{
    doengine::Rect r;
    r.x = std::min(a.x, b.x);
    r.y = std::min(a.y, b.y);
    r.w = std::abs(a.x - b.x);
    r.h = std::abs(a.y - b.y);
    return r;
}

void SelectionRect::setFont(const std::string& font)
{
    this->fontsrc = font;
    setup();
}

void SelectionRect::startDraggingPoint(const doengine::Rect& start)
{
    if (!function_active)
        return;
    this->start.x = start.x;
    this->start.y = start.y;
}

void SelectionRect::updateCoords(const doengine::Rect& rect)
{
    if (function_active && active)
    {
        this->current.x = rect.x;
        this->current.y = rect.y;
    }
}

void SelectionRect::render(doengine::Renderer* render)
{
    if(!render)
        render = Application::getApplication()->getRender();
    if (!function_active)
    {
        return;
    }
    auto rect = NormalizeRect(start, current);
    render->DrawRect(rect, doengine::Colors::red);
    /// if(active)
    {
        int y = rect.y - 32;
        if (y <= 16)
            y = rect.y + 64;

        font->DrawText(rect.x, y, "(%d,%d, %d, %d)", rect.x, rect.y, rect.w,
                       rect.h);
                      if(onSelectionFinished)
        {
            onSelectionFinished(rect);
        }
    }
}

void SelectionRect::OnKeydown(const Keyboard& keyboard)
{

    auto key = keyboard.getKeysBitset();

    if (key[SCANCODE_ESCAPE])
    {
        function_active = (!function_active);
    }
}

void SelectionRect::OnKeyup(const Keyboard& keyboard)
{
}

void SelectionRect::MouseMove(const Mouse& mouse)
{
    if (function_active && active)
    {
        updateCoords({mouse.getMousePosition()});
    }
}
void SelectionRect::MouseButtonDown(const Mouse& mouse)
{
    if (function_active)
    {
        active = true;
        startDraggingPoint(mouse.getMousePosition());
        updateCoords({mouse.getMousePosition()});
    }
}
void SelectionRect::MouseButtonUp(const Mouse& mouse)
{
    if (function_active)
        active = false;
}
void SelectionRect::registerSelectionRectFinished(std::function<void(Rect)> fn)
{
    onSelectionFinished = fn;
}
void SelectionRect::setFontColor(const doengine::Color& color)
{
    if(font)
        font->setForegroundColor(color);
}

} // namespace doengine