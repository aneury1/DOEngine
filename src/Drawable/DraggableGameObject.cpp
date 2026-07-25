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

#include "DraggableGameObject.h"
#include "Event.h"
#include "Geometric.h"
#include "Logger.h"
namespace doengine
{

void DraggableObject::setSelected(bool selected)
{
    this->selected = selected;
}

void DraggableObject::startDraggingPoint(const doengine::Rect& start)
{
    if (this->selected)
    {
        offset.x = start.x;
        offset.y = start.y;
    }
}
void DraggableObject::registerOnSelectedHappenedCallback(
    std::function<void(Rect)> fn)
{
    onSelectedHappened.emplace_back(fn);
}
void DraggableObject::registerOnSelectedStoppedCallback(
    std::function<void(Rect)> fn)
{
    onSelectedStopped.emplace_back(fn);
}
void DraggableObject::registerOnMovementHappenedCallback(
    std::function<void(Rect)> fn)
{
    onMovementHappened.emplace_back(fn);
}
void DraggableObject::registerOnMovementStoppedCallback(
    std::function<void(Rect)> fn)
{
    onMovementStopped.emplace_back(fn);
}

Rect DraggableObject::getDragablePosition()
{
    return offset;
}
void DraggableObject::setObjectDimensionAndPosition(const doengine::Rect rect)
{
    offset = rect;
}

void DraggableObject::updateCoords(const doengine::Rect& rect)
{
    if (this->selected)
    {
        offset.x = rect.x;
        offset.y = rect.y;
    }
}
void DraggableObject::render(std::shared_ptr<doengine::Renderer>  )
{
    //// does nothing.... as protected
}
void DraggableObject::MouseMove(const Mouse& mouse)
{
    updateCoords(mouse.getMousePosition());
}
void DraggableObject::MouseButtonDown(const Mouse& mouse)
{
    this->selected = doengine::checkCollision(offset, mouse.getMousePosition());
    LogOuput(logger_type::Information, "Selected %d", selected);
}
void DraggableObject::MouseButtonUp(const Mouse&  )
{
    selected = false;
}

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

DraggableGameObject::DraggableGameObject(int x, int y, int spriteId,
                                         int spOffset)
{
    offset.x = x;
    offset.y = y;
    offset.w = 64;
    offset.h = 64;
    sprite_id = spriteId;
    sprite_offset = spOffset;
}

void DraggableGameObject::setSpriteOffset(
    std::unordered_map<int, doengine::Rect> sprites)
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

void DraggableGameObject::render(std::shared_ptr<doengine::Renderer> )
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