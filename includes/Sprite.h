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

#include "Geometric.h"
#include "Texture.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace doengine
{

enum class ClipType
{
    Contiguous,
    Free
};

enum class Direction
{
    None,
    Horizontal,
    Vertical,
    Diagonal
};

class Sprite
{
  public:
    Sprite(Texture* texture, const std::vector<Rect>& frames,
           const Point& offset = Point(0, 0),
           const ClipType = ClipType::Contiguous, const size_t spriteCount = 1,
           const Direction direction = Direction::None);

    Sprite(int textureId, const std::vector<Rect>& frames,
           const Point& offset = Point(0, 0),
           const ClipType = ClipType::Contiguous, const size_t spriteCount = 1,
           const Direction direction = Direction::None);

    ~Sprite();

    void Draw(const Rect& dstRect);
    void Update(const float deltaTime);
    void setClipType(const ClipType type);
    void setSpriteCount(const size_t);
    void setDirection(const Direction);
    void setDuration(const float duration);
    void setFrameId(const size_t frameId);

    ClipType getClipType() const;
    Texture* getTexture() const;
    size_t getSpriteCount() const;
    size_t getFrameId() const;
    Direction getDirection() const;

  protected:
    const std::vector<Rect> frames;
    Texture* texture;
    Point offset;
    float duration;
    float startTime;
    ClipType clipType;
    size_t animId;
    size_t spriteCount;
    Direction direction;
};
} // namespace doengine
