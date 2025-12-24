#ifndef DRAGGABLE_H_DEFINED
#define DRAGGABLE_H_DEFINED
#include "Renderer.h"
#include "Geometric.h"

namespace doengine{

struct Draggable{
   virtual ~Draggable();
   Draggable();
   virtual void startDraggingPoint(const doengine::Rect& start)= 0;
   virtual void updateCoords(const doengine::Rect& rect) = 0;
   virtual void render(doengine::Renderer *render) = 0;
};

}
#endif
