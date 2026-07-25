# DOEngine Code Review Document

## Executive Summary

DOEngine is an ambitious 2D game engine project with a clear learning-oriented goal and a reasonable foundation built on SDL and OpenGL-related abstractions. The project shows energy and experimentation, but the current codebase would benefit from a hard cleanup pass before it can be considered stable, maintainable, or production-friendly.

The largest issues are not cosmetic. They are structural:

- core state is not always initialized safely,
- several components rely on raw pointers and implicit ownership,
- the engine contains unfinished or dead branches,
- error handling is inconsistent, and
- the API surface is larger than the implementation quality justifies.

If the project is meant to grow, the most valuable move would be to reduce complexity, make ownership explicit, enforce safer defaults, and remove unfinished paths that currently create confusion rather than value.

---

## What the project does well

### 1. Clear educational direction
The repository has a strong learning purpose. The README explains that the engine is being built to understand game development principles rather than to compete with established engines. That is a healthy foundation.

### 2. A reasonable module layout
The project is organized around major engine concerns such as application lifecycle, game objects, events, audio, textures, timers, and windowing. This kind of separation is a good start.

### 3. CMake-based build structure
The presence of a CMake build system is positive. It gives the project a modern build path and makes cross-platform integration more plausible.

### 4. Samples exist
The sample directory provides practical examples and helps potential contributors understand the intended usage model.

---

## Main flaws and risks

### 1. Uninitialized state in core objects
A serious flaw exists in the application layer. In [includes/Application.h](includes/Application.h), fields such as `run`, `dirty`, and `window_rect` are declared but not initialized in the constructor. In [src/Application/Application.cpp](src/Application/Application.cpp), the constructor never sets these values explicitly.

This creates a real risk of undefined behavior because:

- `IsRunning()` may return garbage instead of a meaningful boolean,
- window dimensions may be invalid until explicitly set,
- the engine may behave inconsistently on startup.

This should be treated as a high-priority fix.

### 2. Null-pointer assumptions throughout the engine
Several methods in [src/Application/Application.cpp](src/Application/Application.cpp) assume that internal subsystems are valid without verifying them carefully. For example:

- `getRender()` directly dereferences the window manager,
- `getDisplayMode()` assumes the window manager exists,
- `Render()` calls `updateScreen()` without guarding against a null window manager,
- `Quit()` assumes texture and state managers are valid.

This style is dangerous because a partially initialized engine can crash at runtime rather than failing gracefully.

### 3. Raw pointers and manual ownership
The event system in [src/Event/Event.cpp](src/Event/Event.cpp) uses raw pointers for event listeners and manually deletes joystick wrappers. That is fragile for several reasons:

- ownership is unclear,
- listeners may outlive the objects that created them,
- deletion can cause use-after-free bugs if the event list is not cleaned correctly,
- the code becomes harder to maintain as the project grows.

The project would be much safer with `std::unique_ptr`, `std::shared_ptr`, or clear ownership boundaries.

### 4. Incomplete or misleading abstraction layers
The window manager abstraction in [src/Application/WindowManager.cpp](src/Application/WindowManager.cpp) uses a hardcoded `opengl_support = false` branch and returns a SDL-only implementation. That means the OpenGL path is effectively a placeholder and may confuse contributors.

This is a classic example of an abstraction that looks complete but is only partially implemented. In practice it becomes maintenance debt.

### 5. Event system is too complex for the current maturity level
The event system supports many event types, but the implementation is broad and somewhat brittle. The code mixes input events, joystick events, keyboard events, and state management in one layer. This makes it harder to understand and more likely to fail under edge cases.

A smaller, cleaner event model would likely deliver better reliability than a large, feature-rich but loosely managed event stack.

### 6. Inconsistent error handling
The code uses logging but not consistently. Some functions log errors, while others silently proceed. This leads to the following problems:

- failures are not always visible,
- callers do not know if an operation actually succeeded,
- recovery paths are weak,
- debugging becomes harder.

