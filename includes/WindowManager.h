

#pragma once
#include <memory>

#include "Renderer.h"

class Renderer;

class WindowManager{

   public:

   WindowManager(){
    
   }

   bool createWindow() = 0;

   std::shared_ptr<Renderer> createRenderer() = 0;

   bool isValid() = 0;

   void clearScreen(Color color) = 0;

   void updateScreen() = 0;

};