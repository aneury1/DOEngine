#ifndef DRAGGABLE_GAMEOBJECT_H_DEFINED
#define DRAGGABLE_GAMEOBJECT_H_DEFINED
#include <unordered_map>
#include "Draggable.h"
#include "Geometric.h"
#include "Renderer.h"
#include "Event.h"
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
        virtual void render(doengine::Renderer *render);
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
        virtual void render(doengine::Renderer *render);

};
}
#endif
