#pragma once
#include <stdint.h>
#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <bitset>
#include <algorithm>

/// Test Components....
#include "Geometric.h"

namespace doengine
{

using ComponentId = int;
class Component;
class Entity;

inline ComponentId getNextComponentId()
{
    static ComponentId lastId = 0;
    return ++lastId;
}

template<class T> inline ComponentId getComponentTypeId() noexcept
{
    static ComponentId typeID = getNextComponentId();
    return typeID;
}

constexpr int maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


struct Component 
{
    public:
        Entity *entity;

        virtual void init(){}
        virtual void Update(){}
        virtual void Render(){}
        virtual ~Component(){}
};

struct Entity
{

    bool active = true;

    std::vector<std::shared_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitset componentBitset;

    bool isActive()
    {
        return active;
    }

    void Update(float elapsed = 0)
    {
        for(auto it : components) it->Update();
    }

    void Render()
    {
        for(auto it : components) it->Render();
    }

    void destroy(){active = false;}

    template<typename T> bool hasComponent() const
    {
        return componentArray[getComponentTypeId<T>];
    }

    template<typename T, typename...Targs>
    T& addComponent(Targs&&... targs)
    {
        T* c(new T(std::forward<Targs>(targs)...));
        c->entity = this;
        std::shared_ptr<Component> uPtr{c};
        components.emplace_back(uPtr);

        componentArray[getComponentTypeId<T>()] = c;
        componentBitset[getComponentTypeId<T>()] = true;

        c->init();

        return *c;
    }

    template<typename T> T& getComponent()const
    {
        auto ptr = componentArray[getComponentTypeId<T>()];
        return *static_cast<T*>(ptr);
    }
};


struct ECSManager
{
    std::vector<std::shared_ptr<Entity>> entities; 

    void Update()
    {
        for(auto it : entities)
        {
            it->Update();
        }
    }

    void Render()
    {
        for(auto it : entities)
        {
            it->Render();
        }
    }

    void Refresh()
    {
        entities.erase(
            std::remove_if(
                entities.begin(),
                entities.end(),
                [](const std::shared_ptr<Entity> &ent){
                    return !ent->isActive();
                })
            );
    }

    Entity& addEntity()
    {
        Entity* ent = new Entity();
        std::shared_ptr<Entity> p{ent};
        entities.emplace_back(std::move(p));
        return *ent;
    }
};



struct PositionComponent : public Component
{
    Point point;

    int X(){return point.x;}
    int Y(){return point.y;}

    void setPosition(Point p)
    {
        point.x = p.x;
        point.y = p.y;
    }
    virtual void init() override{}
    virtual void Update() override{}
    virtual void Render() override{}
};













}