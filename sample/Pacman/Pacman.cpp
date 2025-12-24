

#include "Application.h"
#include "StringUtils.h"
#include "DraggableGameObject.h"
#include "Event.h"
#include "FontCache.h"
#include "GameState.h"
#include "Logger.h"
#include "Mouse.h"
#include "SelectionRect.h"
#include "SpriteOffset.h"
#include "TTFText.h"
#include "Texture.h"
#include "Tile.h"
#include "Tilemap.h"
#include "UI.h"
#include "TextField.h"
#include "TileMapEditor.h"
#include "Utils.h"
#include "GameObject.h"
#include "MessageBox.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <memory>

enum State
{
    playing = 0
};

struct Layer
{
   std::string spriteid;
   doengine::Rect position;
   doengine::Rect position2;
   Layer(const std::string& sp)
   {
      spriteid = sp;
      position.x = 0;
      position.y = 0;
      position.w = 2400;
      position.h = 700;
      position2.x=position.w;

   }
}; 

#define max_rows  20
#define max_cols  31
#define tilesize  32
char this_map[max_rows][max_cols]=
{
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "Xeo|o o o  XXe   o o o| oe XX",
  "X XXX XXXXX XXXXXXXXXXXXXXXXX",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "X       o|o ooooo    o|o    X",
  "XoXXXoXX XXXXXXXXXXX XXoXXXoX",
  "X     |      |XXX|    XX   X",
  "XoXXXoXX XXX  XX     XXoXXXoX",
  "X XXXoXX ooo|ooo|ooo XXoXXX X",
  "Xo    |XX XXXXXXXXXXX XX|oooX",
  "XoXXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXXoXX oo |ooo|ooo XXoXXXoX",
  "XoXXXoXX XXX XXX XXX XXoXXX X",
  "X      X P      XXX         X",
  "X XXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXX| o| o o o o o |o |XXXoX",
  "X XXXoX XX XXXXXXXX XXX ooooX",
  "XoXXXoX XXooooooooooXXX Xoo X",
  "X  o |o oX XXXXXXXX ooo|ooooX",
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

constexpr const int FaceSize = 32;

struct Player : 
    public doengine::GameObject,
    public doengine::KeyboardInputhandlingEvent
{
    doengine::Rect position;
    doengine::Rect clipset;
    doengine::Renderer* renderer;

    int pointGathered = 0;
    doengine::TTFText *font;



    enum class PlayerPosition{
        Up,Down,Left,Right,None, Stopped
    };
    PlayerPosition current = PlayerPosition::None;
    PlayerPosition previous = PlayerPosition::None;
    doengine::TextureManager *textureManager = nullptr;

    Player()
    {
        renderer = doengine::Application::getApplication()->getRender();
        textureManager = doengine::TextureManager::getTextureManager();
        font = new doengine::TTFText();
        font->setFont("./assets/fonts/NirmalaB.ttf",20);
        font->setColor(doengine::Colors::red);
    }

    void setPosition(doengine::Rect rect)
    {
        position.x = rect.x;
        position.y = rect.y;
        position.w = rect.w;
        position.h = rect.h;
    }

    virtual void Update(float timer = 0)
    {
        switch (current)
        {
            case PlayerPosition::Up:
            {
                clipset.x = 2 * FaceSize;
                clipset.y = 0 * FaceSize;
                clipset.w = FaceSize;
                clipset.h = FaceSize;

                int prev_row =  (position.y / FaceSize) - 1;
                int prev_col =  (position.x / FaceSize);
                char prevElement =  this_map[prev_row][prev_col];
                //if(prevElement == ' ' || prevElement =='o'||prevElement =='|')
                if(doengine::isCharInGroup(prevElement," oPp|EeRr"))
                {
                    position.y -= FaceSize;
                    previous = current;
                    current = PlayerPosition::Stopped;
                    if(prevElement =='o')
                    {
                        this_map[prev_row][prev_col] = ' ';
                        pointGathered+=1;
                    }
                }
            }
            break;
            case PlayerPosition::Down:
            {
                clipset.x = 3 * FaceSize;
                clipset.y = 0 * FaceSize;
                clipset.w = FaceSize;
                clipset.h = FaceSize;
                int prev_row =  (position.y / FaceSize) + 1;
                int prev_col =  (position.x / FaceSize);
                char prevElement =  this_map[prev_row][prev_col];
                //if(prevElement == ' '||prevElement =='o'||prevElement =='|')
                if(doengine::isCharInGroup(prevElement," oPp|EeRr"))
                {
                    position.y += FaceSize;
                    previous = current;
                    current = PlayerPosition::Stopped;
                    if(prevElement =='o')
                    {
                        this_map[prev_row][prev_col] = ' ';
                        pointGathered+=1;
                    }
                }
            }
            break;
            case PlayerPosition::Left:
            {
                clipset.x = 0 * FaceSize;
                clipset.y = 0 * FaceSize;
                clipset.w = FaceSize;
                clipset.h = FaceSize;
                int prev_row =  (position.y / FaceSize);
                int prev_col =  (position.x / FaceSize) - 1;
                char prevElement =  this_map[prev_row][prev_col];
                ///if(prevElement == ' '||prevElement =='o'||prevElement =='|')
                if(doengine::isCharInGroup(prevElement," oPp|EeRr"))
                {
                    position.x -= FaceSize;
                    previous = current;
                    current = PlayerPosition::Stopped;
                    if(prevElement =='o')
                    {
                        this_map[prev_row][prev_col] = ' ';
                        pointGathered+=1;
                    }
                }
            }
            break;
           case PlayerPosition::Right:
            {
                clipset.x = 1 * FaceSize;
                clipset.y = 0 * FaceSize;
                clipset.w = FaceSize;
                clipset.h = FaceSize;
                int prev_row =  (position.y / FaceSize);
                int prev_col =  (position.x / FaceSize) + 1;
                char prevElement =  this_map[prev_row][prev_col];
                 //if(prevElement == ' '||prevElement =='o' ||prevElement =='|')
                if(doengine::isCharInGroup(prevElement," oPp|EeRr"))
                {
                    position.x += FaceSize;
                    previous = current;
                    current = PlayerPosition::Stopped;
                    if(prevElement =='o')
                    {
                        this_map[prev_row][prev_col] = ' ';
                        pointGathered+=1;
                    }
                }
            }
            break;
            case PlayerPosition::None:
            {
                clipset.x = 3 * FaceSize;
                clipset.y = 0 * FaceSize;
                clipset.w = FaceSize;
                clipset.h = FaceSize;
            }
            break;
        }
        previous = current;
        current = PlayerPosition::Stopped;
    }
    virtual void Render()
    {
        textureManager->getTexture("pacman_player_1")->Draw(position,clipset);
        font->DrawText(1000,100,"Score:");
        font->setColor(doengine::Colors::yellow1);
        font->DrawText(1090,100,"    %d", this->pointGathered);
    }
    virtual bool isColliding(GameObject* other)
    {
        return false;
    }
    virtual void OnKeydown(const Keyboard& keys)
    {
        auto k = keys.getKeysBitset();
        if(k[doengine::SCANCODE_LEFT])
        {
            previous = current;
            current = PlayerPosition::Left;
        }
        if(k[doengine::SCANCODE_RIGHT])
        {
            previous = current;
            current = PlayerPosition::Right;
        }
        if(k[doengine::SCANCODE_UP])
        {
            previous = current;
            current = PlayerPosition::Up;


        }
        if(k[doengine::SCANCODE_DOWN])
        {
            previous = current;
            current = PlayerPosition::Down;
        }

    }
    virtual void OnKeyup(const Keyboard&)
    {

    }
};

struct Enemy : 
    public doengine::GameObject
{
    bool alive;
    doengine::Rect offset;
    doengine::TextureManager *textureManager = nullptr;
    float currentSpeed = 0.2f;
    enum class EnemyPosition{
        Up,Down,Left,Right,None,Stopped,Frozen
    };
    EnemyPosition prevMovement;
    EnemyPosition current;
    EnemyPosition getNextPosition(){
        int rnd = rand()%4+0;
        switch (rnd)
        {
            case 0: return EnemyPosition::Down;
            case 1: return EnemyPosition::Up;
            case 2: return EnemyPosition::Left;
            case 3: return EnemyPosition::Right;
        }
        return EnemyPosition::Stopped;
    }

    Enemy(doengine::Rect offset)
    {
        textureManager = doengine::TextureManager::getTextureManager();                
        this->offset = offset;
        current = getNextPosition();
    }
    virtual void Update(float timer )
    {
        int row = offset.y / tilesize;
        int col = offset.x / tilesize;
        int max_x = max_rows * tilesize;
        prevMovement = current;
        if(current == EnemyPosition::Right)
        {
            if(this_map[row][col+1] =='X' || this_map[row][col+1] =='|')
                current = getNextPosition();
            else
            {
                offset.x += tilesize;
            }
        }
        if(current == EnemyPosition::Left)
        {
            if(this_map[row][col-1] =='X' || this_map[row][col-1] =='|')
                current = getNextPosition();
            else
            {
                offset.x -= tilesize;
            }
        }
        if(current == EnemyPosition::Up)
        {
            if(this_map[row-1][col] =='X' || this_map[row-1][col] =='|')
                current = getNextPosition();
            else
            {
                offset.y -= tilesize;
            }
        }
        if(current == EnemyPosition::Down)
        {
            if(this_map[row+1][col] =='X' || this_map[row+1][col] =='|')
                current = getNextPosition();
            else
            {
                offset.y += tilesize;
            }
        }

    }
    virtual void Render()
    {
        textureManager->getTexture("pacman_enemy_1")->Draw(offset);
    }
    virtual bool isColliding(GameObject* other)
    {
        return false;
    }
};



struct PlayState : public doengine::GameState,
                   public doengine::KeyboardInputhandlingEvent,
                   public doengine::MouseEvent
{
    doengine::Renderer* renderer;

    doengine::TextureManager *textureManager = nullptr;

 
    Player* player= nullptr;
    std::vector<Enemy*> enemies;

    PlayState()
    {
    }

    virtual ~PlayState()
    {
    }

    


    virtual void OnEnter()
    {
                                                                                
        textureManager = doengine::TextureManager::getTextureManager();                
        doengine::TextureManager::getTextureManager()->loadTextureFromFile("pacman_block_1" ,"./assets/gfx/roca.bmp");
        doengine::TextureManager::getTextureManager()->loadTextureFromFile("pacman_food_1"  ,"./assets/gfx/Comida.bmp");
        doengine::TextureManager::getTextureManager()->loadTextureFromFile("pacman_enemy_1" ,"./assets/gfx/enemigo.bmp");
        doengine::TextureManager::getTextureManager()->loadTextureFromFile("pacman_player_1","./assets/gfx/pacman.bmp");
        player = new Player;
        
    }

    void DrawLayer1()
    {
        textureManager->getTexture("layer1")->Draw(0,0);
    }

    void DrawLayer2()
    {
        
    }

    void DrawLayer3()
    {
  
 
    }
    virtual void MouseWheel(const Mouse&)
    {}
    virtual void MouseMove(const Mouse& mouse)
    {
    }

    virtual void MouseButtonDown(const Mouse& mouse)
    {
    }

    virtual void MouseButtonUp(const Mouse& mouse)
    {
    }

    virtual void OnKeydown(const Keyboard& keyboard)
    {
    }

    virtual void OnKeyup(const Keyboard&)
    {
    }

    virtual void OnExit()
    {
    }

    virtual void Update(float elapsed)
    {
        player->Update(elapsed);
        for(auto enemy : enemies)
            enemy->Update(elapsed);
    }


    void RenderMap()
    {

        for(int r=0;r<max_rows;r++)
        {
            for(int c=0;c<max_cols;c++)
            {
                doengine::Rect rect;
                rect.x = c*tilesize;
                rect.y = r*tilesize;
                rect.w = tilesize;
                rect.h = tilesize;
                switch (this_map[r][c])
                {
                    case 'e':
                    {
                        Enemy* enemy = new Enemy(rect);
                        this->enemies.push_back(enemy);
                        this_map[r][c]='E';
                    }

                case 'x':
                case 'X':
                    textureManager->getTexture("pacman_block_1")->Draw(rect);
                    /* code */
                    break;
                case 'o':
                case 'O':
                    textureManager->getTexture("pacman_food_1")->Draw(rect);
                    /* code */
                    break;
                case 'P':
                {
                    this_map[r][c] = 'R';
                    player->setPosition(rect); 
                }
                default:
                    break;
                }
                
                ///pacman_block_1
            }
        }
}
    virtual void Render()
    { 
        RenderMap();
        player->Render();
        for(auto e : enemies)
            e->Render();
    }
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    auto resoltion = doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{1320, 900};
    app->createWindow(rect);
    auto playstate = new PlayState();
    app->addState(playstate, playing);
    app->setState(playing);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Colors::black);
        app->Render();
    }
    app->Quit();
    return 0;
}
