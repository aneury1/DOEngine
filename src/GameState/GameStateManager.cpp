/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */


#include "GameStateManager.h"
#include "Event.h"
// #include "TTFText.h"
#include "Logger.h"
namespace doengine
{
void GameStateManager::AddState(int state_id, std::shared_ptr<GameState> object)
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

void GameStateManager::clearAllState()
{
    if(states.size()<=0){
        LogOuput(logger_type::Information, "No States to Del");
        return ;
    }
    for(auto it : states){
        if(it.second)
            it.second->OnExit();
    }
}

} // namespace doengine