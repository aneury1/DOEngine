#include "Application.h"




class SimpleBattleCityState : public {


};


int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    app->createWindow(doengine::Rect{800,800});

    while(app->IsRunning()){
        app->PollEvent();
        app->clearScreen(doengine::red);
        app->Render();
    }

    return 0;
}