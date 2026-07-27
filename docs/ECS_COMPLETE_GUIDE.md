# DOEngine Entity Component System (ECS) - Complete Guide

## Overview

The Entity Component System (ECS) is a powerful architectural pattern for building flexible, maintainable game engines. DOEngine now includes a **complete, production-ready ECS implementation** that replaces the inheritance-based `GameObject` hierarchy.

**Key Benefits:**
- ✅ **Composition over inheritance** - More flexible than GameObject hierarchy
- ✅ **Data-oriented design** - Better cache locality and performance
- ✅ **Easy to extend** - Add new systems without modifying existing code
- ✅ **Reusable components** - Mix and match behaviors freely
- ✅ **System scheduling** - Centralized update loop management

---

## Architecture

### Core Concepts

```
World
├── Entities (containers for components)
│   ├── Entity 1
│   │   ├── TransformComponent
│   │   ├── VelocityComponent
│   │   └── SpriteComponent
│   └── Entity 2
│       ├── TransformComponent
│       ├── HealthComponent
│       └── ColliderComponent
│
└── Systems (operate on entities with specific components)
    ├── MovementSystem (reads: Transform, Velocity)
    ├── PhysicsSystem (reads: Velocity, Acceleration)
    ├── CollisionSystem (reads: Transform, Collider)
    └── HealthSystem (reads: Health)
```

### Component Bitset Signature

Each entity maintains a bitset of which components it has:

```cpp
Entity e;
e.addComponent<TransformComponent>();
e.addComponent<VelocityComponent>();

// Components: [Transform=1][Velocity=1][Sprite=0][Health=0]...
// Bitset: 0011 (binary)

// Systems can quickly query: "Give me all entities with bitset pattern 0011"
```

---

## Quick Start (5 minutes)

### Basic Example

```cpp
#include "EntityComponentSystem.h"
using namespace doengine;

// Create a world
World world;

// Register systems
world.registerSystem<MovementSystem>();
world.registerSystem<PhysicsSystem>();

// Create an entity
Entity* player = world.createEntity();

// Add components
player->addComponent<TransformComponent>(100.0f, 50.0f);
player->addComponent<VelocityComponent>(10.0f, 0.0f);
player->addComponent<SpriteComponent>(textureId);

// In game loop:
while (gameRunning) {
    world.update(deltaTime);
    world.render();
}

world.shutdown();
```

---

## Components

### What is a Component?

A **component** is a pure data container that holds a specific aspect of an entity's behavior.

```cpp
struct HealthComponent : public Component {
    float maxHealth = 100.0f;
    float currentHealth = 100.0f;
    
    void takeDamage(float damage) {
        currentHealth -= damage;
    }
};
```

### Built-in Components

#### TransformComponent
Represents position, rotation, and scale.

```cpp
auto& transform = entity->addComponent<TransformComponent>(x, y);
// Or with rotation and scale:
auto& transform = entity->addComponent<TransformComponent>(x, y, rotation, scaleX, scaleY);

transform.x += 10.0f;
transform.setPosition(100.0f, 200.0f);
Point pos = transform.getPosition();
```

#### VelocityComponent
Represents movement per frame.

```cpp
auto& vel = entity->addComponent<VelocityComponent>(vx, vy);
vel.vx = 50.0f;  // 50 pixels per second
vel.vy = 0.0f;
```

#### AccelerationComponent
Represents acceleration (often gravity).

```cpp
auto& accel = entity->addComponent<AccelerationComponent>(ax, ay);
// Apply gravity
accel.ay = 9.8f;
```

#### SpriteComponent
Holds sprite/texture and animation data.

```cpp
auto& sprite = entity->addComponent<SpriteComponent>(textureId);
sprite.frameCount = 8;      // 8-frame animation
sprite.frameDelay = 5;      // 5 updates per frame
sprite.updateAnimation();   // Call in AnimationSystem
```

#### ColliderComponent
Bounding box for collision detection.

```cpp
auto& collider = entity->addComponent<ColliderComponent>(width, height);
// Or with offset:
auto& collider = entity->addComponent<ColliderComponent>(32, 32, offsetX, offsetY);

// Collision check
if (collider.intersects(other, myTransform, otherTransform)) {
    // Collision!
}
```

#### RigidbodyComponent
Physics properties.

```cpp
auto& rb = entity->addComponent<RigidbodyComponent>(mass, isKinematic, useGravity);
rb.mass = 5.0f;
rb.useGravity = true;
```

#### TagComponent
Simple string identifier for categorization.

```cpp
auto& tag = entity->addComponent<TagComponent>("player");
std::string myTag = entity->getComponent<TagComponent>().tag;
```

### Creating Custom Components

