#include "WindowManager.h"
#include "SDLWindowManager.h"
#include <memory.h>

namespace doengine
{

WindowManager* WindowManager::getWindowManager()
{
    SDLWindowManager* manager = new SDLWindowManager();
    return manager;
}

}; // namespace doengine