The engine should adopt a consistent pattern such as:

- return a status code,
- throw a domain-specific exception where appropriate,
- log clearly at the point of failure,
- fail fast for unrecoverable initialization problems.

### 7. The API is not yet disciplined
Some names and types reveal inconsistencies. For example, in [includes/GameObject.h](includes/GameObject.h), the enum member `UknownObject` is misspelled, and the `id` field uses `long long` while `getId()` returns `int`. That may not be catastrophic, but it is a sign that the API has not yet been tightened.

Small inconsistencies like this often become larger problems later because they indicate a lack of consistency in design.

---

## Possible exceptions and failure modes

The following issues are likely to appear as the engine grows:

### 1. Startup crashes due to uninitialized fields
If the application is created and used before the window size or state is properly established, the engine may crash or behave unpredictably.

### 2. Null dereferences during shutdown or late initialization
If the state manager, renderer, or window manager is not fully ready, calls during `Quit()` or `Render()` may fail.

### 3. Memory bugs from manual pointer management
The event system can become a source of crashes if listeners are removed while callbacks are still running or if some objects are destroyed out of order.

### 4. Asset-path problems
The README already notes that assets may be missing. This is an issue for samples and demos, but it also suggests that the engine currently lacks a robust asset loading strategy and path resolution policy.

### 5. Incomplete SDL initialization handling
If SDL fails to initialize or some subsystem is unavailable, the engine should fail clearly. Right now that responsibility is too implicit.

### 6. State machine misuse
The state manager appears to manage transitions in a simple way, but there is no visible protection against invalid state IDs, duplicate IDs, or state transitions from invalid contexts.

---

## How to get the best result from this project

### 1. Fix the core first
Start with correctness and safety. The first priorities should be:

- initialize all fields in constructors,
- avoid raw pointer ownership where possible,
- add null checks around critical subsystems,
- make startup and shutdown deterministic.

### 2. Reduce the number of unfinished abstractions
Do not keep placeholder abstractions around just because they exist. If the OpenGL path is not ready, either remove it or isolate it behind clear compile-time or runtime flags.

### 3. Adopt modern C++ patterns
The project would benefit from:

- `std::unique_ptr` for exclusive ownership,
- `std::shared_ptr` only where shared ownership is truly needed,
- `std::optional` for optional values,
- `std::variant` or enums for clearly defined states,
- RAII-based resource management.

### 4. Establish a clear error strategy
Choose one style and use it everywhere:

- either return bool/status codes,
- or throw exceptions for unrecoverable conditions,
- or use a custom engine error type.

A mixed strategy will continue to create confusion.

### 5. Add tests as soon as possible
The engine should not rely only on samples. It should have small unit tests for:

- application startup and shutdown,
- state transitions,
- event listener registration/removal,
- texture and asset loading failures,
- window creation and resize logic.

### 6. Separate learning code from production-grade code
The project can preserve its educational spirit while becoming more maintainable. The best approach is to keep samples and experiments, but separate them from the core engine interfaces.

---

## What should be removed or simplified

### 1. Remove or isolate dead/unfinished paths
The OpenGL branch in [src/Application/WindowManager.cpp](src/Application/WindowManager.cpp) is a strong candidate for removal or isolation until it is properly implemented.

### 2. Remove confusing or obsolete code
The codebase should be reviewed for:

- unused globals,
- duplicate or near-duplicate APIs,
- commented-out includes and old experiment code,
- unfinished helper methods.

### 3. Simplify the event system
The current event model is broad but not yet robust. The project would likely benefit from a smaller, clearer input handling approach rather than keeping every possible event type in the same layer.

### 4. Reduce the amount of experimental scaffolding in the main branch
The Android-related files in the repository are useful only if the project is actively supporting Android. If this is not a current priority, they should be isolated or removed from the main maintenance path.

### 5. Remove API inconsistencies
Names like `UknownObject` and inconsistent return types should be corrected. These are low-cost fixes that improve clarity immediately.

