# DOEngine

another 2D game engine library base on SDL2 and Opengl. 

#### What is it? why? 

this is a basically a gameengine library on top of SDL2 and opengl(next)
there are tons of Game Engine, Frameworks, Tools and other Software that 
is use to create Games, is ok, we are not competing here. this library 
is create to see if we are able to run a Game without third party and by 
learning at our own pace.

#### Authors

- Aneury Perez -> https://github.com/aneury1 -> linkedin: https://www.linkedin.com/in/aneury-p-06902a3a/
- Victor D. Montero -> https://github.com/victordmontero -> linkedin: https://www.linkedin.com/in/victor-d-montero-adames-888170144/

feel free to contact us and feel to leave comments, bug reports and anything that can 
make it better. this software is suppose to be open source as now.

#### Setup

this is a C++ project, use CMake, there are some config for using installed SDL2(and sublibraries) Version
or fetch from github.com please check CMakeLists.txt to see it. probably some would be listed bellow.

#### Ussage.

you can check the samples in the sample folders. but is basically setting up a State and add to the statemachine
and work from it, using library common function for Drawing, Loading images, Loading fonts, Loading Music. 

please see in samples simplepong.cpp
```cpp
#include "Application.h"
#include "GameObject.h"
#include "Grids.h"
#include "TTFText.h"

struct Paddle : public GameObject
{
   ...
    virtual void Update(float timer = 0)override{}
    virtual void Render()override{}
    virtual bool isColliding(GameObject* other)override{}
};

struct PongState : public GameState, public KeyDownEvent
{
   ...
   virtual void OnKeydown(const Keyboard&) override{...}
   virtual void OnEnter() override
   {
      ...
      ///do setup 
   }
    virtual void OnExit() override
    {
         
      ...
      ///do a cleanup
    }
    virtual void Update(float elapsed)
    {
      ...
      /// process Game State Action
    }
    virtual void Render()
    {
      ...
      ///update Screen if necesary..
    }
};

...
enum StatesId{
   Playstate = 1
};


int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{1200, 900};
    app->createWindow(rect);
    auto pongState = new PongState();
    app->addState(pongState, Playstate);
    app->setState(Playstate);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}


```
##### Issue when Compiling or running the samples.
as this is on going you would have to issues compiling or running the project. if this is a compilation issue 
please head to CMake and check if you are fetch or using local installation probably clean up and do cmake .. 
would make it. 

if there are some issue running the samples, please check the path for assets, probably there would be missing 
some assets due to they are for privately use. in the future we would have own assets but by the time this 
is the state of it.

##### WIP

- Testing Android Setup(no yet ready)
- Testing Opengl currently we have only SDL2 fallback
- TileMap creating, font wrapping, blending, math, ...


#### Docs.

we dont have docs written, but we have a github project where you can see the status and board like kanban board
we have samples and Test folders which its suppose to be very clear and explanatory in general, in addition of 
any doubts you can create and issue for letting us know that something is missing. 

Thanks for reach this place...
