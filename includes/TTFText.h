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
    virtual void setColor(Color color) = 0;
    virtual void setFont(const std::string& path, int fntsize) = 0;
    virtual void DrawText(const char* text, int x, int y)= 0;
    virtual Texture* createText(const std::string& text)=0 ;
};


class TTFText
{
  
  NativeTextRenderer *nativeRenderer;

  public:
  TTFText();
  void setColor(Color color);
  void setFont(const std::string& path, int fntsize);
  void DrawText(const char* text, int x, int y);
  Texture* createText(const std::string& text);
};