```cpp
struct DamageComponent : public Component {
    float damage = 10.0f;
    float attackCooldown = 0.5f;
    float cooldownTimer = 0.0f;
    
    void init() override {
        std::cout << "DamageComponent created\n";
    }
    
    void update(float deltaTime) override {
        cooldownTimer -= deltaTime;
    }
};

// Use it:
Entity* weapon = world.createEntity();
weapon->addComponent<DamageComponent>(15.0f);
```

### Component Lifecycle

```cpp
// Add a component
auto& health = entity->addComponent<HealthComponent>(100.0f);
// → Calls init() automatically

// Check if component exists
if (entity->hasComponent<HealthComponent>()) {
    // ...
}

// Get component (throws if not found)
auto& health = entity->getComponent<HealthComponent>();

// Safely get component (returns nullptr if not found)
auto* health = entity->tryGetComponent<HealthComponent>();
if (health) {
    health->takeDamage(10.0f);
}

// Remove component
entity->removeComponent<HealthComponent>();
```

---

## Systems

### What is a System?

A **system** implements game logic that operates on entities with specific components.

```cpp
class MovementSystem : public System {
private:
    World* world = nullptr;
    
public:
    void init(World* w) override {
        world = w;
        // Initialize system resources
    }
    
    void update(float deltaTime) override {
        // Get all entities with Transform AND Velocity
        auto entities = world->getEntitiesWith<TransformComponent, VelocityComponent>();
        
        for (auto entity : entities) {
            auto& transform = entity->getComponent<TransformComponent>();
            auto& velocity = entity->getComponent<VelocityComponent>();
            
            // Apply movement
            transform.x += velocity.vx * deltaTime;
            transform.y += velocity.vy * deltaTime;
        }
    }
    
    void render() override {
        // Render-specific logic
    }
    
    void shutdown() override {
        // Cleanup resources
    }
};
```

### Built-in Systems

#### MovementSystem
Applies velocity to transform.

```cpp
world.registerSystem<MovementSystem>();
// Entities with <Transform, Velocity> will move automatically
```

#### PhysicsSystem
Applies acceleration to velocity.

```cpp
world.registerSystem<PhysicsSystem>();
// Entities with <Velocity, Acceleration> will accelerate automatically
```

#### AnimationSystem
Updates sprite animation frames.

```cpp
world.registerSystem<AnimationSystem>();
// Entities with <SpriteComponent> will animate automatically
```

### Creating Custom Systems

```cpp
class HealthRegenSystem : public System {
private:
    World* world = nullptr;
    static constexpr float regenRate = 5.0f;
    
public:
    void init(World* w) override { world = w; }
    
    void update(float deltaTime) override {
        // Find all entities with health
        auto entities = world->getEntitiesWith<HealthComponent>();
        
        for (auto entity : entities) {
            auto& health = entity->getComponent<HealthComponent>();
            health.heal(regenRate * deltaTime);
        }
    }
};

// Register it
world.registerSystem<HealthRegenSystem>();
```

### System Order Matters

Systems are executed in the order they were registered:

```cpp
world.registerSystem<InputSystem>();      // Update input first
world.registerSystem<MovementSystem>();   // Then move
world.registerSystem<CollisionSystem>();  // Then check collisions
world.registerSystem<PhysicsSystem>();    // Finally apply physics
```

---

## World & Entity Management

### Creating Entities

```cpp
World world;

Entity* entity = world.createEntity();
// Entity ID is automatically assigned (starting from 1)
uint32_t id = entity->getId();

Entity* player = world.createEntity();
Entity* enemy = world.createEntity();
```

### Querying Entities

```cpp
// Get all entities (expensive - use sparingly)
auto allEntities = world.getEntities();

// Get entities with specific components (FAST - use this!)
auto moving = world.getEntitiesWith<TransformComponent, VelocityComponent>();

// Multiple components
auto alive = world.getEntitiesWith<HealthComponent>();
auto collidables = world.getEntitiesWith<TransformComponent, ColliderComponent>();

// Complex queries - combine multiple queries manually
auto playerCandidates = world.getEntitiesWith<HealthComponent, InputComponent>();
for (auto entity : playerCandidates) {
    auto* tag = entity->tryGetComponent<TagComponent>();
    if (tag && tag->tag == "player") {
        // Found player!
    }
}
```

### Entity Lifecycle

```cpp
// Create
Entity* entity = world.createEntity();

// Check if active
if (entity->isActive()) {
    // Entity is alive
}

// Destroy (deactivate)
entity->destroy();
// Or:
world.destroyEntity(entity);

// After calling destroy(), entity is inactive but still in world
// Clean up inactive entities with:
world.refresh();

// Shutdown everything
world.shutdown();
```

---

## Update & Render Loop

### Basic Loop

```cpp
while (gameRunning) {
    float deltaTime = calculateDeltaTime();
    
    // Update all systems and entities
    world.update(deltaTime);
    
    // Render all systems and entities
    world.render();
}
```

