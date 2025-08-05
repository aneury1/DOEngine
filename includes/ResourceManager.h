#ifndef RESOURCE_MANAGER_H_DEFINED
#define RESOURCE_MANAGER_H_DEFINED
#include <string>
#include "Texture.h"

namespace doengine
{


template<typename IdType>
class ResourceManager
{

    std::map<IdType, Texture*> textures;
public:


    Texture* getTexture(const IdType& type)
    {
        Texture* ret = nullptr;
        
        return ret;
    }


};
}
#endif