---

## Recommended priority order

1. Fix initialization and null-safety issues.
2. Replace fragile ownership patterns with safer modern C++ constructs.
3. Clean up the event system.
4. Remove or isolate unfinished abstractions.
5. Add tests and documentation.
6. Reduce the scope of the API until it is stable and well-understood.

---

## Final verdict

The project is promising and has a good educational foundation, but it needs a discipline pass before it becomes a reliable engine. The biggest opportunities are not in adding more features; they are in making the existing core simpler, safer, and more explicit.

If the goal is to turn this into a maintainable engine, the best path forward is:

- improve correctness first,
- reduce complexity second,
- remove unfinished ideas third,
- document the architecture fourth.

With that approach, DOEngine could evolve from a creative experiment into a much stronger foundation for future work.

---

## Pointer and ownership guidance

The codebase would benefit from a more deliberate ownership strategy. The current use of raw pointers and implicit lifetime assumptions should be replaced with clearer modern C++ patterns.

### Use shared_ptr when:
- an object must be shared across multiple systems,
- several components need to observe the same instance,
- ownership is truly collective rather than exclusive.

Where it fits in this project:
- the application layer in [includes/Application.h](includes/Application.h) and [src/Application/Application.cpp](src/Application/Application.cpp) is a strong candidate for `std::shared_ptr` because the application owns core services such as the window manager, renderer, state manager, and FPS manager and those services are referenced from multiple places,
- game states in [includes/GameStateManager.h](includes/GameStateManager.h) and the state lifecycle in [src/Application/Application.cpp](src/Application/Application.cpp) should be represented with shared ownership if multiple systems need to access the current active state,
- the event system in [src/Event/Event.cpp](src/Event/Event.cpp) would benefit from shared ownership for listeners when several parts of the engine need to observe the same event source without taking full ownership.

Good practice:
- prefer `std::shared_ptr` only when shared lifetime is required,
- avoid using it by default just because it is convenient,
- keep the ownership model obvious in the API.

### Use unique_ptr when:
- one owner should exclusively manage the object,
- the object should be destroyed automatically when the owner goes away,
- the object is created dynamically and should not be shared.

Where it fits in this project:
- internal engine components owned by a higher-level manager should use `std::unique_ptr`, especially in the state and windowing layers where one manager should be the sole owner,
- temporary objects created during scene construction or resource loading should use `std::unique_ptr`,
- joystick or input wrapper objects created in [src/Event/Event.cpp](src/Event/Event.cpp) should ideally be owned by a single manager rather than being manually allocated and deleted.

Good practice:
- prefer `std::unique_ptr` for the majority of heap-owned objects,
- use `std::make_unique` instead of manual `new`.

### Use optional when:
- a value may or may not exist,
- a function may return no result without using null,
- a field represents a state that is intentionally absent.

Where it fits in this project:
- window configuration values such as display mode or fullscreen state in [src/Application/Application.cpp](src/Application/Application.cpp) can be represented as `std::optional` instead of relying on implicit defaults,
- optional renderer or texture handles in the rendering pipeline should use `std::optional` when a resource is not guaranteed to be available,
- optional state-related values in the game object and state manager layers can make missing data explicit rather than using null-like placeholders.

Good practice:
- use `std::optional<T>` instead of `nullptr` when the absence is a valid business state,
- avoid overusing optional for values that are always required.

### What to do next
- replace raw pointers in event listeners and manager relationships with `std::shared_ptr` or `std::unique_ptr` depending on the ownership model,
- replace nullable object state with `std::optional` where appropriate,
- avoid mixing ownership styles in the same subsystem,
- keep ownership comments and type names explicit so the lifetime rules are clear to future contributors.

A simple rule of thumb for this project is:
- use `std::unique_ptr` for exclusive ownership,
- use `std::shared_ptr` for shared ownership,
- use `std::optional` for optional values,
- and avoid raw pointers unless you are interacting with legacy C APIs.
