#pragma once 
#include <Window.h>
#include <Canvas.h>

struct UIObject{
   protected:
     Canvas *canvas;
     int padding;
   public:
   virtual ~UIObject(){}
};