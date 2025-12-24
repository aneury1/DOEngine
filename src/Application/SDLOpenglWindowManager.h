#ifndef SDL_OPENGL_WINDOW_MANAGER_H_DEFINED
#define SDL_OPENGL_WINDOW_MANAGER_H_DEFINED
#include <SDL2/SDL.h>

#include "SDLOpenglRenderer.h"
#include "SDLWindowManager.h"

namespace doengine 
{
    class  SDLOpenglWindowManager : public SDLWindowManager
    {
        private:
        void initEngine();
        public:
        SDLOpenglWindowManager();
        virtual ~SDLOpenglWindowManager();
        virtual bool createWindow(const Rect& rect) override;
        virtual bool createWindow() override;
        virtual Renderer* getRenderer() override;
        virtual bool isValid() override;
        virtual void clearScreen(const Color& color) override;
        virtual void setPincelColor(const Color& color) override;
        virtual void updateScreen() override;
        virtual void setFullScreen() override;
        virtual void setWindowMode() override;
        virtual void setSize(const Rect& rect) override;
        virtual Rect getWindowDisplayMode(int m);
        virtual void* getNativeWindowFormatBuffer() override;
    };
}

#endif /// SDL_OPENGL_WINDOW_MANAGER_H_DEFINED