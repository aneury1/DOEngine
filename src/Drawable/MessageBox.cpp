
#include "MessageBox.h"


namespace doengine
{

MessageBox::MessageBox(const std::string& text,
                       const std::string& fontsrc,
                       std::function<void(int)> onClick)
    : text(text),
      onClick(onClick)
{
    auto* app = doengine::Application::getApplication();

    position.w = app->getW() / 2;
    position.h = 200;
    position.x = (app->getW() - position.w) / 2;
    position.y = (app->getH() - position.h) / 2;

    font = std::make_unique<doengine::TTFText>();
    font->setFont(fontsrc, 19);
    font->setForegroundColor(doengine::Colors::red);

    renderer = app->getRender();

    // Text position
    tposition.x = position.x + 32;
    tposition.y = position.y + 32;

    // Main button position (bottom-right)
    bposition.w = 200;
    bposition.h = 64;
    bposition.x = position.x + position.w - bposition.w - 32;
    bposition.y = position.y + position.h - bposition.h - 32;

    // Close button position (top-right)
    cposition.w = 32;
    cposition.h = 32;
    cposition.x = position.x + position.w - cposition.w - 16;
    cposition.y = position.y + 16;
}

void MessageBox::render()
{
    if(!visible)
        return ;
    // Draw message box
    renderer->DrawFillRect(position, doengine::Color(0x43, 0x43, 0x43, 255));

    // Draw text
    font->setColor(doengine::Colors::white);
    font->DrawText(tposition.x, tposition.y, text.c_str());

    // Draw main button
    renderer->DrawFillRect(bposition, doengine::Colors::green);
    font->DrawText(((bposition.w/2) + bposition.x) - 32, (bposition.y+(bposition.h/2)-16), "Accept");


    // Draw close button
    renderer->DrawFillRect(cposition, doengine::Colors::red);
}

void MessageBox::MouseButtonUp(const Mouse& m)
{
    if(!visible)
        return ;
    doengine::Rect mouse = m.getMousePosition();
    // Check main button click
    if (mouse.x >= bposition.x && mouse.x <= bposition.x + bposition.w &&
        mouse.y >= bposition.y && mouse.y <= bposition.y + bposition.h)
    {
        doengine::LogOuput(doengine::logger_type::Information, "CLICked Accpeted");
        
        if (onClick)
            onClick(1); // 1 = main button
        visible = false;
    }

    // Check close button click
    if (mouse.x >= cposition.x && mouse.x <= cposition.x + cposition.w &&
        mouse.y >= cposition.y && mouse.y <= cposition.y + cposition.h)
    {
        doengine::LogOuput(doengine::logger_type::Information, "CLICked Cancel");
        if (onClick)
            onClick(0); // 0 = close button
        visible = false;

    }
}


}
