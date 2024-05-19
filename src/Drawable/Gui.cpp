#include "Gui.h"

namespace doengine
{

void WidgetContainer::addChild(WidgetElement* element)
{
    // auto it = children.find(element);
    // if(it == children.end())
    //     children.emplace_back(element);
}

void WidgetContainer::removeChild(WidgetElement* element)
{
    // auto it = children.find(element);
    // if(it != children.end())
    //    children.remove(it);
}

void WidgetContainer::setLayoutDirection(const WidgetLayoutDirection& direction)
{
    this->layout = direction;
}

}; // namespace doengine