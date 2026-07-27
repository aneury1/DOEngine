/*
 * ============================================================================
 * DOEngine - Entity Component System (ECS)
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
 * 
 * Complete Entity Component System (ECS)
 * 
 * A flexible, data-oriented architecture for game objects and systems.
 * Combines component-based composition with efficient system scheduling.
 * 
 * Usage Example:
 *   World world;
 *   Entity* player = world.createEntity();
 *   player->addComponent<TransformComponent>(10.0f, 20.0f);
 *   player->addComponent<VelocityComponent>(2.0f, 1.0f);
 *   
 *   world.registerSystem<MovementSystem>();
 *   world.update(deltaTime);
 *   world.render();
 */
#pragma once
#include <stdint.h>
#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <typeinfo>

#include "Geometric.h"

namespace doengine
{

// ============================================================================
// Component Type ID Management
// ============================================================================

using ComponentId = uint32_t;

inline ComponentId getNextComponentId()
{
    static ComponentId lastId = 0;
    return lastId++;
}

template<class T> 
inline ComponentId getComponentTypeId() noexcept
{
    static ComponentId typeID = getNextComponentId();
    return typeID;
}

constexpr int maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<void*, maxComponents>;

// Forward declarations
class Entity;
class World;
class System;

// ============================================================================
// Component Base Class
// ============================================================================

/**
 * @brief Base class for all ECS components
 * 
 * Components are data containers that can be attached to entities.
 * Override init(), update(), and render() for custom behavior.
 */
class Component 
{
public:
    Entity* entity = nullptr;

    virtual void init() {}
    virtual void update(float deltaTime) {}
    virtual void render() {}
    virtual ~Component() = default;
};

// ============================================================================
// Entity Class
// ============================================================================

/**
 * @brief Entity that holds and manages components
 * 
 * An entity is a container for components. It can be queried for components
 * and used within systems for data-driven behavior.
 */
class Entity : public std::enable_shared_from_this<Entity>
{
    friend class World;

private:
    uint32_t id = 0;
    bool active = true;
    World* world = nullptr;

    std::vector<std::shared_ptr<Component>> components;
    ComponentArray componentArray = {};
    ComponentBitset componentBitset;

public:
    Entity() = default;
    virtual ~Entity() = default;

    uint32_t getId() const { return id; }
    
    bool isActive() const { return active; }
    
    void setActive(bool state) { active = state; }
    
    void destroy() { active = false; }

    World* getWorld() const { return world; }

    // ========================================================================
    // Component Management
    // ========================================================================

    /**
     * @brief Add a component of type T to this entity
     * @tparam T Component type to add
     * @tparam Args Constructor argument types
     * @param args Constructor arguments
     * @return Reference to the newly added component
     */
    template<typename T, typename... Args>
    T& addComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        
        ComponentId typeId = getComponentTypeId<T>();
        
        if (componentBitset[typeId])
        {
            // Component already exists, return existing
            return getComponent<T>();
        }

        T* component = new T(std::forward<Args>(args)...);
        component->entity = this;
        
        std::shared_ptr<Component> ptr(component);
        components.emplace_back(ptr);

        componentArray[typeId] = component;
        componentBitset[typeId] = true;

        component->init();
        return *component;
    }

    /**
     * @brief Check if entity has component of type T
     * @tparam T Component type to check
     * @return True if entity has component T
     */
    template<typename T>
    bool hasComponent() const
    {
        return componentBitset[getComponentTypeId<T>()];
    }

    /**
     * @brief Get component of type T
     * @tparam T Component type to retrieve
     * @return Reference to component T
     * @throws std::runtime_error if component not found
     */
    template<typename T>
    T& getComponent() const
    {
        ComponentId typeId = getComponentTypeId<T>();
        if (!componentBitset[typeId])
        {
            throw std::runtime_error("Component not found on entity");
        }
        return *static_cast<T*>(componentArray[typeId]);
    }

