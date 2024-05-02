#include "StringUtils.h"
#include "Tilemap.h"
#include <fstream>
#include <stdio.h>

SimpleLayerTileMap::SimpleLayerTileMap(): TileMap(){
 
      std::cout <<"HERER";
      texture = nullptr;
      std::cout <<"HERER";
      thisMap.clear();
      std::cout <<"HERER";

    }
SimpleLayerTileMap::~SimpleLayerTileMap(){
      std::cout <<"HERER";
}


void SimpleLayerTileMap::setMapRenderer(MapRenderer *render){
   this->mapRenderer = render;
}
void SimpleLayerTileMap::loadTileMapFromFile(const char* file){    
    readMapFile("../sample/assets/maps/simple-map1.map", thisMap);


}
void SimpleLayerTileMap::render(){

}
void SimpleLayerTileMap::update(){
    
}
