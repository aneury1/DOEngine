#include "GameState.h"
#include "Application.h"
#include "Renderer.h"
namespace doengine
{
GameState::GameState()
{
    renderer = Application::getApplication()->getRender();
}
GameState::~GameState()
{
}

std::optional<GameObject*> GameState::queryGameObject(long long id)
{
    for (auto obj : this->registered_game_object)
    {
        if (obj->getId() == id)
            return obj;
    }
    return std::nullopt;
}

void GameState::registerGameObject(GameObject* object)
{
    if (object && queryGameObject(object->getId()) == std::nullopt)
    {
        registered_game_object.emplace_back(object);
    }
}

void GameState::unregisterGameObject(long long id)
{
    registered_game_object.erase(
        std::remove_if(registered_game_object.begin(),
                       registered_game_object.end(),
                       [id](auto x) { return x->getId() == id; }),
        registered_game_object.end());
}

} // namespace doengine