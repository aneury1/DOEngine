#define ROWS 16
#define COLS 20
char ftilemap[ROWS][COLS]=
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


#include <sstream>


enum class PaddleType{
   Left,
   Right,
   Top,
   Bottom,
   Center
};


constexpr int PaddleWidth =32;
constexpr int PaddleHeight =200;

struct Particle : public GameObject{

   enum class PIndex{
      i1,
      i2,
      i3
   };
   PIndex current;
   Rect rect;
  
  
   Renderer *renderer;


   Particle(int x,int y){
      rect.x = 400;
      rect.y = 400;
      rect.w = 8;
      rect.h = 8;
      renderer= Application::getApplication()->getRender();
   }

 

    virtual void Update(float timer = 0){
       
       if(current==PIndex::i3)
          current= PIndex::i1;
       else 
          current = (current==PIndex::i1)?PIndex::i2:PIndex::i3; 
    }
    virtual void Render(){
        Color c1;
        Color c2;
        Color c3;
        Color c4;

        switch(current)
        {
         case PIndex::i1:
            c1 = white;
            c2 = red;
            c3 = blue;
            c4 = green;
         case PIndex::i2: 
            c1 = red;
            c2 = white;
            c3 = green;
            c4 = blue;
         case PIndex::i3: 
            c1 = green;
            c2 = white;
            c3 = red;
            c4 = blue;
        }
 
         rect.w = 100;
         rect.h = 100;
         rect.x = 400;
         rect.y = 400;


         renderer->DrawFillRect(rect,c1);
         rect.x += 5;
         
         renderer->DrawFillRect(rect,c2);
         rect.x -= 10;
         renderer->DrawFillRect(rect,c3);
         rect.x -= 5;
         rect.y -= 5;
         renderer->DrawFillRect(rect,c3);
         rect.y -= 10;
         renderer->DrawFillRect(rect,c4);
             
    }
};



struct Paddle : public GameObject{

   PaddleType type;
   Rect rect;
   Color color;
   Application* app;
   Renderer   *renderer;
   
   int paddleSpeed = 10;

   void MoveUp(){
      rect.y -= paddleSpeed;
      if(rect.top() <= 0)
        rect.y += paddleSpeed;
   }
   void MoveDown(){
      rect.y += paddleSpeed;
      if(rect.bottom()>=app->getH())
        rect.y -= paddleSpeed;
   }

   


   void init(){
         color.r = 255;
         color.g = 255;
         color.b = 255;
         color.a = 255;
         paddleSpeed = 10;
        switch(type){
         case PaddleType::Left:
         rect.x = 6;
         rect.y = app->getH()/2 - 100;
         rect.w = PaddleWidth;
         rect.h = PaddleHeight;
         break;
         case PaddleType::Right:
         rect.x = app->getW() - PaddleWidth - 6;
         rect.y = app->getH()/2 - 100;
         rect.w = PaddleWidth;
         rect.h = PaddleHeight;
         break;
        }
   }

   Paddle(const PaddleType& type):GameObject(), type{type}{
      app = Application::getApplication();
      renderer= app->getRender();
      init();
   
   }


    virtual ~Paddle(){}
 
 
    virtual void Update(float timer = 0){

    }
    virtual void Render(){
      renderer->DrawFillRect(rect, color);
    }
};




struct Ball : public GameObject {
    
    Rect coords;
    int radius;

    int bally_speed;
    int ballx_speed;
     
    Application* app;
    Renderer   *renderer;
    void init(){
        coords.x = (app->getW() / 2) - 16;
        coords.y = (app->getH() / 2) - 16;
        radius = 16;
        bally_speed = -1;
        ballx_speed = -1;
    }

    Ball(){
      app = Application::getApplication();
      renderer = app->getRender();
      init();
    }
    virtual ~Ball(){}

    void checkAndUpdateByCollision(Paddle* paddle){
       if(checkCollision(coords,paddle->rect))
        {         
           bally_speed = -bally_speed;
           ballx_speed = -ballx_speed;
        }
      
    }

    virtual void Update(float timer){

      if(coords.top() <=16 || coords.bottom() >= app->getH()){
         bally_speed *= -1;
      }
      if(coords.left()<=16 || coords.right() >= app->getW()){
         ballx_speed *= -1;
      }

      coords.x += ballx_speed * 16;
      coords.y += bally_speed * 16;
    }
    virtual void Render(){
       renderer->FillCircle(coords.x, coords.y,radius ,white);
    }
};

struct PongGameState : public GameState, KeyDownEvent{

    Application* app;
    WindowManager* winManager;
    Renderer* renderer;
    TTFText* font;
    MapRenderer *mapRenderer;
    SimpleLayerTileMap *tileMap;
    Particle* ts =new Particle(400,400);

    Paddle* left;
    Paddle* right;
    Ball  * ball;

    virtual void OnKeydown(int code){
        
        switch (code)
        {
        case 119:
           left->MoveUp();
         break;
        case 115:
           left->MoveDown();
           break;
        case 1073741906:
           right->MoveUp();
           break;
        case 1073741905:
           right->MoveDown();
           break;
        default:
           DO_TRACE("key NOT HANDLED %d", code);
         break;
        }
 
        
    }


    virtual void OnEnter(){
       app          = Application::getApplication();
       winManager   = app->getWindow();
       renderer     = winManager->getRenderer();
       font         = new TTFText();
       font->setFont("./testfont.ttf", 20);
       left = new Paddle(PaddleType::Left);
       right = new Paddle(PaddleType::Right);
       ball  = new Ball();
       Event::AddKeyPressEventListener(this);
    }
    virtual void OnExit(){

    }
    virtual void Update(float elapsed){
        ball->Update(0);
        left->Update(elapsed);
        right->Update(elapsed);
        ball->checkAndUpdateByCollision(left);
        ball->checkAndUpdateByCollision(right);
    }
    virtual void Render(){
      ts->Render();
      ball->Render();
      left->Render();
      right->Render();
    }
};

