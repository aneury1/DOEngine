
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
#ifndef DRAGGABLE_GAMEOBJECT_H_DEFINED
#define DRAGGABLE_GAMEOBJECT_H_DEFINED
#include <unordered_map>
#include "Draggable.h"
#include "Geometric.h"
#include "Renderer.h"
#include "Event.h"
#include <memory>
#include <functional>
#include <vector>
namespace doengine
{


class DraggableObject : 
    public Draggable,
    public MouseEvent
{
   
   private:
        std::vector<std::function<void(Rect)>> onSelectedHappened;
        std::vector<std::function<void(Rect)>> onSelectedStopped;
        std::vector<std::function<void(Rect)>> onMovementHappened;
        std::vector<std::function<void(Rect)>> onMovementStopped;

   protected:
        virtual void startDraggingPoint(const doengine::Rect& start);
        virtual void updateCoords(const doengine::Rect& rect);
        virtual void render(std::shared_ptr<doengine::Renderer> render);
        virtual void MouseMove(const Mouse&);
        virtual void MouseButtonDown(const Mouse&);
        virtual void MouseButtonUp(const Mouse&);
        virtual void MouseWheel(const Mouse&){}
        void setSelected(bool selected);

        Rect offset;
        bool selected;


   public:


        void registerOnSelectedHappenedCallback(std::function<void(Rect)> fn);
        void registerOnSelectedStoppedCallback(std::function<void(Rect)> fn);
        void registerOnMovementHappenedCallback(std::function<void(Rect)> fn);
        void registerOnMovementStoppedCallback(std::function<void(Rect)> fn);

        Rect getDragablePosition();
        void setObjectDimensionAndPosition(const doengine::Rect rect);
        virtual ~DraggableObject() = default;
        virtual void Update(float elapse) = 0;
        virtual void Render() = 0;
};

class DraggableGameObject : 
    public Draggable
{
        bool selected;
        int sprite;
        int sprite_id;
        int sprite_offset;
        doengine::Rect offset;
        std::unordered_map<int, doengine::Rect> spriteOffsets;
    public:
        virtual ~DraggableGameObject();
        DraggableGameObject();
        DraggableGameObject(int x, int y);
        DraggableGameObject(int x, int y, int spriteId, int spOffset);
        void setSpriteOffset(std::unordered_map<int, doengine::Rect> sprites);
        void setSelectedIfCollided(const doengine::Rect& rect);
        void setSelected(bool selected);
        virtual void startDraggingPoint(const doengine::Rect& start);
        virtual void updateCoords(const doengine::Rect& o);
        virtual void render(std::shared_ptr<doengine::Renderer> render);

};
}
#endif