### What Happens in update()?

```cpp
void World::update(float deltaTime) {
    // 1. Update all systems (in registration order)
    for (auto& system : systems) {
        system->update(deltaTime);  // Systems process entities
    }
    
    // 2. Update all entity components
    for (auto& entity : entities) {
        if (entity->isActive()) {
            entity->update(deltaTime);  // Components can update themselves
        }
    }
    
    // 3. Remove inactive entities
    refresh();
}
```

---

## Practical Examples

### Example 1: Simple Player with Health

```cpp
// Create world and register systems
World world;
world.registerSystem<InputSystem>();
world.registerSystem<MovementSystem>();
world.registerSystem<HealthSystem>();

// Create player
Entity* player = world.createEntity();
player->addComponent<TransformComponent>(400, 300);
player->addComponent<VelocityComponent>();
player->addComponent<InputComponent>(150.0f);  // Move speed
player->addComponent<HealthComponent>(100.0f);
player->addComponent<SpriteComponent>(playerTexture);
player->addComponent<ColliderComponent>(32, 32);

// Game loop
while (gameRunning) {
    world.update(deltaTime);
    world.render();
    
    // Check if player is dead
    if (!player->isActive()) {
        std::cout << "Game Over!\n";
        break;
    }
}

world.shutdown();
```

### Example 2: Projectile System

```cpp
class ProjectileSystem : public System {
private:
    World* world = nullptr;
    
public:
    void init(World* w) override { world = w; }
    
    void update(float deltaTime) override {
        auto projectiles = world->getEntitiesWith<TransformComponent, VelocityComponent, TagComponent>();
        
        for (auto proj : projectiles) {
            auto& tag = proj->getComponent<TagComponent>();
            if (tag.tag != "projectile") continue;
            
            auto& transform = proj->getComponent<TransformComponent>();
            
            // Remove if off-screen
            if (transform.x < 0 || transform.x > 800 ||
                transform.y < 0 || transform.y > 600) {
                proj->destroy();
            }
        }
    }
};

// Spawn projectile
Entity* projectile = world.createEntity();
projectile->addComponent<TransformComponent>(playerX, playerY);
projectile->addComponent<VelocityComponent>(500.0f, 0.0f);  // Move right
projectile->addComponent<ColliderComponent>(4, 4);
projectile->addComponent<TagComponent>("projectile");

world.registerSystem<ProjectileSystem>();
```

### Example 3: Collision Response

```cpp
class DamageOnCollisionSystem : public System {
private:
    World* world = nullptr;
    
public:
    void init(World* w) override { world = w; }
    
    void update(float deltaTime) override {
        // Find all collidable entities
        auto entities = world->getEntitiesWith<TransformComponent, ColliderComponent>();
        
        for (size_t i = 0; i < entities.size(); ++i) {
            for (size_t j = i + 1; j < entities.size(); ++j) {
                auto e1 = entities[i];
                auto e2 = entities[j];
                
                auto& t1 = e1->getComponent<TransformComponent>();
                auto& c1 = e1->getComponent<ColliderComponent>();
                auto& t2 = e2->getComponent<TransformComponent>();
                auto& c2 = e2->getComponent<ColliderComponent>();
                
                if (c1.intersects(c2, t1, t2)) {
                    // Apply damage if both have health
                    auto* h1 = e1->tryGetComponent<HealthComponent>();
                    auto* h2 = e2->tryGetComponent<HealthComponent>();
                    
                    if (h1) h1->takeDamage(10.0f);
                    if (h2) h2->takeDamage(10.0f);
                }
            }
        }
    }
};

world.registerSystem<CollisionSystem>();
world.registerSystem<DamageOnCollisionSystem>();
```

---

## Performance Considerations

### ✅ DO

- Use component queries `getEntitiesWith<>()` instead of looping all entities
- Keep components simple - just data
- Put logic in systems, not components
- Use `tryGetComponent()` to safely check for optional components
- Register systems in logical order
- Call `refresh()` periodically to clean up dead entities

### ❌ DON'T

- Don't create/destroy entities in system updates (causes iterator invalidation)
- Don't add/remove components during system updates
- Don't put game logic in component constructors
- Don't query all entities every frame without caching
- Don't have circular dependencies between systems
- Don't leak entity pointers after calling `destroy()`

### Bitset Query Performance

Entity queries are **O(n)** but very fast because they only check bitsets:

```cpp
// This is FAST - just bitset comparison for each entity
auto moving = world.getEntitiesWith<TransformComponent, VelocityComponent>();
```

---

## Migration from GameObject

### Old Way (Inheritance)

```cpp
class Player : public GameObject {
    void Update() override { /* player logic */ }
    void Render() override { /* player rendering */ }
};

class Enemy : public GameObject {
    void Update() override { /* enemy logic */ }
    void Render() override { /* enemy rendering */ }
};
```