    /**
     * @brief Get component of type T, or nullptr if not found
     */
    template<typename T>
    T* tryGetComponent() const
    {
        if (!hasComponent<T>())
            return nullptr;
        return static_cast<T*>(componentArray[getComponentTypeId<T>()]);
    }

    /**
     * @brief Remove component of type T
     */
    template<typename T>
    void removeComponent()
    {
        ComponentId typeId = getComponentTypeId<T>();
        if (!componentBitset[typeId])
            return;

        componentBitset[typeId] = false;
        componentArray[typeId] = nullptr;

        components.erase(
            std::remove_if(
                components.begin(),
                components.end(),
                [typeId](const std::shared_ptr<Component>& c) {
                    return getComponentTypeId<T>() == typeId && 
                           dynamic_cast<T*>(c.get()) != nullptr;
                }),
            components.end()
        );
    }

    /**
     * @brief Get component bitset (signature of components)
     */
    const ComponentBitset& getComponentBitset() const { return componentBitset; }

    /**
     * @brief Update all components
     */
    void update(float deltaTime)
    {
        for (auto& component : components)
        {
            if (component)
                component->update(deltaTime);
        }
    }

    /**
     * @brief Render all components
     */
    void render()
    {
        for (auto& component : components)
        {
            if (component)
                component->render();
        }
    }
};

// ============================================================================
// Useful Built-in Components
// ============================================================================

/**
 * @brief Transform component: position, rotation, scale
 * 
 * Represents the 2D position, rotation, and scale of an entity.
 */
struct TransformComponent : public Component
{
    float x = 0.0f;
    float y = 0.0f;
    float rotation = 0.0f;  // In degrees
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    TransformComponent() = default;
    TransformComponent(float px, float py) : x(px), y(py) {}
    TransformComponent(float px, float py, float rot, float sx = 1.0f, float sy = 1.0f)
        : x(px), y(py), rotation(rot), scaleX(sx), scaleY(sy) {}

    Point getPosition() const { return Point{static_cast<int>(x), static_cast<int>(y)}; }
    void setPosition(float px, float py) { x = px; y = py; }
};

/**
 * @brief Velocity component: movement per frame
 * 
 * Represents the velocity (speed in X and Y directions) of an entity.
 */
struct VelocityComponent : public Component
{
    float vx = 0.0f;  // Velocity X
    float vy = 0.0f;  // Velocity Y

    VelocityComponent() = default;
    VelocityComponent(float velX, float velY) : vx(velX), vy(velY) {}
};

/**
 * @brief Acceleration component: change in velocity
 * 
 * Represents acceleration (often used for gravity).
 */
struct AccelerationComponent : public Component
{
    float ax = 0.0f;  // Acceleration X
    float ay = 0.0f;  // Acceleration Y (typically gravity)

    AccelerationComponent() = default;
    AccelerationComponent(float accX, float accY) : ax(accX), ay(accY) {}
};

/**
 * @brief Sprite rendering component
 * 
 * Holds sprite/texture information and animation state.
 */
struct SpriteComponent : public Component
{
    int textureId = -1;  // Texture ID
    int frameIndex = 0;  // Current animation frame
    int frameCount = 1;  // Total frames
    int frameDelay = 10; // Delay between frames (in updates)
    int frameTimer = 0;  // Internal frame timer

    SpriteComponent() = default;
    explicit SpriteComponent(int texId) : textureId(texId) {}

    bool isAnimating() const { return frameCount > 1; }
    
    void updateAnimation()
    {
        if (!isAnimating()) return;
        
        frameTimer++;
        if (frameTimer >= frameDelay)
        {
            frameTimer = 0;
            frameIndex = (frameIndex + 1) % frameCount;
        }
    }
};

/**
 * @brief Bounding box for collision detection
 * 
 * Represents a rectangular collision area with optional offset.
 */
struct ColliderComponent : public Component
{
    float width = 0.0f;
    float height = 0.0f;
    float offsetX = 0.0f;  // Offset from transform position
    float offsetY = 0.0f;

