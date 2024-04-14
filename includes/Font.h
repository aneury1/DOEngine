#pragma once

#include "Color.h"

#include <string>

namespace doengine
{

class Font
{
  public:
    virtual void init() = 0;
    virtual void destroy() = 0;
    virtual void setColor(Color color) = 0;
    virtual void setFont(const std::string& path, int fntsize = 23) = 0;
    virtual void drawText(const std::string& text, int x, int y) = 0;
};

} // namespace doengine