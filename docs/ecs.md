# DOEngine Experiment 101 - trying an Entity Component System (ECS)

## Overview

This is a lightweight **Entity Component System (ECS)** implementation for the `doengine` game engine. The ECS pattern is an architectural pattern commonly used in game development that favors composition over inheritance, allowing for flexible and scalable game object management.

---

## Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [Core Components](#core-components)
3. [Current Issues & Bugs](#current-issues--bugs)
4. [API Reference](#api-reference)
5. [Usage Examples](#usage-examples)
6. [Improvements & Recommendations](#improvements--recommendations)

---

## Architecture Overview

### What is ECS?

The Entity Component System pattern separates:
- **Entities**: Containers/IDs that group components together
- **Components**: Pure data structures (position, velocity, sprite, etc.)
- **Systems**: Logic that operates on entities with specific component combinations

### Design Pattern

```
Entity (Container)
    └── Component Array (Fast lookup by type)
    └── Component Vector (Storage)
    └── Bitset (Quick component presence checks)
```

---

## Core Components

### 1. Component Type System

```cpp
using ComponentId = int;

inline ComponentId getNextComponentId()
{
    static ComponentId lastId = 0;
    return ++lastId;
}

template<class T> 
inline ComponentId getComponentTypeId() noexcept
{
    static ComponentId typeID = getNextComponentId();
    return typeID;
}
```

**Purpose**: Assigns unique IDs to each component type at compile-time using template specialization.

**How it works**: Each template instantiation creates a static variable with its own ID.

---

### 2. Component Base Class

```cpp
struct Component 
{
    Entity *entity;  // Back-reference to owning entity
    
    virtual void init(){}     // Called after component added
    virtual void Update(){}   // Per-frame logic
    virtual void Render(){}   // Rendering logic
    virtual ~Component(){}    // Virtual destructor for polymorphism
};
```

**Purpose**: Base class that all components inherit from, providing common interface.

---

### 3. Entity Class

```cpp
struct Entity
{
    bool active = true;
    
    std::vector<std::shared_ptr<Component>> components;  // Ownership
    ComponentArray componentArray;                        // Fast lookup
    ComponentBitset componentBitset;                      // Presence flags
    
    // Methods: isActive, Update, Render, destroy
    // addComponent, getComponent, hasComponent
};
```

**Storage Strategy**:
- **components vector**: Owns all components via shared_ptr
- **componentArray**: Direct pointers indexed by component type ID (O(1) lookup)
- **componentBitset**: Fast boolean checks for component presence

---

### 4. ECSManager

```cpp
struct ECSManager
{
    std::vector<std::shared_ptr<Entity>> entities;
    
    void Update();   // Updates all entities
    void Render();   // Renders all entities
    void Refresh();  // Removes inactive entities
    Entity& addEntity();
};
```

**Purpose**: Central manager for all entities in the game world.

---

## Current Issues & Bugs

### 🔴 Critical Bugs

1. **Typo in `addComponent`**:
   ```cpp
   // WRONG:
   T* c(new T(std::fordward<Targs>(targs)...));
   
   // CORRECT:
   T* c(new T(std::forward<Targs>(targs)...));
   ```

2. **Syntax Error in `getComponent`**:
   ```cpp
   // WRONG:
   auto ptr[componentArray[getComponentTypeId<T>()]];
   
   // CORRECT:
   auto ptr = componentArray[getComponentTypeId<T>()];
   ```

3. **Missing `const` correctness in `getComponent`**:
   - Method is marked `const` but accesses non-const array

---

### ⚠️ Design Issues

1. **Memory Safety**:
   - Raw pointer in `componentArray` alongside `shared_ptr` in `components`
   - Potential dangling pointers if component is removed

2. **No Component Removal**:
   - No `removeComponent<T>()` method

3. **Thread Safety**:
   - Not thread-safe (not suitable for multi-threaded game loops)

4. **Limited Scalability**:
   - `maxComponents = 32` is hardcoded
   - No entity pooling/recycling

5. **Unused Parameter**:
   - `Entity::Update(float elapsed = 0)` doesn't use `elapsed`

---

## API Reference

### Entity Methods

#### `addComponent<T>(Args...)`
Adds a component of type T to the entity.

**Parameters**: Constructor arguments for the component  
**Returns**: Reference to the created component  
**Example**:
```cpp
auto& pos = entity.addComponent<PositionComponent>(100, 200);
```

#### `getComponent<T>()`
Retrieves a component of type T.

**Returns**: Reference to the component  
**Throws**: Undefined behavior if component doesn't exist  
**Example**:
```cpp
auto& pos = entity.getComponent<PositionComponent>();
```

#### `hasComponent<T>()`
Checks if entity has a component of type T.

**Returns**: `bool`  
**Example**:
```cpp
if (entity.hasComponent<PositionComponent>()) { ... }
```

#### `destroy()`
Marks entity as inactive (removed on next `Refresh()`).

---

### ECSManager Methods

#### `addEntity()`
Creates and registers a new entity.

**Returns**: Reference to the new entity

#### `Refresh()`
Removes all inactive entities from the manager.

**Important**: Call this after destroying entities to free memory.

---

## Usage Examples

### Example 1: Basic Entity Creation

```cpp
#include "ECS.h"

doengine::ECSManager manager;

// Create entity
doengine::Entity& player = manager.addEntity();

// Add components
auto& pos = player.addComponent<PositionComponent>();
pos.setPosition({100, 100});

// Game loop
while (running) {
    manager.Update();
    manager.Render();
    manager.Refresh();
}
```

---

### Example 2: Creating Custom Components

```cpp
// Velocity component
struct VelocityComponent : public doengine::Component
{
    float vx = 0.0f;
    float vy = 0.0f;
    
    void init() override {
        // Initialize velocity
    }
    
    void Update() override {
        // Apply physics
        auto& pos = entity->getComponent<PositionComponent>();
        pos.point.x += static_cast<int>(vx);
        pos.point.y += static_cast<int>(vy);
    }
};

// Sprite component
struct SpriteComponent : public doengine::Component
{
    std::string texturePath;
    int width, height;
    
    void init() override {
        // Load texture
    }
    
    void Render() override {
        auto& pos = entity->getComponent<PositionComponent>();
        // Draw sprite at pos.X(), pos.Y()
    }
};
```

---

### Example 3: Game Object with Multiple Components

```cpp
// Create player entity
doengine::Entity& player = manager.addEntity();

// Position
auto& pos = player.addComponent<PositionComponent>();
pos.setPosition({400, 300});

// Velocity
auto& vel = player.addComponent<VelocityComponent>();
vel.vx = 5.0f;
vel.vy = 0.0f;

// Sprite
auto& sprite = player.addComponent<SpriteComponent>();
sprite.texturePath = "assets/player.png";
sprite.width = 64;
sprite.height = 64;

// Input handling (outside ECS)
void handleInput() {
    if (entity.hasComponent<VelocityComponent>()) {
        auto& vel = entity.getComponent<VelocityComponent>();
        if (keyPressed(KEY_RIGHT)) vel.vx = 5.0f;
        if (keyPressed(KEY_LEFT)) vel.vx = -5.0f;
    }
}
```

---

### Example 4: Entity Destruction

```cpp
// Mark enemy as dead
enemy.destroy();

// Clean up inactive entities
manager.Refresh();  // Enemy is now removed
```

---

### Example 5: System-like Pattern

```cpp
// Physics System (updates all entities with position + velocity)
void PhysicsSystem(doengine::ECSManager& manager) 
{
    for (auto& entity : manager.entities) {
        if (entity->hasComponent<PositionComponent>() && 
            entity->hasComponent<VelocityComponent>()) 
        {
            auto& pos = entity->getComponent<PositionComponent>();
            auto& vel = entity->getComponent<VelocityComponent>();
            
            pos.point.x += static_cast<int>(vel.vx);
            pos.point.y += static_cast<int>(vel.vy);
        }
    }
}

// Call in game loop
PhysicsSystem(manager);
```

---

### Example 6: Collision Detection System

```cpp
struct ColliderComponent : public doengine::Component
{
    int width, height;
    bool isTrigger = false;
    
    bool intersects(const ColliderComponent& other) {
        auto& pos1 = entity->getComponent<PositionComponent>();
        auto& pos2 = other.entity->getComponent<PositionComponent>();
        
        return (pos1.X() < pos2.X() + other.width &&
                pos1.X() + width > pos2.X() &&
                pos1.Y() < pos2.Y() + other.height &&
                pos1.Y() + height > pos2.Y());
    }
};

// Collision System
void CollisionSystem(doengine::ECSManager& manager)
{
    for (size_t i = 0; i < manager.entities.size(); ++i) {
        if (!manager.entities[i]->hasComponent<ColliderComponent>())
            continue;
            
        auto& col1 = manager.entities[i]->getComponent<ColliderComponent>();
        
        for (size_t j = i + 1; j < manager.entities.size(); ++j) {
            if (!manager.entities[j]->hasComponent<ColliderComponent>())
                continue;
                
            auto& col2 = manager.entities[j]->getComponent<ColliderComponent>();
            
            if (col1.intersects(col2)) {
                // Handle collision
                OnCollision(manager.entities[i], manager.entities[j]);
            }
        }
    }
}
```

---

## Improvements & Recommendations

### 1. Fix Critical Bugs

```cpp
// Fixed addComponent
template<typename T, typename...Targs>
T& addComponent(Targs&&... targs)
{
    T* c = new T(std::forward<Targs>(targs)...);  // FIX: forward
    c->entity = this;
    std::shared_ptr<Component> uPtr{c};
    components.emplace_back(uPtr);

    componentArray[getComponentTypeId<T>()] = c;
    componentBitset[getComponentTypeId<T>()] = true;

    c->init();
    return *c;
}

// Fixed getComponent
template<typename T> 
T& getComponent() const
{
    auto ptr = componentArray[getComponentTypeId<T>()];  // FIX: syntax
    return *static_cast<T*>(ptr);
}
```

---

### 2. Add Component Removal

```cpp
template<typename T>
void removeComponent()
{
    if (!hasComponent<T>()) return;
    
    ComponentId id = getComponentTypeId<T>();
    
    // Remove from array
    componentArray[id] = nullptr;
    componentBitset[id] = false;
    
    // Remove from vector
    components.erase(
        std::remove_if(components.begin(), components.end(),
            [id](const std::shared_ptr<Component>& c) {
                return dynamic_cast<T*>(c.get()) != nullptr;
            }),
        components.end()
    );
}
```

---

### 3. Add Safety Checks

```cpp
template<typename T> 
T& getComponent() const
{
    if (!hasComponent<T>()) {
        throw std::runtime_error("Component not found");
    }
    auto ptr = componentArray[getComponentTypeId<T>()];
    return *static_cast<T*>(ptr);
}
```

---

### 4. Use Delta Time

```cpp
struct Entity
{
    void Update(float deltaTime)
    {
        for(auto& it : components) 
            it->Update(deltaTime);
    }
};

struct Component 
{
    virtual void Update(float deltaTime) {}
};
```

---

### 5. Entity Pooling

```cpp
struct ECSManager
{
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entityPool;
    
    Entity& addEntity()
    {
        std::shared_ptr<Entity> p;
        
        if (!entityPool.empty()) {
            p = std::move(entityPool.back());
            entityPool.pop_back();
            p->active = true;
        } else {
            p = std::make_shared<Entity>();
        }
        
        entities.emplace_back(p);
        return *p;
    }
    
    void Refresh()
    {
        for (auto it = entities.begin(); it != entities.end();) {
            if (!(*it)->isActive()) {
                entityPool.push_back(*it);
                it = entities.erase(it);
            } else {
                ++it;
            }
        }
    }
};
```

---

### 6. Component Groups (Systems Pattern)

```cpp
template<typename... ComponentTypes>
std::vector<Entity*> getEntitiesWith()
{
    std::vector<Entity*> result;
    
    for (auto& entity : entities) {
        if ((entity->hasComponent<ComponentTypes>() && ...)) {
            result.push_back(entity.get());
        }
    }
    
    return result;
}

// Usage:
auto movingEntities = manager.getEntitiesWith<PositionComponent, VelocityComponent>();
```

---

### 7. Performance: Reserve Capacity

```cpp
ECSManager() 
{
    entities.reserve(1000);  // Pre-allocate
}
```

---

### 8. Better Memory Management

```cpp
// Use make_shared for better performance
Entity& addEntity()
{
    entities.emplace_back(std::make_shared<Entity>());
    return *entities.back();
}
```

---

## Performance Considerations

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Add Component | O(1) | Direct array indexing |
| Get Component | O(1) | Array lookup by type ID |
| Has Component | O(1) | Bitset check |
| Remove Component | O(n) | Vector erase |
| Iterate Entities | O(n) | Linear scan |
| Refresh (cleanup) | O(n) | Erase-remove idiom |

---

## Best Practices

1. **Always call `Refresh()`** after destroying entities to prevent memory leaks
2. **Check `hasComponent()`** before `getComponent()` to avoid crashes
3. **Use composition** over deep inheritance hierarchies
4. **Keep components data-only** when possible
5. **Implement Systems** as free functions operating on component groups
6. **Profile before optimizing** - ECS is already quite fast for small-medium games

---

## Limitations

- Maximum 32 component types (can be increased by changing `maxComponents`)
- Not thread-safe
- No built-in serialization
- No component dependencies/requirements
- No event system

---

## Conclusion

This ECS implementation provides a solid foundation for a component-based game engine. With the suggested improvements, it would be production-ready for small to medium-sized games. For larger projects, consider libraries like EnTT or FLECS which offer more advanced features.

---

## Additional Resources

- [Game Programming Patterns - Component Pattern](http://gameprogrammingpatterns.com/component.html)
- [EnTT - Modern C++ ECS](https://github.com/skypjack/entt)
- [Data-Oriented Design](https://www.dataorienteddesign.com/dodbook/)


#### Sample Usage...

```cpp
 

#include "EntityComponentSystem.h"
#include <iostream>
#include <cmath>

using namespace doengine;

// ============================================================================
// EXAMPLE 1: Basic Entity Creation and Component Management
// ============================================================================

void example1_basic_usage()
{
    std::cout << "=== Example 1: Basic Usage ===" << std::endl;

    ECSManager manager;

    // Create a simple entity with position
    Entity& player = manager.addEntity();
    auto& pos = player.addComponent<PositionComponent>(100, 200);

    std::cout << "Player position: (" << pos.X() << ", " << pos.Y() << ")" << std::endl;

    // Move the player
    pos.move(50, 30);
    std::cout << "After move: (" << pos.X() << ", " << pos.Y() << ")" << std::endl;

    // Check for components
    if (player.hasComponent<PositionComponent>()) {
        std::cout << "Player has PositionComponent" << std::endl;
    }

    // Game loop simulation
    for (int frame = 0; frame < 3; ++frame) {
        manager.Update(0.016f);  // ~60 FPS
        manager.Render();
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 2: Multiple Components - Moving Entity
// ============================================================================

void example2_moving_entity()
{
    std::cout << "=== Example 2: Moving Entity ===" << std::endl;

    ECSManager manager;

    // Create entity with position and velocity
    Entity& bullet = manager.addEntity();
    bullet.addComponent<PositionComponent>(0, 0);
    bullet.addComponent<VelocityComponent>(100.0f, 50.0f);  // pixels per second

    // Simulate 5 frames
    float deltaTime = 0.016f;  // 60 FPS
    for (int i = 0; i < 5; ++i) {
        manager.Update(deltaTime);
        
        auto& pos = bullet.getComponent<PositionComponent>();
        std::cout << "Frame " << i << ": Position (" 
                  << pos.X() << ", " << pos.Y() << ")" << std::endl;
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 3: Complete Game Entity (Player)
// ============================================================================

void example3_complete_player()
{
    std::cout << "=== Example 3: Complete Player Entity ===" << std::endl;

    ECSManager manager;

    // Create player with all components
    Entity& player = manager.addEntity();
    
    auto& pos = player.addComponent<PositionComponent>(400, 300);
    auto& vel = player.addComponent<VelocityComponent>(0.0f, 0.0f);
    auto& sprite = player.addComponent<SpriteComponent>("assets/player.png", 64, 64);
    auto& collider = player.addComponent<ColliderComponent>(64, 64, "player");

    std::cout << "Created player entity with:" << std::endl;
    std::cout << "  - Position: (" << pos.X() << ", " << pos.Y() << ")" << std::endl;
    std::cout << "  - Sprite: " << sprite.texturePath << std::endl;
    std::cout << "  - Collider: " << collider.width << "x" << collider.height << std::endl;

    // Simulate player input (move right)
    vel.vx = 200.0f;  // Move right at 200 px/s

    // Update a few frames
    for (int i = 0; i < 3; ++i) {
        manager.Update(0.016f);
        auto& currentPos = player.getComponent<PositionComponent>();
        std::cout << "Frame " << i << ": Player at (" 
                  << currentPos.X() << ", " << currentPos.Y() << ")" << std::endl;
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 4: Component Removal
// ============================================================================

void example4_component_removal()
{
    std::cout << "=== Example 4: Component Removal ===" << std::endl;

    ECSManager manager;
    Entity& entity = manager.addEntity();

    // Add components
    entity.addComponent<PositionComponent>(10, 20);
    entity.addComponent<VelocityComponent>(5.0f, 5.0f);

    std::cout << "Has Position: " << entity.hasComponent<PositionComponent>() << std::endl;
    std::cout << "Has Velocity: " << entity.hasComponent<VelocityComponent>() << std::endl;

    // Remove velocity
    entity.removeComponent<VelocityComponent>();

    std::cout << "After removing velocity:" << std::endl;
    std::cout << "Has Position: " << entity.hasComponent<PositionComponent>() << std::endl;
    std::cout << "Has Velocity: " << entity.hasComponent<VelocityComponent>() << std::endl;

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 5: Entity Destruction and Cleanup
// ============================================================================

void example5_entity_lifecycle()
{
    std::cout << "=== Example 5: Entity Lifecycle ===" << std::endl;

    ECSManager manager;

    // Create multiple entities
    for (int i = 0; i < 5; ++i) {
        Entity& ent = manager.addEntity();
        ent.addComponent<PositionComponent>(i * 10, i * 10);
    }

    std::cout << "Created " << manager.getEntityCount() << " entities" << std::endl;

    // Destroy some entities
    manager.entities[1]->destroy();
    manager.entities[3]->destroy();

    std::cout << "Marked 2 entities for destruction" << std::endl;
    std::cout << "Before refresh: " << manager.getEntityCount() << " entities" << std::endl;

    // Clean up
    manager.Refresh();

    std::cout << "After refresh: " << manager.getEntityCount() << " entities" << std::endl;

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 6: Query Entities by Components (System Pattern)
// ============================================================================

void example6_entity_queries()
{
    std::cout << "=== Example 6: Entity Queries ===" << std::endl;

    ECSManager manager;

    // Create different types of entities
    // Static objects (position only)
    for (int i = 0; i < 3; ++i) {
        Entity& wall = manager.addEntity();
        wall.addComponent<PositionComponent>(i * 100, 0);
    }

    // Moving objects (position + velocity)
    for (int i = 0; i < 2; ++i) {
        Entity& enemy = manager.addEntity();
        enemy.addComponent<PositionComponent>(i * 50, 100);
        enemy.addComponent<VelocityComponent>(10.0f, 0.0f);
    }

    std::cout << "Total entities: " << manager.getEntityCount() << std::endl;

    // Query entities with both position and velocity
    auto movingEntities = manager.getEntitiesWith<PositionComponent, VelocityComponent>();
    std::cout << "Moving entities (Position + Velocity): " << movingEntities.size() << std::endl;

    // Process only moving entities
    for (auto* entity : movingEntities) {
        auto& pos = entity->getComponent<PositionComponent>();
        auto& vel = entity->getComponent<VelocityComponent>();
        std::cout << "  Moving entity at (" << pos.X() << ", " << pos.Y() 
                  << ") with velocity (" << vel.vx << ", " << vel.vy << ")" << std::endl;
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 7: Collision Detection System
// ============================================================================

void example7_collision_system()
{
    std::cout << "=== Example 7: Collision Detection ===" << std::endl;

    ECSManager manager;

    // Create player
    Entity& player = manager.addEntity();
    player.addComponent<PositionComponent>(100, 100);
    player.addComponent<ColliderComponent>(32, 32, "player");

    // Create enemies
    Entity& enemy1 = manager.addEntity();
    enemy1.addComponent<PositionComponent>(120, 120);  // Overlapping
    enemy1.addComponent<ColliderComponent>(32, 32, "enemy");

    Entity& enemy2 = manager.addEntity();
    enemy2.addComponent<PositionComponent>(300, 300);  // Far away
    enemy2.addComponent<ColliderComponent>(32, 32, "enemy");

    // Check collisions
    auto collidables = manager.getEntitiesWith<PositionComponent, ColliderComponent>();
    
    std::cout << "Checking collisions for " << collidables.size() << " entities" << std::endl;

    for (size_t i = 0; i < collidables.size(); ++i) {
        auto& col1 = collidables[i]->getComponent<ColliderComponent>();
        
        for (size_t j = i + 1; j < collidables.size(); ++j) {
            auto& col2 = collidables[j]->getComponent<ColliderComponent>();
            
            if (col1.intersects(col2)) {
                std::cout << "COLLISION: " << col1.tag << " hit " << col2.tag << std::endl;
            }
        }
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 8: Custom Physics System
// ============================================================================

// Custom component for gravity
struct GravityComponent : public Component
{
    float gravity = 9.8f;  // pixels per second squared
    
    void Update(float deltaTime) override
    {
        if (entity->hasComponent<VelocityComponent>()) {
            auto& vel = entity->getComponent<VelocityComponent>();
            vel.vy += gravity * deltaTime;
        }
    }
};

void example8_physics_system()
{
    std::cout << "=== Example 8: Physics System ===" << std::endl;

    ECSManager manager;

    // Create falling object
    Entity& ball = manager.addEntity();
    ball.addComponent<PositionComponent>(100, 0);
    ball.addComponent<VelocityComponent>(0.0f, 0.0f);
    ball.addComponent<GravityComponent>();

    std::cout << "Simulating falling ball:" << std::endl;

    // Simulate 5 frames
    for (int i = 0; i < 5; ++i) {
        manager.Update(0.1f);  // 10 FPS for visible effect
        
        auto& pos = ball.getComponent<PositionComponent>();
        auto& vel = ball.getComponent<VelocityComponent>();
        
        std::cout << "Frame " << i << ": Y=" << pos.Y() 
                  << ", Velocity=" << vel.vy << std::endl;
    }

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 9: Entity Pooling Performance
// ============================================================================

void example9_entity_pooling()
{
    std::cout << "=== Example 9: Entity Pooling ===" << std::endl;

    ECSManager manager;

    // Create and destroy entities multiple times
    std::cout << "Creating 100 entities..." << std::endl;
    for (int i = 0; i < 100; ++i) {
        Entity& ent = manager.addEntity();
        ent.addComponent<PositionComponent>(i, i);
    }
    std::cout << "Active entities: " << manager.getEntityCount() << std::endl;

    // Destroy half
    std::cout << "Destroying 50 entities..." << std::endl;
    for (size_t i = 0; i < 50; ++i) {
        manager.entities[i]->destroy();
    }
    manager.Refresh();
    std::cout << "Active entities after refresh: " << manager.getEntityCount() << std::endl;

    // Create new entities (will reuse from pool)
    std::cout << "Creating 50 new entities (from pool)..." << std::endl;
    for (int i = 0; i < 50; ++i) {
        Entity& ent = manager.addEntity();
        ent.addComponent<PositionComponent>(i * 2, i * 2);
    }
    std::cout << "Active entities: " << manager.getEntityCount() << std::endl;

    std::cout << std::endl;
}


// ============================================================================
// EXAMPLE 10: Complete Mini-Game
// ============================================================================

struct HealthComponent : public Component
{
    int health = 100;
    int maxHealth = 100;

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) {
            health = 0;
            entity->destroy();
        }
    }
};

void example10_mini_game()
{
    std::cout << "=== Example 10: Mini Shooter Game ===" << std::endl;

    ECSManager manager;

    // Create player
    Entity& player = manager.addEntity();
    player.addComponent<PositionComponent>(400, 500);
    player.addComponent<VelocityComponent>(0.0f, 0.0f);
    player.addComponent<SpriteComponent>("player.png", 32, 32);
    player.addComponent<ColliderComponent>(32, 32, "player");
    player.addComponent<HealthComponent>();

    // Create enemies
    for (int i = 0; i < 3; ++i) {
        Entity& enemy = manager.addEntity();
        enemy.addComponent<PositionComponent>(100 + i * 150, 100);
        enemy.addComponent<VelocityComponent>(0.0f, 50.0f);  // Move down
        enemy.addComponent<SpriteComponent>("enemy.png", 32, 32);
        enemy.addComponent<ColliderComponent>(32, 32, "enemy");
        auto& health = enemy.addComponent<HealthComponent>();
        health.health = 50;
    }

    std::cout << "Game initialized with:" << std::endl;
    std::cout << "  - 1 Player" << std::endl;
    std::cout << "  - 3 Enemies" << std::endl;

    // Simulate game loop
    for (int frame = 0; frame < 10; ++frame) {
        float deltaTime = 0.016f;
        
        // Update all entities
        manager.Update(deltaTime);

        // Check collisions
        auto collidables = manager.getEntitiesWith<ColliderComponent>();
        for (size_t i = 0; i < collidables.size(); ++i) {
            for (size_t j = i + 1; j < collidables.size(); ++j) {
                auto& col1 = collidables[i]->getComponent<ColliderComponent>();
                auto& col2 = collidables[j]->getComponent<ColliderComponent>();

                if (col1.intersects(col2)) {
                    // Handle collision
                    if (col1.tag == "player" && col2.tag == "enemy") {
                        std::cout << "Frame " << frame << ": Player hit by enemy!" << std::endl;
                        
                        if (collidables[i]->hasComponent<HealthComponent>()) {
                            auto& health = collidables[i]->getComponent<HealthComponent>();
                            health.takeDamage(10);
                            std::cout << "  Player health: " << health.health << std::endl;
                        }
                    }
                }
            }
        }

        // Clean up destroyed entities
        manager.Refresh();
    }

    std::cout << "Game ended. Remaining entities: " << manager.getEntityCount() << std::endl;
    std::cout << std::endl;
}


// ============================================================================
// MAIN
// ============================================================================

int main()
{
    std::cout << "ECS System - Usage Examples" << std::endl;
    std::cout << "======================================" << std::endl << std::endl;

    try {
        example1_basic_usage();
        example2_moving_entity();
        example3_complete_player();
        example4_component_removal();
        example5_entity_lifecycle();
        example6_entity_queries();
        example7_collision_system();
        example8_physics_system();
        example9_entity_pooling();
        example10_mini_game();

        std::cout << "All examples completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```