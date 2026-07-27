/*
 * ============================================================================
 * DOEngine ECS System Unit Tests
 * ============================================================================
 * 
 * Comprehensive test suite for the Entity Component System.
 * Tests core functionality, edge cases, and system integration.
 * 
 * Build: g++ -std=c++17 utEntityComponentSystem.cpp -o test_ecs
 * Run: ./test_ecs
 * 
 * ============================================================================
 */

#include <cassert>
#include <iostream>
#include <sstream>

// Minimal DOEngine includes (would be from actual build)
// For standalone testing, include EntityComponentSystem.h

#define TEST_ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "❌ FAILED: " << message << std::endl; \
        return false; \
    } else { \
        std::cout << "✓ " << message << std::endl; \
    }

#define TEST_THROWS(expression, message) \
    try { \
        expression; \
        std::cerr << "❌ FAILED: Expected exception but none thrown: " << message << std::endl; \
        return false; \
    } catch (...) { \
        std::cout << "✓ " << message << std::endl; \
    }

// ============================================================================
// Test Components
// ============================================================================

struct TestComponent : public doengine::Component {
    int value = 0;
    bool initialized = false;
    
    void init() override { initialized = true; }
};

struct TestComponent2 : public doengine::Component {
    float data = 0.0f;
};

struct CounterComponent : public doengine::Component {
    static int updateCount;
    
    void update(float dt) override {
        updateCount++;
    }
};

int CounterComponent::updateCount = 0;

// ============================================================================
// Test Systems
// ============================================================================

class CountingSystem : public doengine::System {
public:
    static int updateCalls;
    
    void update(float deltaTime) override {
        updateCalls++;
    }
};

int CountingSystem::updateCalls = 0;

// ============================================================================
// Test Suites
// ============================================================================

bool test_entity_creation() {
    using namespace doengine;
    
    World world;
    Entity* e1 = world.createEntity();
    Entity* e2 = world.createEntity();
    
    TEST_ASSERT(e1 != nullptr, "Entity creation returns non-null");
    TEST_ASSERT(e2 != nullptr, "Second entity creation returns non-null");
    TEST_ASSERT(e1->getId() != e2->getId(), "Each entity has unique ID");
    TEST_ASSERT(world.getEntityCount() == 2, "World has 2 entities");
    
    return true;
}

bool test_component_addition() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    auto& comp = e->addComponent<TestComponent>();
    TEST_ASSERT(e->hasComponent<TestComponent>(), "Entity has component after addition");
    TEST_ASSERT(comp.initialized, "Component init() was called");
    
    return true;
}

bool test_component_retrieval() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    auto& comp1 = e->addComponent<TestComponent>();
    comp1.value = 42;
    
    auto& comp2 = e->getComponent<TestComponent>();
    TEST_ASSERT(comp2.value == 42, "Retrieved component has correct data");
    
    return true;
}

bool test_component_missing_exception() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    TEST_THROWS(
        e->getComponent<TestComponent>(),
        "getComponent throws for missing component"
    );
    
    return true;
}

bool test_try_get_component() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    auto* comp = e->tryGetComponent<TestComponent>();
    TEST_ASSERT(comp == nullptr, "tryGetComponent returns nullptr for missing component");
    
    e->addComponent<TestComponent>();
    comp = e->tryGetComponent<TestComponent>();
    TEST_ASSERT(comp != nullptr, "tryGetComponent returns valid pointer for present component");
    
    return true;
}

bool test_multiple_components() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    e->addComponent<TestComponent>();
    e->addComponent<TestComponent2>();
    
    TEST_ASSERT(e->hasComponent<TestComponent>(), "Entity has first component");
    TEST_ASSERT(e->hasComponent<TestComponent2>(), "Entity has second component");
    TEST_ASSERT(world.getEntityCount() == 1, "Still only 1 entity");
    
    return true;
}

bool test_component_removal() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    e->addComponent<TestComponent>();
    TEST_ASSERT(e->hasComponent<TestComponent>(), "Component exists after addition");
    
    e->removeComponent<TestComponent>();
    TEST_ASSERT(!e->hasComponent<TestComponent>(), "Component removed successfully");
    
    return true;
}

bool test_entity_destruction() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    TEST_ASSERT(e->isActive(), "Entity is active after creation");
    
    e->destroy();
    TEST_ASSERT(!e->isActive(), "Entity inactive after destroy()");
    TEST_ASSERT(world.getEntityCount() == 1, "Destroyed entity still in world");
    
    world.refresh();
    TEST_ASSERT(world.getEntityCount() == 0, "Destroyed entity removed after refresh()");
    
    return true;
}

bool test_system_registration() {
    using namespace doengine;
    
    World world;
    CountingSystem::updateCalls = 0;
    
    auto* sys = world.registerSystem<CountingSystem>();
    TEST_ASSERT(sys != nullptr, "registerSystem returns valid system");
    
    return true;
}

