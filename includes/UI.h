#pragma once
#include "Color.h"
#include "Renderer.h"
#include "Geometric.h"
namespace doengine
{

enum class Border
{
    None,
    Left,
    Right,
    Top,
    Bottom
};

enum class MouseBtn
{
    None,
    Left,
    Middle,
    Right
};

struct BorderPress
{
    bool        pressed;     // true if border hit + button pressed
    Border      border;      // which border
    MouseBtn    button;      // which mouse button
    int         x, y;        // mouse position
};


   enum class ComponentType{
        container,
        child
   };

   struct UIElement
   {
        Renderer *getRenderer(){
            return renderer;
        }
        UIElement(){
           // auto manager = Application::getApplication()
           //     ->getWindow()
           //     ->getGUIManager()
           //     ->getLastIndex();
        }

        protected:
            int index;
            Renderer *renderer;
            ComponentType type;    
   };
    
   struct UIPanel : UIElement
   {
       bool mouseOverPanelBorder;
       Color backgroundColor;
       Rect size;
       UIPanel();
       virtual ~UIPanel();
       void Draw();
       void Update();
   };


};