#include "WindowManager.h"
#include "SDLWindowManager.h"
#include "SDLOpenglWindowManager.h"
#include <memory.h>

namespace doengine
{

WindowManager* WindowManager::getWindowManager()
{
    bool opengl_support = true;
    if(!opengl_support)
    {
        SDLWindowManager* manager = new SDLWindowManager();
        return manager;
    }
    else
    {
        SDLWindowManager* manager = new SDLOpenglWindowManager(); ///
        return manager;
    }
}

}; // namespace doengine
