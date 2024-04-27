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
   SDL_Log("is valid = %ld %s", this->realNativeTexture->validTexture(), SDL_GetError());
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
 