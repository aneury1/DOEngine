#include "Application.h"
#include "GameState.h"
#include "Logger.h"
#include "Texture.h"
#include "TTFText.h"
#include "Event.h"


#include <SDL2/SDL.h>
#include <random>
#include <ctime>

std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(0, 2);
#define ROWS 16
#define COLS 20
char tilemap[ROWS][COLS]=
{
   {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','2','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
   {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
};



char get_random_char(){
    int random_number = dist(rng);
    switch(random_number){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        default: return '1';
    }
    ///return char(random_number - '0');
}


struct TestGameState : public GameState{

    Renderer *renderer;
    TTFText *textHandler;
    bool showHint = false;
    
    void reset_tile_map(){
        for(int row=0;row<ROWS;row++)
        {
            for(int col=0;col<COLS;col++)
            {
                tilemap[row][col]='0';
            }
        }
    }

    void save_tile_map(){

    }

    void appQuit(){
        Application::getApplication()->Quit();
    }

    void generate_random_map(){
      for(int row=0;row<ROWS;row++)
        {
            for(int col=0;col<COLS;col++)
            {
                tilemap[row][col]= get_random_char();
            }
        }
    }

    struct KeyboardEventHandler : KeyDownEvent{
 
        public:
        TestGameState *test;
        KeyboardEventHandler(TestGameState *this_handler){
            test = this_handler;
        }
        
        ~KeyboardEventHandler()
        {
       
       
        }

        virtual void OnKeydown(int code){
            SDL_Log("keydown: %02x", code);
            switch(code){
                case 0x1b: test->appQuit();return;
                case 0x31: test->reset_tile_map(); return;
                case 0x32: test->save_tile_map(); return;
                case 0x33: test->generate_random_map(); return;
            }
        }
    
    
    };
    KeyboardEventHandler* keyboardEventHandler;


    struct MouseEventHandler : public MouseEvent{
    virtual ~MouseEventHandler()
    {
    }

        virtual void MouseMove(unsigned int which, int x, int y){
            /// SDL_Log("Mouse Movement in %d %d", x,y);
             int row = x / ROWS;
             int col = y / COLS;
            //// SDL_Log("Mouse Movement COL ==> %d %d", row,col);

        }

        virtual void MouseButtonDown(unsigned int which, MouseButton button, int x, int y){
             ////SDL_Log("Mouse Button down");
            /// SDL_Log("Mouse Movement in %d %d", x,y);
             int row = y / 32;
             int col = x / 32;
             bool r =row>=0||row<ROWS;
             bool c =col>=0||col<COLS;
            /// SDL_Log("Really?? %d %d", r, c);
             if(r&&c){
                tilemap[row][col]= '1';
             }else{
              ////  SDL_Log("Really??");
             }
             
            //// SDL_Log("Mouse Movement COL ==> %d %d", row,col);
        }

        virtual void MouseButtonUp(unsigned int which, MouseButton button, int x, int y){
            
        }
    }mouseEventHandler;



    virtual void OnEnter(){
        keyboardEventHandler = new KeyboardEventHandler(this);
        Event::AddMouseEvent(&mouseEventHandler);
        Event::AddKeyPressEventListener(keyboardEventHandler);
        renderer = Application::getApplication()->getRender();
        textHandler = new TTFText();
        textHandler->setFont("testfont.ttf", 16);
    }
    virtual void OnExit(){
        Event::RemovedMouseEvent(&mouseEventHandler);
        Event::RemoveKeyPressEventListener(keyboardEventHandler);
    }
    virtual void Update(float elapsed) {
     
    }
    virtual void Render(){
        renderOptions();
        for(int row= 0;row<ROWS;row++)
        {
            for(int col =0;col<COLS;col++)
            {
                Rect block;
                block.w = 32;
                block.h = 32;
                block.x = col * 32 ;///+ 20;
                block.y = row * 32 ;///+ 72;
                Color color;
                getTileColorByChar(color,tilemap[row][col]);
                renderer->DrawFillRect(block, color);
                DrawYellowGrid(block.x, block.y,32,renderer);
            }
        }
    }

   
    void renderOptions(){
        Color yellow;
        yellow.a = 255;
        yellow.r = 255;
        yellow.g = 255;
        yellow.b = 0;
        Color Red;
        Red.a = 255;
        Red.r = 255;
        Red.g = 0;
        Red.b = 0;
        int tmpw =0;
        int tmph =0;
        textHandler->setForegroundColor(yellow);
        textHandler->setFontSize(24);
        textHandler->DrawText("Opciones del Mapa",650, 16);

        textHandler->getTextSize("Escape",&tmpw, &tmph);

        textHandler->setForegroundColor(Red);
        textHandler->DrawText("Escape",650, 58);
        textHandler->setForegroundColor(yellow);
        textHandler->DrawText("Salir de la app",760, 58);


        textHandler->setForegroundColor(Red);
        textHandler->DrawText("1 -> ",650, 128);
        textHandler->setForegroundColor(yellow);
        textHandler->DrawText("Reset Map",760, 128);

        textHandler->setForegroundColor(Red);
        textHandler->DrawText("2 -> ",650, 192);
        textHandler->setForegroundColor(yellow);
        textHandler->DrawText("Guardar",760, 192);

        textHandler->setForegroundColor(Red);
        textHandler->DrawText("3 -> ",650, 256);
        textHandler->setForegroundColor(yellow);
        textHandler->DrawText("Aleatorio Map",760, 256);



        textHandler->DrawText("Modo edicion: ",10, ROWS * 32 + 10);
    }


     void getTileColorByChar(Color& color, char ch ){
         switch(ch)
         {

            case '2':
                color.r = 255;
                color.a =255;
                color.g =100;
                color.b = 255;

            break;

            case '1':
                color.r = 0;
                color.a =255;
                color.g =100;
                color.b = 255;

            break;
            case '0':
            default:
                color.r = 0;
                color.a =255;
                color.g =0;
                color.b = 255;
         }
     }


     void DrawYellowGrid(int x, int y, int tiz, Renderer *render){
                Rect block;
                block.w = 32;
                block.h = 32;
                block.x = x;
                block.y = y;
                Color color;
                color.r = 100;
                color.a =255;
                color.g =100;
                color.b = 0;
                render->DrawRect(block, color);
     }

};



int main(int argc, char *argv[]){
   auto app = Application::getApplication();
   app->createWindow({1000,800});

   auto testState = new TestGameState();

   app->addState(testState, 1);
   app->setState(1);

   Color color;
   color.rgba = 0x00000000;
   while(app->IsRunning()){
    
       app->PollEvent();
       app->Update();
       app->clearScreen(color);
       app->Render();
   }
   
   return 0;
}