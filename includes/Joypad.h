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

#include "Color.h"
#include <cstddef>
#include <string>
#include <vector>

namespace doengine
{
namespace devices
{

enum class PowerLevel : char
{
    Unknown = -1,
    Empty,
    Low,
    Medium,
    Full,
    Wired,
    Max
};

class Joypad
{
  public:
    virtual int getId() const = 0;
    virtual void getName(std::string&) = 0;
    virtual PowerLevel getPowerLevel() const = 0;
    virtual std::size_t getNumberOfButtons() const = 0;
    virtual std::size_t getNumberOfAxes() const = 0;
    virtual int getPlayerIndex() const = 0;

    virtual bool hasLED() const = 0;
    virtual bool hasRumble() const = 0;
    virtual void getJoypadButtonsPressed(std::vector<bool>&) = 0;
    virtual short getAxisValue(int axis) const = 0;

    virtual void startRumble(unsigned short left, unsigned short right,
                             unsigned int duration_ms) = 0;
    virtual void setLEDColor(const Color&) = 0;
    virtual void setPlayerIndex(int index) = 0;
};

} // namespace devices
} // namespace doengine