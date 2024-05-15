#include <memory.h>
#include "WindowManager.h"
#include "SDLWindowManager.h"

WindowManager* WindowManager::getWindowManager(){
   SDLWindowManager* manager = new SDLWindowManager();
   return manager;
}