bool test_system_update() {
    using namespace doengine;
    
    World world;
    CountingSystem::updateCalls = 0;
    
    world.registerSystem<CountingSystem>();
    world.update(0.016f);
    
    TEST_ASSERT(CountingSystem::updateCalls == 1, "System update called once");
    
    world.update(0.016f);
    TEST_ASSERT(CountingSystem::updateCalls == 2, "System update called twice");
    
    return true;
}

bool test_entity_query() {
    using namespace doengine;
    
    World world;
    
    Entity* e1 = world.createEntity();
    e1->addComponent<TestComponent>();
    e1->addComponent<TestComponent2>();
    
    Entity* e2 = world.createEntity();
    e2->addComponent<TestComponent>();
    
    Entity* e3 = world.createEntity();
    e3->addComponent<TestComponent2>();
    
    auto withBoth = world.getEntitiesWith<TestComponent, TestComponent2>();
    TEST_ASSERT(withBoth.size() == 1, "Query finds 1 entity with both components");
    TEST_ASSERT(withBoth[0] == e1, "Query returns correct entity");
    
    auto withTest = world.getEntitiesWith<TestComponent>();
    TEST_ASSERT(withTest.size() == 2, "Query finds 2 entities with TestComponent");
    
    auto withTest2 = world.getEntitiesWith<TestComponent2>();
    TEST_ASSERT(withTest2.size() == 2, "Query finds 2 entities with TestComponent2");
    
    return true;
}

bool test_built_in_components() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    auto& transform = e->addComponent<TransformComponent>(100.0f, 200.0f);
    TEST_ASSERT(transform.x == 100.0f, "Transform X coordinate set");
    TEST_ASSERT(transform.y == 200.0f, "Transform Y coordinate set");
    
    auto& velocity = e->addComponent<VelocityComponent>(10.0f, 20.0f);
    TEST_ASSERT(velocity.vx == 10.0f, "Velocity X set");
    TEST_ASSERT(velocity.vy == 20.0f, "Velocity Y set");
    
    auto& health = e->addComponent<RigidbodyComponent>(5.0f, false, true);
    TEST_ASSERT(health.mass == 5.0f, "Rigidbody mass set");
    
    return true;
}

bool test_movement_system() {
    using namespace doengine;
    
    World world;
    world.registerSystem<MovementSystem>();
    
    Entity* e = world.createEntity();
    auto& transform = e->addComponent<TransformComponent>(0.0f, 0.0f);
    auto& velocity = e->addComponent<VelocityComponent>(10.0f, 5.0f);
    
    world.update(1.0f);  // 1 second
    
    TEST_ASSERT(transform.x == 10.0f, "Transform X updated by MovementSystem");
    TEST_ASSERT(transform.y == 5.0f, "Transform Y updated by MovementSystem");
    
    world.update(1.0f);  // Another second
    
    TEST_ASSERT(transform.x == 20.0f, "Transform X updated again");
    TEST_ASSERT(transform.y == 10.0f, "Transform Y updated again");
    
    return true;
}

bool test_physics_system() {
    using namespace doengine;
    
    World world;
    world.registerSystem<PhysicsSystem>();
    
    Entity* e = world.createEntity();
    auto& velocity = e->addComponent<VelocityComponent>(10.0f, 0.0f);
    auto& accel = e->addComponent<AccelerationComponent>(5.0f, 0.0f);
    
    world.update(1.0f);
    
    TEST_ASSERT(velocity.vx == 15.0f, "Velocity updated by PhysicsSystem");
    
    world.update(1.0f);
    
    TEST_ASSERT(velocity.vx == 20.0f, "Velocity updated again");
    
    return true;
}

bool test_animation_system() {
    using namespace doengine;
    
    World world;
    world.registerSystem<AnimationSystem>();
    
    Entity* e = world.createEntity();
    auto& sprite = e->addComponent<SpriteComponent>(1);
    sprite.frameCount = 4;
    sprite.frameDelay = 2;
    
    world.update(0.016f);
    TEST_ASSERT(sprite.frameIndex == 0, "Frame index unchanged before delay");
    
    world.update(0.016f);
    TEST_ASSERT(sprite.frameIndex == 1, "Frame index incremented after delay");
    
    return true;
}

bool test_collider_intersection() {
    using namespace doengine;
    
    Entity e1, e2;
    
    auto& t1 = e1.addComponent<TransformComponent>(0.0f, 0.0f);
    auto& c1 = e1.addComponent<ColliderComponent>(10.0f, 10.0f);
    
    auto& t2 = e2.addComponent<TransformComponent>(5.0f, 5.0f);
    auto& c2 = e2.addComponent<ColliderComponent>(10.0f, 10.0f);
    
    TEST_ASSERT(c1.intersects(c2, t1, t2), "Overlapping colliders detected");
    
    t2.x = 20.0f;
    TEST_ASSERT(!c1.intersects(c2, t1, t2), "Non-overlapping colliders not detected");
    
    return true;
}