    ColliderComponent() = default;
    ColliderComponent(float w, float h) : width(w), height(h) {}
    ColliderComponent(float w, float h, float ox, float oy) 
        : width(w), height(h), offsetX(ox), offsetY(oy) {}

    /**
     * @brief Check if this collider intersects with another
     */
    bool intersects(const ColliderComponent& other, 
                   const TransformComponent& myTransform,
                   const TransformComponent& otherTransform) const
    {
        float x1 = myTransform.x + offsetX;
        float y1 = myTransform.y + offsetY;
        float x2 = otherTransform.x + other.offsetX;
        float y2 = otherTransform.y + other.offsetY;

        return !(x1 + width < x2 || x2 + other.width < x1 ||
                 y1 + height < y2 || y2 + other.height < y1);
    }
};

/**
 * @brief Basic physics component
 * 
 * Stores physics properties like mass and flags.
 */
struct RigidbodyComponent : public Component
{
    float mass = 1.0f;
    bool isKinematic = false;  // If true, not affected by physics
    bool useGravity = true;

    RigidbodyComponent() = default;
    explicit RigidbodyComponent(float m, bool kinematic = false, bool gravity = true)
        : mass(m), isKinematic(kinematic), useGravity(gravity) {}
};

/**
 * @brief Tag component: simple string identifier
 * 
 * Use for entity classification and querying by tag.
 */
struct TagComponent : public Component
{
    std::string tag;

    TagComponent() = default;
    explicit TagComponent(const std::string& t) : tag(t) {}
};

// ============================================================================
// System Base Class
// ============================================================================

/**
 * @brief Base class for all ECS systems
 * 
 * Systems implement game logic that operates on entities with specific components.
 * Systems are updated once per frame by the World.
 */
class System
{
public:
    virtual ~System() = default;

    /**
     * @brief Called when system is registered
     */
    virtual void init(World* world) { }

    /**
     * @brief Update system - called once per frame
     * @param deltaTime Time elapsed since last update (seconds)
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Render system - called once per frame
     */
    virtual void render() { }

    /**
     * @brief Called when system is unregistered
     */
    virtual void shutdown() { }
};

// ============================================================================
// World/ECS Manager
// ============================================================================

/**
 * @brief Main ECS World that manages entities and systems
 * 
 * The World is the central manager for all entities and systems.
 * It handles entity creation/destruction, system registration, and
 * orchestrates updates and rendering.
 */
class World
{
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<System>> systems;
    uint32_t nextEntityId = 1;

public:
    World() = default;
    ~World() { shutdown(); }

    // ========================================================================
    // Entity Management
    // ========================================================================

    /**
     * @brief Create a new entity
     * @return Pointer to the created entity
     */
    Entity* createEntity()
    {
        auto entity = std::make_shared<Entity>();
        entity->id = nextEntityId++;
        entity->world = this;
        entities.push_back(entity);
        return entity.get();
    }

    /**
     * @brief Destroy an entity (marks as inactive)
     */
    void destroyEntity(Entity* entity)
    {
        if (entity)
            entity->destroy();
    }

    /**
     * @brief Remove inactive entities from world
     */
    void refresh()
    {
        entities.erase(
            std::remove_if(
                entities.begin(),
                entities.end(),
                [](const std::shared_ptr<Entity>& e) { return !e->isActive(); }),
            entities.end()
        );
    }

    /**
     * @brief Get all entities
     */
    const std::vector<std::shared_ptr<Entity>>& getEntities() const { return entities; }

    /**
     * @brief Get entities with specific components (filter)
     * @tparam Components Component types to filter by
     * @return Vector of entities having all specified components
     */
    template<typename... Components>
    std::vector<Entity*> getEntitiesWith()
    {
        std::vector<Entity*> result;

        for (auto& entity : entities)
        {
            if (entity->isActive() && (... && entity->hasComponent<Components>()))
            {
                result.push_back(entity.get());
            }
        }

        return result;
    }

    // ========================================================================
    // System Management
    // ========================================================================

