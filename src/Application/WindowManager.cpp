#include "WindowManager.h"
#include "SDLWindowManager.h"
#include "SDLOpenglWindowManager.h"
#include <memory.h>

namespace doengine
{

WindowManager* WindowManager::getWindowManager()
{
    bool opengl_support = false;
    if(!opengl_support)
    {
        SDLWindowManager* manager = new SDLWindowManager();
        return manager;
    }
    else
    {
        LogOuput(logger_type::Information," Opengl Renderer");
        WindowManager* manager = new SDLOpenglWindowManager(); ///
        return manager;
    }
}

}; // namespace doengine
