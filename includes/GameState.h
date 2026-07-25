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
    std::shared_ptr<Renderer> renderer;
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