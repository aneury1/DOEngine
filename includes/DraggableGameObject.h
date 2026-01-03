#ifndef DRAGGABLE_GAMEOBJECT_H_DEFINED
#define DRAGGABLE_GAMEOBJECT_H_DEFINED
#include <unordered_map>
#include "Draggable.h"
#include "Geometric.h"
#include "Renderer.h"

namespace doengine
{

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
