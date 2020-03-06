#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include "GeometricRender.h"

struct WindowObserver
{
    virtual void OnQuit()=0;
    virtual void OnFullscreen()=0;
    virtual void OnMinimize()=0;
};


struct KeyboardObserver{
   virtual void onKeyDown(std::map<SDL_Keycode, bool>keys)=0;
   virtual void onKeyUp(std::map<SDL_Keycode, bool>keys)=0;
};



struct MouseObserver{
   virtual void onMouseMotion(Point point)=0;
   virtual void onMouseButtonDown(int wich)=0;
   virtual void onMouseButtonUp(int wich)=0;
};

struct TouchObserver{
   virtual void onTouchMotion(Point point)=0;
   virtual void onTouchButtonDown(int wich)=0;
   virtual void onTouchButtonUp(int wich)=0;
};

struct Event
{
    bool keydown_done;
    bool keydown_up;
    bool mouse_move;
    bool touch_motion;
    bool touch_click;
    std::map<SDL_Keycode, bool>keydown;
    std::map<SDL_Keycode, bool>keyup;
    Point mouse_pointer;
    void *keys;


    std::vector<WindowObserver*>window_observers;
    std::vector<KeyboardObserver*>keyboard_observers;
    std::vector<MouseObserver*>mouse_observers;
    std::vector<TouchObserver*>touch_observers;

    void addKeyboardObserver(KeyboardObserver *ob);
    void addMouseObserver(MouseObserver *mo);
    void addTouchObserver(TouchObserver *to);
 
    void removeKeyboardObserver(KeyboardObserver *ob);
    void removeMouseObserver(MouseObserver *mo);
    void removeTouchObserver(TouchObserver *to);
   
    void PollEvent();

    static Event *getEventHandler(){
       if(!single)
          single = new Event;
          return single;
    }

    private:
    static Event *single;
    Event(){}

};