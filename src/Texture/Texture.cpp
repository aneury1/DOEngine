/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */


#include "Texture.h"
#include "Application.h"
#include <variant>
namespace doengine
{
Texture::Texture()
{
    realNativeTexture = nullptr;
}

void Texture::SetTransparentColor(const Color& color)
{
    realNativeTexture->SetTransparentColor(color);
}

Texture::Texture(std::string path)
{
    auto render = Application::getApplication()->getRender();
    Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
    this->realNativeTexture =
        render->loadTextureFromImageFile(path.c_str(), color);
}

Texture::Texture(std::string path, const Color& color)
{
    auto render = Application::getApplication()->getRender();
    this->realNativeTexture =
        render->loadTextureFromImageFile(path.c_str(), color);
}

Texture::~Texture()
{
    delete realNativeTexture;
}
void Texture::Draw(int x, int y)
{
    realNativeTexture->Draw(x, y);
}
void Texture::Draw(const Rect& offset)
{
    realNativeTexture->Draw(offset);
}

void Texture::Draw(const Rect& offset, const Rect& clipset)
{
    this->realNativeTexture->Draw(offset, clipset);
}
void Texture::Draw(const Rect& offset, const Rect& clipset, const double angle)
{
    this->realNativeTexture->Draw(offset, clipset, angle);
}

void Texture::Draw(const Rect& offset, const Rect& clipset, const double angle,
                   const Point& center)
{
    this->realNativeTexture->Draw(offset, clipset, angle, center);
}
void Texture::ModulateColor(const Color& color)
{
    this->realNativeTexture->ModulateColor(color);
}
int Texture::getWidth()
{
    return this->realNativeTexture->getWidth();
}
int Texture::getHeight()
{
    return this->realNativeTexture->getHeight();
}
bool Texture::validTexture()
{
    return realNativeTexture->validTexture();
}

Texture* Texture::subTexture(const Rect& clipset)
{
    Texture* ret = new Texture();
    ret->realNativeTexture = this->realNativeTexture->subTexture(clipset);
    return ret;
}

Texture* Texture::setNativeTexture(void* t)
{
    Texture* ret = new Texture();
    ret->realNativeTexture =
        Application::getApplication()->getRender()->createTexture();
    ret->realNativeTexture->setNativeTexture(t);
    return ret;
}

TextureManager* TextureManager::instance;

std::map<std::variant<std::string, int>, Texture*> textures;

TextureManager* TextureManager::getTextureManager()
{
    if (instance == nullptr)
        instance = new TextureManager();
    return instance;
}

void TextureManager::loadTextureFromFile(
    const std::variant<std::string, int>& id, string src, const Color  )
{
    Texture* texture = new Texture(src);
    addTexture(id, texture);
}

void TextureManager::loadTextureFromTexture(std::string  , Texture*  ,
                                            const Rect&  )
{
    /// Todo, easy.
}

void TextureManager::addTexture(std::string id, Texture* texture)
{
    auto it = textures.find(id);
    if (texture->validTexture())
    {
        if (it != textures.end())
        {
            removeTexture(id);
        }
        else
        {
            textures[id] = texture;
        }
    }
}
void TextureManager::addTexture(const std::variant<std::string, int>& id,
                                Texture* texture)
{
    auto it = textures.find(id);
    if (texture->validTexture())
    {
        if (it != textures.end())
        {
            // removeTexture(id);
        }
        else
        {
            textures[id] = texture;
        }
    }
}

void* Texture::getNativeBuffer()
{
    return this->realNativeTexture->getNativeBuffer();
}

void TextureManager::removeTexture(std::string )
{
}

Texture* TextureManager::getTexture(const std::variant<std::string, int>& id)
{

    auto find = textures.find(id);
    if (find == textures.end())
        return new Texture();
    return find->second;
}

Texture* TextureManager::getTextureOr(const std::variant<std::string, int>& id,
                                      std::function<void()>  )
{
    return textures[id];
}

void TextureManager::loadFont(const std::variant<std::string, int>& key,
                              string src, int pts)
{
    auto pf = new TTFText();
    pf->setFont(src, pts);
    fonts[key] = pf;
}
TTFText* TextureManager::getFont(const std::variant<std::string, int>& id)
{
    return fonts[id];
}

TextureManager::TextureStatus TextureManager::drawTexture(const std::string id,
                                                          const Rect offset,
                                                          const Rect clipset)
{
    auto text = getTexture(id);
    if (text == nullptr)
        return TextureManager::TextureStatus::TextureIdInvalid;
    text->Draw(offset, clipset);
    return TextureManager::TextureStatus::Success;
}
TextureManager::TextureStatus TextureManager::drawTexture(const std::string id,
                                                          const Rect offset)
{
    auto text = getTexture(id);
    if (text == nullptr)
        return TextureManager::TextureStatus::TextureIdInvalid;
    text->Draw(offset);
    return TextureManager::TextureStatus::Success;
}

} // namespace doengine