### New Way (ECS)

```cpp
// Single system handles all movement
class MovementSystem : public System {
    void update(float dt) override {
        auto entities = world->getEntitiesWith<Transform, Velocity>();
        for (auto e : entities) {
            // Update all moving things
        }
    }
};

// Create players and enemies the same way
Entity* player = world.createEntity();
player->addComponent<TransformComponent>();
player->addComponent<InputComponent>();
player->addComponent<HealthComponent>();

Entity* enemy = world.createEntity();
enemy->addComponent<TransformComponent>();
enemy->addComponent<AIComponent>();
enemy->addComponent<HealthComponent>();
```

**Benefits:**
- No deep inheritance hierarchies
- Reusable components
- Centralized game logic in systems
- Easy to add new behaviors without new classes

---

## Troubleshooting

### "Component not found on entity"

```cpp
// ❌ WRONG - component doesn't exist yet
auto& health = entity->getComponent<HealthComponent>();

// ✅ RIGHT - check first
if (entity->hasComponent<HealthComponent>()) {
    auto& health = entity->getComponent<HealthComponent>();
}

// ✅ RIGHT - use try version
auto* health = entity->tryGetComponent<HealthComponent>();
if (health) {
    health->takeDamage(10.0f);
}
```

### Entities not updating

```cpp
// ❌ WRONG - forgot to register systems
World world;
Entity* e = world.createEntity();
e->addComponent<TransformComponent>();
e->addComponent<VelocityComponent>();
// Nothing moves - no MovementSystem!

// ✅ RIGHT
World world;
world.registerSystem<MovementSystem>();  // Register system first
Entity* e = world.createEntity();
e->addComponent<TransformComponent>();
e->addComponent<VelocityComponent>();
// Now it moves!
```

### Dangling pointers after destroy()

```cpp
// ❌ WRONG
Entity* e = world.createEntity();
e->addComponent<HealthComponent>();
world.destroyEntity(e);
world.update(1.0f);  // world.refresh() called, e removed

// Using e here is undefined behavior!
e->addComponent<VelocityComponent>();  // Crash!

// ✅ RIGHT
Entity* e = world.createEntity();
e->addComponent<HealthComponent>();
world.destroyEntity(e);
e = nullptr;  // Clear pointer
world.update(1.0f);

if (e) {
    e->addComponent<VelocityComponent>();
}
```

---

## API Reference

### World

```cpp
Entity* createEntity();                                      // Create new entity
void destroyEntity(Entity* entity);                          // Mark as inactive
void refresh();                                              // Remove inactive entities
const std::vector<std::shared_ptr<Entity>>& getEntities();   // Get all entities
size_t getEntityCount() const;                               // Get entity count

template<typename... Components>
std::vector<Entity*> getEntitiesWith();                      // Query entities

template<typename T, typename... Args>
T* registerSystem(Args&&... args);                           // Register system

void update(float deltaTime);                                // Update all systems
void render();                                               // Render all systems
void shutdown();                                             // Cleanup everything
```

### Entity

```cpp
uint32_t getId() const;                    // Get entity ID
bool isActive() const;                     // Check if active
void setActive(bool state);                // Set active state
void destroy();                            // Mark as inactive
World* getWorld() const;                   // Get parent world

template<typename T, typename... Args>
T& addComponent(Args&&... args);           // Add component

template<typename T>
bool hasComponent() const;                 // Check if has component

template<typename T>
T& getComponent() const;                   // Get component (throws if not found)

template<typename T>
T* tryGetComponent() const;                // Get component (returns nullptr if not found)

template<typename T>
void removeComponent();                    // Remove component

const ComponentBitset& getComponentBitset() const;  // Get component signature
void update(float deltaTime);              // Update all components
void render();                             // Render all components
```

### System

```cpp
virtual void init(World* world);           // Called on registration
virtual void update(float deltaTime);      // Called each frame (pure virtual)
virtual void render();                     // Called each render frame
virtual void shutdown();                   // Called on unregistration
```

### Component

```cpp
virtual void init();                       // Called when added to entity
virtual void update(float deltaTime);      // Called each frame
virtual void render();                     // Called each render frame
virtual ~Component();                      // Destructor
```

---

## Summary

The DOEngine ECS system provides:

✅ **Flexible composition** - Mix and match components freely
✅ **Efficient querying** - Bitset-based component lookup
✅ **Organized systems** - Centralized game logic
✅ **Easy to extend** - Create custom components and systems
✅ **Production-ready** - Robust memory management with smart pointers
✅ **Well-documented** - Comprehensive examples and API docs

Start with simple systems and components, and build up your game logic incrementally!

For a complete working example, see [`sample/ECS_Example.cpp`](../sample/ECS_Example.cpp).
