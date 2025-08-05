#ifndef GAMEOBJECT_POOL_H_DEFINED
#define GAMEOBJECT_POOL_H_DEFINED

#include "GameObject.h"
#include <vector>
namespace doengine{


struct GameObjectPool{
   static std::vector<GameObject*> ref;
};


}

#endif