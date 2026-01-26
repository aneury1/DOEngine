#include "GameObject.h"
#include "Renderer.h"
#include "Application.h"
namespace doengine
{
GameObject::GameObject()
{
    renderer= Application::getApplication()->getRender();
    LogOuput(logger_type::Information,"Creating an object");
}
GameObject::~GameObject()
{
}
Rect GameObject::getPosition()
{
    return position;
}
    
Renderer* GameObject::getRenderer()
{
    return renderer;
}


};