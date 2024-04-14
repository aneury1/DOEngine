#pragma once
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "WindowManager.h"


/// @brief this class is for internal use only it will instance by Application
class SDLWindowManager : public Renderer, WindowManager{

   SDL_Renderer *render

   public:

   WindowManager(){}

   bool createWindow();

   std::shared_ptr<Renderer> createRenderer();

   bool isValid();

   void clearScreen(Color color);

   void updateScreen();

};