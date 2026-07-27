/*
 * ============================================================================
 * DOEngine ECS System - Complete Usage Example
 * ============================================================================
 * 
 * This example demonstrates the complete Entity Component System (ECS)
 * architecture in DOEngine. It shows:
 * 
 * 1. Creating a World and entities
 * 2. Adding components to entities
 * 3. Registering systems
 * 4. Running the game loop with ECS
 * 5. Querying entities with specific components
 * 6. Creating custom components and systems
 * 
 * Compile with: g++ -std=c++17 ECS_Example.cpp -o ecs_example
 * (Requires DOEngine headers in include path)
 * 
 * ============================================================================
 */

#include "../includes/EntityComponentSystem.h"
#include <iostream>
#include <cmath>

using namespace doengine;

// ============================================================================
// Custom Component Example: Health System
// ============================================================================

/**
 * @brief Custom health component for game entities
 * 
 * Demonstrates how to create custom components by deriving from Component.
 */
struct HealthComponent : public Component
{
    float maxHealth = 100.0f;
    float currentHealth = 100.0f;
    bool isDead = false;

    HealthComponent() = default;
    explicit HealthComponent(float maxHp) 
        : maxHealth(maxHp), currentHealth(maxHp) {}

    void takeDamage(float damage)
    {
        currentHealth = std::max(0.0f, currentHealth - damage);
        if (currentHealth <= 0.0f)
            isDead = true;
    }

    void heal(float amount)
    {
        currentHealth = std::min(maxHealth, currentHealth + amount);
    }

    float getHealthPercent() const
    {
        return currentHealth / maxHealth;
    }

    void init() override
    {
        std::cout << "  [HealthComponent] Initialized with " << maxHealth << " HP\n";
    }
};

/**
 * @brief Custom input component for player control
 */
struct InputComponent : public Component
{
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
    float moveSpeed = 100.0f;  // pixels per second

    void init() override
    {
        std::cout << "  [InputComponent] Initialized with speed " << moveSpeed << " px/s\n";
    }
};

// ============================================================================
// Custom System Example: Health System
// ============================================================================

/**
 * @brief System that manages entity health
 * 
 * Demonstrates a custom system that:
 * - Processes entities with HealthComponent
 * - Logs health changes
 * - Removes dead entities
 */
class HealthSystem : public System
{
private:
    World* world = nullptr;

public:
    void init(World* w) override
    {
        world = w;
        std::cout << "[HealthSystem] Initialized\n";
    }

    void update(float deltaTime) override
    {
        // Get all entities with health component
        auto entities = world->getEntitiesWith<HealthComponent>();

        for (auto entity : entities)
        {
            auto& health = entity->getComponent<HealthComponent>();

            // Mark dead entities for removal
            if (health.isDead)
            {
                std::cout << "  [HealthSystem] Entity " << entity->getId() 
                         << " is dead. Removing.\n";
                entity->destroy();
            }
        }
    }

    void shutdown() override
    {
        std::cout << "[HealthSystem] Shutdown\n";
    }
};

/**
 * @brief System that handles player input and movement
 * 
 * Demonstrates a system that:
 * - Processes input components
 * - Updates velocity based on input
 * - Clamps movement within bounds
 */
class InputSystem : public System
{
private:
    World* world = nullptr;
    static constexpr float WORLD_WIDTH = 800.0f;
    static constexpr float WORLD_HEIGHT = 600.0f;

public:
    void init(World* w) override
    {
        world = w;
        std::cout << "[InputSystem] Initialized\n";
    }

    void update(float deltaTime) override
    {
        // Get all entities with input and transform
        auto entities = world->getEntitiesWith<InputComponent, TransformComponent>();

        for (auto entity : entities)
        {
            auto& input = entity->getComponent<InputComponent>();
            auto& transform = entity->getComponent<TransformComponent>();

            // Simulate input (in a real app, this would come from keyboard/controller)
            input.moveUp = false;
            input.moveDown = false;
            input.moveLeft = false;
            input.moveRight = false;

            // Update position based on input
            if (input.moveLeft)
                transform.x -= input.moveSpeed * deltaTime;
            if (input.moveRight)
                transform.x += input.moveSpeed * deltaTime;
            if (input.moveUp)
                transform.y -= input.moveSpeed * deltaTime;
            if (input.moveDown)
                transform.y += input.moveSpeed * deltaTime;

            // Clamp position to world bounds
            transform.x = std::max(0.0f, std::min(WORLD_WIDTH - 32.0f, transform.x));
            transform.y = std::max(0.0f, std::min(WORLD_HEIGHT - 32.0f, transform.y));
        }
    }
};

/**
 * @brief System that handles collisions
 * 
 * Demonstrates a system that:
 * - Queries all entities with colliders
 * - Detects collisions between pairs
 * - Applies collision response (damage, knockback, etc.)
 */
class CollisionSystem : public System
{
private:
    World* world = nullptr;

public:
    void init(World* w) override
    {
        world = w;
        std::cout << "[CollisionSystem] Initialized\n";
    }

