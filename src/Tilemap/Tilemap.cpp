#include "StringUtils.h"
#include "Tilemap.h"
#include <fstream>
#include <stdio.h>

SimpleLayerTileMap::SimpleLayerTileMap(): TileMap(){
 
    
      texture = nullptr;
      margin_left = 14;
      margin_top = 72;
      thisMapRows.clear();
     

    }
SimpleLayerTileMap::~SimpleLayerTileMap(){
       
}


void SimpleLayerTileMap::setMapRenderer(MapRenderer *render){
   this->mapRenderer = render;
}
#include <SDL2/SDL.h>
void SimpleLayerTileMap::loadTileMapFromFile(const char* file){    
    readMapFile("../sample/assets/maps/simple-map1.map", thisMapFile);
        tileset_asset = thisMapFile[0];
        rows= StringAsInt(thisMapFile[1]);
        cols= StringAsInt(thisMapFile[2]);
        auto sw = Application::getApplication()->getW();
        auto sh = Application::getApplication()->getH();
        tilesize_width  = (sw - margin_left) / rows ;
        tilesize_height = tilesize_width;  ///(sh - margin_top)  / cols ;

        SDL_Log("tilesizew =(%d, %d)", tilesize_width, tilesize_height);

        for(int r = 0; r <= rows; r++){
        SDL_Log("tilesizew =(%d, %d)", tilesize_width, tilesize_height);
           
          std::string row = thisMapFile[r+2];
          SDL_Log("Row=%s", row.c_str());
          std::vector<char> chars = splitChar(row," \r\n\t\0");
  
          thisMapRows.emplace_back(chars);
        }
    
}

void SimpleLayerTileMap::render(){
    if(mapRenderer)
       mapRenderer->RenderTileMap(thisMapRows);
}

void SimpleLayerTileMap::update(){
    
}

int SimpleLayerTileMap::getTileType(int r, int c){
    return (int)thisMapRows[r][c];
}