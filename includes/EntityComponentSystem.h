#pragma once

#include <stdint.h>

namespace doengine
{
// ============================================================================
// MINIMAL ECS (Entity Component System) EXPLANATION
// ============================================================================

#include <vector>
#include <unordered_map>
#include <memory>

// ============================================================================
// 1. ENTITY - Just a unique ID, nothing more
// ============================================================================
using Entity = unsigned int;

// ============================================================================
// 2. COMPONENTS - Pure data, no logic
//    Think of them as properties or attributes
// ============================================================================

struct PositionComponent {
    float x, y;
};

struct VelocityComponent {
    float dx, dy;  // Movement speed
};

struct SpriteComponent {
    int textureID;
    float width, height;
};

struct HealthComponent {
    int current;
    int maximum;
};

// ============================================================================
// 3. COMPONENT STORAGE - Where all component data lives
//    Each component type has its own array for cache efficiency
// ============================================================================

class ComponentManager {
public:
    // Store components in separate arrays by type
    std::unordered_map<Entity, PositionComponent> positions;
    std::unordered_map<Entity, VelocityComponent> velocities;
    std::unordered_map<Entity, SpriteComponent> sprites;
    std::unordered_map<Entity, HealthComponent> healths;
    
    // Add/remove/get components for entities
    template<typename T>
    void AddComponent(Entity entity, const T& component);
    
    template<typename T>
    T& GetComponent(Entity entity);
    
    template<typename T>
    bool HasComponent(Entity entity);
};

// ============================================================================
// 4. ENTITY MANAGER - Creates and destroys entities
// ============================================================================

class EntityManager {
private:
    Entity nextEntityID = 0;
    std::vector<Entity> entities;
    
public:
    Entity CreateEntity() {
        Entity id = nextEntityID++;
        entities.push_back(id);
        return id;
    }
    
    void DestroyEntity(Entity entity) {
        // Remove from list and clean up all its components
        entities.erase(std::remove(entities.begin(), entities.end(), entity));
    }
    
    const std::vector<Entity>& GetAllEntities() const {
        return entities;
    }
};

// ============================================================================
// 5. SYSTEMS - Pure logic that processes entities with specific components
//    Systems iterate over entities and update their components
// ============================================================================

// MovementSystem: Updates position based on velocity
class MovementSystem {
private:
    ComponentManager* components;
    
public:
    MovementSystem(ComponentManager* cm) : components(cm) {}
    
    void Update(float deltaTime, const std::vector<Entity>& entities) {
        // Process ONLY entities that have BOTH Position AND Velocity
        for (Entity entity : entities) {
            if (components->HasComponent<PositionComponent>(entity) &&
                components->HasComponent<VelocityComponent>(entity)) {
                
                // Get the components
                auto& pos = components->GetComponent<PositionComponent>(entity);
                auto& vel = components->GetComponent<VelocityComponent>(entity);
                
                // Apply logic: move the entity
                pos.x += vel.dx * deltaTime;
                pos.y += vel.dy * deltaTime;
            }
        }
    }
};

// RenderSystem: Draws entities with sprites
class RenderSystem {
private:
    ComponentManager* components;
    
public:
    RenderSystem(ComponentManager* cm) : components(cm) {}
    
    void Render(const std::vector<Entity>& entities) {
        // Process ONLY entities that have BOTH Position AND Sprite
        for (Entity entity : entities) {
            if (components->HasComponent<PositionComponent>(entity) &&
                components->HasComponent<SpriteComponent>(entity)) {
                
                auto& pos = components->GetComponent<PositionComponent>(entity);
                auto& sprite = components->GetComponent<SpriteComponent>(entity);
                
                // Draw the sprite at the entity's position
                // DrawSprite(sprite.textureID, pos.x, pos.y, sprite.width, sprite.height);
            }
        }
    }
};

// ============================================================================
// 6. USAGE EXAMPLE - How to actually use ECS
// ============================================================================

void ExampleUsage() {
    EntityManager entityManager;
    ComponentManager componentManager;
    
    // Create systems
    MovementSystem movementSystem(&componentManager);
    RenderSystem renderSystem(&componentManager);
    
    // ========================================================================
    // Create a PLAYER entity
    // ========================================================================
    Entity player = entityManager.CreateEntity();
    
    // Add components to define what the player HAS
    componentManager.positions[player] = {100.0f, 100.0f};      // Has position
    componentManager.velocities[player] = {50.0f, 0.0f};        // Has velocity (moves right)
    componentManager.sprites[player] = {1, 32.0f, 32.0f};       // Has sprite
    componentManager.healths[player] = {100, 100};              // Has health
    
    // ========================================================================
    // Create a TREE entity (static, no movement)
    // ========================================================================
    Entity tree = entityManager.CreateEntity();
    
    // Tree has position and sprite, but NO velocity (won't move)
    componentManager.positions[tree] = {200.0f, 150.0f};
    componentManager.sprites[tree] = {2, 64.0f, 128.0f};
    // Notice: no velocity, no health
    
    // ========================================================================
    // Create a PROJECTILE entity
    // ========================================================================
    Entity bullet = entityManager.CreateEntity();
    
    // Bullet has position, velocity, sprite (but no health)
    componentManager.positions[bullet] = {120.0f, 110.0f};
    componentManager.velocities[bullet] = {200.0f, 0.0f};       // Moves fast
    componentManager.sprites[bullet] = {3, 8.0f, 8.0f};
    
    // ========================================================================
    // GAME LOOP - Systems process entities
    // ========================================================================
    float deltaTime = 0.016f; // 60 FPS
    
    // MovementSystem updates player and bullet (both have Position + Velocity)
    // Tree is NOT updated because it has no Velocity component
    movementSystem.Update(deltaTime, entityManager.GetAllEntities());
    
    // RenderSystem draws ALL entities with Position + Sprite
    // Draws player, tree, and bullet
    renderSystem.Render(entityManager.GetAllEntities());
}

// ============================================================================
// KEY BENEFITS OF ECS
// ============================================================================
//
// 1. COMPOSITION OVER INHERITANCE
//    - Don't need Player class, Enemy class, Bullet class
//    - Just mix and match components to define behavior
//
// 2. FLEXIBILITY
//    - Want to make tree damageable? Add HealthComponent
//    - Want to make bullet bounce? Add PhysicsComponent
//    - No need to change class hierarchies
//
// 3. PERFORMANCE
//    - Components stored together in memory (cache-friendly)
//    - Systems process similar data in tight loops
//    - Easy to parallelize systems
//
// 4. REUSABILITY
//    - Same components work for any entity type
//    - Same systems work for any entity with required components
//
// ============================================================================
 

}