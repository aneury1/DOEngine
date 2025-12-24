#include "Tilemap.h"
#include "TileMapEditor.h"
#include "Logger.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

namespace doengine
{

bool NonScrollCharTileMap::loadTileMapFromFile(const std::string& fn)
{
 
    std::ifstream file(fn);
    if (!file.is_open())
    {
        std::cerr << "Failed to open tilemap file: " << fn << std::endl;
        return false;
    }

    // Clear previous data
    tiles.clear();
    rows = cols = tilesize = 0;

    // Read header
    if (!(file >> rows >> cols >> tilesize))
    {
        std::cerr << "Invalid tilemap header in file: " << fn << std::endl;
        return false;
    }
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
    std::string line;
    std::string full;
    while(std::getline(file, line))
    {
        if(!line.empty())
            full.append(line);
    }
        // IMPORTANT: consume newline after header
    std::cout << full;
    int cr = 0;
    int cc = 0;
    for(auto it : full)
    {
        if(std::isspace(it)|| it =='\n' || it=='\t' || it<= 0x20)continue;
        Tile tile;
        tile.layer = 0;
        tile.offset.x = (cc * tilesize) + paddingLeft;
        tile.offset.y = (cr * tilesize) + paddingTop;
        tile.offset.w = tilesize;
        tile.offset.h = tilesize;
        tile.type = it;
        cc+=1;
        if(cc >= cols)
        {
            cc =  0;
            cr += 1;
        }
        tiles.emplace_back(tile);
    }
    return true;
}

NonScrollCharTileMap::NonScrollCharTileMap()
{
    renderer = Application::getApplication()
        ->getRender();
}
 
void NonScrollCharTileMap::Update(double elapse)
{

}

void NonScrollCharTileMap::Draw()
{
    if (!renderer || tiles.empty())
        return;

    doengine::Rect dst;
    dst.w = tilesize;
    dst.h = tilesize;
    
    for (int r = 0; r < tiles.size(); ++r)
    {
            char tileChar = (char)tiles[r].type;

            auto it = tile_defs.find(tileChar);
            if (it == tile_defs.end())
            {
                
                if(tileChar =='@')
                    renderer->DrawFillRect(tiles[r].offset, doengine::Colors::yellow1);
                else if(tileChar =='*')
                    renderer->DrawFillRect(tiles[r].offset, doengine::Colors::red);
                else if(tileChar =='#')
                    renderer->DrawFillRect(tiles[r].offset, doengine::Colors::blue);
                else if(tileChar =='$')
                    renderer->DrawFillRect(tiles[r].offset, doengine::Colors::green);
                else
                    renderer->DrawFillRect(tiles[r].offset, doengine::Colors::black);
                
                renderer->DrawRect(tiles[r].offset, doengine::Colors::red, 2);
               
                ///const TileDef& tile = (++tile_defs.begin())->second;
                ///dst.x = tiles[r].offset.x; 
                ///dst.y = tiles[r].offset.y;
                
                ///Texture *texture = TextureManager::getTextureManager()->getTexture(tilesetId);
                ///if(texture)
                {
                   
                    /// texture->Draw(dst, {0,0,tilesize,tilesize});
                }
                ////renderer->DrawFillRect()
                /// continue; // unknown tile → skip
            }  
            else
            {
                const TileDef& tile = it->second;
                dst.x = tiles[r].offset.x; 
                dst.y = tiles[r].offset.y;
                Texture *texture = TextureManager::getTextureManager()->getTexture(tile.textureId);
                if(texture)
                {
                    texture->Draw(dst, tile.src);
                }
            } 
    }

    if(debug)
    {
        renderer->DrawRect(debugRect, doengine::Colors::red, 3);
    }
}

void NonScrollCharTileMap::MouseMove(const Mouse& mouse)
{
    if(debug)
    {
        for(auto it : tiles)
        {
            if(checkCollision(mouse.getMousePosition(), it.offset))
            {
                debugRect = it.offset;
            }
        }
    }
}

void NonScrollCharTileMap::MouseButtonDown(const Mouse& mouse)
{
    for(auto& it : tiles)
    {
        if(checkCollision(mouse.getMousePosition(), it.offset))
        {
            if(type_to_change_by_editor!=0)
                it.type = this->type_to_change_by_editor;
            debugRect = it.offset;
        }
    }

}

void NonScrollCharTileMap::MouseButtonUp(const Mouse&){}




void NonScrollCharTileMap::setTileDef(std::unordered_map<char, TileDef> tile_defs)
{
    this->tile_defs = tile_defs;
    for(auto tiled : tile_defs)
    {
        LogOuput(logger_type::Information,
            "type=[%c], textureId=[%s] clipset[%d, %d, %d, %d]",
            tiled.first,
            tiled.second.textureId.c_str(),
            tiled.second.src.x,
            tiled.second.src.y,
            tiled.second.src.w,
            tiled.second.src.h
        );
    }
}

void NonScrollCharTileMap::setTileMapEditor(TileMapEditor *ptr)
{
    this->editor = ptr;
    if(editor)
    {

        editor->registerSelectedTileByChar([&](char c){
            std::cout << "Tile selected: " << c << std::endl;
            this->type_to_change_by_editor = c;
        });
    }
}

void NonScrollCharTileMap::changeGroupOfTileByRectCollision(char ch, doengine::Rect rect)
{
   for(auto &tile : tiles)
   {
       if(checkCollision(tile.offset, rect))
       {
          tile.type = ch;
       }
   }
}


char NonScrollCharTileMap::getTile(int row, int col) const
{
    return 0;
}


////////
////////


ScrollableCharTileMap::ScrollableCharTileMap()
{

}

ScrollableCharTileMap::~ScrollableCharTileMap()
{

}

bool ScrollableCharTileMap::loadTileMapFromFile(const std::string& fn)
{
   return false;
}

void ScrollableCharTileMap::Update(double)
{

}
void ScrollableCharTileMap::Draw()
{

}

void ScrollableCharTileMap::setTileDef(std::unordered_map<char, TileDef> tile_defs)
{

}
void ScrollableCharTileMap::setTileMapEditor(TileMapEditor *ptr)
{

}
void ScrollableCharTileMap::changeGroupOfTileByRectCollision(char ch, doengine::Rect rect)
{

}

void ScrollableCharTileMap::MouseMove(const Mouse&)
{
    
}

void ScrollableCharTileMap::MouseButtonDown(const Mouse& m)
{

}
    
void ScrollableCharTileMap::MouseButtonUp(const Mouse& m)
{

}

} // namespace doengine
