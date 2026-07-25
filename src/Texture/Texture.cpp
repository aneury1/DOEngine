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
#include "NativeStructs.h"
#include "Logger.h"
#include <variant>
namespace doengine
{
Texture::Texture()
{
    realNativeTexture = nullptr;
}

void Texture::SetTransparentColor(const Color& color)
{
    if (realNativeTexture)
        realNativeTexture->SetTransparentColor(color);
}

Texture::Texture(std::string path)
{
    this->realNativeTexture = nullptr;
    if (!Application::getApplication()->IsRunning())
        return;
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
    this->realNativeTexture = nullptr;

    
    auto render = Application::getApplication()->getRender();
    this->realNativeTexture =
        render->loadTextureFromImageFile(path.c_str(), color);
}

Texture::Texture(std::string path, doengine::NativeTexture* realNativeTexture)
    : realNativeTexture(realNativeTexture)
{
}

Texture::~Texture()
{
    if (realNativeTexture)
    {
        realNativeTexture->Destroy();
        realNativeTexture.reset();
    }
}
void Texture::Draw(int x, int y)
{
    if (!realNativeTexture)
        return;
    realNativeTexture->Draw(x, y);
}
void Texture::Draw(const Rect& offset)
{
    if (!realNativeTexture)
        return;

    realNativeTexture->Draw(offset);
}

void Texture::Draw(const Rect& offset, const Rect& clipset)
{
    if (!realNativeTexture)
        return;

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
    if (!realNativeTexture)
        return;

    this->realNativeTexture->ModulateColor(color);
}
int Texture::getWidth()
{
    if (!realNativeTexture)
        return 0;

    return this->realNativeTexture->getWidth();
}
int Texture::getHeight()
{
    if (!realNativeTexture)
        return 0;

    return this->realNativeTexture->getHeight();
}
bool Texture::validTexture()
{
    if (!realNativeTexture)
        return false;

    return realNativeTexture->validTexture();
}

void Texture::LoadTexture(const std::string& file, const Color& color)
{
    if(!Application::getApplication()->IsRunning())return;
    if (!realNativeTexture)
    {
        auto render = Application::getApplication()->getRender();
        this->realNativeTexture =
            render->loadTextureFromImageFile(file.c_str(), color);
    }
    else
    {
        realNativeTexture->Destroy();
    }
}

std::shared_ptr<Texture> Texture::subTexture(const Rect& clipset)
{
    std::shared_ptr<Texture> ret = std::make_shared<Texture>();
    ret->realNativeTexture = this->realNativeTexture->subTexture(clipset);
    return ret;
}

std::shared_ptr<Texture> Texture::setNativeTexture(void* t)
{
    std::shared_ptr<Texture> ret = std::make_shared<Texture>();
    ret->realNativeTexture =
        Application::getApplication()->getRender()->createTexture();
    ret->realNativeTexture->setNativeTexture(t);
    return ret;
}

std::map<std::variant<std::string, int>, std::shared_ptr<Texture>> textures;

std::shared_ptr<TextureManager> TextureManager::getTextureManager()
{
    static std::shared_ptr<TextureManager> instance(
        std::make_shared<TextureManager>());
    return instance;
}

void TextureManager::loadTextureFromFile(
    const std::variant<std::string, int>& id, string src, const Color)
{
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(src);
    addTexture(id, texture);
}

void TextureManager::loadTextureFromTexture(std::string,
                                            std::shared_ptr<Texture>,
                                            const Rect&)
{
    /// Todo, easy.
}

void TextureManager::addTexture(std::string id,
                                std::shared_ptr<Texture> texture)
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
                                std::shared_ptr<Texture> texture)
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

void TextureManager::removeTexture(std::string)
{
}

std::shared_ptr<Texture> TextureManager::getTexture(
    const std::variant<std::string, int>& id)
{
    auto find = textures.find(id);
    if (find == textures.end())
        return std::make_shared<Texture>();
    return find->second;
}

std::shared_ptr<Texture> TextureManager::getTextureOr(
    const std::variant<std::string, int>& id, std::function<void()>)
{
    return textures[id];
}

void TextureManager::loadFont(const std::variant<std::string, int>& key,
                              string src, int pts)
{
    auto pf = std::make_shared<TTFText>();
    pf->setFont(src, pts);
    fonts[key] = pf;
}
std::shared_ptr<TTFText> TextureManager::getFont(
    const std::variant<std::string, int>& id)
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

TextureManager::TextureStatus TextureManager::drawTexture(int id,
                                                          const Rect offset)
{
    auto text = getTexture(id);
    if (text == nullptr)
        return TextureManager::TextureStatus::TextureIdInvalid;
    text->Draw(offset);
    return TextureManager::TextureStatus::Success;
}
void TextureManager::destroyAll()
{

    if (textures.size() <= 0)
    {
        LogOuput(logger_type::Information, "No Texture to Del");
        return;
    }
    for (auto it : textures)
    {
        it.second.reset();
    }
}

} // namespace doengine
