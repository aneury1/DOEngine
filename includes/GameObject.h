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
#include "Application.h"
#include "Geometric.h"
#include "Renderer.h"

#include <string>
#include <variant>
namespace doengine
{

class Renderer;

enum class ObjecType
{
    Player = 0,
    Level,
    Tile,
    AnimateTile,
    Npc,
    Ui,
    DebugObject,
    UknownObject,
    LastDefaultUnused
};

[[maybe_unused]] static unsigned long long id_pool = 0;
class GameObject
{
  private:
    long long id;

  protected:
    bool debuging_enable;

    Rect position;
    std::shared_ptr<doengine::Renderer> renderer;

    bool renderable;
    bool solid;
    int layer;

    std::string sprite_id;
    std::string texture_id;

  public:
    GameObject();
    virtual ~GameObject();
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    std::shared_ptr<doengine::Renderer> getRenderer();
    Rect getPosition();

    inline int getId()
    {
        return id;
    }
};

} // namespace doengine