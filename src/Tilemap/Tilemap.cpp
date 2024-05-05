#include "StringUtils.h"
#include "Tilemap.h"
#include "Logger.h"
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

void SimpleLayerTileMap::loadTileMapFromFile(const char* file){    
    readMapFile(file, thisMapFile);
        tileset_asset = thisMapFile[0];
        rows= StringAsInt(thisMapFile[1]);
        cols= StringAsInt(thisMapFile[2]);
        auto sw = Application::getApplication()->getW();
        auto sh = Application::getApplication()->getH();
        tilesize_width  = (sw - margin_left) / rows ;
        tilesize_height = tilesize_width;  ///(sh - margin_top)  / cols ;

        for(int r = 0; r <= rows; r++){  
          std::string row = thisMapFile[r+2];
          DO_TRACE("Row=%s", row.c_str());
          std::vector<char> chars = splitChar(row," \r\n\t\0");
          thisMapRows.emplace_back(chars);
        }
}

void SimpleLayerTileMap::saveLoadedTileMap(){

}

void SimpleLayerTileMap::setTileType(int r, int c, char t){
   if((r >=0 || r<=this->rows) &&(c >=0 || c<=this->cols)){
      DO_TRACE("CHANGE ROW=%d, COL=%d FROM %c TO %d", r,c,thisMapRows[r][c], t);
      thisMapRows[r][c]=t;
   }
}
char SimpleLayerTileMap::getTileType(int r, int c){
   if((r >=0 || r<=this->rows) &&(c >=0 || c<=this->cols)){
      return thisMapRows[r][c];
   }
   return (char)0xFF;
}


void SimpleLayerTileMap::render(){
    if(mapRenderer)
       mapRenderer->RenderTileMap(thisMapRows);
}

void SimpleLayerTileMap::update(){
    
}
