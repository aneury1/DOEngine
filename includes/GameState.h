#pragma once
#include <variant>
#include <string>
#include <optional>
#include "Application.h"
#include "Renderer.h"
#include "GameObject.h"
namespace doengine
{

class GameObject;
typedef std::variant<int, std::string, GameObject *> ArgValue;

class GameState
{
  protected:
    std::vector<GameObject*> registered_game_object;
    Renderer *renderer;
  public:
    GameState();
    virtual ~GameState();
    std::optional<GameObject*> queryGameObject(long long id);
    void registerGameObject(GameObject *object);
    void unregisterGameObject(long long id);
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update(float elapsed) = 0;
    virtual void Render() = 0;
};

} // namespace doengine