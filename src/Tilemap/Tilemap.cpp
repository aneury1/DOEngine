#include "TileMap.h"
#include "Application.h"
#include "Logger.h"
#include "StringUtils.h"
#include "Renderer.h"
#include "pugixml.hpp"

#include <fstream>
#include <iostream>
#include <stdio.h>

namespace doengine
{
 

const Rect clipsetOfType[]=
{
   {(21*16),0,16,16},
   {(16*16),0,16,16},
   {(17*16),16,16,16},
   {(18*16),16+16,16,16},
   {(19*16),16*3,16,16},
   {(19*16),16*3,16,16},
   {(18*16),16*3,16,16},
   {(21*16),0,16,16},
   {(21*16),0,16,16},
   {(21*16),0,16,16},
   {(21*16),0,16,16},
   {(21*16),0,16,16},
};

const Color colorsMap[]=
{
    yellow,
    red,
    black,
    blue,
    white,
    white,
    white,
    white,
    white,
    white,
    white,
    white
};

void Tile::Draw(Renderer *render)
{
   Rect offsetWithPadding=
      {
         offset.x+200,
         offset.y,
         offset.w,
         offset.h
      };
   if(texture)
   {

      texture->Draw(offsetWithPadding, clipset);
   }
   
   if(Application::getApplication()->isDebug())
   {
      render->DrawRect(offsetWithPadding, yellow);
      std::stringstream stream;
      stream << index;
      if(textTexture)
      {
         textTexture->DrawText(stream.str().c_str(),offsetWithPadding.x+4,
           offsetWithPadding.y+3);
      }
   }
}


void TileMap::MoveEditorCursor(EditorCursorPosition c)
{
   switch(c)
   {
     case EditorCursorPosition::Bottom:
        cursorRow++;
        break;
     case EditorCursorPosition::Top:
        cursorRow--;
        break;
     case EditorCursorPosition::Left:
        cursorCol--;
        break;
     case EditorCursorPosition::Right:
        cursorCol++;
        break;
   }
}


void TileMap::displayEditor()
{
    auto renderer = Application::getApplication()->getRender();
    offsetOfMap.x = 20;
    offsetOfMap.y = 20;
    offsetOfMap.w = texture->getWidth()*2 + 250;
    offsetOfMap.h = texture->getHeight()*2 + 100;

    texturePosition.x = offsetOfMap.x + 32;
    texturePosition.y = offsetOfMap.y + 32;
    texturePosition.w = texture->getWidth()*2;
    texturePosition.h = texture->getHeight()*2;

    cursorRect.x = (texturePosition.x + cursorCol * scaledTileW) ;
    cursorRect.y = texturePosition.y + cursorRow * scaledTileH;
    cursorRect.w = scaledTileW;
    cursorRect.h = scaledTileH;

    renderer->DrawFillRect(offsetOfMap, black);
    texture->Draw(texturePosition);
    renderer->DrawRect(cursorRect, red);
    texture->Draw(previousOffset, selClipset);


    std::stringstream stream;

    stream <<"("<< this->cursorCol<<", "<<this->cursorRow<<")";

    textTexture->DrawText(stream.str().c_str()
        , previousOffset.x + (previousOffset.w / 2), 
        previousOffset.y + previousOffset.h + 21);

    bool isInvalid = cursorCol < 0 
        || cursorCol > 24 
        || cursorRow < 0
        || cursorRow >=16;

    if(isInvalid)
    {
        textTexture->setColor(black, red);
        textTexture->DrawText("Invalid Position...", previousOffset.x-10
        ,previousOffset.y + previousOffset.h + 100);
    }
    bool tanqs = cursorCol< 16;
    if(tanqs)
    {
       /// textTexture->setColor(black, blue5);
        textTexture->DrawText("Non Selectable tiles"
        , previousOffset.x-10,
         previousOffset.y + previousOffset.h +  64);
    }
}

 TileMap::TileMap()
 {
    textTexture = new TTFText();
    textTexture->setFont("/home/neon/Desktop/DOEngine/assets/fonts/NirmalaB.ttf", 18);
    textTexture->setColor(black, red);
 }

void TileMap::loadTileMap(int r, int c, int ts, int *map)
{
   this->r = r;
   this->c = c;
   this->tilesize = ts;
   this->map = map;
   for(int row=0;row<r;row++)
   {
      for(int cols=0;cols<c;cols++)
      {
            Rect offset=
            {
                cols * tilesize * 3,
                row  * tilesize * 3,
                tilesize * 3,
                tilesize * 3
            };
            auto type = this->map[row * c + cols];
            auto clipset = clipsetOfType[type];
            Tile *tile = new Tile();
            tile->index = type;
            tile->layer = 1;
            tile->type = type;
            tile->offset.x = offset.x;
            tile->offset.y = offset.y;
            tile->offset.w = offset.w;
            tile->offset.h = offset.h;
            tile->clipset.x = clipset.x; 
            tile->clipset.y = clipset.y; 
            tile->clipset.w = clipset.w; 
            tile->clipset.h = clipset.h;
            tile->texture = texture;
            tile->tileset_path = tilset_path;
            tile->textTexture = textTexture;
            tileset.emplace_back(tile);
      }
   }

}

void TileMap::loadTexture(const std::string path)
{
   texture = new Texture(path.c_str());
   tilset_path = path;
   for(auto it : tileset)
   {
      it->tileset_path = path;
      it->texture = texture;
      it->textTexture = textTexture;
   }
}

void TileMap::render(Renderer *render)
{
   render->setDrawColor(doengine::gray);
   render->clear();

 
   if(showEditor)
   {
       displayEditor();
       return;
   }

   for(auto tile : tileset)
      tile->Draw(render);
}





TileMapData *TileMapData::fromXMLStr(const std::string& str)
{
    TileMapData *ret = new TileMapData;
    ret->valid = false;
   
  
    return ret;
}
TileMapData *TileMapData::fromXMLFile(const std::string& path)
{


   return nullptr;
}

} // namespace doengine