bool test_tag_component() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    auto& tag = e->addComponent<TagComponent>("player");
    TEST_ASSERT(tag.tag == "player", "Tag component stores string");
    
    auto& retrieved = e->getComponent<TagComponent>();
    TEST_ASSERT(retrieved.tag == "player", "Tag retrieved correctly");
    
    return true;
}

bool test_component_initialization() {
    using namespace doengine;
    
    World world;
    Entity* e = world.createEntity();
    
    TestComponent::init() should have been called
    auto& comp = e->addComponent<TestComponent>();
    
    TEST_ASSERT(comp.initialized, "Component init() called during addition");
    
    return true;
}

bool test_world_shutdown() {
    using namespace doengine;
    
    World world;
    Entity* e1 = world.createEntity();
    Entity* e2 = world.createEntity();
    e1->addComponent<TestComponent>();
    
    TEST_ASSERT(world.getEntityCount() == 2, "World has 2 entities");
    
    world.shutdown();
    
    TEST_ASSERT(world.getEntityCount() == 0, "World has 0 entities after shutdown");
    
    return true;
}

bool test_component_update() {
    using namespace doengine;
    
    World world;
    
    Entity* e1 = world.createEntity();
    Entity* e2 = world.createEntity();
    
    CounterComponent::updateCount = 0;
    
    e1->addComponent<CounterComponent>();
    e2->addComponent<CounterComponent>();
    
    world.update(0.016f);
    
    TEST_ASSERT(CounterComponent::updateCount == 2, "Both component updates called");
    
    return true;
}

bool test_query_with_inactive_entities() {
    using namespace doengine;
    
    World world;
    
    Entity* e1 = world.createEntity();
    e1->addComponent<TestComponent>();
    
    Entity* e2 = world.createEntity();
    e2->addComponent<TestComponent>();
    e2->destroy();
    
    auto results = world.getEntitiesWith<TestComponent>();
    TEST_ASSERT(results.size() == 2, "Query includes inactive entities");
    
    world.refresh();
    results = world.getEntitiesWith<TestComponent>();
    TEST_ASSERT(results.size() == 1, "Query excludes inactive entities after refresh");
    
    return true;
}

// ============================================================================
// Test Runner
// ============================================================================

typedef bool (*TestFunc)();

struct TestCase {
    const char* name;
    TestFunc func;
};

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  DOEngine Entity Component System - Unit Tests         ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    
    TestCase tests[] = {
        { "Entity Creation", test_entity_creation },
        { "Component Addition", test_component_addition },
        { "Component Retrieval", test_component_retrieval },
        { "Component Missing Exception", test_component_missing_exception },
        { "Try Get Component", test_try_get_component },
        { "Multiple Components", test_multiple_components },
        { "Component Removal", test_component_removal },
        { "Entity Destruction", test_entity_destruction },
        { "System Registration", test_system_registration },
        { "System Update", test_system_update },
        { "Entity Query", test_entity_query },
        { "Built-in Components", test_built_in_components },
        { "Movement System", test_movement_system },
        { "Physics System", test_physics_system },
        { "Animation System", test_animation_system },
        { "Collider Intersection", test_collider_intersection },
        { "Tag Component", test_tag_component },
        { "Component Initialization", test_component_initialization },
        { "World Shutdown", test_world_shutdown },
        { "Component Update", test_component_update },
        { "Query with Inactive Entities", test_query_with_inactive_entities },
    };
    
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    int failed = 0;
    
    for (int i = 0; i < numTests; ++i) {
        std::cout << "\n[" << (i + 1) << "/" << numTests << "] " << tests[i].name << ":\n";
        
        try {
            if (tests[i].func()) {
                passed++;
                std::cout << "  ✓ PASSED\n";
            } else {
                failed++;
                std::cout << "  ❌ FAILED\n";
            }
        } catch (const std::exception& e) {
            failed++;
            std::cout << "  ❌ EXCEPTION: " << e.what() << "\n";
        } catch (...) {
            failed++;
            std::cout << "  ❌ UNKNOWN EXCEPTION\n";
        }
    }
    
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Test Results                                          ║\n";
    std::cout << "├────────────────────────────────────────────────────────┤\n";
    std::cout << "║  Total:  " << numTests << " tests\n";
    std::cout << "║  Passed: " << passed << " ✓\n";
    std::cout << "║  Failed: " << failed << " ❌\n";
    
    if (failed == 0) {
        std::cout << "║                                                        ║\n";
        std::cout << "║  🎉 ALL TESTS PASSED! 🎉                              ║\n";
    }
    
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    
    return failed == 0 ? 0 : 1;
}
