#include "DraggableGameObject.h"

namespace doengine
{

DraggableGameObject::~DraggableGameObject()
{
}

DraggableGameObject::DraggableGameObject()
{
    offset.x = 400;
    offset.y = 500;
    offset.w = 32;
    offset.h = 32;
}
DraggableGameObject::DraggableGameObject(int x, int y)
{
    offset.x = x;
    offset.y = y;
    offset.w = 32;
    offset.h = 32;
}

DraggableGameObject::DraggableGameObject(int x, int y, int spriteId, int spOffset)
{
    offset.x = x;
    offset.y = y;
    offset.w = 64;
    offset.h = 64;
    sprite_id = spriteId;
    sprite_offset = spOffset;
}

void DraggableGameObject::setSpriteOffset(std::unordered_map<int, doengine::Rect> sprites)
{
   this->spriteOffsets = sprites;
}


void DraggableGameObject::setSelectedIfCollided(const doengine::Rect& rect)
{
    this->selected = doengine::checkCollision(offset, rect);
}

void DraggableGameObject::setSelected(bool selected)
{
    this->selected = selected;
}

void DraggableGameObject::startDraggingPoint(const doengine::Rect& start)
{
    if (this->selected)
    {
        offset.x = start.x;
        offset.y = start.y;
    }
}

void DraggableGameObject::updateCoords(const doengine::Rect& o)
{
    if (this->selected)
    {
        offset.x = o.x;
        offset.y = o.y;
        offset.w = 32; /// o.w;
        offset.h = 32; /// o.h;
    }
}

void DraggableGameObject::render(doengine::Renderer* render)
{

    auto texture =
        doengine::TextureManager::getTextureManager()->getTexture(sprite_id);
    if (texture)
    {
        auto rect = spriteOffsets[sprite_offset];
        this->offset.w = rect.w;
        this->offset.h = rect.h;
        texture->Draw(this->offset, rect);
    }
}

} // namespace doengine