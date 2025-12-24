#ifndef RENDERER_QUEUE_DEFINED
#define RENDERER_QUEUE_DEFINED

#include "constant.h"
#include <unordered_map>
#include <string>
#include <vector>
/// @brief System to paint through layers.next
namespace doengine
{

struct Drawable
{
   virtual ~Drawable() = default;
   protected:
    LayerId id;
    std::string guid;
    std::string name;
};

struct RendererQueue
{
    std::unordered_map<LayerId, std::vector<Drawable *>> drawable_layers;
};


}

#endif