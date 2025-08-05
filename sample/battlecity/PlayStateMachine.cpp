#include "PlayStateMachine.h"
#include "Event.h"
#include "Keyboard.h"


const int Row  = 15;
const int Cols = 13;

  int level1[15*13]=
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,1,0,1,0,1,0,1,0,1,0,1,0,
   0,1,0,1,0,0,0,0,0,0,0,0,0,
   0,1,0,1,0,1,2,1,0,1,0,1,0, 
   0,1,0,1,0,1,0,1,0,1,0,1,0,
   0,1,0,1,0,0,0,0,0,1,0,1,0,
   0,0,0,0,0,0,0,0,0,1,0,1,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,
   3,0,1,1,0,0,0,0,0,1,1,3,3,
   2,1,0,1,0,0,0,0,0,0,1,3,3,
   2,1,0,1,0,0,1,0,0,0,1,0,0,
   2,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,1,1,1,0,0,0,0,0,
   0,0,0,0,9,1,5,1,0,0,0,0,0,
};

#include <iostream>

void PlayStateMachine::OnEnter()
{
    render = doengine::Application::getApplication()->getRender();
    map = new doengine::TileMap();
    map->loadTileMap(15,13,16, level1);
    map->loadTexture("/home/neon/Desktop/DOEngine/assets/images/battlecitysprites.png");
    
 
    auto keypressed = [this](const doengine::devices::Keyboard& key) {

        if(key.getLastKeyPressed() == SDL_SCANCODE_E)
        {
           this->map->showEditor = !this->map->showEditor;   
        }
    
        if(this->map->showEditor==false)
            return;
   


        if(key.getLastKeyPressed()  == SDL_SCANCODE_R)
        {
            ///This could be done into tilemap as internal function or public
            this->map->isATileOnEditorSelected = !this->map->isATileOnEditorSelected;
            if(this->map->isATileOnEditorSelected)
            {
                this->map->selColIdx = this->map->cursorCol;
                this->map->selRowIdx = this->map->cursorRow;
                this->map->selClipset.x = this->map->selColIdx * 16;
                this->map->selClipset.y = this->map->selRowIdx * 16;
                this->map->selClipset.h = 16;
                this->map->selClipset.w = 16;

                this->map->previousOffset.x = this->map->offsetOfMap.w - 150;
                this->map->previousOffset.y = 100;
                this->map->previousOffset.w = 100;
                this->map->previousOffset.h = 100;  
            }
        }

         if(key.getLastKeyPressed()==SDL_SCANCODE_LEFT)
         {
             this->map->MoveEditorCursor(doengine::TileMap::EditorCursorPosition::Left);
         }
         if(key.getLastKeyPressed()==SDL_SCANCODE_RIGHT)
         {
             this->map->MoveEditorCursor(doengine::TileMap::EditorCursorPosition::Right);
         }
         if(key.getLastKeyPressed()==SDL_SCANCODE_UP)
         {
             this->map->MoveEditorCursor(doengine::TileMap::EditorCursorPosition::Top);
         }
         if(key.getLastKeyPressed()==SDL_SCANCODE_DOWN)
         {
             this->map->MoveEditorCursor(doengine::TileMap::EditorCursorPosition::Bottom);
         }
    };
    
    doengine::Event::AddKeyPressEventCallback(keypressed);

}
void PlayStateMachine::OnExit()
{
}
void PlayStateMachine::Update(float elapsed)
{

}
 
void PlayStateMachine::Render()
{
   map->render(render);
}
