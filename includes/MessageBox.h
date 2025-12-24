#ifndef MESSAGE_BOX_H_DEFINED
#define MESSAGE_BOX_H_DEFINED
#include "Application.h"
#include "Renderer.h"
#include "Geometric.h"
#include "Event.h"
#include "Logger.h"
#include "TTFText.h"
#include <memory>
#include <functional>
#include <string>
namespace doengine
{

enum class MessageBoxFlag : int
{
     AcceptOnly,
     YesOrNot,
     YesOrNotOrCancel
};

struct MessageBox : public doengine::MouseEvent
{
    doengine::Renderer* renderer;
    doengine::Rect position;
    doengine::Rect tposition;
    doengine::Rect bposition;
    doengine::Rect cposition;
    bool visible = true;
    std::string text;
    std::unique_ptr<doengine::TTFText> font;
    std::function<void(int)> onClick;
    MessageBoxFlag flags;

    MessageBox(const std::string& text,
               const std::string& fontsrc,
               std::function<void(int)> onClick);
    
    void setFlags(MessageBoxFlag flag)
    {
        flags = flag;
    }
    virtual void MouseMove(const Mouse&) override {}
    virtual void MouseButtonDown(const Mouse&) override {}
    virtual void MouseButtonUp(const Mouse&) override;
    void show(){
        visible = true;
    }
    void hide(){
        visible = false;
    }
    void render();
};  
}

#endif