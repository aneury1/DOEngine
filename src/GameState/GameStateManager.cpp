#include "GameStateManager.h"
// #include "TTFText.h"
namespace doengine
{
void GameStateManager::AddState(int state_id, GameState* object)
{
    if (object)
    {
        states[state_id] = object;
    }
}
void GameStateManager::RemoveState(int state_id)
{
    if (states[state_id])
    {
        states[state_id]->OnExit();
        states.erase(state_id);
    }
}
void GameStateManager::SetState(int state_id)
{
    if (states[state_id])
    {
        if (states[current_state])
            states[current_state]->OnExit();
        current_state = state_id;
        states[current_state]->OnEnter();
    }
}
#include "Logger.h"
void GameStateManager::Update(float elapsed)
{

    if (states[current_state])
        states[current_state]->Update(elapsed);
}
void GameStateManager::Render()
{
    if (states[current_state])
        states[current_state]->Render();
}
} // namespace doengine