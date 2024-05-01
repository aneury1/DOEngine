#include "Texture.h"
#include "Application.h"

#include <SDL2/SDL.h>

Texture::Texture(std::string path){
   auto render = Application::getApplication()->getRender();
   Color color;
   color.r = 0;
   color.g = 0;
   color.b = 0;
   color.a = 0;
   this->realNativeTexture = render->loadTextureFromImageFile(path.c_str(), color); 
  /// SDL_Log("is valid = %ld %s", this->realNativeTexture->validTexture(), SDL_GetError());
}
Texture::~Texture(){}
void Texture::Draw(const Rect &offset){
    this->realNativeTexture->Draw(offset);
}
void Texture::Draw(const Rect &offset, const Rect& clipset){
    this->realNativeTexture->Draw(offset, clipset);
}
void Texture::ModulateColor(const Color& color){
    this->realNativeTexture->ModulateColor(color);
}
int Texture::getWidth(){
    return this->realNativeTexture->getWidth();
}
int Texture::getHeight(){
    return this->realNativeTexture->getHeight();
}


 Texture *Texture::subTexture(const Rect& clipset){
    Texture *ret = new Texture();
    ret->realNativeTexture = this->realNativeTexture->subTexture(clipset);
    return ret;
 }



TextureManager *TextureManager::instance;

std::map<std::string, Texture*> textures;


TextureManager *TextureManager::getTextureManager(){
    if(instance == nullptr)
       instance = new TextureManager();
    return instance;
}

void TextureManager::loadTextureFromFile(std::string id, std::string src){
    Texture *texture = new Texture(src);
    addTexture(id, texture);
}

void TextureManager::loadTextureFromTexture(std::string id, Texture* texture, const Rect &clipset){
    ///Todo, easy.
}

void TextureManager::addTexture(std::string id, Texture* texture){
    auto it = textures.find(id);
    if(texture->validTexture()){
         if(it != textures.end()){
            removeTexture(id);
         }else{
           textures[id] = texture;
         }
    }
}

void TextureManager::removeTexture(std::string id){
 
}

 Texture *TextureManager::getTexture(std::string id){
    ///todo: add validation
    return textures[id];
 }