    void update(float deltaTime) override
    {
        // Get all entities with colliders and transforms
        auto entities = world->getEntitiesWith<TransformComponent, ColliderComponent>();

        // Check all pairs for collisions
        for (size_t i = 0; i < entities.size(); ++i)
        {
            for (size_t j = i + 1; j < entities.size(); ++j)
            {
                auto entity1 = entities[i];
                auto entity2 = entities[j];

                auto& transform1 = entity1->getComponent<TransformComponent>();
                auto& collider1 = entity1->getComponent<ColliderComponent>();
                auto& transform2 = entity2->getComponent<TransformComponent>();
                auto& collider2 = entity2->getComponent<ColliderComponent>();

                if (collider1.intersects(collider2, transform1, transform2))
                {
                    handleCollision(entity1, entity2);
                }
            }
        }
    }

private:
    void handleCollision(Entity* entity1, Entity* entity2)
    {
        std::cout << "  [CollisionSystem] Collision between Entity " 
                 << entity1->getId() << " and Entity " << entity2->getId() << "\n";

        // If one has health, take damage
        auto* health1 = entity1->tryGetComponent<HealthComponent>();
        if (health1)
        {
            health1->takeDamage(10.0f);
            std::cout << "    -> Entity " << entity1->getId() 
                     << " took 10 damage (HP: " << health1->currentHealth << ")\n";
        }

        auto* health2 = entity2->tryGetComponent<HealthComponent>();
        if (health2)
        {
            health2->takeDamage(10.0f);
            std::cout << "    -> Entity " << entity2->getId() 
                     << " took 10 damage (HP: " << health2->currentHealth << ")\n";
        }
    }
};

// ============================================================================
// Example Application
// ============================================================================

void printWorldStatus(World& world)
{
    std::cout << "\n--- World Status ---\n";
    std::cout << "Total entities: " << world.getEntityCount() << "\n";
    
    // Count entities by component
    auto movingEntities = world.getEntitiesWith<TransformComponent, VelocityComponent>();
    std::cout << "Moving entities: " << movingEntities.size() << "\n";
    
    auto healthyEntities = world.getEntitiesWith<HealthComponent>();
    std::cout << "Entities with health: " << healthyEntities.size() << "\n";
    
    for (auto entity : healthyEntities)
    {
        auto& health = entity->getComponent<HealthComponent>();
        auto& transform = entity->getComponent<TransformComponent>();
        std::cout << "  Entity " << entity->getId() << ": " 
                 << health.currentHealth << "/" << health.maxHealth << " HP at (" 
                 << transform.x << ", " << transform.y << ")\n";
    }
}

/**
 * @brief Main ECS example
 */