    /**
     * @brief Register and instantiate a system
     * @tparam T System type to register
     * @tparam Args Constructor argument types
     * @return Pointer to the registered system
     */
    template<typename T, typename... Args>
    T* registerSystem(Args&&... args)
    {
        static_assert(std::is_base_of_v<System, T>, "T must derive from System");

        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        system->init(this);
        systems.push_back(system);
        return system.get();
    }

    // ========================================================================
    // Update & Render
    // ========================================================================

    /**
     * @brief Update all systems and entities
     * @param deltaTime Time elapsed since last frame (seconds)
     */
    void update(float deltaTime)
    {
        // Update all systems
        for (auto& system : systems)
        {
            system->update(deltaTime);
        }

        // Update all entity components
        for (auto& entity : entities)
        {
            if (entity->isActive())
                entity->update(deltaTime);
        }

        // Remove inactive entities
        refresh();
    }

    /**
     * @brief Render all systems and entities
     */
    void render()
    {
        // Render all systems
        for (auto& system : systems)
        {
            system->render();
        }

        // Render all entities
        for (auto& entity : entities)
        {
            if (entity->isActive())
                entity->render();
        }
    }

    /**
     * @brief Shutdown world and cleanup all resources
     */
    void shutdown()
    {
        for (auto& system : systems)
        {
            system->shutdown();
        }
        systems.clear();
        entities.clear();
    }

    /**
     * @brief Get entity count
     */
    size_t getEntityCount() const { return entities.size(); }
};

// ============================================================================
// Example Systems (Commonly used)
// ============================================================================

/**
 * @brief System that applies velocity to transform
 * 
 * For entities with both TransformComponent and VelocityComponent,
 * this system updates the position based on velocity each frame.
 */
class MovementSystem : public System
{
private:
    World* world = nullptr;

public:
    void init(World* w) override { world = w; }

    void update(float deltaTime) override
    {
        auto entities = world->getEntitiesWith<TransformComponent, VelocityComponent>();

        for (auto entity : entities)
        {
            auto& transform = entity->getComponent<TransformComponent>();
            auto& velocity = entity->getComponent<VelocityComponent>();

            transform.x += velocity.vx * deltaTime;
            transform.y += velocity.vy * deltaTime;
        }
    }
};

/**
 * @brief System that applies acceleration to velocity
 * 
 * For entities with both VelocityComponent and AccelerationComponent,
 * this system updates velocity based on acceleration each frame.
 */
class PhysicsSystem : public System
{
private:
    World* world = nullptr;

public:
    void init(World* w) override { world = w; }

    void update(float deltaTime) override
    {
        auto entities = world->getEntitiesWith<VelocityComponent, AccelerationComponent>();

        for (auto entity : entities)
        {
            auto& velocity = entity->getComponent<VelocityComponent>();
            auto& acceleration = entity->getComponent<AccelerationComponent>();

            velocity.vx += acceleration.ax * deltaTime;
            velocity.vy += acceleration.ay * deltaTime;
        }
    }
};

/**
 * @brief System that handles sprite animation
 * 
 * Updates animation frame indices for entities with SpriteComponent.
 */
class AnimationSystem : public System
{
private:
    World* world = nullptr;

public:
    void init(World* w) override { world = w; }

    void update(float deltaTime) override
    {
        auto entities = world->getEntitiesWith<SpriteComponent>();

        for (auto entity : entities)
        {
            auto& sprite = entity->getComponent<SpriteComponent>();
            sprite.updateAnimation();
        }
    }
};

// ============================================================================
// Singleton World accessor (optional, for backward compatibility)
// ============================================================================

/**
 * @brief Static accessor for a global World instance
 * 
 * Optional: Use this for projects that need a singleton World,
 * otherwise create World instances directly.
 */
class ECSManager
{
private:
    static std::unique_ptr<World> instance;

public:
    /**
     * @brief Get or create the global World instance
     */
    static World* getWorld()
    {
        if (!instance)
            instance = std::make_unique<World>();
        return instance.get();
    }

    /**
     * @brief Shutdown the global World instance
     */
    static void shutdown()
    {
        instance.reset();
    }
};

}  // namespace doengine
