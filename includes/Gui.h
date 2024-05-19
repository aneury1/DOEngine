#pragma once
#include "Color.h"
#include "Geometric.h"
#include <list>
#include <string>

namespace doengine
{

struct Style
{
    Color backgroundColor;
    Color foregroundColor;
    Color disableColor;
    int PrimaryfontSize;
    int secondaryFontSize;
    int padding;
    int margin;
    int borderWidth;
    Color borderColor;
    int borderRadius; /// unused
    std::string fontFamily;
};

struct UIObject
{
  protected:
    Point position;
    Rect size;
    bool _focus;
    bool disable;

  public:
    virtual void setStyle(const Style& style) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void focus() = 0;
    virtual void unFocus() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual int type() = 0;
};

enum class WidgetLayoutDirection : int
{
    Horizontal,
    Vertical,
    Grid,
    List,
    Absolute
};

class WidgetElement;
struct WidgetContainer : public UIObject
{

  protected:
    virtual void focus() = 0;
    virtual void unFocus() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void update() = 0;

    WidgetLayoutDirection layout;

    UIObject* parent;

    std::list<WidgetElement*> children;

  public:
    virtual void setStyle(const Style& style) = 0;

    virtual void render() = 0;

    void addChild(WidgetElement* element);

    void removeChild(WidgetElement* element);

    void setLayoutDirection(const WidgetLayoutDirection& direction);
};

}; // namespace doengine