int main()
{
    std::cout << "============================================\n";
    std::cout << "DOEngine ECS System - Complete Example\n";
    std::cout << "============================================\n\n";

    // ========================================================================
    // Step 1: Create World
    // ========================================================================
    std::cout << "Step 1: Creating World...\n";
    World world;

    // ========================================================================
    // Step 2: Register Systems
    // ========================================================================
    std::cout << "\nStep 2: Registering Systems...\n";
    world.registerSystem<PhysicsSystem>();
    world.registerSystem<MovementSystem>();
    world.registerSystem<InputSystem>();
    world.registerSystem<CollisionSystem>();
    world.registerSystem<HealthSystem>();
    world.registerSystem<AnimationSystem>();

    // ========================================================================
    // Step 3: Create Player Entity
    // ========================================================================
    std::cout << "\nStep 3: Creating Player Entity...\n";
    Entity* player = world.createEntity();
    std::cout << "Created entity " << player->getId() << "\n";
    
    player->addComponent<TransformComponent>(100.0f, 100.0f);
    player->addComponent<VelocityComponent>(0.0f, 0.0f);
    player->addComponent<HealthComponent>(100.0f);
    player->addComponent<InputComponent>(150.0f);
    player->addComponent<ColliderComponent>(32.0f, 32.0f);
    player->addComponent<SpriteComponent>(1);

    // ========================================================================
    // Step 4: Create Enemy Entities
    // ========================================================================
    std::cout << "\nStep 4: Creating Enemy Entities...\n";
    
    Entity* enemy1 = world.createEntity();
    std::cout << "Created entity " << enemy1->getId() << "\n";
    enemy1->addComponent<TransformComponent>(300.0f, 150.0f);
    enemy1->addComponent<VelocityComponent>(50.0f, 0.0f);
    enemy1->addComponent<HealthComponent>(50.0f);
    enemy1->addComponent<ColliderComponent>(32.0f, 32.0f);
    enemy1->addComponent<SpriteComponent>(2);

    Entity* enemy2 = world.createEntity();
    std::cout << "Created entity " << enemy2->getId() << "\n";
    enemy2->addComponent<TransformComponent>(400.0f, 250.0f);
    enemy2->addComponent<VelocityComponent>(-30.0f, 0.0f);
    enemy2->addComponent<HealthComponent>(75.0f);
    enemy2->addComponent<AccelerationComponent>(0.0f, 100.0f);  // Gravity
    enemy2->addComponent<ColliderComponent>(32.0f, 32.0f);
    enemy2->addComponent<SpriteComponent>(3);

    // ========================================================================
    // Step 5: Create Projectile Entity
    // ========================================================================
    std::cout << "\nStep 5: Creating Projectile Entity...\n";
    
    Entity* projectile = world.createEntity();
    std::cout << "Created entity " << projectile->getId() << "\n";
    projectile->addComponent<TransformComponent>(150.0f, 120.0f);
    projectile->addComponent<VelocityComponent>(200.0f, 0.0f);
    projectile->addComponent<ColliderComponent>(8.0f, 8.0f);
    projectile->addComponent<SpriteComponent>(4);

    printWorldStatus(world);

    // ========================================================================
    // Step 6: Simulate World Updates
    // ========================================================================
    std::cout << "\n============================================\n";
    std::cout << "Simulating 5 seconds of gameplay (5 updates @ 1s each)\n";
    std::cout << "============================================\n";

    for (int frame = 1; frame <= 5; ++frame)
    {
        std::cout << "\n--- Frame " << frame << " (t=" << frame << "s) ---\n";
        
        // Make enemy1 move towards player
        if (frame == 1)
        {
            auto& enemy1_transform = enemy1->getComponent<TransformComponent>();
            auto& enemy1_velocity = enemy1->getComponent<VelocityComponent>();
            std::cout << "Enemy1 changing direction...\n";
            enemy1_velocity.vx = -50.0f;  // Move towards player
        }

        // Projectile hits enemy at frame 3
        if (frame == 3)
        {
            std::cout << "Simulating collision event...\n";
            auto& proj_transform = projectile->getComponent<TransformComponent>();
            auto& enemy1_transform = enemy1->getComponent<TransformComponent>();
            
            // Move projectile to enemy position
            proj_transform.x = 300.0f;
            proj_transform.y = 150.0f;
        }

        // Player takes damage at frame 4
        if (frame == 4)
        {
            std::cout << "Player gets hit by enemy!\n";
            auto& player_health = player->getComponent<HealthComponent>();
            player_health.takeDamage(20.0f);
            std::cout << "  Player health: " << player_health.currentHealth << " HP\n";
        }

        // Update world
        world.update(1.0f);  // 1 second delta time
        world.render();

        printWorldStatus(world);
    }

    // ========================================================================
    // Step 7: Advanced Queries
    // ========================================================================
    std::cout << "\n============================================\n";
    std::cout << "Step 7: Advanced Entity Queries\n";
    std::cout << "============================================\n";

    // Query: All entities with health
    auto healthEntities = world.getEntitiesWith<HealthComponent>();
    std::cout << "\nEntities with Health: " << healthEntities.size() << "\n";
    for (auto e : healthEntities)
    {
        std::cout << "  Entity " << e->getId() << ": " 
                 << e->getComponent<HealthComponent>().currentHealth << " HP\n";
    }

    // Query: All moving entities
    auto movingEntities = world.getEntitiesWith<TransformComponent, VelocityComponent>();
    std::cout << "\nMoving Entities: " << movingEntities.size() << "\n";
    for (auto e : movingEntities)
    {
        auto& pos = e->getComponent<TransformComponent>();
        auto& vel = e->getComponent<VelocityComponent>();
        std::cout << "  Entity " << e->getId() << ": pos(" << pos.x << "," 
                 << pos.y << ") vel(" << vel.vx << "," << vel.vy << ")\n";
    }

    // Query: All collidable entities
    auto collidables = world.getEntitiesWith<TransformComponent, ColliderComponent>();
    std::cout << "\nCollidable Entities: " << collidables.size() << "\n";
    for (auto e : collidables)
    {
        auto& collider = e->getComponent<ColliderComponent>();
        std::cout << "  Entity " << e->getId() << ": " 
                 << collider.width << "x" << collider.height << "\n";
    }

    // ========================================================================
    // Step 8: Cleanup
    // ========================================================================
    std::cout << "\n============================================\n";
    std::cout << "Step 8: Shutting Down\n";
    std::cout << "============================================\n";
    
    world.shutdown();
    std::cout << "World shutdown complete. All entities and systems cleaned up.\n";

    std::cout << "\n--- Example Complete ---\n";
    std::cout << "\nKey Takeaways:\n";
    std::cout << "1. Create a World instance\n";
    std::cout << "2. Register systems via world.registerSystem<SystemType>()\n";
    std::cout << "3. Create entities via world.createEntity()\n";
    std::cout << "4. Add components via entity->addComponent<ComponentType>(...)\n";
    std::cout << "5. Query entities via world.getEntitiesWith<Component1, Component2>(...)\n";
    std::cout << "6. Systems process matched entities in world.update(deltaTime)\n";
    std::cout << "7. Always call world.shutdown() to cleanup resources\n";

    return 0;
}
