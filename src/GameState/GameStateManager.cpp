#include "GameStateManager.h"
// #include "TTFText.h"

void GameStateManager::AddState(int state_id, GameState* object)
{
    if (object)
    {
        states[state_id] = object;
    }
}
void GameStateManager::RemoveState(int state_id)
{
    /// todo
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
