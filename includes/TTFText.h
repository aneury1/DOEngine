#pragma once
#include <string>
#include "Application.h"
#include "DOEngine.h"
#include "Geometric.h"
#include "Font.h"

class Application;
class Texture;
class Renderer;

struct NativeTextRenderer{
 
    virtual void setFont(const std::string& path, int fntsize) = 0;
    virtual void DrawText(const char* text, int x, int y)= 0;
    virtual Texture* createText(const std::string& text)=0 ;
    virtual void setColor(Color fg, Color bg) = 0;
    virtual void setForegroundColor(Color color) = 0;
    virtual void setBackgroundColor(Color color) = 0;
    virtual void setFontSize(int fntSize) =0;
    virtual void getTextSize(const std::string& text, int *w, int *h) =0;

};


class TTFText
{
  
  NativeTextRenderer *nativeRenderer;

  public:
  TTFText();
  void setFont(const std::string& path, int fntsize);
  void DrawText(const char* text, int x, int y);
  Texture* createText(const std::string& text);
  void setForegroundColor(Color color);
  void setBackgroundColor(Color color);
  void setFontSize(int fntSize);
  void setColor(Color fg, Color bg);
  void getTextSize(const std::string& text, int *w, int *h);
};